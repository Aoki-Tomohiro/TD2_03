#pragma once
#include "DescriptorHeap.h"

class DSVHeap : public DescriptorHeap {
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="numDescriptors"></param>
	void Create(UINT numDescriptors);

	/// <summary>
	/// DSVの作成
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="format"></param>
	/// <returns></returns>
	uint32_t CreateDepthStencilView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format);

private:

};

