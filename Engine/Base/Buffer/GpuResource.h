#pragma once
#include <d3d12.h>
#include <wrl.h>

class GpuResource {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GpuResource() = default;

	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="heapProperties"></param>
	/// <param name="resourceDesc"></param>
	/// <param name="clearValue"></param>
	/// <param name="state"></param>
	void Create(const D3D12_HEAP_PROPERTIES* heapProperties, const D3D12_RESOURCE_DESC* resourceDesc, const D3D12_CLEAR_VALUE* clearValue, D3D12_RESOURCE_STATES state);

	/// <summary>
	/// リソースを取得
	/// </summary>
	/// <returns></returns>
	ID3D12Resource* GetResource() const { return resource_.Get(); };

protected:
	//リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> resource_ = nullptr;
};

