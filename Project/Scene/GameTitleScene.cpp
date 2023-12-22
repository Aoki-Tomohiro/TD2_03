#include "GameTitleScene.h"
#include "Engine/Framework/Scene/SceneManager.h"

void GameTitleScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();

	//インプットのインスタンスを取得
	input_ = Input::GetInstance();

	camera_.Initialize();

	puzzleModel_.reset(Model::CreateFromOBJ("Project/Resources/Player", "Player.obj", renderer_->Opaque));

	puzzle_ = std::make_unique<Puzzle>();
	puzzle_->Initialize(puzzleModel_.get(), { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });

}

void GameTitleScene::Finalize() {

}

void GameTitleScene::Update() {

	puzzle_->Update();

	camera_.UpdateMatrix();

	if (input_->IsControllerConnected())
	{
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A))
		{
			sceneManager_->ChangeScene("GamePlayScene");
		}
	}
	
	if (input_->IsPushKeyEnter(DIK_SPACE))
	{
		sceneManager_->ChangeScene("GamePlayScene");
    }
	

	ImGui::Begin("Title");
	ImGui::Text("GamePlayScene : A Button or SPACE");
	ImGui::End();
}

void GameTitleScene::Draw() {
#pragma region モデルの描画処理

	puzzle_->Draw(camera_);

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