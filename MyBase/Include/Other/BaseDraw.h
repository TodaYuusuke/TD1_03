#pragma once
#include "Base/Include/Define/BaseStruct.h"
#include "Base/Include/Other/BaseMath.h"

#include <Novice.h>

class BaseDraw {

public:


	// スクリーン座標関連


	// ゲットスクリーン座標関数
	// 返り値：スクリーンの座標（Point）
	// 引数：無し
	// スクリーンの座標をそのまま受け取る関数
	static Point GetScreenPosition();

	// セットスクリーン座標関数
	// 返り値：無し
	// 引数：
	// setPosition ... セットする座標
	// スクリーンの座標をセットする関数
	static void SetScreenPosition(Point setPosition);

	// ワールド座標をスクリーン座標にして返す関数
	// 返り値：変換されたスクリーン座標
	// 引数：
	// worldPosition ... ワールド座標
	// ワールド座標をスクリーン座標に変換したいときに使う関数
	static Point WorldtoScreen(Point worldPosition);

	// スクリーン座標をワールド座標にして返す関数
	// 返り値：変換されたワールド座標
	// 引数：
	// screenPosition ... スクリーン座標
	// スクリーン座標をワールド座標に変換したいときに使う関数
	static Point ScreentoWorld(Point _screenPosition);

	// フルスクリーンモードを切り替える関数
	// 返り値：なし
	// 引数：なし
	static void ChangeFullScreen();



	// イージング関数
	// 返り値：結果
	// 引数：
	// t ... 現在のタイム値(秒)
	// b ... プロパティの初めの値
	// c ... プロパティの初めの値と終わりの値との差(変化量)
	// d ... アニメーションの時間（秒）
	static float Linear(float t, float  b, float  c, float  d) {
		return c * t / d + b;
	};
	// イージング関数
	// 返り値：結果
	// 引数：
	// t ... 現在のタイム値(秒)
	// b ... プロパティの初めの値
	// c ... プロパティの初めの値と終わりの値との差(変化量)
	// d ... アニメーションの時間（秒）
	static float Ease_In(float t, float b, float c, float d) {
		t /= d;
		return c * t * t + b;
	}
	// イージング関数
	// 返り値：結果
	// 引数：
	// t ... 現在のタイム値(秒)
	// b ... プロパティの初めの値
	// c ... プロパティの初めの値と終わりの値との差(変化量)
	// d ... アニメーションの時間（秒）
	static float Ease_Out(float t, float b, float c, float d) {
		t /= d;
		return -c * t * (t - 2.0) + b;
	}
	// イージング関数
	// 返り値：結果
	// 引数：
	// t ... 現在のタイム値(秒)
	// b ... プロパティの初めの値
	// c ... プロパティの初めの値と終わりの値との差(変化量)
	// d ... アニメーションの時間（秒）
	static float Ease_InOut(float t, float b, float c, float d) {
		return -c / 2.0 * (cosf(M_PI * t / d) - 1) + b;
	}



	// 各種描画関数のワールド座標対応Ver


	// ワールド座標からスプライトを描画する関数（DrawSprite）
	// 返り値：無し
	// 引数：
	// worldPosition ... 描画するスプライトの左上座標
	// textureHandle ... テクスチャのハンドル
	// scale ... 描画するスプライトの倍率
	// angle ... 描画するスプライトの回転角（Degree）
	// color ... 描画するスプライトの色
	// ワールド座標のまま呼び出せる描画関数（DrawSprite）
	static void DrawSprite(Point worldPosition, int textureHandle, Point scale, float angle, unsigned int color);

	// ワールド座標からスプライトを描画する関数（DrawQuad）
	// 返り値：無し
	// 引数：
	// worldPosition ... 描画するスプライトの中心座標
	// textureHandle ... テクスチャのハンドル
	// textureSize ... テクスチャのサイズ
	// scale ... 描画するスプライトの倍率
	// angle ... 描画するスプライトの回転角（Degree）
	// color ... 描画するスプライトの色
	// ワールド座標のまま呼び出せる描画関数（DrawQuad）
	static void DrawQuad(Point worldPosition, int textureHandle, Point textureSize, float scale, float angle, unsigned int color);


private:

	// スクリーン座標
	static Point screenPosition;
	// 現在フルスクリーンかどうか
	static bool isFullScreen;
};