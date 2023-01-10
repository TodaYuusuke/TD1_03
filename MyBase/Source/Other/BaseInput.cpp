#include "MyBase/Include/Other/BaseInput.h"


// 初期化
void BaseInput::Initialize() {

	// メンバ変数の初期化

	// マウス座標
	mousePosition = { 0,0 };

	// キー入力の初期化
	for (int i = 0; i < 256; i++) {
		keys[i] = { 0 };
		preKeys[i] = { 0 };
	}
}
// 更新
void BaseInput::Update() {

	// マウス座標を更新
	int x = 0, y = 0;
	Novice::GetMousePosition(&x, &y);
	mousePosition = { (float)x,(float)y };

	// キー入力を受け取る
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);

}
// 描画
void BaseInput::Draw() {

}



// マウス座標を受け取る関数
// 返り値：マウス座標のPoint
// 引数：無し
// マウスの座標をPoint型で受け取る関数
Point BaseInput::GetMousePosition() {
	return mousePosition;
}


// マウスの入力状態を受け取る関数
// 返り値：key が state の場合 -> true そうでない場合 -> false
// 引数：
// key ... 検証するキー
// state ... 検証したい状態
// 特定のキーがどんな状態（Null,Trigger,Press,Release）かをチェックする関数（Release未実装）
bool BaseInput::GetMouseState(MouseButton key, InputState state) {
	switch (state)
	{
		// 押されていない
		case Null:
			// 押されていない か検証
			if (!Novice::IsTriggerMouse(key) && !Novice::IsPressMouse(key)) {
				return true;
			}
			else {
				return false;
			}

		// 押された瞬間
		case Trigger:
			// 押された瞬間 か検証
			if (Novice::IsTriggerMouse(key)) {
				return true;
			}
			else {
				return false;
			}

		// 押しっぱなし
		case Press:
			// 押しっぱなし か検証
			if (Novice::IsPressMouse(key)) {
				return true;
			}
			else {
				return false;
			}

		// 離された瞬間
		case Release:
			// 離された瞬間 か検証
			
			// 未実装
		
		// エラー
		default:
			return false;
	}
}


// キーの入力状態を受け取る関数
// 返り値：key が state の場合 -> true そうでない場合 -> false
// 引数：
// key ... 検証するキー
// state ... 検証したい状態
// 特定のキーがどんな状態（Null,Trigger,Press,Release）かをチェックする関数
bool BaseInput::GetKeyboardState(int key, InputState state) {
	switch (state)
	{
		// 押されていない
		case Null:
			// 押されていない か検証
			if (!keys[key] && !preKeys[key]) {
				return true;
			}
			else {
				return false;
			}
			// 押された瞬間
		case Trigger:
			// 押された瞬間 か検証
			if (keys[key] && !preKeys[key]) {
				return true;
			}
			else {
				return false;
			}
			// 押しっぱなし
		case Press:
			// 押しっぱなし か検証
			if (keys[key]) {
				return true;
			}
			else {
				return false;
			}
			// 離された瞬間
		case Release:
			// 離された瞬間 か検証
			if (!keys[key] && preKeys[key]) {
				return true;
			}
			else {
				return false;
			}
			// エラー
		default:
			return false;
	}
}


// マウスをフォームに固定する関数
// 返り値：無し
// 引数：無し
// マウスをフォーム内に固定する関数
void BaseInput::ClipMouseinFoam() {
	// マウスのクライアント座標
	LPPOINT mouseClientPos = new tagPOINT();
	GetCursorPos(mouseClientPos);

	// フォームの座標を求める
	LONG foamPositionX = { mouseClientPos->x - (LONG)mousePosition.x };
	LONG foamPositionY = { mouseClientPos->y - (LONG)mousePosition.y };

	// カーソル移動制限
	const RECT rect = { foamPositionX, foamPositionY + 1, foamPositionX + BaseConst::kWindowWidth, foamPositionY + BaseConst::kWindowHeight };
	ClipCursor(&rect);
}


// マウスを一定範囲に固定する関数
// 返り値：無し
// 引数：
// position ... 固定するクライアント座標（x,y）
// length ... 固定する範囲（width,height）
// マウスを特定の範囲に固定する関数
void BaseInput::ClipMouseinRectangle(Point position, Point length) {
	// カーソル移動制限
	const RECT rect = { position.x, position.y, position.x + length.x, position.y + length.y };
	ClipCursor(&rect);
}


// 固定したマウスを解放する関数
// 返り値：無し
// 引数：無し
// マウスの固定を解除する関数。固定した後は必ず呼び出すこと！！！！！
void BaseInput::ClipMouseClear() {
	ClipCursor(NULL);
}


//////////////////////////////////
/* - staticメンバ変数の実態を宣言 - */
//////////////////////////////////

// マウス座標
Point BaseInput::mousePosition;

// キーの入力状況（今回のフレーム）
char BaseInput::keys[256];
// キーの入力状況（前回のフレーム）
char BaseInput::preKeys[256];