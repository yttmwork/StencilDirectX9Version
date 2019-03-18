#ifndef GAME_H_
#define GAME_H_

/**
* @brief Character更新関数
* キャラクターの絵を切り替えるための更新処理を行う
*/
void UpdateCharacter();

/** キャラクター描画関数 */
void RenderingCharacter();
/** 
* @brief キャラクターの影描画関数
* キャラクターの影を描画する
* 描画方法は頂点カラーを黒にしているだけ
*/
void RenderingCharacterShadow();

/** 背景描画 */
void RenderingBg();

/** 
* @brief マップチップ描画
* マップチップは単体ではなく、特定の位置から縦～列、横～行となるように複数描画している
*/
void RenderingMapChip();

#endif
