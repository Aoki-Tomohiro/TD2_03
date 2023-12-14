#pragma once
#include "GpuResource.h"
#include "Engine/Externals/DirectXTex/DirectXTex.h"
#include "Engine/Externals/DirectXTex/d3dx12.h"

class TextureResource : public GpuResource {
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="metadata"></param>
	void Create(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// リソースの設定を取得
	/// </summary>
	/// <returns></returns>
	const D3D12_RESOURCE_DESC& GetResourceDesc() const { return resourceDesc_; };

private:
	//リソースの設定
	D3D12_RESOURCE_DESC resourceDesc_{};
};

