#pragma once
#include "Engine/Base/PipelineState.h"
#include "Engine/Utilities/ShaderCompiler.h"
#include <algorithm>

class Renderer {
public:
	enum RootBindings {
		//マテリアル
		kMaterial,
		//ワールドトランスフォーム
		kWorldTransform,
		//カメラ
		kCamera,
		//テクスチャ
		kTexture,
		//ライト
		kDirectionalLight,
	};

	enum ModelRenderingType {
		//不透明
		Opaque,
		//透明
		Transparent,
		//利用してはいけない
		RenderingTypeCount
	};

	enum BlendMode {
		//ブレンドなし
		kBlendModeNone,
		//通常aブレンド
		kBlendModeNormal,
		//加算
		kBlendModeAdd,
		//減算
		kBlendModeSubtract,
		//乗算
		kBlendModeMultiply,
		//スクリーン
		kBlendModeScreen,
		//利用してはいけない
		kCountOfBlendMode,
	};

	/// <summary>
	/// シングルトンインスタンスを取得
	/// </summary>
	/// <returns></returns>
	static Renderer* GetInstance();

	/// <summary>
	/// シングルトンインスタンスを削除
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// SortObjectを追加
	/// </summary>
	/// <param name="vertexBufferView_"></param>
	/// <param name="materialCBV"></param>
	/// <param name="worldTransformCBV"></param>
	/// <param name="cameraCBV"></param>
	/// <param name="directionalLightCBV"></param>
	/// <param name="textureSRV"></param>
	/// <param name="type"></param>
	void AddObject(D3D12_VERTEX_BUFFER_VIEW vertexBufferView,
		D3D12_GPU_VIRTUAL_ADDRESS materialCBV,
		D3D12_GPU_VIRTUAL_ADDRESS worldTransformCBV,
		D3D12_GPU_VIRTUAL_ADDRESS cameraCBV,
		D3D12_GPU_VIRTUAL_ADDRESS directionalLightCBV,
		D3D12_GPU_DESCRIPTOR_HANDLE textureSRV,
		UINT vertexCount,
		ModelRenderingType type);

	/// <summary>
	/// ソート
	/// </summary>
	void Sort();

	/// <summary>
	/// 描画
	/// </summary>
	void Render();

	/// <summary>
	/// スプライト描画前処理
	/// </summary>
	void PreDrawSprites(BlendMode blendMode);

	/// <summary>
	/// スプライト描画後処理
	/// </summary>
	void PostDrawSprites();

	/// <summary>
	/// パーティクル描画前処理
	/// </summary>
	void PreDrawParticles();

	/// <summary>
	/// パーティクル描画後処理
	/// </summary>
	void PostDrawParticles();

private:
	Renderer() = default;
	~Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	/// <summary>
	/// モデル用のPSOを作成
	/// </summary>
	void CreateModelPipelineState();

	/// <summary>
	/// スプライト用のPSOを作成
	/// </summary>
	void CreateSpritePipelineState();

	/// <summary>
	/// パーティクル用のPSOを作成
	/// </summary>
	void CreateParticlePipelineState();

private:
	//SortObject構造体
	struct SortObject {
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
		D3D12_GPU_VIRTUAL_ADDRESS materialCBV;
		D3D12_GPU_VIRTUAL_ADDRESS worldTransformCBV;
		D3D12_GPU_VIRTUAL_ADDRESS cameraCBV;
		D3D12_GPU_VIRTUAL_ADDRESS directionalLightCBV;
		D3D12_GPU_DESCRIPTOR_HANDLE textureSRV;
		UINT vertexCount;
		ModelRenderingType type;
	};

	//インスタンス
	static Renderer* instance_;

	//コマンドリスト
	ID3D12GraphicsCommandList* commandList_ = nullptr;

	//ShaderCompiler
	std::unique_ptr<ShaderCompiler> shaderCompiler_ = nullptr;

	//RootSignature
	std::unique_ptr<RootSignature> modelRootSignature_ = nullptr;

	std::unique_ptr<RootSignature> spriteRootSignature_ = nullptr;

	std::unique_ptr<RootSignature> particleRootSignature_ = nullptr;

	//PipelineState
	std::vector<std::unique_ptr<PipelineState>> modelPipelineStates_{};

	std::vector<std::unique_ptr<PipelineState>> spritePipelineStates_{};

	std::vector<std::unique_ptr<PipelineState>> particlePipelineStates_{};

	//SortObject
	std::vector<SortObject> sortObjects_{};
};

