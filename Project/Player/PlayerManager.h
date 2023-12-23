#pragma once
#include "Player.h"


class PlayerManager{
public:
	void Initialize();
	void Update();
	void Draw(const Camera& camera);
	Vector3 GetPlayerPosition() { return player_->GetWorldPosition(); };

	


private:
	WorldTransform worldTransformBase_;
	std::unique_ptr <Model> Model_;
	std::unique_ptr<Player> player_;
	

	bool isDead_ = false;

};