#include "SRVHeap.h"
#include <cassert>

void SRVHeap::Create(UINT numDescriptors) {
	//作成
	DescriptorHeap::Create(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, numDescriptors, true);
}

uint32_t SRVHeap::CreateShaderResourceView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format) {
	//ディスクリプタの最大数を超えていたら止める
	if (useCount_ > numDescriptors_) {
		assert(false);
	}

	//SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Format = format;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	//SRVの作成
	D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle = GetCPUDescriptorHandle(useCount_);
	device_->CreateShaderResourceView(resource.Get(), &srvDesc, srvCpuHandle);

	return useCount_++;
}

uint32_t SRVHeap::CreateShaderResourceView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format, UINT mipLevels) {
	//ディスクリプタの最大数を超えていたら止める
	if (useCount_ > numDescriptors_) {
		assert(false);
	}

	//SRVの設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Format = format;
	srvDesc.Texture2D.MipLevels = mipLevels;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	//SRVの作成
	D3D12_CPU_DESCRIPTOR_HANDLE srvCpuHandle = GetCPUDescriptorHandle(useCount_);
	device_->CreateShaderResourceView(resource.Get(), &srvDesc, srvCpuHandle);

	return useCount_++;
}

uint32_t SRVHeap::CreateShaderResourceView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, uint32_t kNumInstance, size_t size) {
	//ディスクリプタの最大数を超えていたら止める
	if (useCount_ > numDescriptors_) {
		assert(false);
	}

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = DXGI_FORMAT_UNKNOWN;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	srvDesc.Buffer.FirstElement = 0;
	srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	srvDesc.Buffer.NumElements = kNumInstance;
	srvDesc.Buffer.StructureByteStride = UINT(size);

	D3D12_CPU_DESCRIPTOR_HANDLE srvHandleCpu = GetCPUDescriptorHandle(useCount_);
	device_->CreateShaderResourceView(resource.Get(), &srvDesc, srvHandleCpu);

	return useCount_++;
}
