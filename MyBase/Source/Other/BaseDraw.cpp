#include "MyBase/Include/Other/BaseDraw.h"

using namespace BaseStruct;

// スクリーン座標系


// ゲットスクリーン座標関数
// 返り値：スクリーンの座標（Point）
// 引数：無し
// スクリーンの座標をそのまま受け取る関数
Point BaseDraw::GetScreenPosition() {
	return screenPosition;
}

// セットスクリーン座標関数
// 返り値：無し
// 引数：
// setPosition ... セットする座標
// スクリーンの座標をセットする関数
void BaseDraw::SetScreenPosition(Point setPosition) {
	screenPosition = setPosition;
}

// ワールド座標をスクリーン座標にして返す関数
// 返り値：変換されたスクリーン座標
// 引数：
// worldPosition ... ワールド座標
// ワールド座標をスクリーン座標に変換したいときに使う関数
Point BaseDraw::WorldtoScreen(Point worldPosition) {
	return { worldPosition.x - screenPosition.x, (worldPosition.y - screenPosition.y) * -1 };
}

// スクリーン座標をワールド座標にして返す関数
// 返り値：変換されたワールド座標
// 引数：
// screenPosition ... スクリーン座標
// スクリーン座標をワールド座標に変換したいときに使う関数
Point BaseDraw::ScreentoWorld(Point _screenPosition) {
	return { _screenPosition.x + screenPosition.x, _screenPosition.y * -1 + screenPosition.y };
}

// フルスクリーンモードを切り替える関数
// 返り値：なし
// 引数：なし
void BaseDraw::ChangeFullScreen() {
	if (isFullScreen) {
		Novice::SetWindowMode(kWindowed);
		isFullScreen = false;
	}
	else {
		Novice::SetWindowMode(kFullscreen);
		isFullScreen = true;
	}
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
void BaseDraw::DrawSprite(Point worldPosition, int textureHandle, Point scale, float angle, unsigned int color) {
	Point screenPos = WorldtoScreen(worldPosition);
	Novice::DrawSprite(screenPos.x, screenPos.y, textureHandle, scale.x, scale.y, angle, color);
}

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
void BaseDraw::DrawQuad(Point worldPosition, int textureHandle, Point textureSize, float scale, float angle, unsigned int color) {

	// 四つ角を求める
	Quad quad = {
		-textureSize.x / 2.0f * scale,
		-textureSize.y / 2.0f * scale,
		+textureSize.x / 2.0f * scale,
		-textureSize.y / 2.0f * scale,
		-textureSize.x / 2.0f * scale,
		+textureSize.y / 2.0f * scale,
		+textureSize.x / 2.0f * scale,
		+textureSize.y / 2.0f * scale
	};

	// 回転
	quad = BaseMath::TurnBox(quad, angle);
	// スクリーン座標に
	quad.q1 = WorldtoScreen({ quad.q1.x + worldPosition.x, quad.q1.y + worldPosition.y });
	quad.q2 = WorldtoScreen({ quad.q2.x + worldPosition.x, quad.q2.y + worldPosition.y });
	quad.q3 = WorldtoScreen({ quad.q3.x + worldPosition.x, quad.q3.y + worldPosition.y });
	quad.q4 = WorldtoScreen({ quad.q4.x + worldPosition.x, quad.q4.y + worldPosition.y });

	// 描画
	Novice::DrawQuad(
		quad.q1.x, quad.q1.y,
		quad.q2.x, quad.q2.y,
		quad.q3.x, quad.q3.y,
		quad.q4.x, quad.q4.y,
		0, 0,
		textureSize.x, textureSize.y,
		textureHandle,
		color
	);
}


//////////////////////////////////
/* - staticメンバ変数の実態を宣言 - */
//////////////////////////////////

// 現在のロード率
Point BaseDraw::screenPosition;
bool BaseDraw::isFullScreen = false;