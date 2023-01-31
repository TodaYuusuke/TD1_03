#include "MyBase/Other/BaseInput.h"


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
	// ボタン入力の初期化
	for (int i = 0; i < 20; i++) {
		buttons[i] = false;
		preButtons[i] = false;
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
	// ボタン入力を受け取る
	memcpy(preButtons, buttons, 20);
	for (int i = 0; i < 20; i++) {
		buttons[i] = Novice::IsPressButton(0, (PadButton)i);
	}
	// コントローラーが反応しなくなる自体が発生していたのでデバッグ用
	//int a = Novice::GetNumberOfJoysticks();
	//Novice::ScreenPrintf(10, 100, "BaseInput.cpp Update(): Joysticks :%d", a);
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

/// <summary>
/// 特定のキーがどんな状態（Null,Trigger,Press,Release）かをチェックする関数
/// ボタンの入力状態を受け取る関数
/// </summary>
/// <param name="key">検証するボタン</param>
/// <param name="state">検証したい状態</param>
/// <returns>key が state の場合 -> true そうでない場合 -> false</returns>
bool BaseInput::GetControllerState(ControllerButton button, InputState state){
	switch (state)
	{
		// 押されていない
	case Null:
		// 押されていない か検証
		if (!buttons[button] && !preButtons[button]) {
			return true;
		}
		else {
			return false;
		}
		// 押された瞬間
	case Trigger:
		// 押された瞬間 か検証
		if (buttons[button] && !preButtons[button]) {
			return true;
		}
		else {
			return false;
		}
		// 押しっぱなし
	case Press:
		// 押しっぱなし か検証
		if (buttons[button]) {
			return true;
		}
		else {
			return false;
		}
		// 離された瞬間
	case Release:
		// 離された瞬間 か検証
		if (!keys[button] && preButtons[button]) {
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

/// <summary>
/// コントローラーのスティックの状態を受け取る関数
/// </summary>
/// <param name="left">左スティック</param>
/// <param name="right">右スティック</param>
/// <returns>正常に受け取れた場合 true</returns>
void BaseInput::GetControllerJoysState(Point* left, Point* right) {

	// スティックの座標
	int AnalogLeft_X;
	int AnalogLeft_Y;
	int AnalogRight_X;
	int AnalogRight_Y;

	// 左スティックの座標を取得
	Novice::GetAnalogInputLeft(0, &AnalogLeft_X, &AnalogLeft_Y);
	// 右スティックの座標を取得
	Novice::GetAnalogInputRight(0, &AnalogRight_X, &AnalogRight_Y);

	left->x = AnalogToPer(AnalogLeft_X);
	left->y = AnalogToPer(AnalogLeft_Y);
	right->x = AnalogToPer(AnalogRight_X);
	right->y = AnalogToPer(AnalogRight_Y);
}

void BaseInput::GetControllerLeftJoysState(Point* left) {
	// スティックの座標
	int AnalogLeft_X;
	int AnalogLeft_Y;
	// 左スティックの座標を取得
	Novice::GetAnalogInputLeft(0, &AnalogLeft_X, &AnalogLeft_Y);
	left->x = AnalogToPer(AnalogLeft_X);
	left->y = AnalogToPer(AnalogLeft_Y);
}
void BaseInput::GetControllerRightJoysState(Point* right) {
	// スティックの座標
	int AnalogRight_X;
	int AnalogRight_Y;
	// 右スティックの座標を取得
	Novice::GetAnalogInputRight(0, &AnalogRight_X, &AnalogRight_Y);
	right->x = AnalogToPer(AnalogRight_X);
	right->y = AnalogToPer(AnalogRight_Y);
}

/// <summary>
/// アナログスティックを 100% - 0% で表す関数
/// </summary>
/// <param name="p">アナログスティックの入力値</param>
/// <returns>傾きの %</returns>
float BaseInput::AnalogToPer(int p) {
	return p / 32767.0f;
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

// ボタンの入力状況 (今回のフレーム)
bool BaseInput::buttons[20];
// ボタンの入力状況 (前回のフレーム)
bool BaseInput::preButtons[20];
