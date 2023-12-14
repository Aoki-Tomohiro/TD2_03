#include "TextureResource.h"

void TextureResource::Create(const DirectX::TexMetadata& metadata) {
	//利用するHeapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	//metadataを基にResourceの設定
	resourceDesc_.Width = UINT(metadata.width);//Textureの幅
	resourceDesc_.Height = UINT(metadata.height);//Textureの高さ
	resourceDesc_.MipLevels = UINT16(metadata.mipLevels);//mipmapの数
	resourceDesc_.DepthOrArraySize = UINT16(metadata.arraySize);//奥行or配列Textureの配列数
	resourceDesc_.Format = metadata.format;//TextureのFormat
	resourceDesc_.SampleDesc.Count = 1;//サンプルカウント。1固定
	resourceDesc_.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);//Textureの次元数。普段使っているのは2次元

	//作成
	GpuResource::Create(&heapProperties, &resourceDesc_, nullptr, D3D12_RESOURCE_STATE_COPY_DEST);
}