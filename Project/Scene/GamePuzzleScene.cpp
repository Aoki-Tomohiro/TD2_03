#include "GamePuzzleScene.h"
#include "Engine/Framework/Scene/SceneManager.h"

void GamePuzzleScene::Initialize() {
	//インプットのインスタンスを取得
	input_ = Input::GetInstance();

	puzzleModel_.reset(Model::CreateFromOBJ("Project/Resources/Player", "Player.obj", Renderer::Opaque));

	puzzle_ = std::make_unique<Puzzle>();
	puzzle_->Initialize(puzzleModel_.get(), {0.0f,0.0f,0.0f}, {0.0f,0.0f,0.0f});
}

void GamePuzzleScene::Finalize() {

}

void GamePuzzleScene::Update() {

	puzzle_->Update();

	if (input_->IsControllerConnected())
	{
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_B) || input_->IsPushKeyEnter(DIK_RETURN))
		{
			sceneManager_->ChangeScene("GamePlayScene");
		}
	}

	if (input_->IsPushKeyEnter(DIK_RETURN))
	{
		sceneManager_->ChangeScene("GamePlayScene");
	}

	ImGui::Begin("GamePuzzleScene");
	ImGui::Text("GamePlayScene : B Button or ENTER");
	ImGui::End();
}

void GamePuzzleScene::Draw() {
	puzzle_->Draw(camera_);
}

void GamePuzzleScene::DrawUI() {

}
