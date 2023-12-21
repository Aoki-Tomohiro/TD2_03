#include "Puzzle.h"
#include <cassert>

void Puzzle::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	//モデルの初期化
	assert(model);
	model_ = model;
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	//速度の初期化
	velocity_ = velocity;
}

void Puzzle::Update() {
	//移動処理
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	if (worldTransform_.translation_.x >= 30.0f || worldTransform_.translation_.x <= -30.0f) {
		velocity_.x *= -1.0f;
	}

	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrixFromEuler();
}

void Puzzle::Draw(const Camera& camera) {
	//モデルの描画
	model_->Draw(worldTransform_, camera);
}

void Puzzle::OnCollision(Collider* collider) {

}

Vector3 Puzzle::GetWorldPosition() {
	Vector3 pos{};
	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];
	return pos;
}