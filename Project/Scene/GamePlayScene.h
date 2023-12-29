#pragma once
#include "Engine/Framework/Scene/IScene.h"
#include "Engine/Framework/Object/GameObjectManager.h"
#include "Engine/Base/Renderer.h"
#include "Engine/Components/Input.h"
#include "Project/Player/PlayerManager.h"

#include "Project/GameObject/StageObject/StageObject.h"
#include "Engine/Components/CollisionManager/CollisionManager.h"

class GamePlayScene : public IScene {
public:
	//ステージの番号
	static int stageNum;

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
	//レンダラー
	Renderer* renderer_ = nullptr;

	//衝突マネージャー
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;

	std::unique_ptr<Model> stageObjectModel_;
	std::unique_ptr<StageObject> stageObject_[3];
};

