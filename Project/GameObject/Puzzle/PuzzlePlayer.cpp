#include "PuzzlePlayer.h"
#include <cassert>

void PuzzlePlayer::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	input_ = Input::GetInstance();

	//モデルの初期化
	assert(model);
	model_ = model;
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	velocity_ = velocity;

	SetCollisionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);
	SetCollisionPrimitive(kCollisionPrimitiveAABB);
}

void PuzzlePlayer::Update() {

	if (input_->IsPushKey(DIK_A))
	{
		worldTransform_.translation_.x -= velocity_.x;
	}

	if (input_->IsPushKey(DIK_D))
	{
		worldTransform_.translation_.x += velocity_.x;
	}

	if (input_->IsPushKey(DIK_W))
	{
		worldTransform_.translation_.y += velocity_.y;
	}

	if (input_->IsPushKey(DIK_S))
	{
		worldTransform_.translation_.y -= velocity_.y;
	}

	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrixFromEuler();
}

void PuzzlePlayer::Draw(const Camera& camera) {
	//モデルの描画
	model_->Draw(worldTransform_, camera);
}

void PuzzlePlayer::OnCollision(Collider* collider) {

}

Vector3 PuzzlePlayer::GetWorldPosition() {
	Vector3 pos{};
	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];
	return pos;
}
