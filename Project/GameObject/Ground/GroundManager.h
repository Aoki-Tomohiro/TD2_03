#pragma once
#include "Ground.h"

class GroundManager {
public:
	void Initialize();
	void Update();
	void Draw(const Camera& camera);
private:
	WorldTransform worldTransformBase_;
	std::unique_ptr <Model> Model_;
	std::unique_ptr<Ground> ground_;

};