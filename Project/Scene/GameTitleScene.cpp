#include "GameTitleScene.h"
#include "Engine/Framework/Scene/SceneManager.h"
#include "GamePuzzleScene.h"

void GameTitleScene::Initialize() {
	//レンダラーのインスタンスを取得
	renderer_ = Renderer::GetInstance();

	//インプットのインスタンスを取得
	input_ = Input::GetInstance();

	//Audioのインスタンスを取得
	audio_ = Audio::GetInstance();

	GamePuzzleScene::form = 0;

	titleTextureHandle_ = TextureManager::Load("Project/Resources/Images/titles.png");
	titleSprite_.reset(Sprite::Create(titleTextureHandle_, { 0.0f,0.0f }));

	soundHandle_[0] = audio_->SoundLoadWave("Project/Resources/Sounds/bgm.wav");
	soundHandle_[1] = audio_->SoundLoadWave("Project/Resources/Sounds/select.wav");
	audio_->SoundPlayWave(soundHandle_[0], true, 1.0f);
}

void GameTitleScene::Finalize() {

}

void GameTitleScene::Update() {

	if (input_->IsControllerConnected())
	{
		if (input_->IsPressButtonEnter(XINPUT_GAMEPAD_A))
		{
			/*audio_->StopAudio(soundHandle_[0]);*/
			audio_->SoundPlayWave(soundHandle_[1], false, 1.0f);
			sceneManager_->ChangeScene("StageSelectScene");
		}
	}

	if (input_->IsPushKeyEnter(DIK_SPACE))
	{
		/*audio_->StopAudio(soundHandle_[0]);*/
		audio_->SoundPlayWave(soundHandle_[1], false, 1.0f);
		sceneManager_->ChangeScene("StageSelectScene");
	}

	ImGui::Begin("Title");
	ImGui::Text("StageSelectScene : A Button or SPACE");
	ImGui::End();
}

void GameTitleScene::Draw() {
#pragma region モデルの描画処理

	//モデルの描画
	renderer_->Render();

#pragma endregion

#pragma region パーティクルの描画処理

	renderer_->PreDrawParticles();

	renderer_->PostDrawParticles();

#pragma endregion
}

void GameTitleScene::DrawUI() {
#pragma region スプライトの描画

	//スプライト描画
	renderer_->PreDrawSprites(Renderer::kBlendModeNormal);

	titleSprite_->Draw();

	renderer_->PostDrawSprites();

#pragma endregion
}