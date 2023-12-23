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

	//カメラの追従処理
	if (playerManager_->GetPlayerPosition().x > -12.0f && playerManager_->GetPlayerPosition().x <= 12.0f) {
		camera_.translation_.x = 0.0f;
	}
	else if (playerManager_->GetPlayerPosition().x > 12.0f && playerManager_->GetPlayerPosition().x <= 36.0f) {
		camera_.translation_.x = 24.0f;
	}
	else if (playerManager_->GetPlayerPosition().x > 36.0f && playerManager_->GetPlayerPosition().x <= 60.0f) {
		camera_.translation_.x = 48.0f;
	}
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