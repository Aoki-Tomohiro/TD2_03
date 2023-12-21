#pragma once
#include "Engine/Framework/Scene/IScene.h"
#include "Engine/Components/Input.h"
#include "Project/Player/PlayerManager.h"

class GamePlayScene : public IScene {
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
	Camera camera_;
	//インプット
	Input* input_ = nullptr;

	//プレイヤー
	std::unique_ptr<PlayerManager> playerManager_ = nullptr;
	std::unique_ptr<Player> player_ = nullptr;
};

