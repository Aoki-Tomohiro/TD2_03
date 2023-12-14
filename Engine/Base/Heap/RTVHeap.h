#pragma once
#include "DescriptorHeap.h"

class RTVHeap : public DescriptorHeap {
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="numDescriptors"></param>
	void Create(UINT numDescriptors);

	/// <summary>
	/// RTVの作成
	/// </summary>
	/// <param name="resource"></param>
	uint32_t CreateRenderTargetView(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, DXGI_FORMAT format);

private:

};

