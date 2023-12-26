#pragma once
#include "Engine/Framework/Scene/IScene.h"
#include "Engine/Base/Renderer.h"
#include "Engine/Components/Input.h"
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

	//レンダラー
	Renderer* renderer_ = nullptr;
	
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//スプライト
	struct Stage {
		std::unique_ptr<Sprite> sprite = nullptr;
		uint32_t num = 0;
	};
	std::array<Stage, 8> stages_{};

	//カーソルのスプライト
	uint32_t cursorTextureHandle_ = 0;
	std::unique_ptr<Sprite> cursorSprite_ = nullptr;

	//カーソルの座標
	Vector2 cursorPosition_{ 256.0f,212.0f };

	//カーソルの移動のフラグ
	bool isCursorMovementEnabled_ = true;
	uint32_t cursorMovementEnableTimer_ = 0;
};

