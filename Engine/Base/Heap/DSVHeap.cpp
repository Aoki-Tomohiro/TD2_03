#include "DSVHeap.h"
#include <cassert>

void DSVHeap::Create(UINT numDescriptors) {
	//作成
	DescriptorHeap::Create(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, numDescriptors, false);
}

uint32_t DSVHeap::CreateDepthStencilView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format) {
	//ディスクリプタの最大数を超えていたら止める
	if (useCount_ > numDescriptors_) {
		assert(false);
	}

	//DSVの設定
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = format;//Format。基本的にはResourceに合わせる
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;//2DTexture

	//DSVHeapの先頭にDSVを作る
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = GetCPUDescriptorHandle(useCount_);
	device_->CreateDepthStencilView(resource.Get(), &dsvDesc, dsvHandle);

	return useCount_++;
}