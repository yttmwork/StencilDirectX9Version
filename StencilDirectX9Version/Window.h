#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>

/**
* @brief ウィンドウ初期化関数
* 引き数の内容でウィンドウを初期化し、表示する
* @return 初期化の成否 成功(true)
* @param[in] app_handle アプリケーションのハンドル
* @param[in] title タイトルの名前
* @param[in] width ウィンドウの横幅
* @param[in] height ウィンドウの縦幅
*/
bool InitializeWindow(HINSTANCE app_handle, const char* title, int width, int height);

/** ウィンドウハンドルのゲッター */
HWND GetWindowHandle();
/** アプリケーションハンドルのゲッター */
HINSTANCE GetAppHandle();

#endif
