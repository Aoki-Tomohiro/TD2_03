#include "PuzzleScenePortal.h"
#include <cassert>

void PuzzleScenePortal::Initialize(Model* model, const Vector3& position)
{
	input_ = Input::GetInstance();

	//モデルの初期化
	assert(model);
	model_ = model;
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	SetCollisionAttribute(kCollisionAttributeGoal);
	SetCollisionMask(kCollisionMaskGoal);
	SetCollisionPrimitive(kCollisionPrimitiveAABB);
}

void PuzzleScenePortal::Update() {

	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrixFromEuler();
}

void PuzzleScenePortal::Draw(const Camera& camera) {
	//モデルの描画
	model_->Draw(worldTransform_, camera);
}

void PuzzleScenePortal::OnCollision(Collider* collider) {

}

Vector3 PuzzleScenePortal::GetWorldPosition() {
	Vector3 pos{};
	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];
	return pos;
}
