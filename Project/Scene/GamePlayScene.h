#pragma once
#include "Engine/Framework/Scene/IScene.h"
#include "Engine/Framework/Object/GameObjectManager.h"
#include "Engine/Base/Renderer.h"
#include "Engine/2D/Sprite.h"
#include "Engine/Base/TextureManager.h"
#include "Engine/Components/Input.h"
#include "Engine/Components/Audio.h"
#include "Project/Player/PlayerManager.h"
#include "Engine/Components/CollisionManager/CollisionManager.h"

#include "Project/GameObject/StageObject/StageObject.h"
#include "Project/GameObject/Goal/Goal.h"
#include "Project/GameObject/Puzzle/PuzzleScenePortal.h"

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

	//衝突マネージャー
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;
	
	//TextureManager
	TextureManager* textureManager_ = nullptr;

	//インプット
	Input* input_ = nullptr;

	//オーディオ
	Audio* audio_ = nullptr;

	//プレイヤー
	std::unique_ptr<PlayerManager> playerManager_ = nullptr;
	std::unique_ptr<Player> player_ = nullptr;
	//レンダラー
	Renderer* renderer_ = nullptr;

	std::unique_ptr<Model> stageObjectModel_;
	std::unique_ptr<StageObject> stageObject_[4];

	std::unique_ptr<Model> puzzleScenePortalModel_;
	std::unique_ptr<PuzzleScenePortal> puzzleScenePortal_;

	std::unique_ptr<Model> goalModel_;
	std::unique_ptr<Goal> goal_;

	//サウンドハンドル
	uint32_t soundHandle_ = 0u;

	//タイトル用のスプライト
	std::unique_ptr<Sprite> backSprite_ = nullptr;
	//タイトルのテクスチャ
	uint32_t backTextureHandle_ = 0;

	//移動UI用のスプライト
	std::unique_ptr<Sprite> moveSprite_ = nullptr;
	//移動UIのテクスチャ
	uint32_t moveTextureHandle_ = 0;

	//ジャンプUI用のスプライト
	std::unique_ptr<Sprite> jumpSprite_ = nullptr;
	//ジャンプUIのテクスチャ
	uint32_t jumpTextureHandle_ = 0;
};

