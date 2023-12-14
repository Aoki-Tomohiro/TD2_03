#include "TextureManager.h"
#include "GraphicsCore.h"
#include "Engine/Utilities/Log.h"

//実体定義
TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::GetInstance() {
	if (instance == nullptr) {
		instance = new TextureManager();
	}
	return instance;
}

void TextureManager::DeleteInstance() {
	delete instance;
	instance = nullptr;
}

uint32_t TextureManager::Load(const std::string& filePath) {
	//テクスチャを読み込む
	uint32_t textureHandle = TextureManager::GetInstance()->LoadInternal(filePath);

	return textureHandle;
}

void TextureManager::Initialize() {
	//デバイスの取得
	device_ = GraphicsCore::GetInstance()->GetDevice();
	//コマンドリストの取得
	commandList_ = GraphicsCore::GetInstance()->GetCommandList();

	//ディスクリプタヒープの作成
	std::unique_ptr<SRVHeap> srvHeap = std::make_unique<SRVHeap>();
	srvHeap->Create(kNumDescriptors);
	srvDescriptorHeap_ = std::move(srvHeap);

	//デフォルト画像を読み込む
	LoadInternal("Project/Resources/Images/white.png");
}

uint32_t TextureManager::CreateShaderResourceView(const std::string& name, const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format) {
	//同じテクスチャがないか探す
	for (Texture& texture : textures_) {
		if (texture.name == name) {
			return texture.textureHandle;
		}
	}

	//SRVの作成
	SRVHeap* srvHeap = dynamic_cast<SRVHeap*>(srvDescriptorHeap_.get());
	textures_[useCount_].textureHandle = srvHeap->CreateShaderResourceView(resource, format);

	//名前を保存
	textures_[useCount_].name = name;

	return useCount_++;
}

uint32_t TextureManager::CreateShaderResourceView(const std::string& name, const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, uint32_t kNumInstance, size_t size) {
	//同じテクスチャがないか探す
	for (Texture& texture : textures_) {
		if (texture.name == name) {
			return texture.textureHandle;
		}
	}

	//SRVの作成
	SRVHeap* srvHeap = dynamic_cast<SRVHeap*>(srvDescriptorHeap_.get());
	textures_[useCount_].textureHandle = srvHeap->CreateShaderResourceView(resource, kNumInstance, size);

	//名前を保存
	textures_[useCount_].name = name;

	return useCount_++;
}

void TextureManager::SetGraphicsDescriptorHeap() {
	//DescriptorHeapを設定
	ID3D12DescriptorHeap* descriptorHeaps[] = { srvDescriptorHeap_->GetDescriptorHeap() };
	commandList_->SetDescriptorHeaps(1, descriptorHeaps);
}

//void TextureManager::SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t textureHandle) {
//	//GPUハンドルを取得
//	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = srvDescriptorHeap_->GetGPUDescriptorHandle(textureHandle);
//	//SRVのDescriptorTableの先頭を設定
//	commandList_->SetGraphicsRootDescriptorTable(rootParameterIndex, gpuHandle);
//}

D3D12_GPU_DESCRIPTOR_HANDLE TextureManager::GetGpuHandle(uint32_t textureHandle) {
	//GPUハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = srvDescriptorHeap_->GetGPUDescriptorHandle(textureHandle);
	return gpuHandle;
}

const D3D12_RESOURCE_DESC TextureManager::GetResourceDesc(uint32_t textureHandle) {
	//テクスチャの情報を取得
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc = textures_[textureHandle].resource->GetResourceDesc();

	return resourceDesc;
}

uint32_t TextureManager::LoadInternal(const std::string& filePath) {
	//同じテクスチャがないか探す
	for (Texture& texture : textures_) {
		if (texture.name == filePath) {
			return texture.textureHandle;
		}
	}

	//テクスチャを読み込む
	DirectX::ScratchImage mipImages = LoadTexture(filePath);

	//メタデータを取得
	const DirectX::TexMetadata& metadata = mipImages.GetMetadata();

	//テクスチャ情報を基にリソースを作成
	std::unique_ptr<TextureResource> textureResource = std::make_unique<TextureResource>();
	textureResource->Create(metadata);
	textures_[useCount_].resource = std::move(textureResource);

	//テクスチャのリソースにデーターを転送する
	std::unique_ptr<UploadBuffer> intermediateResource = UploadTextureData(textures_[useCount_].resource->GetResource(), mipImages);
	textures_[useCount_].intermediateResource = std::move(intermediateResource);

	//SRVの作成
	SRVHeap* srvHeap = dynamic_cast<SRVHeap*>(srvDescriptorHeap_.get());
	textures_[useCount_].textureHandle = srvHeap->CreateShaderResourceView(textures_[useCount_].resource->GetResource(), metadata.format, UINT(metadata.mipLevels));

	//テクスチャの名前を保存する
	textures_[useCount_].name = filePath;

	return useCount_++;
}

DirectX::ScratchImage TextureManager::LoadTexture(const std::string& filePath) {
	//テクスチャファイルを読んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	//ミップマップの作成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	//ミップマップ付きのデータを返す
	return mipImages;
}

[[nodiscard]]
std::unique_ptr<UploadBuffer> TextureManager::UploadTextureData(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, const DirectX::ScratchImage& mipImages) {
	//中間リソースを作成
	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
	DirectX::PrepareUpload(device_, mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresources);
	uint64_t intermediateSize = GetRequiredIntermediateSize(resource.Get(), 0, UINT(subresources.size()));
	std::unique_ptr<UploadBuffer> intermediateResource = std::make_unique<UploadBuffer>();
	intermediateResource->Create(intermediateSize);

	//データ転送をコマンドに積む
	UpdateSubresources(commandList_, resource.Get(), intermediateResource->GetResource(), 0, 0, UINT(subresources.size()), subresources.data());

	//Textureへの転送後は利用できるよう、D3D12_RESOURCE_STATE_COPY_DESTからD3D12_RESOURCE_STATE_GENERIC_READへResourceStateを変更する
	GraphicsCore::GetInstance()->TransitionResource(resource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);

	return intermediateResource;
}