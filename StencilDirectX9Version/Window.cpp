#include "Window.h"

const char* g_WindowClassName = "WindowClass";

static HWND g_WindowHandle = nullptr;		// ウィンドウハンドル
static HINSTANCE g_AppHandle = nullptr;		// ウィンドウプロシージャ

// ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam);

HWND GetWindowHandle()
{
	return g_WindowHandle;
}

HINSTANCE GetAppHandle()
{
	return g_AppHandle;
}

LRESULT CALLBACK WindowProc(HWND window_handle, UINT message_id, WPARAM wparam, LPARAM lparam)
{
	switch (message_id)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(window_handle, message_id, wparam, lparam);
		break;
	}

	return 0;
}

bool InitializeWindow(HINSTANCE app_handle, const char* title, int width, int height)
{
	g_AppHandle = app_handle;

	WNDCLASSEX window_class = {
		sizeof(WNDCLASSEX),									// 構造体のサイズ
		CS_HREDRAW | CS_VREDRAW,							// クラスのスタイル
		WindowProc,											// ウィンドウプロシージャ
		0,													// 補助メモリ
		0,													// 補助メモリ
		g_AppHandle,										// このプログラムのインスタンスハンドル
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),	// アイコン画像
		LoadCursor(NULL, IDC_ARROW),						// カーソル画像
		NULL,												// 背景ブラシ(背景色)
		NULL,												// メニュー名
		g_WindowClassName,									// クラス名									
		NULL												// 小さいアイコン
	};

	// 構造体の登録
	if (RegisterClassEx(&window_class) == 0)
	{
		return false;
	}

	// ウィンドウ作成
	g_WindowHandle = CreateWindow(
			g_WindowClassName,
			title,
			(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
			CW_USEDEFAULT,
			0,
			width,
			height,
			NULL,
			NULL,
			g_AppHandle,
			NULL);

	if (g_WindowHandle == nullptr)
	{
		return false;
	}

	RECT window_rect;
	RECT client_rect;

	GetWindowRect(g_WindowHandle, &window_rect);
	GetClientRect(g_WindowHandle, &client_rect);

	int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
	int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

	SetWindowPos(g_WindowHandle, NULL, CW_USEDEFAULT, 0, frame_size_x + width, frame_size_y + height, SWP_NOMOVE);

	ShowWindow(g_WindowHandle, SW_SHOW);
	UpdateWindow(g_WindowHandle);

	return true;
}
