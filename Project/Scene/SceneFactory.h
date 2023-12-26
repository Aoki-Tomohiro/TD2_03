#pragma once
#include "Engine/Framework/Scene/AbstractSceneFactory.h"
#include "Project/Scene/GameTitleScene.h"
#include "Project/Scene/StageSelectScene.h"
#include "Project/Scene/GamePlayScene.h"
#include "Project/Scene/GamePuzzleScene.h"
#include "Project/Scene/GameClearScene.h"
#include "Project/Scene/GameOverScene.h"

class SceneFactory : public AbstractSceneFactory {
public:
	/// <summary>
	/// シーンの作成
	/// </summary>
	/// <param name="sceneName"></param>
	/// <returns></returns>
	IScene* CreateScene(const std::string& sceneName) override;
};

