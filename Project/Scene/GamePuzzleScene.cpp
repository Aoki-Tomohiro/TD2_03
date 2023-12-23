#include "GamePuzzleScene.h"
#include "Engine/Framework/Scene/SceneManager.h"

void GamePuzzleScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();

	//衝突マネージャーの作成
	collisionManager_ = std::make_unique<CollisionManager>();

	//インプットのインスタンスを取得
	input_ = Input::GetInstance();

	camera_.Initialize();

	//プレイヤー
	puzzlePlayerModel_.reset(Model::CreateFromOBJ("Project/Resources/Player", "Player.obj", renderer_->Opaque));
	puzzlePlayer_ = std::make_unique<PuzzlePlayer>();
	puzzlePlayer_->Initialize(puzzlePlayerModel_.get(), { 0.0f,0.0f,0.0f }, { 0.05f,0.05f,0.0f });

	//タイル
	for (int i = 0; i < 9; i++)
	{
		puzzleModel_[i].reset(Model::CreateFromOBJ("Project/Resources/Models/Tile", "Tile.obj", renderer_->Opaque));
		puzzle_[i] = std::make_unique<Puzzle>();
	}

	puzzle_[0]->Initialize(puzzleModel_[0].get(), { -3.0f,3.0f,0.0f });
	puzzle_[1]->Initialize(puzzleModel_[1].get(), { 0.0f,3.0f,0.0f });
	puzzle_[2]->Initialize(puzzleModel_[2].get(), { 3.0f,3.0f,0.0f });
	puzzle_[3]->Initialize(puzzleModel_[3].get(), { -3.0f,0.0f,0.0f });
	puzzle_[4]->Initialize(puzzleModel_[4].get(), { 0.0f,0.0f,0.0f });
	puzzle_[5]->Initialize(puzzleModel_[5].get(), { 3.0f,0.0f,0.0f });
	puzzle_[6]->Initialize(puzzleModel_[6].get(), { -3.0f,-3.0f,0.0f });
	puzzle_[7]->Initialize(puzzleModel_[7].get(), { 0.0f,-3.0f,0.0f });
	puzzle_[8]->Initialize(puzzleModel_[8].get(), { 3.0f,-3.0f,0.0f });
}

void GamePuzzleScene::Finalize() {

}

void GamePuzzleScene::Update() {

	puzzlePlayer_->Update();

	for (int i = 0; i < 9; i++)
	{
		puzzle_[i]->Update();
	}

	if (input_->IsControllerConnected())
	{
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A))
		{
			sceneManager_->ChangeScene("GamePlayScene");
		}
	}

	if (input_->IsPushKeyEnter(DIK_P))
	{
		sceneManager_->ChangeScene("GamePlayScene");
	}

	if (puzzle_[0]->GetIsSelect() == true && puzzle_[4]->GetIsSelect() == true && puzzle_[8]->GetIsSelect() == true)
	{
		ImGui::Begin("Clear");

		ImGui::End();
	}

	//衝突判定
	collisionManager_->ClearColliderList();
	collisionManager_->SetColliderList(puzzlePlayer_.get());

	for (int i = 0; i < 9; i++)
	{
		collisionManager_->SetColliderList(puzzle_[i].get());
	}

	collisionManager_->CheckAllCollisions();

	camera_.UpdateMatrix();


	ImGui::Begin("Title");
	ImGui::Text("GamePlayScene : A Button or PKey");
	ImGui::End();
}

void GamePuzzleScene::Draw() {
#pragma region モデルの描画処理

	for (int i = 0; i < 9; i++)
	{
		puzzle_[i]->Draw(camera_);
	}

	puzzlePlayer_->Draw(camera_);

	//モデルの描画
	renderer_->Render();

#pragma endregion

#pragma region パーティクルの描画処理

	renderer_->PreDrawParticles();

	renderer_->PostDrawParticles();

#pragma endregion
}

void GamePuzzleScene::DrawUI() {
#pragma region スプライトの描画

	//スプライト描画
	renderer_->PreDrawSprites(Renderer::kBlendModeNormal);

	renderer_->PostDrawSprites();

#pragma endregion
}