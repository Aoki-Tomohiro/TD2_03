#include "Player.h"
#include "Engine/Components/CollisionManager/CollisionConfig.h"
#include "Project/Scene/GamePuzzleScene.h"
#include <numbers>

void Player::Initialize() {
	input_ = Input::GetInstance();
	worldTransformBase_.Initialize(); 
	worldTransformBase_.translation_.x = -0.8f;
	worldTransformBase_.translation_.y = -0.3f;
	AABB aabbSize{ .min{-0.4f,0.14f,-0.4f},.max{0.4f,0.8f,0.4f} };
	SetAABB(aabbSize);
	SetCollisionPrimitive(kCollisionPrimitiveAABB);
	SetCollisionAttribute(kCollisionAttributePlayer);
	SetCollisionMask(kCollisionMaskPlayer);

	if (GamePuzzleScene::form == 0)
	{
		worldTransformBase_.translation_.x = -7.0f;
		worldTransformBase_.translation_.y = -3.7f;
	}

	if (GamePuzzleScene::form == 1 || GamePuzzleScene::form == 2)
	{
		worldTransformBase_.translation_.x = 15.0f;
		worldTransformBase_.translation_.y = -3.7f;
	}
};
void Player::Update() {

	if (behaviorRequest_) {
		// 振る舞い変更
		behavior_ = behaviorRequest_.value();
		// 各振る舞いごとの初期化
		switch (behavior_) {
		case Behavior::kRoot:
		default:
			MoveInitialize();
			break;
		case Behavior::kJump:
			JumpInitialize();
			break;
		case Behavior::kDead:

			break;
		}

		// 振る舞いリセット
		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_) {
	case Behavior::kRoot:
	default:
		// 通常行動
		MoveUpdata();
		break;
	case Behavior::kJump:
		JumpUpdata();
		break;
	case Behavior::kDead:
		break;
	}

	
	// 回転
	worldTransformBase_.rotation_.y = LerpShortAngle(worldTransformBase_.rotation_.y, destinationAngleY_, 0.2f);

	worldTransformBase_.UpdateMatrixFromEuler();
	ImGui::Begin("Player");
	ImGui::SliderFloat3("PlayerPos", &worldTransformBase_.translation_.x, -3.0f, 3.0f);
	ImGui::SliderFloat3("PlayerVelocity", &velocity_.x, -3.0f, 3.0f);
	if (behavior_ == Behavior::kRoot)
	{
		ImGui::Text("Behavior : kRoot");
	}
	else if (behavior_ == Behavior::kJump)
	{
		ImGui::Text("Behavior : kJump");
	}
	ImGui::End();
};

