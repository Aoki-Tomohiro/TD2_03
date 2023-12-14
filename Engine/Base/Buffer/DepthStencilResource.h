#pragma once
#include "GpuResource.h"
#include <cstdint>

class DepthStencilResource : public GpuResource {
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="format"></param>
	void Create(int32_t width, int32_t height, DXGI_FORMAT format);

private:

};

