#pragma once
#include "Engine/Framework/Scene/IScene.h"
#include "Engine/Components/Input.h"
#include "Engine/3D/Camera/Camera.h"

#include "Project/GameObject/Puzzle/Puzzle.h"

class GamePuzzleScene : public IScene {
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

	Camera camera_;

	std::unique_ptr<Model> puzzleModel_ = nullptr;
	std::unique_ptr<Puzzle> puzzle_;
};

