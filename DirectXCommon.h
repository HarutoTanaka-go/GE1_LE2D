#pragma once
#include "WinApp.h"
#include "StringUtility.h"
#include <cstdint>
#include <array>
#include <string>
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

//DirectX基盤
class DirectXCommon
{
public:
	//初期化
	void Initialize(WinApp* winApp);

	//デバイスの生成
	void CreateDevice();

	//コマンド周りの生成
	void CreateCommand();

	//スワップチェインの生成
	void CreateSwapChain();

	//ディスクリプタヒープの生成
	void CreateDescriptor();

	//DSVの生成
	void CreateDSV();

	//RTVの生成
	void CreateRTV();

	//Fenceの生成
	void CreateFence();

	//深度バッファの生成
	void CreateDepth();

	//ビューポート矩形の初期化
	void CreateViewport();

	//シザリング矩形の初期化
	void CreateScissorRect();

	//ImGuiの初期化
	void CreateImGui();


	//描画開始
	void PreDraw();
	//描画終了
	void PostDraw();

	/// <summary>
	/// デスクリプタヒープを生成
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	ID3D12Resource* CreateDepthStencilTextureResource(int32_t width, int32_t height);

	/// <summary>
	/// SRVの指定番号のCPUデスクリプタハンドルを取得する
	/// </summary>
	//D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);

	/// <summary>
	/// SRVの指定番号のGPUデスクリプタハンドルを取得する
	/// </summary>
	//D3D12_CPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	////getter
	//ID3D12Device* GetDevice() const { return device.Get(); }
	//ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }



	//スワップチェーンリソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources{};

	////シェーダーのコンパイル
	//Microsoft::WRL::ComPtr<ID

private:

	HRESULT hr;

	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;



	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	ID3D12GraphicsCommandList* commandList = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	IDXGISwapChain4* swapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	ID3D12PipelineState* graphicsPipelineState = nullptr;


	/*Microsoft::WRL::ComPtr<ID3D12Fence> fence;*/

	D3D12_RESOURCE_BARRIER barrier{};

	ID3D12Fence* fence;

	//WindowsAPI
	WinApp* winApp = nullptr;

	//ディスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap = nullptr;

	uint32_t rtvDescriptorSize = 0;
	uint32_t srvDescriptorSize = 0;
	uint32_t dsvDescriptorSize = 0;


	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//RTVを2つ作るのでディスクリプタを２つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2]{};

	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;

	D3D12_VIEWPORT viewport{};

	D3D12_RECT scissorRect{};

	HANDLE fenceEvent;

	uint64_t fenceValue = 0;

	//頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};

	ID3D12Resource* depthStencilResource;

	//使用するアダプタ用の変数。最初にnullptrを入れておく
	IDXGIAdapter4* useAdapter = nullptr;
	//DXGIファクトリーの作成
	//IDXGIFactory7* dxgiFactory = nullptr;

	ID3D12Debug1* debugController = nullptr;

	/// <summary>
	/// 指定番号のCPUデスクリプタハンドルを取得する
	/// </summary>
	//static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descripHeap, uint32_t descriptorSize, uint32_t index);

	/// <summary>
	/// 指定番号のGPUデスクリプタハンドルを取得する
	/// </summary>
	//static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descripHeap, uint32_t descriptorSize, uint32_t index);



};
