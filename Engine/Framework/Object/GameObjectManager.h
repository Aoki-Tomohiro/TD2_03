#pragma once
#include "IGameObject.h"
#include <vector>
#include <memory>

class GameObjectManager {
public:
	/// <summary>
	/// シングルトンインスタンスを取得
	/// </summary>
	/// <returns></returns>
	static GameObjectManager* GetInstance();

	/// <summary>
	/// シングルトンインスタンスを削除
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// モデルの描画
	/// </summary>
	/// <param name="camera"></param>
	void Draw(const Camera& camera);

	/// <summary>
	/// ゲームオブジェクトの作成
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <param name="name"></param>
	/// <returns></returns>
	template <typename Type>
	static Type* CreateGameObject();

	/// <summary>
	/// ゲームオブジェクトを取得
	/// </summary>
	/// <returns></returns>
	const IGameObject* GetGameObject(const std::string& tag) const;

	/// <summary>
	/// ゲームオブジェクトを取得
	/// </summary>
	/// <param name="tag"></param>
	/// <returns></returns>
	const std::vector<IGameObject*> GetGameObjects(const std::string& tag) const;

private:
	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(const GameObjectManager&) = delete;
	const GameObjectManager& operator=(const GameObjectManager&) = delete;

	/// <summary>
	/// ゲームオブジェクトを作成
	/// </summary>
	/// <typeparam name="Type"></typeparam>
	/// <param name="name"></param>
	/// <returns></returns>
	template <typename Type>
	Type* CreateGameObjectInternal();

private:
	//インスタンス
	static GameObjectManager* instance_;

	//ゲームオブジェクトの配列
	std::vector<std::unique_ptr<IGameObject>> gameObjects_{};
};

template <typename Type>
Type* GameObjectManager::CreateGameObject() {
	//ゲームオブジェクトを作成
	Type* newObject = GameObjectManager::GetInstance()->CreateGameObjectInternal<Type>();
	return newObject;
}

template <typename Type>
Type* GameObjectManager::CreateGameObjectInternal() {
	Type* newObject = new Type();
	newObject->Initialize();
	gameObjects_.push_back(std::unique_ptr<IGameObject>(newObject));
	return newObject;
}

