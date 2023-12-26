#include "GamePlayScene.h"
#include "Engine/Framework/Scene/SceneManager.h"
#include "Project/Game/GameManager.h"
#include "GamePuzzleScene.h"

void GamePlayScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();

	//インプットのインスタンスを取得
	input_ = Input::GetInstance();

	camera_.Initialize();

	stageObjectModel_.reset(Model::CreateFromOBJ("Project/Resources/Models/Tile", "Tile.obj", renderer_->Opaque));

	for (int i = 0; i < 3; i++)
	{
		stageObject_[i] = std::make_unique<StageObject>();
	}

	stageObject_[0]->Initialize(stageObjectModel_.get(), { -3.0f,-3.0f,0.0f });
	stageObject_[1]->Initialize(stageObjectModel_.get(), { 0.0f,0.0f,0.0f });
	stageObject_[2]->Initialize(stageObjectModel_.get(), { 3.0f,3.0f,0.0f });
}

void GamePlayScene::Finalize() {

}

void GamePlayScene::Update() {
	
	for (int i = 0; i < 3; i++)
	{
		stageObject_[i]->Update();
	}

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

	if (input_->IsPushKeyEnter(DIK_P))
	{
		sceneManager_->ChangeScene("GamePuzzleScene");
	}

	if (input_->IsPushKeyEnter(DIK_SPACE))
	{
		sceneManager_->ChangeScene("GameClearScene");
	}

	if (input_->IsPushKeyEnter(DIK_RETURN))
	{
		sceneManager_->ChangeScene("GameOverScene");
	}

	camera_.UpdateMatrix();

	ImGui::Begin("Play");
	ImGui::Text("GamePuzzleScene :  PKey");
	ImGui::Text("GameClearScene : A Button or SPACE");
	ImGui::Text("GameOverScene : B Button or ENTER");
	ImGui::Text("StageNumber : %d", GameManager::stageNum);
	ImGui::End();
}

void GamePlayScene::Draw() {
#pragma region モデルの描画処理

	if (GamePuzzleScene::form == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			stageObject_[i]->Draw(camera_);
		}
	}

	//モデルの描画
	renderer_->Render();

#pragma endregion

#pragma region パーティクルの描画処理

	renderer_->PreDrawParticles();

	renderer_->PostDrawParticles();

#pragma endregion
}

void GamePlayScene::DrawUI() {
#pragma region スプライトの描画

	//スプライト描画
	renderer_->PreDrawSprites(Renderer::kBlendModeNormal);

	renderer_->PostDrawSprites();

#pragma endregion
}