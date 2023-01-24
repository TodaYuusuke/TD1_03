#pragma 
#include "MyBase/Resource/BaseConst.h"
#include "MyBase/Define/BaseEnum.h"
#include "MyBase/Define/BaseStruct.h"
#include "MyBase/Resource/BaseTexture.h"

#include <Novice.h>


///////////////////////////////////////////////
/* - ゲーム内で使う全ての入力操作を管理するクラス - */
///////////////////////////////////////////////


class BaseInput
{

public: // メンバ関数

	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画
	static void Draw();



	// マウス座標を受け取る関数
	// 返り値：マウス座標のPoint
	// 引数：無し
	// マウスの座標をPoint型で受け取る関数
	static Point GetMousePosition();


	// マウスの入力状態を受け取る関数
	// 返り値：key が state の場合 -> true そうでない場合 -> false
	// 引数：
	// key ... 検証するキー
	// state ... 検証したい状態
	// 特定のキーがどんな状態（Null,Trigger,Press,Release）かをチェックする関数
	static bool GetMouseState(MouseButton key, InputState state);


	// キーの入力状態を受け取る関数
	// 返り値：key が state の場合 -> true そうでない場合 -> false
	// 引数：
	// key ... 検証するキー
	// state ... 検証したい状態
	// 特定のキーがどんな状態（Null,Trigger,Press,Release）かをチェックする関数
	static bool GetKeyboardState(int key, InputState state);


	// マウスをフォームに固定する関数
	// 返り値：無し
	// 引数：無し
	// マウスをフォーム内に固定する関数
	static void ClipMouseinFoam();


	// マウスを一定範囲に固定する関数
	// 返り値：無し
	// 引数：
	// position ... 固定するクライアント座標（x,y）
	// length ... 固定する範囲（width,height）
	// マウスを特定の範囲に固定する関数
	static void ClipMouseinRectangle(Point position, Point length);


	// 固定したマウスを解放する関数
	// 返り値：無し
	// 引数：無し
	// マウスの固定を解除する関数。固定した後は必ず呼び出すこと！！！！！
	static void ClipMouseClear();


private: // メンバ変数

	// マウス座標
	static Point mousePosition;

	// キーの入力状況（今回のフレーム）
	static char keys[];
	// キーの入力状況（前回のフレーム）
	static char preKeys[];

};

