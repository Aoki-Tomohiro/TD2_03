#include "GamePlayScene.h"
#include "Engine/Framework/Scene/SceneManager.h"
#include "GamePuzzleScene.h"

int GamePlayScene::stageNum = 0;

void GamePlayScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();

	//衝突マネージャーの作成
	collisionManager_ = std::make_unique<CollisionManager>();

	//インプットのインスタンスを取得
	input_ = Input::GetInstance();

	//Audioのインスタンスを取得
	audio_ = Audio::GetInstance();

	backTextureHandle_ = TextureManager::Load("Project/Resources/Images/back.png");
	backSprite_.reset(Sprite::Create(backTextureHandle_, { 0.0f,0.0f }));

	moveTextureHandle_ = TextureManager::Load("Project/Resources/Images/moveL.png");
	moveSprite_.reset(Sprite::Create(moveTextureHandle_, { 890.0f,550.0f }));
	moveSprite_->SetSize({ 150.0f, 150.0f});

	jumpTextureHandle_ = TextureManager::Load("Project/Resources/Images/jamp.png");
	jumpSprite_.reset(Sprite::Create(jumpTextureHandle_, { 1090.0f,580.0f }));
	jumpSprite_->SetSize({ 150.0f, 150.0f });

	decisionTextureHandle_ = TextureManager::Load("Project/Resources/Images/xbotton.png");
	decisionSprite_.reset(Sprite::Create(decisionTextureHandle_, { 270.0f,370.0f }));
	decisionSprite_->SetSize({ 120.0f, 120.0f });

	camera_.Initialize();
	camera_.translation_.z = -30.0f;

	playerManager_ = std::make_unique<PlayerManager>();
	playerManager_->Initialize();

	//StageObject
	stageObjectModel_.reset(Model::CreateFromOBJ("Project/Resources/Models/Tile", "Tile.obj", renderer_->Opaque));

	for (int i = 0; i < 4; i++)
	{
		stageObject_[i] = std::make_unique<StageObject>();
	}
	stageObject_[0]->SetScale({ 0.8f,0.8f,0.8f });
	stageObject_[0]->Initialize(stageObjectModel_.get(), { 20.0f,-2.7f,0.0f });
	stageObject_[1]->SetScale({ 0.8f,0.8f,0.8f });
	stageObject_[1]->Initialize(stageObjectModel_.get(), { 23.0f,0.3f,0.0f });
	stageObject_[2]->SetScale({ 0.8f,0.8f,0.8f });
	stageObject_[2]->Initialize(stageObjectModel_.get(), { 26.0f,3.3f,0.0f });
	stageObject_[3]->SetScale({ 3.0f,0.8f,0.8f });
	stageObject_[3]->Initialize(stageObjectModel_.get(), { 32.0f,3.3f,0.0f });
	

	//PuzzleScenePortal
	puzzleScenePortalModel_.reset(Model::CreateFromOBJ("Project/Resources/Models/Tile", "Tile.obj", renderer_->Opaque));
	puzzleScenePortalModel_->GetMaterial()->SetColor({ 0.0f,0.0f,1.0f,1.0f });

	puzzleScenePortal_ = std::make_unique<PuzzleScenePortal>();
	puzzleScenePortal_->Initialize(puzzleScenePortalModel_.get(), { 17.0f,-3.0f,0.0f });
	puzzleScenePortal_->SetScale({ 0.5f,0.5f,0.5f });

	//Goal
	goalModel_.reset(Model::CreateFromOBJ("Project/Resources/Models/Tile", "Tile.obj", renderer_->Opaque));
	goalModel_->GetMaterial()->SetColor({ 0.0f,1.0f,0.0f,1.0f });

	goal_ = std::make_unique<Goal>();
	goal_->Initialize(goalModel_.get(), { 32.0f,5.3f,0.0f });
	goal_->SetScale({ 0.5f,0.5f,0.5f });

	soundHandle_ = audio_->SoundLoadWave("Project/Resources/Sounds/select.wav");
}

void GamePlayScene::Finalize() {

}

void GamePlayScene::Update() {
	
	for (int i = 0; i < 4; i++)
	{
		stageObject_[i]->Update();
	}

	playerManager_->Update();

	puzzleScenePortal_->Update();

	goal_->Update();

	//カメラの追従処理
	Vector3 playerCenterPosition = playerManager_->GetPlayer()->GetWorldTransform().translation_;
	if (playerCenterPosition.x > -12.0f && playerCenterPosition.x <= 12.0f) {
		camera_.translation_.x = 0.0f;
	}
	else if (playerCenterPosition.x > 12.0f && playerCenterPosition.x <= 36.0f) {
		camera_.translation_.x = 24.0f;
	}
	else if (playerCenterPosition.x > 36.0f && playerCenterPosition.x <= 60.0f) {
		camera_.translation_.x = 48.0f;
	}
	camera_.UpdateMatrix();

	collisionManager_->ClearColliderList();
	collisionManager_->SetColliderList(playerManager_->GetPlayer());
	if (GamePuzzleScene::form == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			collisionManager_->SetColliderList(stageObject_[i].get());
		}
	}
	collisionManager_->SetColliderList(puzzleScenePortal_.get());
	collisionManager_->CheckAllCollisions();

	if (input_->IsControllerConnected())
	{
		/*if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A))
		{
			sceneManager_->ChangeScene("GameClearScene");
		}*/

		/*if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_B) || input_->IsPushKeyEnter(DIK_RETURN))
		{
			sceneManager_->ChangeScene("GameOverScene");
		}*/
	}

	if (puzzleScenePortal_->GetIsHit() == true && input_->IsPressButtonEnter(XINPUT_GAMEPAD_X))
	{
		audio_->SoundPlayWave(soundHandle_, false, 1.0f);
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

	ImGui::Begin("Play");
	ImGui::Text("GamePuzzleScene :  PKey");
	ImGui::Text("GameClearScene : A Button or SPACE");
	ImGui::Text("GameOverScene : B Button or ENTER");
	ImGui::End();
}

void GamePlayScene::Draw() {

	renderer_->PreDrawSprites(Renderer::kBlendModeNormal);

	backSprite_->Draw();

	renderer_->PostDrawSprites();

	GraphicsCore::GetInstance()->ClearDepthBuffer();

#pragma region モデルの描画処理

	if (GamePuzzleScene::form == 2)
	{
		for (int i = 0; i < 3; i++)
		{
			stageObject_[i]->Draw(camera_);
		}
	}

	playerManager_->Draw(camera_);

	puzzleScenePortal_->Draw(camera_);

	goal_->Draw(camera_);

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

	moveSprite_->Draw();

	jumpSprite_->Draw();

	if (puzzleScenePortal_->GetIsHit() == true)
	{
		decisionSprite_->Draw();
	}

	renderer_->PostDrawSprites();

#pragma endregion
}