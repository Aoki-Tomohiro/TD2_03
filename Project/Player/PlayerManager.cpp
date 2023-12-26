#include "PlayerManager.h"

void PlayerManager::Initialize() {
	
	Model_.reset(Model::CreateFromOBJ("Project/Resources/Models/Player", "float_Head.obj", Renderer::Opaque));

	player_ = std::make_unique <Player>();
	player_->Initialize();

	worldTransformBase_.Initialize();
	
}

void PlayerManager::Update() {
	player_->Update();
	/*worldTransformBase_ = player_->GetWorldTransform();
	worldTransformBase_.UpdateMatrixFromEuler();*/
	
};

void PlayerManager::Draw(const Camera& camera) {
	Model_->Draw(player_->GetWorldTransform(), camera);
};


