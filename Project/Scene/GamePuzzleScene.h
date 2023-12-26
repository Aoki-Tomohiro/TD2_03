#include "Engine/Framework/Scene/IScene.h"
#include "Engine/Framework/Object/GameObjectManager.h"
#include "Engine/Base/Renderer.h"
#include "Engine/Components/Input.h"
#include "Engine/3D/Camera/Camera.h"
#include "Engine/Components/CollisionManager/CollisionManager.h"

#include "Project/GameObject/Puzzle/Puzzle.h"
#include "Project/GameObject/Puzzle/PuzzlePlayer.h"

class GamePuzzleScene : public IScene {
public:
	static int form;

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

	//衝突マネージャー
	std::unique_ptr<CollisionManager> collisionManager_ = nullptr;

	//インプット
	Input* input_ = nullptr;

	Camera camera_;

	std::unique_ptr<Model> puzzleModel_[9];
	std::unique_ptr<Puzzle> puzzle_[9];

	std::unique_ptr<Model> puzzlePlayerModel_;
	std::unique_ptr<PuzzlePlayer> puzzlePlayer_;
};

