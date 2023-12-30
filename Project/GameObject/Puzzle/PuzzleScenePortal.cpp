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

	SetCollisionAttribute(kCollisionAttributePuzzleScenePortal);
	SetCollisionMask(kCollisionMaskPuzzleScenePortal);
	SetCollisionPrimitive(kCollisionPrimitiveAABB);
}

void PuzzleScenePortal::Update() {

	//ワールドトランスフォームの更新
	worldTransform_.UpdateMatrixFromEuler();

	isHit_ = false;
}

void PuzzleScenePortal::Draw(const Camera& camera) {
	//モデルの描画
	model_->Draw(worldTransform_, camera);
}

void PuzzleScenePortal::OnCollision(Collider* collider) {
	if (collider->GetCollisionAttribute() & kCollisionAttributePlayer)
	{
		isHit_ = true;
	}

	ImGui::Begin("HIT");
	ImGui::Text("%d", isHit_);
	ImGui::End();
}

Vector3 PuzzleScenePortal::GetWorldPosition() {
	Vector3 pos{};
	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];
	return pos;
}
