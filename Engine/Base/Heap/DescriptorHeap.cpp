#include "DescriptorHeap.h"
#include "Engine/Base/GraphicsCore.h"

void DescriptorHeap::Create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible) {
    //デバイスの取得
    device_ = GraphicsCore::GetInstance()->GetDevice();

    //ディスクリプタサイズの取得
    descriptorSize_ = device_->GetDescriptorHandleIncrementSize(type);

    //ディスクリプタヒープの最大数の初期化
    numDescriptors_ = numDescriptors;

    //ディスクリプタヒープの作成
    D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
    descriptorHeapDesc.Type = type;
    descriptorHeapDesc.NumDescriptors = numDescriptors;
    descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    HRESULT hr = device_->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap_));
    assert(SUCCEEDED(hr));
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCPUDescriptorHandle(uint32_t index) {
    D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
    handleCPU.ptr += static_cast<D3D12_CPU_DESCRIPTOR_HANDLE>((descriptorSize_ * index)).ptr;
    return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetGPUDescriptorHandle(uint32_t index) {
    D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();
    handleGPU.ptr += static_cast<D3D12_GPU_DESCRIPTOR_HANDLE>((descriptorSize_ * index)).ptr;
    return handleGPU;
}