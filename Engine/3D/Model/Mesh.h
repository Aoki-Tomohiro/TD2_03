#pragma once
#include "Engine/Base/Buffer/UploadBuffer.h"
#include "Engine/Math/Vector2.h"
#include "Engine/Math/Vector3.h"
#include "Engine/Math/Vector4.h"
#include <vector>
#include <memory>

class Mesh {
public:
	/// <summary>
	/// 頂点データ
	/// </summary>
	struct VertexData {
		Vector4 position;
		Vector2 texcoord;
		Vector3 normal;
	};

	/// <summary>
	/// メッシュの初期化
	/// </summary>
	/// <param name="vertices"></param>
	void Initialize(const std::vector<VertexData>& vertices);

	/// <summary>
	/// VertexBufferViewを取得
	/// </summary>
	/// <returns></returns>
	const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView() { return vertexBufferView_; };

	/// <summary>
	/// 頂点数を取得
	/// </summary>
	/// <returns></returns>
	size_t GetVertexCount() { return vertices_.size(); };

private:
	//VertexBuffer
	std::unique_ptr<UploadBuffer> vertexBuffer_ = nullptr;

	//書き込み用
	VertexData* vertexData_ = nullptr;

	//VertexBufferView
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};

	//頂点データ
	std::vector<VertexData> vertices_{};
};