//移動
void Player::MoveInitialize() {
	verticalVelocity_ = { 0.0f,0.0f,0.0f };
};
void Player::MoveUpdata() {
	if (input_->IsControllerConnected())
	{

		const float value = 0.7f;
		bool isMove = false;

		// 移動速度
		const float kCharacterSpeed = 0.2f;
		// 移動量
		velocity_ = {
			(float)input_->GetLeftStickX(), 0.0f,0.0f };

		if (Length(velocity_) > value) {
			isMove = true;
			velocity_ = Normalize(velocity_);
			velocity_ = Multiply(velocity_, kCharacterSpeed);
		}
		else {
			velocity_ = { 0.0f,0.0f,0.0f };
		}

		if (isMove) {
			// 現在の位置から移動する位置へのベクトル
			Vector3 sub = (worldTransformBase_.translation_ + velocity_) - GetLocalPosition();
			// 平行移動
			worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, velocity_);
			if (sub.z != 0.0) {
				destinationAngleY_ = std::asin(sub.x / std::sqrt(sub.x * sub.x + sub.z * sub.z));

				if (sub.z < 0.0) {
					destinationAngleY_ = (sub.x >= 0.0)
						? std::numbers::pi_v<float> -destinationAngleY_
						: -std::numbers::pi_v<float> -destinationAngleY_;
				}
			}
			else {
				destinationAngleY_ = (sub.x >= 0.0) ? std::numbers::pi_v<float> / 2.0f
					: -std::numbers::pi_v<float> / 2.0f;
			}
		}
		
		// 重力加速度
		const float kGravity = 0.05f;
		// 加速ベクトル
		Vector3 accelerationVector = { 0.0f, -kGravity, 0.0f };
		// 加速
		verticalVelocity_ += accelerationVector;
		// 移動
		worldTransformBase_.translation_ += verticalVelocity_;
		// 地面より下に行かないようにする
		if (worldTransformBase_.translation_.y <= -3.7f) {
			worldTransformBase_.translation_.y = -3.7f;
		}

		//ジャンプ
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A)){
			behaviorRequest_ = Behavior::kJump;
			const float kJumpFirstSpeed = 0.6f;
			worldTransformBase_.translation_.y += kJumpFirstSpeed;
		}
	}
	else {
		const float value = 0.7f;
		bool isMove_ = false;
		/*----------移動処理----------*/
		float kCharacterSpeed = 0.3f;
		// 移動量
		velocity_ = { 0.0f, 0.0f, 0.0f };

		// 左右移動
		if (input_->IsPushKey(DIK_A)) {
			velocity_.x = -1;

		}
		else if (input_->IsPushKey(DIK_D)) {
			velocity_.x = 1;
		}



		if (input_->IsPushKey(DIK_A) ||input_->IsPushKey(DIK_D)) {
			isMove_ = true;
			velocity_ = Normalize(velocity_);
			velocity_ = Multiply(velocity_, kCharacterSpeed);
		}


		if (isMove_) {
			// 現在の位置から移動する位置へのベクトル
			Vector3 sub = (worldTransformBase_.translation_ + velocity_) - GetLocalPosition();
			// 平行移動
			worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, velocity_);
			if (sub.z != 0.0) {
				destinationAngleY_ = std::asin(sub.x / std::sqrt(sub.x * sub.x + sub.z * sub.z));

				if (sub.z < 0.0) {
					destinationAngleY_ = (sub.x >= 0.0)
						? std::numbers::pi_v<float> -destinationAngleY_
						: -std::numbers::pi_v<float> -destinationAngleY_;
				}
			}
			else {
				destinationAngleY_ = (sub.x >= 0.0) ? std::numbers::pi_v<float> / 2.0f
					: -std::numbers::pi_v<float> / 2.0f;
			}

		}

		// 重力加速度
		const float kGravity = 0.05f;
		// 加速ベクトル
		Vector3 accelerationVector = { 0, -kGravity, 0 };
		// 加速
		verticalVelocity_ += accelerationVector;
		// 移動
		worldTransformBase_.translation_ += verticalVelocity_;
		// 地面より下に行かないようにする
		if (worldTransformBase_.translation_.y <= -3.7f) {
			worldTransformBase_.translation_.y = -3.7f;
		}

		// ジャンプ
		if (input_->IsPushKeyEnter(DIK_W)) {
			behaviorRequest_ = Behavior::kJump;
			const float kJumpFirstSpeed = 0.6f;
			worldTransformBase_.translation_.y += kJumpFirstSpeed;
		}
	}
}

//ジャンプ
void Player::JumpInitialize() {
	// ジャンプ初速
	const float kJumpFirstSpeed = 0.6f;
	velocity_.y = kJumpFirstSpeed;
};
void Player::JumpUpdata() {
	// 移動
	worldTransformBase_.translation_ += velocity_;
	// 重力加速度
	const float kGravity = 0.05f;
	// 加速ベクトル
	Vector3 accelerationVector = { 0, -kGravity, 0 };
	// 加速
	velocity_ += accelerationVector;

	if (worldTransformBase_.translation_.y <= -3.7f) {
		// ジャンプ終了
		behaviorRequest_ = Behavior::kRoot;
		worldTransformBase_.translation_.y = -3.7f;
	}
};


Vector3 Player::GetWorldPosition() {

	return worldTransformBase_.translation_;
}


