#include "GameClearScene.h"
#include "Engine/Framework/Scene/SceneManager.h"

void GameClearScene::Initialize() {
	//インプットのインスタンスを取得
	input_ = Input::GetInstance();
}

void GameClearScene::Finalize() {

}

void GameClearScene::Update() {

	if (input_->IsControllerConnected())
	{
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A) || input_->IsPushKeyEnter(DIK_SPACE))
		{
			sceneManager_->ChangeScene("GameTitleScene");
		}
	}

	ImGui::Begin("Clear");
	ImGui::Text("GameTitleScene : A Button or SPACE");
	ImGui::End();
}

void GameClearScene::Draw() {

}

void GameClearScene::DrawUI() {

}