#include "Base/Include/Other/BaseMath.h"



// 角度関連


// radianからdegreeに変換する関数
// 返り値：degree
// 引数：
// radian ... radianの角度
// radianの角度をdegreeの角度に変換する関数。引数で要求されるのは基本Degreeなのであまり使わない。
float BaseMath::RadiantoDegree(float radian) {
	return radian * (180.0f / M_PI);
}

// degreeからradianに変換する関数
// 返り値：radian
// 引数：
// degree ... degreeの角度
// degreeの角度をradianの角度に変換する関数。引数で要求されるのは基本Degreeなので関数内では使われる。
float BaseMath::DegreetoRadian(float degree) {
	return degree * (M_PI / 180.0f);
}

// 2点間の角度（degree）を求める関数
// 返り値：2点の角度（degree）
// 引数：
// from ... 座標１
// to ... 座標２
// 2点の角度をDegreeで受け取る関数。
float BaseMath::GetDegree(Point from, Point to) {

	// 角度を計算
	float radian = atan2(to.y - from.y, to.x - from.x);

	// 180°未満の場合
	if (radian <= 0) {
		radian *= -1;
	}
	else {
		float def = M_PI - radian;

		radian = def + M_PI;
	}

	return BaseMath::RadiantoDegree(radian);
}


// 回転関連


// Pointの回転計算関数
// 返り値：回転後のPoint
// 引数：
// point ... 計算するPoints
// degree ... 回転角度（degree）
// 原点中心の回転しか行えないので注意
Point BaseMath::TurnPoint(Point point, float degree) {
	// 座標を保存（計算用）
	float preX = point.x;
	float preY = point.y;

	// 回転角度（radian）
	float radian = DegreetoRadian(degree);

	// 計算（回転させる）
	point.x = preX * cosf(radian) - preY * sinf(radian);
	point.y = preY * cosf(radian) + preX * sinf(radian);

	return point;
}

// Boxの回転計算関数
// 返り値：回転後のBox
// 引数：
// box ... 計算するPoints
// degree ... 回転角度（degree）
// 原点中心の回転しか行えないので注意
Quad BaseMath::TurnBox(Quad box, float degree) {

	// 計算（theta回転させる）
	box.q1 = TurnPoint(box.q1, degree);
	box.q2 = TurnPoint(box.q2, degree);
	box.q3 = TurnPoint(box.q3, degree);
	box.q4 = TurnPoint(box.q4, degree);

	return box;
}