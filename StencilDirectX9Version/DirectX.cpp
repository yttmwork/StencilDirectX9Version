#include "DirectX.h"

extern const char* g_WindowClassName;

static LPDIRECT3D9	g_pD3DInterface;	// DirectXインターフェース
static LPDIRECT3DDEVICE9 g_pD3DDevice;

void StartRendering()
{
	g_pD3DDevice->Clear(0L,
		NULL,
		D3DCLEAR_TARGET,			// 初期化するバッファの種類
		D3DCOLOR_ARGB(255, 0, 0, 0),// フレームバッファの初期化色
		1.0f,						// Zバッファの初期値
		0);							// ステンシルバッファの初期値

	g_pD3DDevice->BeginScene();

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void FinishRendering()
{
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void ReleaseDirectX()
{
	if (g_pD3DDevice != nullptr)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = nullptr;
	}

	if (g_pD3DInterface != nullptr)
	{
		g_pD3DInterface->Release();
		g_pD3DInterface = nullptr;
	}
}

bool CreateInterface()
{
	// インターフェース作成
	g_pD3DInterface = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3DInterface == NULL)
	{
		// 作成失敗
		return false;
	}

	return true;
}

void SetUpPresentParameter(HWND window_handle, int widow_width, int window_height, D3DPRESENT_PARAMETERS *present_param)
{
	ZeroMemory(present_param, sizeof(D3DPRESENT_PARAMETERS));

	// バックバッファの数 => 1
	present_param->BackBufferCount = 1;
	// バックバッファのフォーマット => D3DFMT_UNKNOWN(フォーマットを知りません)
	present_param->BackBufferFormat = D3DFMT_X8R8G8B8;
	// ウィンドウモード設定 => 定数で切り替え
		// プレゼンテーションパラメータの設定
	// フルスクリーンかどうか
	present_param->Windowed = TRUE;

	// スワップエフェクト設定 => ディスプレイドライバ依存
	// スワップエフェクト => バックバッファとフロントバッファへの切り替え方法
	present_param->SwapEffect = D3DSWAPEFFECT_DISCARD;
}

bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS *present_param, HWND window_handle)
{
	// DirectDeviceの作成
	if (FAILED(g_pD3DInterface->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
		present_param,
		&g_pD3DDevice)))
	{
		return false;
	}

	return true;
}

bool CreateViewPort(D3DPRESENT_PARAMETERS *present_param)
{
	// ビューポートパラメータ
	D3DVIEWPORT9 view_port;

	// ビューポートの左上座標
	view_port.X = 0;
	view_port.Y = 0;
	// ビューポートの幅
	view_port.Width = present_param->BackBufferWidth;
	// ビューポートの高さ
	view_port.Height = present_param->BackBufferHeight;
	// ビューポート深度設定
	view_port.MinZ = 0.0f;
	view_port.MaxZ = 1.0f;

	// ビューポート設定
	if (FAILED(g_pD3DDevice->SetViewport(&view_port)))
	{
		return false;
	}

	return true;
}

bool InitializeDirectX()
{
	D3DPRESENT_PARAMETERS present_param;
	HWND window_handle = FindWindow(g_WindowClassName, nullptr);
	RECT client_rect;
	GetClientRect(window_handle, &client_rect);

	// プレゼントパラメータの設定
	SetUpPresentParameter(
			window_handle, 
			(client_rect.right - client_rect.left), 
			(client_rect.bottom - client_rect.top),
			&present_param);

	// インターフェース作成
	if (CreateInterface() == false)
	{
		// 作成失敗
		return false;
	}

	// デバイス作成
	if (CreateGraphicsDevice(&present_param, window_handle) == false)
	{
		return false;
	}

	if (CreateViewPort(&present_param) == false)
	{
		return false;
	}

	return true;
}
