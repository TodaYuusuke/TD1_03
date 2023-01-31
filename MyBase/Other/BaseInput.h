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


	/// <summary>
	/// 特定のキーがどんな状態（Null,Trigger,Press,Release）かをチェックする関数
	/// ボタンの入力状態を受け取る関数
	/// </summary>
	/// <param name="key">検証するボタン</param>
	/// <param name="state">検証したい状態</param>
	/// <returns>key が state の場合 -> true そうでない場合 -> false</returns>
	static bool GetControllerState(ControllerButton key, InputState state);

	/// <summary>
	/// コントローラーのスティックの状態を受け取る関数
	/// </summary>
	/// <param name="left">左スティック</param>
	/// <param name="right">右スティック</param>
	/// <returns>正常に受け取れた場合 true</returns>
	static void GetControllerJoysState(Point* left, Point* right);
	static void GetControllerLeftJoysState(Point* left);
	static void GetControllerRightJoysState(Point* right);

	/// <summary>
	/// アナログスティックを 100% - 0% で表す関数
	/// </summary>
	/// <param name="p">アナログスティックの入力値</param>
	/// <returns>傾きの %</returns>
	static float AnalogToPer(int p);

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

	// ボタンの入力状況 (今回のフレーム)
	static bool buttons[];
	// ボタンの入力状況 (前回のフレーム)
	static bool preButtons[];


};

