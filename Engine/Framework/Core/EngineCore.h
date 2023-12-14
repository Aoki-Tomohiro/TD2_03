#pragma once
#include "Engine/Base/Application.h"
#include "Engine/Base/GraphicsCore.h"
#include "Engine/Base/TextureManager.h"
#include "Engine/Base/ImGuiManager.h"
#include "Engine/Base/Renderer.h"
#include "Engine/Components/Audio.h"
#include "Engine/Components/Input.h"
#include "Engine/Framework/Object/GameObjectManager.h"
#include "Engine/Framework/Scene/SceneManager.h"
#include "Engine/Framework/Scene/AbstractSceneFactory.h"
#include "Engine/Utilities/D3DResourceLeakChecker.h"
#include <memory>

class EngineCore {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~EngineCore() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 終了処理
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 終了リクエスト
	/// </summary>
	/// <returns></returns>
	virtual bool IsEndRequest();

	/// <summary>
	/// ゲームループ
	/// </summary>
	void Run();

protected:
	//リークチェッカー
	D3DResourceLeakChecker leakChecker_{};

	//Application
	Application* application_ = nullptr;

	//GraphicsCore
	GraphicsCore* graphicsCore_ = nullptr;

	//テクスチャマネージャー
	TextureManager* textureManager_ = nullptr;

	//ImGuiManager
	ImGuiManager* imguiManager_ = nullptr;

	//レンダラー
	Renderer* renderer_ = nullptr;

	//オーディオ
	Audio* audio_ = nullptr;

	//インプット
	Input* input_ = nullptr;

	//ゲームオブジェクトマネージャー
	GameObjectManager* gameObjectManager_ = nullptr;

	//シーンマネージャー
	SceneManager* sceneManager_ = nullptr;

	//シーンファクトリー
	std::unique_ptr<AbstractSceneFactory> sceneFactory_ = nullptr;
};

