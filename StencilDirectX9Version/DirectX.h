﻿#ifndef DIRECT_X_H_
#define DIRECT_X_H_

#include <d3d9.h>

/**
* @brief DirectX初期化関数
* DirectX9の初期化処理を実行する
* @return 初期化の成否 成功(true)
*/
bool InitializeDirectX();

/**
* @brief 描画開始関数
* 描画処理はこの関数実行以降に実行すること
* ゲームループにつき１回実行する
*/
void StartRendering();

/**
* @brief 描画終了関数
* 描画処理を終了させる
* 必ずStartRenderingの後に実行する
*/
void FinishRendering();

/**
* @brief DirectX解放
* DirectXのデバイスなどを解放する
* ゲームループ終了後に実行させる
*/
void ReleaseDirectX();

#endif