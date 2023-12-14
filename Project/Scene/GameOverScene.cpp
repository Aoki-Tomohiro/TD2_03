#include "GameOverScene.h"
#include "Engine/Framework/Scene/SceneManager.h"

void GameOverScene::Initialize() {
	//インプットのインスタンスを取得
	input_ = Input::GetInstance();
}

void GameOverScene::Finalize() {

}

void GameOverScene::Update() {

	if (input_->IsControllerConnected())
	{
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A))
		{
			sceneManager_->ChangeScene("GameTitleScene");
		}
	}

	if (input_->IsPushKeyEnter(DIK_SPACE))
	{
		sceneManager_->ChangeScene("GameTitleScene");
	}

	ImGui::Begin("Over");
	ImGui::Text("GameTitleScene : A Button or SPACE");
	ImGui::End();
}

void GameOverScene::Draw() {

}

void GameOverScene::DrawUI() {

}