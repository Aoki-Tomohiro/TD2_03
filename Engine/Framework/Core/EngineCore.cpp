#include "EngineCore.h"
#include "Engine/2D/Sprite.h"
#include "Engine/3D/Model/Model.h"
#include "Engine/Components/Particle/ParticleSystem.h"
#include "Engine/Utilities/GlobalVariables.h"
#include "Engine/Utilities/RandomGenerator.h"

void EngineCore::Initialize() {
	//Applicationの初期化
	application_ = Application::GetInstance();
	application_->CreateGameWindow(L"DirectXGame", Application::kClientWidth, Application::kClientHeight);

	//GraphicsCoreの初期化
	graphicsCore_ = GraphicsCore::GetInstance();
	graphicsCore_->Initialize();

	//テクスチャマネージャーの初期化
	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize();

	//ImGuiManagerの初期化
	imguiManager_ = ImGuiManager::GetInstance();
	imguiManager_->Initialize();

	//レンダラーの初期化
	renderer_ = Renderer::GetInstance();
	renderer_->Initialize();

	//オーディオの初期化
	audio_ = Audio::GetInstance();
	audio_->Initialize();

	//インプットの初期化
	input_ = Input::GetInstance();
	input_->Initialize();

	//ゲームオブジェクトマネージャーの初期化
	gameObjectManager_ = GameObjectManager::GetInstance();
	gameObjectManager_->Initialize();

	//シーンマネージャーのインスタンスを取得
	sceneManager_ = SceneManager::GetInstance();

	//スプライトの静的初期化
	Sprite::StaticInitialize();

	//パーティクルシステムの静的初期化
	ParticleSystem::StaticInitialize();

	//RandomGeneratorの初期化
	RandomGenerator::Initialize();
}

void EngineCore::Finalize() {
	//シーンマネージャの解放
	SceneManager::DeleteInstance();

	//ゲームオブジェクトマネージャーの解放
	GameObjectManager::DeleteInstance();

	//インプットの解放
	Input::DeleteInstance();

	//オーディオの解放
	audio_->Finalize();

	//レンダラーの解放
	Renderer::DeleteInstance();

	//ImGuiManagerの解放
	imguiManager_->ShutDown();

	//テクスチャマネージャーの解放
	TextureManager::DeleteInstance();

	//GraphicsCoreの解放
	GraphicsCore::DeleteInstance();

	//ゲームウィンドウを閉じる
	application_->CloseGameWindow();
}

void EngineCore::Update() {
	//インプットの更新
	input_->Update();

	//ImGuiの受付開始
	imguiManager_->Begin();

	//グローバル変数の更新
	GlobalVariables::GetInstance()->Update();

	//シーンの更新
	sceneManager_->Update();

	//ImGuiの受付終了
	imguiManager_->End();
}

void EngineCore::Draw() {
	//描画前処理
	graphicsCore_->PreDraw();

	//シーンの描画
	sceneManager_->Draw();

	//スプライトの描画
	sceneManager_->DrawUI();

	//ImGuiの描画
	imguiManager_->Draw();

	//描画後処理
	graphicsCore_->PostDraw();
}

bool EngineCore::IsEndRequest() {
	//終了リクエストを取得
	bool endRequest = application_->ProcessMessage();
	return endRequest;
}

void EngineCore::Run() {
	//初期化
	Initialize();

	//ゲームループ
	while (true) {
		//ゲームループを抜ける
		if (IsEndRequest()) {
			break;
		}

		//更新
		Update();

		//描画
		Draw();
	}

	//終了処理
	Finalize();
}