#include "UploadBuffer.h"

void UploadBuffer::Create(size_t sizeInBytes) {
	//リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;//UploadHeapを使う

	//リソースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = sizeInBytes;
	//バッファの場合はこれらは1にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	//バッファの場合はこれにする決まり
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//作成
	GpuResource::Create(&heapProperties, &resourceDesc, nullptr, D3D12_RESOURCE_STATE_GENERIC_READ);
}

void* UploadBuffer::Map() {
	//マップ
	resource_->Map(0, nullptr, &mappedData_);
	return mappedData_;
}

void UploadBuffer::Unmap() {
	//アンマップ
	resource_->Unmap(0, nullptr);
	mappedData_ = nullptr;
}