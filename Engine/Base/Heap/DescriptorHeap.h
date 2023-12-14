#pragma once
#include <cstdint>
#include <d3d12.h>
#include <wrl.h>

class DescriptorHeap {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~DescriptorHeap() = default;

	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="numDescriptors"></param>
	void Create(D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible);

	/// <summary>
	/// CPUディスクリプタハンドルを取得
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);

	/// <summary>
	/// GPUディスクリプタハンドルを取得
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);

	/// <summary>
	/// ディスクリプタヒープを取得
	/// </summary>
	/// <returns></returns>
	ID3D12DescriptorHeap* GetDescriptorHeap() const { return descriptorHeap_.Get(); };

protected:
	//デバイス
	ID3D12Device* device_ = nullptr;

	//ディスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_ = nullptr;
	
	//ディスクリプタサイズ
	UINT descriptorSize_ = 0;

	//ディスクリプタの最大数
	uint32_t numDescriptors_ = 0;

	//使用数
	uint32_t useCount_ = 0;
};

