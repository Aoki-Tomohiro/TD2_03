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
		stages_[i].sprite.reset(Sprite::Create(textureHandle_, { 0.0f,0.0f }));
		stages_[i].sprite->SetAnchorPoint({ 0.5f,0.5f });
		stages_[i].sprite->SetSize({ 64.0f,64.0f });
		stages_[i].num = i;
	}
	stages_[0].sprite->SetPosition({ 256.0f,212.0f });
	stages_[1].sprite->SetPosition({ 512.0f,212.0f });
	stages_[2].sprite->SetPosition({ 768.0f,212.0f });
	stages_[3].sprite->SetPosition({ 1024.0f,212.0f });
	stages_[4].sprite->SetPosition({ 256.0f,508.0f });
	stages_[5].sprite->SetPosition({ 512.0f,508.0f });
	stages_[6].sprite->SetPosition({ 768.0f,508.0f });
	stages_[7].sprite->SetPosition({ 1024.0f,508.0f });

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
			//左右にカーソルを動かす
			if (isCursorMovementEnabled_) {
				if (stickTilt.x < -threshold) {
					cursorPosition_.x -= 256.0f;
					isCursorMovementEnabled_ = false;
				}
				else if (stickTilt.x > threshold) {
					cursorPosition_.x += 256.0f;
					isCursorMovementEnabled_ = false;
				}

				//上下にカーソルを動かす
				if (stickTilt.y < -threshold) {
					cursorPosition_.y += 296.0f;
					isCursorMovementEnabled_ = false;
				}
				else if (stickTilt.y > threshold) {
					cursorPosition_.y -= 296.0f;
					isCursorMovementEnabled_ = false;
				}
			}
		}

		//ステージを選択する
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A)) {
			for (Stage& stage : stages_) {
				if (cursorPosition_.x == stage.sprite->GetPosition().x && cursorPosition_.y == stage.sprite->GetPosition().y) {
					GamePlayScene::stageNum = stage.num;
					audio_->SoundPlayWave(soundHandle_, false, 1.0f);
					sceneManager_->ChangeScene("GamePlayScene");
				}
			}
		}
	}

	const float kPosMinX = 256.0f;
	const float kPosMaxX = 1024.0f;
	const float kPosMinY = 212.0f;
	const float kPosMaxY = 508.0f;
	cursorPosition_.x = std::clamp(cursorPosition_.x, kPosMinX, kPosMaxX);
	cursorPosition_.y = std::clamp(cursorPosition_.y, kPosMinY, kPosMaxY);

	//スプライトの座標を設定
	cursorSprite_->SetPosition(cursorPosition_);

	ImGui::Begin("Select");
	ImGui::End();
}

void StageSelectScene::Draw() {

}

void StageSelectScene::DrawUI() {
#pragma region スプライトの描画
	renderer_->PreDrawSprites(Renderer::kBlendModeNormal);

	//スプライトの描画
	for (Stage& stage : stages_) {
		stage.sprite->Draw();
	}

	//カーソルのスプライトの描画
	cursorSprite_->Draw();

	renderer_->PostDrawSprites();

#pragma endregion
}