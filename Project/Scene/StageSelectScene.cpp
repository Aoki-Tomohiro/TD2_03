#include "StageSelectScene.h"
#include "Engine/Framework/Scene/SceneManager.h"
#include "Engine/Base/TextureManager.h"
#include "Project/Scene/GamePlayScene.h"

void StageSelectScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();

	//インプットのインスタンスを取得
	input_ = Input::GetInstance();

	//Audioのインスタンスを取得
	audio_ = Audio::GetInstance();

	//スプライトの生成
	for (uint32_t i = 0; i < stages_.size(); i++) {
		stages_[i].num = i;
	}
	stages_[0].position = { 254.0f,226.0f };
	stages_[1].position = { 636.0f,226.0f };
	stages_[2].position = { 1018.0f,226.0f };
	stages_[3].position = { 254.0f,506.0f };
	stages_[4].position = { 636.0f,506.0f };
	stages_[5].position = { 1018.0f,506.0f };

	//背景のスプライトの生成
	backGroundTexture_ = TextureManager::Load("Project/Resources/Images/select.png");
	backGroundSprite_.reset(Sprite::Create(backGroundTexture_, { 0.0f,0.0f }));

	//カーソルのスプライトの生成
	cursorTextureHandle_ = TextureManager::Load("Project/Resources/Images/Cursor.png");
	cursorSprite_.reset(Sprite::Create(cursorTextureHandle_, cursorPosition_));
	cursorSprite_->SetAnchorPoint({ 0.5f,0.5f });

	soundHandle_ = audio_->SoundLoadWave("Project/Resources/Sounds/select.wav");
}

void StageSelectScene::Finalize() {

}

void StageSelectScene::Update() {
	if (!isCursorMovementEnabled_) {
		const uint32_t kEnableTime = 15;
		if (++cursorMovementEnableTimer_ >= kEnableTime) {
			isCursorMovementEnabled_ = true;
			cursorMovementEnableTimer_ = 0;
		}
	}

	if (input_->IsControllerConnected())
	{
		bool isSelect = false;

		const float threshold = 0.8f;

		Vector3 stickTilt{
			input_->GetLeftStickX(),
			input_->GetLeftStickY(),
			0.0f
		};

		if (Length(stickTilt) > threshold) {
			if (isCursorMovementEnabled_) {
				//左右にカーソルを動かす
				if (stickTilt.x < -threshold) {
					cursorPosition_.x -= cursorVelocity_.x;
					isCursorMovementEnabled_ = false;
				}
				else if (stickTilt.x > threshold) {
					cursorPosition_.x += cursorVelocity_.x;
					isCursorMovementEnabled_ = false;
				}

				//上下にカーソルを動かす
				if (stickTilt.y < -threshold) {
					cursorPosition_.y += cursorVelocity_.y;
					isCursorMovementEnabled_ = false;
				}
				else if (stickTilt.y > threshold) {
					cursorPosition_.y -= cursorVelocity_.y;
					isCursorMovementEnabled_ = false;
				}
			}
		}

		//ステージを選択する
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A)) {
			for (Stage& stage : stages_) {
				if (cursorPosition_.x == stage.position.x && cursorPosition_.y == stage.position.y) {
					GamePlayScene::stageNum = stage.num;
					audio_->SoundPlayWave(soundHandle_, false, 1.0f);
					sceneManager_->ChangeScene("GamePlayScene");
				}
			}
		}
	}

	//キーボード操作
	if (input_->IsPushKeyEnter(DIK_A)) {
		cursorPosition_.x -= cursorVelocity_.x;
		isCursorMovementEnabled_ = false;
	}
	else if (input_->IsPushKeyEnter(DIK_D))
	{
		cursorPosition_.x += cursorVelocity_.x;
		isCursorMovementEnabled_ = false;
	}

	if (input_->IsPushKeyEnter(DIK_S)) {
		cursorPosition_.y += cursorVelocity_.y;
		isCursorMovementEnabled_ = false;
	}
	else if (input_->IsPushKeyEnter(DIK_W)) {
		cursorPosition_.y -= cursorVelocity_.y;
		isCursorMovementEnabled_ = false;
	}

	//ステージを選択する
	if (input_->IsPushKeyEnter(DIK_SPACE)) {
		for (Stage& stage : stages_) {
			if (cursorPosition_.x == stage.position.x && cursorPosition_.y == stage.position.y) {
				GamePlayScene::stageNum = stage.num;
				audio_->SoundPlayWave(soundHandle_, false, 1.0f);
				sceneManager_->ChangeScene("GamePlayScene");
			}
		}
	}

	const float kPosMinX = 254.0f;
	const float kPosMaxX = 1018.0f;
	const float kPosMinY = 226.0f;
	const float kPosMaxY = 506.0f;
	cursorPosition_.x = std::clamp(cursorPosition_.x, kPosMinX, kPosMaxX);
	cursorPosition_.y = std::clamp(cursorPosition_.y, kPosMinY, kPosMaxY);

	//スプライトの座標を設定
	cursorSprite_->SetPosition(cursorPosition_);

	ImGui::Begin("Select");
	ImGui::DragFloat2("CursorPosition", &cursorPosition_.x);
	ImGui::DragFloat2("CursorVelocity", &cursorVelocity_.x);
	ImGui::End();
}

void StageSelectScene::Draw() {

}

void StageSelectScene::DrawUI() {
#pragma region スプライトの描画
	renderer_->PreDrawSprites(Renderer::kBlendModeNormal);

	//背景スプライト
	backGroundSprite_->Draw();

	//カーソルのスプライトの描画
	cursorSprite_->Draw();

	renderer_->PostDrawSprites();

#pragma endregion
}