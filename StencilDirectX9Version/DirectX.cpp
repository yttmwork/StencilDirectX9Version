#include <map>
#include "DirectX.h"

typedef struct
{
	LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャデータ
	int m_Width;					// 横幅
	int m_Height;					// 縦幅
} TEXTURE_DATA;

typedef struct
{
	D3DXVECTOR4 m_Pos;			// 座標(w込み)
	DWORD m_Color;				// 色
	D3DXVECTOR2 m_TextureUV;	// tutv
} CUSTOM_VERTEX;

const DWORD RenderingFVF = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

extern const char* g_WindowClassName;

static LPDIRECT3D9	g_pD3DInterface;					// DirectXインターフェース
static LPDIRECT3DDEVICE9 g_pD3DDevice;					// DirectXDevice
std::map<const char*, TEXTURE_DATA*> g_TextureList;		// テクスチャ格納用配列

bool LoadingTexture(const char* file_name)
{
	if (g_TextureList.count(file_name) == 1)
	{
		return true;
	}

	g_TextureList[file_name] = new TEXTURE_DATA();

	D3DXIMAGE_INFO info;
	// 2の階乗じゃないので元のサイズを取得してD3DXCreateTextureFromFileExで使う
	D3DXGetImageInfoFromFile(file_name, &info);
	
	if (FAILED( D3DXCreateTextureFromFileEx(g_pD3DDevice,
										file_name,
										info.Width,
										info.Height,
										1,
										0,
										D3DFMT_UNKNOWN,
										D3DPOOL_MANAGED,
										D3DX_DEFAULT,
										D3DX_DEFAULT,
										0x0000ff00,
										nullptr,
										nullptr,
										&g_TextureList[file_name]->m_pTexture)))
	{
		return false;
	} 
	else
	{
		// テクスチャサイズの取得
		D3DSURFACE_DESC desc;

		if( FAILED( g_TextureList[file_name]->m_pTexture->GetLevelDesc( 0, &desc ) ))
		{
			g_TextureList[file_name]->m_pTexture->Release();
			g_TextureList[file_name]->m_pTexture = nullptr;
			return false;
		}
		g_TextureList[file_name]->m_Width = desc.Width;
		g_TextureList[file_name]->m_Height = desc.Height;
	}

	return true;
}

void ReleaseTexture(const char* file_name)
{
	if (g_TextureList.count(file_name) == 0)
	{
		return;
	}

	if (g_TextureList[file_name]->m_pTexture != NULL)
	{
		g_TextureList[file_name]->m_pTexture->Release();
		TEXTURE_DATA *data = g_TextureList[file_name];
		g_TextureList.erase(file_name);
		delete(data);
	}
}

void ReleaseAllTexture()
{
	for (auto itr = g_TextureList.begin(); itr != g_TextureList.end(); itr++)
	{
		if (g_TextureList[itr->first] == nullptr)
		{
			continue;
		}
		g_TextureList[itr->first]->m_pTexture->Release();
		delete(g_TextureList[itr->first]);
	}
	g_TextureList.clear();
}

void RenderingTexture(const char* file_name, float x, float y)
{
	const TEXTURE_DATA* texture_data = g_TextureList[file_name];

	float left_tu = 0.0f;
	float right_tu = 1.0f;
	float top_tv = 0.0f;
	float bottom_tv = 0.0f;

	if (texture_data == nullptr ||
		texture_data->m_pTexture == nullptr)
	{
		return;
	}

	DWORD color = D3DCOLOR_ARGB(255, 255, 255, 255);

	// 三角形を描画 start
	CUSTOM_VERTEX v[4] = 
	{
		{ D3DXVECTOR4(x, y, 0.0f, 1.0f), color, D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR4(x + texture_data->m_Width, y, 0.0f, 1.0f), color, D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR4(x + texture_data->m_Width, y + texture_data->m_Height, 0.0f, 1.0f), color, D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR4(x, y + texture_data->m_Height, 0.0f, 1.0f), color, D3DXVECTOR2(0.0f, 1.0f) },
	};

	// 頂点構造の指定
	g_pD3DDevice->SetFVF(RenderingFVF);

	g_pD3DDevice->SetTexture(0, texture_data->m_pTexture);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(CUSTOM_VERTEX));
}

void StartRendering()
{
	g_pD3DDevice->Clear(
		0,
		nullptr,
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

	g_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
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
	if (g_pD3DInterface == nullptr)
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
