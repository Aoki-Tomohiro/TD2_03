#include "DirectionalLight.h"

void DirectionalLight::Initialize() {
	//lightingResourceの作成
	lightingResource_ = std::make_unique<UploadBuffer>();
	lightingResource_->Create(sizeof(ConstBufferDataDirectionalLight));

	//lightingResourceに書き込む
	directionalLightData_ = static_cast<ConstBufferDataDirectionalLight*>(lightingResource_->Map());
	directionalLightData_->lightingMethod = lightingMethod_;
	directionalLightData_->enableLighting = enableLighting_;
	directionalLightData_->color = color_;
	directionalLightData_->direction = direction_;
	directionalLightData_->intensity = intensity_;
	lightingResource_->Unmap();
}

void DirectionalLight::Update() {
	//lightingResourceに書き込む
	directionalLightData_ = static_cast<ConstBufferDataDirectionalLight*>(lightingResource_->Map());
	directionalLightData_->lightingMethod = lightingMethod_;
	directionalLightData_->enableLighting = enableLighting_;
	directionalLightData_->color = color_;
	directionalLightData_->direction = direction_;
	directionalLightData_->intensity = intensity_;
	lightingResource_->Unmap();
}