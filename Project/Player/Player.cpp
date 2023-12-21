#include "Player.h"
#include "Engine/Components/CollisionManager/CollisionConfig.h"

void Player::Initialize() {
	//models_ = models;
	worldTransformBase_.Initialize();

};
void Player::Update() {

	worldTransformBase_.UpdateMatrixFromQuaternion();
};


void Player::Draw(const Camera& camera) {
	//models_[0]->Draw(worldTransformBase_, camera);
}

Vector3 Player::GetWorldPosition() {

	return worldTransformBase_.translation_;
}

void Player::OnCollision(Collider* collider) {

}