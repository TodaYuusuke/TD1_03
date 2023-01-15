#include "MyBase/Include/Other/BaseMath.h"



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


// 当たり判定処理


// 四角同士の当たり判定チェック
bool BaseMath::CheckHitBox(Box hitBox1, Box hitBox2) {

	// 中心座標を調べる
	Point hitBox1Center = { hitBox1.position.x + (hitBox1.width / 2), hitBox1.position.y + (hitBox1.height / 2) };
	Point hitBox2Center = { hitBox2.position.x + (hitBox2.width / 2), hitBox2.position.y + (hitBox2.height / 2) };

	// 二点間の距離を調べる
	Point hitBoxDistance = { hitBox1Center.x - hitBox2Center.x,hitBox1Center.y - hitBox2Center.y };
	if (hitBoxDistance.x < 0.0f) {
		hitBoxDistance.x *= -1.0f;
	}
	if (hitBoxDistance.y < 0.0f) {
		hitBoxDistance.y *= -1.0f;
	}

	// サイズの和を算出する
	Point hitBoxSize = { (hitBox1.width + hitBox2.width) / 2,(hitBox1.height + hitBox2.height) / 2 };

	// ヒット判定
	if (hitBoxDistance.x < hitBoxSize.x && hitBoxDistance.y < hitBoxSize.y) {
		return true;
	}

	return false;
}

// ベクトル関連

/// <summary>
/// ベクトルの長さを求める関数
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns>ベクトルの長さ</returns>
float BaseMath::GetLength(Point vector) {
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}


/// <summary>
/// ベクトルの正規化をする関数
/// </summary>
/// <param name="vector">ベクトル</param>
/// <returns>正規化されたベクトル</returns>
Point BaseMath::GetNormalize(Point vector) {
	Point norm = vector;
	float length = GetLength(vector);
	if (length != 0.0f) {
		norm.x /= length;
		norm.y /= length;
	}
	return norm;
}

/// <summary>
/// Degree を受け取ってベクトルを生成する関数
/// </summary>
/// <param name="degree">degree</param>
/// <returns>ベクトル</returns>
Point BaseMath::GetVector(float degree) {
	return { cosf(BaseMath::DegreetoRadian(degree)),sinf(BaseMath::DegreetoRadian(degree)) };
}
/// <summary>
/// Degree を受け取ってベクトルを生成する関数
/// </summary>
/// <param name="degree">degree</param>
/// <param name="speed">スピード</param>
/// <returns>正規化されたベクトルにスピードを掛けたベクトル</returns>
Point BaseMath::GetVector(float degree, Point speed) {
	return { cosf(BaseMath::DegreetoRadian(degree)) * speed.x,sinf(BaseMath::DegreetoRadian(degree)) * speed.y };
}
