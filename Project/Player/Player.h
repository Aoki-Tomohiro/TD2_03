#pragma once
#include "Engine/Components/Input.h"
#include "Engine/3D/Model/Model.h"
#include "Engine/3D/Matrix/WorldTransform.h"
#include "Engine/3D/Camera/Camera.h"
#include "Engine/Components/CollisionManager/Collider.h"
#include <vector>
#include <memory>

class Player : public Collider {
public:
	//~Player();
	void Initialize();
	void Update();
	
	//移動
	void MoveInitialize();
	void MoveUpdata();

	//ジャンプ
	void JumpInitialize();
	void JumpUpdata();



	WorldTransform& GetWorldTransform() override { return worldTransformBase_; };
	Vector3 GetWorldPosition()override;
	// ローカル座標
	Vector3 GetLocalPosition();
	void OnCollision(Collider * collider) override;
private:
	Input* input_ = nullptr;
	WorldTransform worldTransformBase_;
	
	// 目標の角度
	float destinationAngleY_ = 0.0f;

	// 振る舞い
	enum class Behavior {
		kRoot,   // 通常状態
		kJump,   // ジャンプ
		kDead,   // 死亡
	};

	Behavior behavior_ = Behavior::kRoot;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	// 速度
	Vector3 velocity_ = {};
	Vector3 verticalVelocity_{};
	bool isDead_ = false;
};