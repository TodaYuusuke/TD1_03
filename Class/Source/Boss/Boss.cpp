#include "Class/Include/Boss/Boss.h"

/*********************************
	ボスクラス
*********************************/

// コンストラクタ
Boss::Boss() {
	Boss::Initialize();
}

// デストラクタ
Boss::~Boss() {

}

// 初期化処理
void Boss::Initialize() {
	// ボスの位置を画面中央に持っていく
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	// ボスの画像サイズを設定
	this->textureSize = { 225.0f, 450.0f };

	// 核の位置を設定
	kernelCenterPosition = centerPosition;
	// 核の画像サイズを設定
	kernelTextureSize = { 256.0f, 256.0f };
}

// 更新処理
void Boss::Update(Point playerPosition) {

	/******** デバック処理 **********/
	// すべてをリセットする
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		offset = 0.0f;
		degree = 0;
	}

	// ボスを左右に開かせる
	if (BaseInput::GetKeyboardState(DIK_I, Press))
		offset += 1.0f;

	else if (BaseInput::GetKeyboardState(DIK_K, Press))
		offset-= 1.0f;

	// オフセットが指定の値以下になると0にする
	if (offset < 0) {
		offset = 0;
	}

	// ボスを回転させる
	if (BaseInput::GetKeyboardState(DIK_L, Press))
		degree++;

	else if (BaseInput::GetKeyboardState(DIK_J, Press))
		degree--;

	// 核が分離していない状態では核をボスに追従させる
	if (kernelSeparated == false) {
		kernelCenterPosition = centerPosition;
	}

}

// 描画処理
void Boss::Draw() {
	// ボス核画像
	BaseDraw::DrawQuad(
		kernelCenterPosition,
		BaseTexture::kBossKernel,
		kernelTextureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	// ボス左側画像
	BaseDraw::DrawQuad(
		Boss::GetLCoverPosition(centerPosition),
		BaseTexture::kBossLCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	// ボス右側画像
	BaseDraw::DrawQuad(
		Boss::GetRCoverPosition(centerPosition),
		BaseTexture::kBossRCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);
}

// ボス左画像の相対座標を求める
Point Boss::GetLCoverPosition(Point centerPosition) { 
	// 回転中心からの差異ベクトル作成
	Point p = { -textureSize.x / 2 - offset, 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}
//ボス右画像の相対座標を求める
Point Boss::GetRCoverPosition(Point centerPosition) { 
	// 回転中心からの差異ベクトル作成
	Point p = { textureSize.x / 2 + offset, 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}