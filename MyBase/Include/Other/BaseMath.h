#pragma once
#include "MyBase/Include/Define/BaseStruct.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "MyBase/Include/Other/BaseDraw.h"

////////////////////////////////////////////////////
/* - プログラム中に使う全ての数学的関数を管理するクラス - */
////////////////////////////////////////////////////

class BaseDraw;

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

	/// <summary>
	/// 四角形と点の当たり判定チェック（回転を考慮可能、当たり判定の四角形が自身の中心を原点に回転している前提）
	/// </summary>
	/// <param name="hitBoxCenterPosition">ヒット対象の四角の中心座標</param>
	/// <param name="hitBoxWidth">ヒット対象の横幅</param>
	/// <param name="hitBoxHeight">ヒット対象の縦幅</param>
	/// <param name="boxAngle">ヒット対象の四角の回転角度</param>
	/// <param name="hitPosition">ヒットしているか検証する座標</param>
	/// <returns>ヒット時はtrue、それ以外はfalse</returns>
	static bool CheckHitBox(Point hitBoxCenterPosition, float hitBoxWidth, float hitBoxHeight, float boxAngle, Point hitPosition);

	// 四角同士の当たり判定チェック
	static bool CheckHitBox(Box hitBox1, Box hitBox2);



	// ベクトル関連

	/// <summary>
	/// ベクトルの長さを求める関数
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>ベクトルの長さ</returns>
	static float GetLength(Point vector);

	/// <summary>
	/// ベクトルの正規化をする関数
	/// </summary>
	/// <param name="vector">ベクトル</param>
	/// <returns>正規化されたベクトル</returns>
	static Point GetNormalize(Point vector);

	/// <summary>
	/// Degree を受け取ってベクトルを生成する関数
	/// </summary>
	/// <param name="degree">degree</param>
	/// <returns>正規化されたベクトル</returns>
	static Point GetVector(float degree);
	/// <summary>
	/// Degree を受け取ってベクトルを生成する関数
	/// </summary>
	/// <param name="degree">degree</param>
	/// <param name="speed">スピード</param>
	/// <returns>正規化されたベクトルにスピードを掛けたベクトル</returns>
	static Point GetVector(float degree, Point speed);
	/// <summary>
	/// from と to を受け取ってベクトルを生成する関数
	/// </summary>
	/// <param name="from">座標 1</param>
	/// <param name="to">座標 2</param>
	/// <returns>from から to へのベクトル</returns>
	static Point GetVector(Point from, Point to);

	/// <summary>
	/// 内積を求める関数
	/// </summary>
	/// <param name="a">ベクトル 1</param>
	/// <param name="b">ベクトル 2</param>
	/// <returns>内積</returns>
	static float GetDot(Point a, Point b);

	static float GetCross(Point a, Point b);

	// 線分

	/// <summary>
	/// 点とカプセルの一番近い点をカプセルの線分から求める関数
	/// </summary>
	/// <param name="hitCenterPosition">対象の中心座標</param>
	/// <param name="hitPosition">カプセルの始点座標</param>
	/// <param name="hitVelocity">カプセルの長さ</param>
	/// <param name="hitRadius">カプセルの中の円の半径</param>
	/// <param name="hitAngle">カプセルの中の円の回転角</param>
	/// <returns>点とカプセルの最近傍点</returns>
	//static Point GetCapsuleNearestPosition(Point hitCenterPosition, Point hitPosition, Point hitVelocity, Point hitRadius, float hitAngle);

	/// <summary>
	/// 点と線分の一番近い点を線分から求める関数
	/// </summary>
	/// <param name="hitCenterPosition">対象の中心座標</param>
	/// <param name="hitPosition">線分の始点座標</param>
	/// <param name="hitVelocity">線分の長さ</param>
	/// <returns>点と線分の最近傍点</returns>
	static Point GetNearestPosition(Point hitCenterPosition, Point hitPosition, Point hitVelocity);

	/// <summary>
	/// 点と線分の一番近い点を線分から求める関数
	/// </summary>
	/// <param name="hitQuad">対象の矩形</param>
	/// <param name="hitPosition">線分の始点座標</param>
	/// <param name="hitVelocity">線分の長さ</param>
	/// <returns>点と線分の最近傍点</returns>
	static Point GetNearestPosition(Quad hitQuad, Point hitPosition, Point hitVelocity);

	// その他

	/// <summary>
	/// 値を min から max の値に収める関数
	/// </summary>
	/// <param name="a">収める値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>範囲内の値</returns>
	static float Clamp(float a, float min, float max);


};

