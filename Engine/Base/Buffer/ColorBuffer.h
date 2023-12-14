#pragma once
#include "GpuResource.h"
#include <dxgi1_6.h>
#include <cstdint>

class ColorBuffer : public GpuResource {
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="format"></param>
	/// <param name="clearColor"></param>
	void Create(int32_t width, int32_t height, DXGI_FORMAT format, float* clearColor);

	/// <summary>
	/// スワップチェーンから作成
	/// </summary>
	/// <param name="swapChain"></param>
	/// <param name="buffer"></param>
	/// <param name="clearColor"></param>
	void CreateFromSwapChain(IDXGISwapChain* swapChain, UINT buffer, float* clearColor);

private:

};

