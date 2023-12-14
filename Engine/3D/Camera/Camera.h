#pragma once
#include "Engine/Base/Buffer/UploadBuffer.h"
#include "Engine/Math/MathFunction.h"
#include <memory>

struct ConstBuffDataViewProjection {
	Matrix4x4 view;
	Matrix4x4 projection;
};

class Camera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// ビュー行列の更新
	/// </summary>
	void UpdateViewMatrix();

	/// <summary>
	/// プロジェクション行列の更新
	/// </summary>
	void UpdateProjectionMatrix();

	/// <summary>
	/// 行列の計算
	/// </summary>
	void UpdateMatrix();

	/// <summary>
	/// CBVを転送
	/// </summary>
	void TransferMatrix();

	/// <summary>
	/// CBVを取得
	/// </summary>
	/// <returns></returns>
	UploadBuffer* GetConstantBuffer() const { return constBuff_.get(); };

	/// <summary>
	/// コピー
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	Camera& operator=(const Camera& other);

private:
	//CBV
	std::unique_ptr<UploadBuffer> constBuff_ = nullptr;

	//書き込み用
	ConstBuffDataViewProjection* viewProjectionData_ = nullptr;

public:
	//角度
	Vector3 rotation_ = { 0.0f,0.0f,0.0f };

	//座標
	Vector3 translation_ = { 0.0f,0.0f,-50.0f };

	//ビュー行列
	Matrix4x4 matView_{};

	//プロジェクション行列
	Matrix4x4 matProjection_{};

	//視野角
	float fov_ = 0.45f;

	//アスペクト比
	float aspectRatio_ = 1280.0f / 720.0f;

	//近平面への距離
	float nearClip_ = 0.1f;

	//遠平面への距離
	float farClip_ = 100.0f;
};

