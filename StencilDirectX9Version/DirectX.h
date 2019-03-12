#ifndef DIRECT_X_H_
#define DIRECT_X_H_

#include <d3d9.h>
#include <d3dx9.h>

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

/**
* @brief テクスチャ読み込み関数
* 指定されたファイル名のテクスチャを読み込む
* @return 読み込みの成否 成功(true)
* @param[in] file_name 読み込むファイル名(パス付き)
*/
bool LoadingTexture(const char* file_name);


/**
* @brief テクスチャ解放関数
* 指定されたファイル名のテクスチャを解放する
* @param[in] file_name 解放するテクスチャのファイル名(パス付き)
*/
void ReleaseTexture(const char* file_name);

/**
* @brief 全テクスチャ解放関数
* 全てのテクスチャを解放する
*/
void ReleaseAllTexture();

/**
* @brief テクスチャ描画
* 指定した座標にテクスチャを描画する
* @param[in] file_name 描画対象テクスチャ
* @param[in] x 描画位置(X)
* @param[in] y 描画位置(Y)
*/
void RenderingTexture(const char* file_name, float x, float y);

#endif

