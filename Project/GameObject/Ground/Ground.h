#pragma once
#include "Engine/Components/Input.h"
#include "Engine/3D/Model/Model.h"
#include "Engine/3D/Matrix/WorldTransform.h"
#include "Engine/3D/Camera/Camera.h"
#include "Engine/Components/CollisionManager/Collider.h"
#include <vector>
#include <memory>

class Ground {
public:
	void Initialize();
	void Update();
	
	WorldTransform& GetWorldTransform() { return worldTransform_; }
	void SetTranslate(const Vector3& translate) { worldTransform_.translation_ = translate; }

private:
	WorldTransform worldTransform_;
	Model* groundModel_;
	uint32_t textureHandle_;
};