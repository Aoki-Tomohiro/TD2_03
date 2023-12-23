#include "GamePlayScene.h"
#include "Engine/Framework/Scene/SceneManager.h"
#include "Project/Game/GameManager.h"

void GamePlayScene::Initialize() {
	//インプットのインスタンスを取得
	input_ = Input::GetInstance();
}

void GamePlayScene::Finalize() {

}

void GamePlayScene::Update() {

	if (input_->IsControllerConnected())
	{
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A))
		{
			sceneManager_->ChangeScene("GameClearScene");
		}

		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_B) || input_->IsPushKeyEnter(DIK_RETURN))
		{
			sceneManager_->ChangeScene("GameOverScene");
		}
	}

	if (input_->IsPushKeyEnter(DIK_SPACE))
	{
		sceneManager_->ChangeScene("GameClearScene");
	}

	if (input_->IsPushKeyEnter(DIK_RETURN))
	{
		sceneManager_->ChangeScene("GameOverScene");
	}

	ImGui::Begin("Play");
	ImGui::Text("GameClearScene : A Button or SPACE");
	ImGui::Text("GameOverScene : B Button or ENTER");
	ImGui::Text("StageNumber : %d", GameManager::stageNum);
	ImGui::End();
}

void GamePlayScene::Draw() {

}

void GamePlayScene::DrawUI() {

}