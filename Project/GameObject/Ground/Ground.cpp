#include "Ground.h"

void Ground::Initialize() {
	
	worldTransform_.Initialize();
	worldTransform_.translation_.x = 15.0f;
	worldTransform_.translation_.y = -5.0f;
	worldTransform_.scale_.x = 50.0f;
	
}

void Ground::Update() {
	worldTransform_.UpdateMatrixFromEuler();
}
