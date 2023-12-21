#pragma once

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
	void Draw(const Camera& camera);
	WorldTransform& GetWorldTransform() override { return worldTransformBase_; };
	Vector3 GetWorldPosition()override;
	void OnCollision(Collider * collider) override;


private:
	//std::vector<Model*> models_;

	WorldTransform worldTransformBase_;

	bool isDead_ = false;

};