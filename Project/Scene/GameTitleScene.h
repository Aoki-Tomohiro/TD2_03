#pragma once
#include "Engine/Framework/Scene/IScene.h"
#include "Engine/Framework/Object/GameObjectManager.h"
#include "Engine/Base/Renderer.h"
#include "Engine/Components/Input.h"
#include "Engine/Components/Audio.h"
#include "Engine/2D/Sprite.h"
#include "Engine/Base/TextureManager.h"

class GameTitleScene : public IScene {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	/// <summary>
	/// スプライト描画
	/// </summary>
	void DrawUI() override;

private:
	//レンダラー
	Renderer* renderer_ = nullptr;

	//TextureManager
	TextureManager* textureManager_ = nullptr;

	//インプット
	Input* input_ = nullptr;

	//オーディオ
	Audio* audio_ = nullptr;

	//サウンドハンドル
	uint32_t soundHandle_[2] = {};

	//タイトル用のスプライト
	std::unique_ptr<Sprite> titleSprite_ = nullptr;
	//タイトルのテクスチャ
	uint32_t titleTextureHandle_ = 0;
};

