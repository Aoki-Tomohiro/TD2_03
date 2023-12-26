#include "Player.h"
#include "Engine/Components/CollisionManager/CollisionConfig.h"
#include <numbers>

void Player::Initialize() {
	input_ = Input::GetInstance();
	worldTransformBase_.Initialize();

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
	ImGui::End();
};

//移動
void Player::MoveInitialize() {
	worldTransformBase_.translation_.y = 0.0f;
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
			(float)input_->GetLeftStickX()/* / SHRT_MAX*/, 0.0f,0.0f };

		if (Length(velocity_) > value) {
			isMove = true;
			velocity_ = Normalize(velocity_);
			velocity_ = Multiply(velocity_, kCharacterSpeed);
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
		



		//ジャンプ
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A)){
			behaviorRequest_ = Behavior::kJump;
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
		

		// ジャンプ
		if (input_->IsPushKeyEnter(DIK_W)) {
			behaviorRequest_ = Behavior::kJump;
		}
	}
}

//ジャンプ
void Player::JumpInitialize() {
	worldTransformBase_.translation_.y = 0.0f;
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

	if (worldTransformBase_.translation_.y <= 0.0f) {
		// ジャンプ終了
		behaviorRequest_ = Behavior::kRoot;
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

}