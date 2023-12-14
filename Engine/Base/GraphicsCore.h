#pragma once
#include "Engine/Base/Application.h"
#include "Engine/Base/Heap/RTVHeap.h"
#include "Engine/Base/Heap/DSVHeap.h"
#include "Engine/Base/Buffer/ColorBuffer.h"
#include "Engine/Base/Buffer/DepthStencilResource.h"
#include <chrono>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <memory>
#include <wrl.h>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"winmm.lib")

class GraphicsCore {
public:
	//Descrioptorの最大数
	static const int kNumRTVDescriptors_ = 2;
	static const int kNumDSVDescriptors_ = 1;

	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns></returns>
	static GraphicsCore* GetInstance();

	/// <summary>
	/// シングルトンインスタンスの削除
	/// </summary>
	static void DeleteInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// レンダーターゲットをクリア
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// デプスバッファのクリア
	/// </summary>
	void ClearDepthBuffer();

	/// <summary>
	/// 状態遷移
	/// </summary>
	/// <param name="resource"></param>
	/// <param name="currentState"></param>
	/// <param name="newState"></param>
	void TransitionResource(const Microsoft::WRL::ComPtr<ID3D12Resource>& resource, D3D12_RESOURCE_STATES currentState, D3D12_RESOURCE_STATES newState);

	/// <summary>
	/// デバイスの取得
	/// </summary>
	/// <returns></returns>
	ID3D12Device* GetDevice() const { return device_.Get(); };

	/// <summary>
	/// コマンドリストを取得
	/// </summary>
	/// <returns></returns>
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList_.Get(); };

private:
	GraphicsCore() = default;
	~GraphicsCore() = default;
	GraphicsCore(const GraphicsCore&) = delete;
	GraphicsCore& operator=(const GraphicsCore&) = delete;

	/// <summary>
	/// DXGIデバイスの作成
	/// </summary>
	void CreateDevice();

	/// <summary>
	/// コマンド関連の作成
	/// </summary>
	void CreateCommand();

	/// <summary>
	/// スワップチェーンの作成
	/// </summary>
	void CreateSwapChain();

	/// <summary>
	/// フェンスの作成
	/// </summary>
	void CreateFence();

	/// <summary>
	/// ディスクリプタヒープの作成
	/// </summary>
	void CreateDescriptorHeaps();

	/// <summary>
	/// スワップチェーンのリソースとRTVの作成
	/// </summary>
	void CreateSwapChainResourcesAndViews();

	/// <summary>
	/// 深度テクスチャとDSVの作成
	/// </summary>
	void CreateDepthBufferAndView();

	/// <summary>
	/// FPS固定初期化
	/// </summary>
	void InitializeFixFPS();

	/// <summary>
	/// FPS固定更新
	/// </summary>
	void UpdateFixFPS();

private:
	//インスタンス
	static GraphicsCore* instance;

	//ウィンドウズアプリケーション
	Application* app_ = nullptr;

	//DXGIファクトリー
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_ = nullptr;

	//アダプタ
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter_ = nullptr;

	//デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device_ = nullptr;

	//コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_ = nullptr;

	//コマンドアロケーター
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_ = nullptr;

	//コマンドリスト
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_ = nullptr;

	//スワップチェーン
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_ = nullptr;

	//フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_ = nullptr;

	//フェンスの値
	uint64_t fenceValue_{};

	//RTV用のヒープ
	std::unique_ptr<DescriptorHeap> rtvDescriptorHeap_ = nullptr;

	//DSV用のヒープ
	std::unique_ptr<DescriptorHeap> dsvDescriptorHeap_ = nullptr;

	//スワップチェーン用のリソース
	std::unique_ptr<GpuResource> swapChainResources_[2] = { nullptr };

	//深度用のリソース
	std::unique_ptr<GpuResource> depthStencilResource_ = nullptr;

	//記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_{};
};

