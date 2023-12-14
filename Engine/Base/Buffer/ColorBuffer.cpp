#include "ColorBuffer.h"
#include <cassert>

void ColorBuffer::Create(int32_t width, int32_t height, DXGI_FORMAT format, float* clearColor) {
	//ヒープの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	//リソースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Width = width;
	resourceDesc.Height = height;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.Format = format;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;

	//ClearValue
	D3D12_CLEAR_VALUE clearValue{};
	clearValue.Format = format;
	clearValue.Color[0] = clearColor[0];
	clearValue.Color[1] = clearColor[1];
	clearValue.Color[2] = clearColor[2];
	clearValue.Color[3] = clearColor[3];

	//作成
	GpuResource::Create(&heapProperties, &resourceDesc, &clearValue, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
}

void ColorBuffer::CreateFromSwapChain(IDXGISwapChain* swapChain, UINT buffer, float* clearColor) {
	//SwapChainからResourceを引っ張ってくる
	HRESULT hr = swapChain->GetBuffer(buffer, IID_PPV_ARGS(&resource_));
	//うまく取得できなければ起動できない
	assert(SUCCEEDED(hr));
}