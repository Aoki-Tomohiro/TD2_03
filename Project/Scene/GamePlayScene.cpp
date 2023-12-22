#include "GamePlayScene.h"
#include "Engine/Framework/Scene/SceneManager.h"

void GamePlayScene::Initialize() {
	//インプットのインスタンスを取得
	input_ = Input::GetInstance();
	camera_.Initialize();
	camera_.translation_.z = -30.0f;
	playerManager_ = std::make_unique<PlayerManager>();
	playerManager_->Initialize();
}

void GamePlayScene::Finalize() {

}

void GamePlayScene::Update() {

	playerManager_->Update();
	camera_.UpdateMatrix();

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
	ImGui::End();
}

void GamePlayScene::Draw() {

	playerManager_->Draw(camera_);
	Renderer::GetInstance()->Render();
	
}

void GamePlayScene::DrawUI() {

}