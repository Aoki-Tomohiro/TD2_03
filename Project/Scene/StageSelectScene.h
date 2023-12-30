#pragma once
#include "Engine/Framework/Scene/IScene.h"
#include "Engine/Base/Renderer.h"
#include "Engine/Components/Input.h"
#include "Engine/Components/Audio.h"
#include "Engine/2D/Sprite.h"

class StageSelectScene : public IScene {
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
	//インプット
	Input* input_ = nullptr;

	//オーディオ
	Audio* audio_ = nullptr;

	//レンダラー
	Renderer* renderer_ = nullptr;
	
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//サウンドハンドル
	uint32_t soundHandle_ = 0u;

	//スプライト
	struct Stage {
		Vector2 position{};
		uint32_t num = 0;
	};
	std::array<Stage, 6> stages_{};

	//背景スプライトのスプライト
	uint32_t backGroundTexture_ = 0;
	std::unique_ptr<Sprite> backGroundSprite_ = nullptr;

	//カーソルのスプライト
	uint32_t cursorTextureHandle_ = 0;
	std::unique_ptr<Sprite> cursorSprite_ = nullptr;

	//カーソルの座標
	Vector2 cursorPosition_{ 254.0f,226.0f };
	Vector2 cursorVelocity_{ 382.0f,280.0f };

	//カーソルの移動のフラグ
	bool isCursorMovementEnabled_ = true;
	uint32_t cursorMovementEnableTimer_ = 0;
};

