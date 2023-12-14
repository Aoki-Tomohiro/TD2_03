#include "GpuResource.h"
#include "Engine/Base/GraphicsCore.h"

void GpuResource::Create(const D3D12_HEAP_PROPERTIES* heapProperties, const D3D12_RESOURCE_DESC* resourceDesc, const D3D12_CLEAR_VALUE* clearValue, D3D12_RESOURCE_STATES state) {
	//デバイスの取得
	ID3D12Device* device = GraphicsCore::GetInstance()->GetDevice();

	//作成
	HRESULT hr = device->CreateCommittedResource(heapProperties, D3D12_HEAP_FLAG_NONE,
		resourceDesc, state, clearValue,
		IID_PPV_ARGS(&resource_));
	assert(SUCCEEDED(hr));
}