#include "GameObjectManager.h"

//実体定義
GameObjectManager* GameObjectManager::instance_ = nullptr;

GameObjectManager* GameObjectManager::GetInstance() {
	if (instance_ == nullptr) {
		instance_ = new GameObjectManager();
	}
	return instance_;
}

void GameObjectManager::DeleteInstance() {
	delete instance_;
	instance_ = nullptr;
}

void GameObjectManager::Initialize() {
	//ゲームオブジェクトをクリア
	gameObjects_.clear();
}

void GameObjectManager::Update() {
	//破壊フラグが立ったゲームオブジェクトを削除
	std::vector<std::unique_ptr<IGameObject>>::iterator it = std::remove_if(gameObjects_.begin(), gameObjects_.end(), [](std::unique_ptr<IGameObject>& gameObject) {
		return gameObject->GetIsDestroy();
	});
	gameObjects_.erase(it, gameObjects_.end());

	//ゲームオブジェクトの更新
	for (std::unique_ptr<IGameObject>& gameObject : gameObjects_) {
		if (gameObject->GetIsActive()) {
			gameObject->Update();
		}
	}
}

void GameObjectManager::Draw(const Camera& camera) {
	for (std::unique_ptr<IGameObject>& gameObject : gameObjects_) {
		if (gameObject->GetIsVisible()) {
			gameObject->Draw(camera);
		}
	}
}

const IGameObject* GameObjectManager::GetGameObject(const std::string& tag) const {
	//ゲームオブジェクトを探す
	for (const std::unique_ptr<IGameObject>& gameObject : gameObjects_) {
		if (gameObject->GetTag() == tag) {
			return gameObject.get();
		}
	}
	return nullptr;
}

const std::vector<IGameObject*> GameObjectManager::GetGameObjects(const std::string& tag) const {
	//ゲームオブジェクトを探す
	std::vector<IGameObject*> gameObjects{};
	for (const std::unique_ptr<IGameObject>& gameObject : gameObjects_) {
		if (gameObject->GetTag() == tag) {
			gameObjects.push_back(gameObject.get());
		}
	}
	return gameObjects;
}