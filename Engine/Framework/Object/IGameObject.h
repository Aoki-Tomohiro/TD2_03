#pragma once
#include "Engine/3D/Model/Model.h"

class GameObjectManager;

class IGameObject {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~IGameObject() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera"></param>
	virtual void Draw(const Camera& camera);

	/// <summary>
	/// ローカル座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetTranslation() { return worldTransform_.translation_; };

	/// <summary>
	/// 角度を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetRotation() { return worldTransform_.rotation_; };

	/// <summary>
	/// スケールを取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetScale() { return worldTransform_.scale_; };

	/// <summary>
	/// クォータニオンを取得
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetQuaternion() { return worldTransform_.quaternion_; };

	/// <summary>
	/// モデルを取得
	/// </summary>
	/// <returns></returns>
	const Model* GetModel() const { return model_; };

	/// <summary>
	/// モデルを設定
	/// </summary>
	/// <param name="model"></param>
	void SetModel(Model* model) { model_ = model; };

	/// <summary>
	/// タグを取得
	/// </summary>
	/// <returns></returns>
	const std::string& GetTag() const { return tag_; };

	/// <summary>
	/// タグを設定
	/// </summary>
	/// <param name="name"></param>
	void SetTag(const std::string& tag) { tag_ = tag; };

	/// <summary>
	/// 描画フラグを取得
	/// </summary>
	/// <returns></returns>
	const bool GetIsVisible() const { return isVisible_; };

	/// <summary>
	/// 描画フラグを設定
	/// </summary>
	/// <param name="isVisible"></param>
	void SetIsVisible(bool isVisible) { isVisible_ = isVisible; };

	/// <summary>
	/// アクティブフラグを取得
	/// </summary>
	/// <returns></returns>
	const bool GetIsActive() const { return isActive_; };

	/// <summary>
	/// アクティブフラグを設定
	/// </summary>
	/// <param name="isActive"></param>
	void SetIsActive(bool isActive) { isActive_ = isActive; };

	/// <summary>
	/// 破壊フラグを取得
	/// </summary>
	/// <returns></returns>
	const bool GetIsDestroy() const  { return isDestroy_; };

	/// <summary>
	/// 破壊フラグを設定
	/// </summary>
	/// <param name="isDestroy"></param>
	void SetIsDestroy(bool isDestroy) { isDestroy_ = isDestroy; };

	/// <summary>
	/// ゲームオブジェクトマネージャーを設定
	/// </summary>
	/// <param name="gameObjectManager"></param>
	void SetGameObjectManager(GameObjectManager* gameObjectManager) { gameObjectManager_ = gameObjectManager; };

protected:
	//ゲームオブジェクトマネージャー
	GameObjectManager* gameObjectManager_ = nullptr;

	//ワールドトランスフォーム
	WorldTransform worldTransform_{};

	//モデル
	Model* model_ = nullptr;

	//タグ
	std::string tag_{};

	//描画フラグ
	bool isVisible_ = true;

	//アクティブフラグ
	bool isActive_ = true;

	//破壊フラグ
	bool isDestroy_ = false;
};

