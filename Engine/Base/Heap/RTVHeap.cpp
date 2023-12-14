#include "RTVHeap.h"
#include <cassert>

void RTVHeap::Create(UINT numDescriptors) {
	//作成
	DescriptorHeap::Create(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, numDescriptors, false);
}

uint32_t RTVHeap::CreateRenderTargetView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format) {
	//ディスクリプタの最大数を超えていたら止める
	if (useCount_ > numDescriptors_) {
		assert(false);
	}

	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Format = format;

	//RTVの作成
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = GetCPUDescriptorHandle(useCount_);
	device_->CreateRenderTargetView(resource.Get(), &rtvDesc, rtvHandle);

	return useCount_++;
}