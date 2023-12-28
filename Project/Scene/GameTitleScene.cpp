#include "GameTitleScene.h"
#include "Engine/Framework/Scene/SceneManager.h"
#include "GamePuzzleScene.h"

void GameTitleScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();

	//インプットのインスタンスを取得
	input_ = Input::GetInstance();


	GamePuzzleScene::form = 0;

}

void GameTitleScene::Finalize() {

}

void GameTitleScene::Update() {

	if (input_->IsControllerConnected())
	{
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A))
		{
			sceneManager_->ChangeScene("StageSelectScene");
		}
	}

	if (input_->IsPushKeyEnter(DIK_SPACE))
	{
		sceneManager_->ChangeScene("StageSelectScene");
	}

	ImGui::Begin("Title");
	ImGui::Text("StageSelectScene : A Button or SPACE");
	ImGui::End();
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