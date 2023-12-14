#pragma once
#include "GpuResource.h"

class UploadBuffer : public GpuResource {
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="sizeInBytes"></param>
	void Create(size_t sizeInBytes);

	/// <summary>
	/// マップ
	/// </summary>
	/// <returns></returns>
	void* Map();

	/// <summary>
	/// アンマップ
	/// </summary>
	void Unmap();

	/// <summary>
	/// GPUアドレスを取得
	/// </summary>
	/// <returns></returns>
	const D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const { return resource_->GetGPUVirtualAddress(); };

private:
	//マップされたデータ
	void* mappedData_ = nullptr;
};

