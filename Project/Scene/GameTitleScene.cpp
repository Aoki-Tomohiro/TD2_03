#include "GameTitleScene.h"
#include "Engine/Framework/Scene/SceneManager.h"

void GameTitleScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();

	//インプットのインスタンスを取得
	input_ = Input::GetInstance();

	camera_.Initialize();

	/*puzzleModel_[0].reset(Model::CreateFromOBJ("Project/Resources/Models/Tile", "Tile.obj", renderer_->Opaque));
	puzzleModel_[1].reset(Model::CreateFromOBJ("Project/Resources/Models/Tile", "Tile.obj", renderer_->Opaque));*/

	for (int i = 0; i < 9; i++)
	{
		puzzleModel_[i].reset(Model::CreateFromOBJ("Project/Resources/Models/Tile", "Tile.obj", renderer_->Opaque));
		puzzle_[i] = std::make_unique<Puzzle>();
	}

	puzzle_[0]->Initialize(puzzleModel_[0].get(), { -2.0f,2.0f,0.0f });
	puzzle_[1]->Initialize(puzzleModel_[1].get(), { 0.0f,2.0f,0.0f });
	puzzle_[2]->Initialize(puzzleModel_[2].get(), { 2.0f,2.0f,0.0f });
	puzzle_[3]->Initialize(puzzleModel_[3].get(), { -2.0f,0.0f,0.0f });
	puzzle_[4]->Initialize(puzzleModel_[4].get(), { 0.0f,0.0f,0.0f });
	puzzle_[5]->Initialize(puzzleModel_[5].get(), { 2.0f,0.0f,0.0f });
	puzzle_[6]->Initialize(puzzleModel_[6].get(), { -2.0f,-2.0f,0.0f });
	puzzle_[7]->Initialize(puzzleModel_[7].get(), { 0.0f,-2.0f,0.0f });
	puzzle_[8]->Initialize(puzzleModel_[8].get(), { 2.0f,-2.0f,0.0f });
}

void GameTitleScene::Finalize() {

}

void GameTitleScene::Update() {

	for (int i = 0; i < 9; i++)
	{
		puzzle_[i]->Update();
	}

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
		/*sceneManager_->ChangeScene("GamePlayScene");*/
		/*puzzleModel_->GetMaterial()->SetColor({ 1.0f,0.0f,0.0f,1.0f });*/
		puzzleModel_[0]->GetMaterial()->SetColor({1.0f,0.0f,0.0f,1.0f});
    }
	

	ImGui::Begin("Title");
	ImGui::Text("GamePlayScene : A Button or SPACE");
	ImGui::End();
}

void GameTitleScene::Draw() {
#pragma region モデルの描画処理

	for (int i = 0; i < 9; i++)
	{
		puzzle_[i]->Draw(camera_);
	}

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