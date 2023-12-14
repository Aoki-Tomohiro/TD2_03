#pragma once
#include "DescriptorHeap.h"

class SRVHeap : public DescriptorHeap {
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="numDescriptors"></param>
	void Create(UINT numDescriptors);

	/// <summary>
	/// SRVの作成
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="format"></param>
	/// <returns></returns>
	uint32_t CreateShaderResourceView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format);

	/// <summary>
	/// SRVの作成
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="format"></param>
	/// <param name="mipLevels"></param>
	/// <returns></returns>
	uint32_t CreateShaderResourceView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format, UINT mipLevels);

	/// <summary>
	/// SRVの作成
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="kNumInstance"></param>
	/// <param name="size"></param>
	/// <returns></returns>
	uint32_t CreateShaderResourceView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, uint32_t kNumInstance, size_t size);

private:

};

