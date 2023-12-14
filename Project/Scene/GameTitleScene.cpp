#include "GameTitleScene.h"

void GameTitleScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();
}

void GameTitleScene::Finalize() {

}

void GameTitleScene::Update() {

}

void GameTitleScene::Draw() {
#pragma region モデルの描画処理

	//モデルの描画
	renderer_->Render();

#pragma endregion

#pragma region パーティクルの描画処理

	renderer_->PreDrawParticles();

	renderer_->PostDrawParticles();

#pragma endregion
}

void GameTitleScene::DrawUI() {
#pragma region スプライトの描画

	//スプライト描画
	renderer_->PreDrawSprites(Renderer::kBlendModeNormal);

	renderer_->PostDrawSprites();

#pragma endregion
}