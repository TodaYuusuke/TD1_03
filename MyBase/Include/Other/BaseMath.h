#pragma once
#include "MyBase/Include/Define/BaseStruct.h"

#define _USE_MATH_DEFINES
#include <math.h>

////////////////////////////////////////////////////
/* - プログラム中に使う全ての数学的関数を管理するクラス - */
////////////////////////////////////////////////////


class BaseMath
{

public:


	// 角度関連


	// radianからdegreeに変換する関数
	// 返り値：degree
	// 引数：
	// radian ... radianの角度
	// radianの角度をdegreeの角度に変換する関数。引数で要求されるのは基本Degreeなのであまり使わない。
	static float RadiantoDegree(float radian);

	// degreeからradianに変換する関数
	// 返り値：radian
	// 引数：
	// degree ... degreeの角度
	// degreeの角度をradianの角度に変換する関数。引数で要求されるのは基本Degreeなので関数内では使われる。
	static float DegreetoRadian(float degree);

	// 2点間の角度（degree）を求める関数
	// 返り値：2点の角度（degree）
	// 引数：
	// from ... 座標１
	// to ... 座標２
	// 2点の角度をDegreeで受け取る関数。
	static float GetDegree(Point from, Point to);


	// 回転処理


	// Pointの回転計算関数
	// 返り値：回転後のPoint
	// 引数：
	// point ... 計算するPoints
	// degree ... 回転角度（degree）
	// 原点中心の回転しか行えないので注意
	static Point TurnPoint(Point point, float degree);
	
	// Boxの回転計算関数
	// 返り値：回転後のBox
	// 引数：
	// box ... 計算するPoints
	// degree ... 回転角度（degree）
	// 原点中心の回転しか行えないので注意
	static Quad TurnBox(Quad box, float degree);


	// 当たり判定処理


	// 四角同士の当たり判定チェック
	static bool CheckHitBox(Box hitBox1, Box hitBox2);

};

