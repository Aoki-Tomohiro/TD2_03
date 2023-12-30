#include "GroundManager.h"

void GroundManager::Initialize() {
	Model_.reset(Model::CreateFromOBJ("Project/Resources/ground", "Ground.obj", Renderer::Opaque));

	ground_ = std::make_unique <Ground>();
	ground_->Initialize();
	
}

void GroundManager::Update() {
	ground_->Update();
}

void GroundManager::Draw(const Camera& camera) {
	Model_->Draw(ground_->GetWorldTransform(), camera);
}