Vector3 Player::GetLocalPosition() {
	// ワールド座標を入れる関数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransformBase_.translation_.x;
	worldPos.y = worldTransformBase_.translation_.y;
	worldPos.z = worldTransformBase_.translation_.z;
	return worldPos;
}


void Player::OnCollision(Collider* collider) {
	if (collider->GetCollisionAttribute() == kCollisionAttributeEnemy)
	{
		AABB aabbA = {
		.min{worldTransformBase_.translation_.x + GetAABB().min.x,worldTransformBase_.translation_.y + GetAABB().min.y,worldTransformBase_.translation_.z + GetAABB().min.z},
		.max{worldTransformBase_.translation_.x + GetAABB().max.x,worldTransformBase_.translation_.y + GetAABB().max.y,worldTransformBase_.translation_.z + GetAABB().max.z},
		};
		AABB aabbB = {
			.min{collider->GetWorldTransform().translation_.x + collider->GetAABB().min.x,collider->GetWorldTransform().translation_.y + collider->GetAABB().min.y,collider->GetWorldTransform().translation_.z + collider->GetAABB().min.z},
			.max{collider->GetWorldTransform().translation_.x + collider->GetAABB().max.x,collider->GetWorldTransform().translation_.y + collider->GetAABB().max.y,collider->GetWorldTransform().translation_.z + collider->GetAABB().max.z},
		};

		Vector3 overlapAxis = {
			std::min<float>(aabbA.max.x,aabbB.max.x) - std::max<float>(aabbA.min.x,aabbB.min.x),
			std::min<float>(aabbA.max.y,aabbB.max.y) - std::max<float>(aabbA.min.y,aabbB.min.y),
			std::min<float>(aabbA.max.z,aabbB.max.z) - std::max<float>(aabbA.min.z,aabbB.min.z),
		};

		Vector3 directionAxis{};
		if (overlapAxis.x < overlapAxis.y && overlapAxis.x < overlapAxis.z) {
			//X軸方向で最小の重なりが発生している場合
			directionAxis.x = (worldTransformBase_.translation_.x < collider->GetWorldTransform().translation_.x) ? -1.0f : 1.0f;
			directionAxis.y = 0.0f;
		}
		else if (overlapAxis.y < overlapAxis.x && overlapAxis.y < overlapAxis.z) {
			//Y軸方向で最小の重なりが発生している場合
			directionAxis.y = (worldTransformBase_.translation_.y < collider->GetWorldTransform().translation_.y) ? -1.0f : 1.0f;
			directionAxis.x = 0.0f;
		}
		else if (overlapAxis.z < overlapAxis.x && overlapAxis.z < overlapAxis.y)
		{
			directionAxis.z = (worldTransformBase_.translation_.z < collider->GetWorldTransform().translation_.z) ? -1.0f : 1.0f;
			directionAxis.x = 0.0f;
			directionAxis.y = 0.0f;
		}

		worldTransformBase_.translation_ += Multiply(overlapAxis, directionAxis);
		worldTransformBase_.UpdateMatrixFromEuler();

		// Rayの原点
		Vector3 origin = worldTransformBase_.translation_;

		// Rayの方向ベクトル
		Vector3 direction = { 0.0f, -1.0f, 0.0f };

		// X軸方向での交差距離を計算
		float tMin = (aabbB.min.x - origin.x) / direction.x;
		float tMax = (aabbB.max.x - origin.x) / direction.x;
		if (tMin > tMax) std::swap(tMin, tMax);

		// Y軸方向での交差距離を計算
		float tyMin = (aabbB.min.y - origin.y) / direction.y;
		float tyMax = (aabbB.max.y - origin.y) / direction.y;

		// 有効な範囲内での最小と最大の交差距離を更新
		if (tyMin > tyMax) std::swap(tyMin, tyMax);
		if (tyMin > tMax || tyMax < tMin) return;

		behaviorRequest_ = Behavior::kRoot;
	}
}