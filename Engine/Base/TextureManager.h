#pragma once
#include "Engine/Base/Heap/SRVHeap.h"
#include "Engine/Base/Buffer/TextureResource.h"
#include "Engine/Base/Buffer/UploadBuffer.h"
#include <array>
#include <memory>

class TextureManager {
public:
	//ディスクリプタの最大数
	static const size_t kNumDescriptors = 256;

	//テクスチャ
	struct Texture {
		//テクスチャリソース
		std::unique_ptr<TextureResource> resource = nullptr;
		//中間リソース
		std::unique_ptr<UploadBuffer> intermediateResource = nullptr;
		//テクスチャの名前
		std::string name{};
		//テクスチャハンドル
		uint32_t textureHandle = 0;
	};

	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns></returns>
	static TextureManager* GetInstance();

	/// <summary>
	/// シングルトンインスタンスの削除
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	static uint32_t Load(const std::string& filePath);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// SRVの作成
	/// </summary>
	/// <param name="name"></param>
	/// <param name="colorBuffer"></param>
	/// <param name="format"></param>
	/// <returns></returns>
	uint32_t CreateShaderResourceView(const std::string& name, const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format);

	/// <summary>
	/// SRVの作成
	/// </summary>
	/// <param name=""></param>
	/// <param resource=""></param>
	/// <param kNumInstance=""></param>
	/// <param size=""></param>
	uint32_t CreateShaderResourceView(const std::string& name, const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, uint32_t kNumInstance, size_t size);

	/// <summary>
	/// ディスクリプタヒープを設定
	/// </summary>
	void SetGraphicsDescriptorHeap();

	///// <summary>
	///// ディスクリプタテーブルを設定
	///// </summary>
	///// <param name="rootParameterIndex"></param>
	///// <param name="textureHandle"></param>
	//void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t textureHandle);

	/// <summary>
	/// Gpuハンドルを取得
	/// </summary>
	/// <param name="textureHandle"></param>
	D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle(uint32_t textureHandle);

	/// <summary>
	/// テクスチャの情報を取得
	/// </summary>
	/// <param name="textureHandle"></param>
	/// <returns></returns>
	const D3D12_RESOURCE_DESC GetResourceDesc(uint32_t textureHandle);

private:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	/// <summary>
	/// テクスチャを読み込む
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	uint32_t LoadInternal(const std::string& filePath);

	/// <summary>
	/// テクスチャデータの読み込み
	/// </summary>
	/// <param name="filePath">名</param>
	/// <returns></returns>
	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	/// <summary>
	/// リソースにテクスチャのデータを転送
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="mipImages"></param>
	/// <returns></returns>
	std::unique_ptr<UploadBuffer> UploadTextureData(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, const DirectX::ScratchImage& mipImages);

private:
	//インスタンス
	static TextureManager* instance;

	//デバイス
	ID3D12Device* device_ = nullptr;

	//コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	//ディスクリプタヒープ
	std::unique_ptr<DescriptorHeap> srvDescriptorHeap_ = nullptr;

	//テクスチャの配列
	std::array<Texture, kNumDescriptors> textures_{};

	//使用数
	uint32_t useCount_ = 0;
};

