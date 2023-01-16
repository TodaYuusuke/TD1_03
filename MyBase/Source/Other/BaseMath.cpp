#include "MyBase/Include/Other/BaseMath.h"

#include <Novice.h>

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


// 四角形と点の当たり判定チェック（回転を考慮する）
// 返り値：ヒット時はtrue、それ以外はfalse
// 引数：
// hitBoxCenterPosition ... ヒット対象の四角の中心座標
// hitBoxWidth ... ヒット対象の横幅
// hitBoxHeight ... ヒット対象の縦幅
// boxAngle ... ヒット対象の四角の回転角度
// hitPoisiton ... ヒットしているか検証する座標
bool BaseMath::CheckHitBox(Point hitBoxCenterPosition, float hitBoxWidth, float hitBoxHeight, float boxAngle, Point hitPosition) {

	//hitBoxCenterPosition = BaseDraw::WorldtoScreen(hitBoxCenterPosition);
	//hitPosition = BaseDraw::WorldtoScreen(hitPosition);

	// hitPositionをヒット対象の四角の中心を原点に回転させて戻す
	Point pos = { hitPosition.x - hitBoxCenterPosition.x, hitPosition.y - hitBoxCenterPosition.y };
	hitPosition = BaseMath::TurnPoint(pos, -boxAngle);
	hitPosition = { hitPosition.x + hitBoxCenterPosition.x, hitPosition.y + hitBoxCenterPosition.y };

	// 点が上辺より下で
	if (hitPosition.y > hitBoxCenterPosition.y - hitBoxHeight / 2) {
		Novice::ScreenPrintf(0, 0, "1");
		// 点が下辺より上で
		if (hitPosition.y < hitBoxCenterPosition.y + hitBoxHeight / 2) {
			Novice::ScreenPrintf(0, 20, "2");
			// 点が左辺より右で
			if (hitPosition.x > hitBoxCenterPosition.x - hitBoxWidth / 2) {
				Novice::ScreenPrintf(0, 40, "3");
				// 点が右辺より左の場合 -> ヒットしている
				if (hitPosition.x < hitBoxCenterPosition.x + hitBoxWidth / 2) {
					Novice::ScreenPrintf(0, 60, "4");
					return true;
				}
			}
		}
	}

	return false;
}


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
	return { cosf(BaseMath::DegreetoRadian(degree)) * speed.x, -sinf(BaseMath::DegreetoRadian(degree)) * speed.y };
}

/// <summary>
/// from と to を受け取ってベクトルを生成する関数
/// </summary>
/// <param name="from">座標 1</param>
/// <param name="to">座標 2</param>
/// <returns>from から to へのベクトル</returns>
Point BaseMath::GetVector(Point from, Point to) {
	return { to.x - from.x,to.y - from.y };
}

/// <summary>
/// 内積を求める関数
/// </summary>
/// <param name="a">ベクトル 1</param>
/// <param name="b">ベクトル 2</param>
/// <returns>内積</returns>
float BaseMath::GetDot(Point a, Point b) {
	return a.x * b.x + a.y * b.y;
}

/// <summary>
/// 外積を求める関数
/// </summary>
/// <param name="a">ベクトル 1</param>
/// <param name="b">ベクトル 2</param>
/// <returns>外積</returns>
float BaseMath::GetCross(Point a, Point b) {
	return a.x * b.y - a.y * b.y;
}

// カプセル

/// <summary>
/// 点と線分の一番近い点を線分から求める関数
/// </summary>
/// <param name="hitCenterPosition">対象の中心座標</param>
/// <param name="hitPosition">線分の始点座標</param>
/// <param name="hitVelocity">線分の長さ</param>
/// <returns>点と線分の最近傍点</returns>
Point BaseMath::GetNearestPosition(Point hitCenterPosition, Point hitPosition, Point hitVelocity) {
	// 線分を正規化
	Point e = GetNormalize(hitVelocity);
	// 線分の始点から点までのベクトル
	Point a = { hitCenterPosition.x - hitPosition.x,hitCenterPosition.y - hitPosition.y };
	if (GetDot(e, a) < 0) {
		return hitPosition;
	}
	// 線分の終点から点までのベクトル
	Point b = { hitCenterPosition.x - (hitPosition.x + hitVelocity.x),hitCenterPosition.y - (hitPosition.y + hitVelocity.y) };
	if (0 < GetDot(e, b)) {
		return { hitPosition.x + hitVelocity.x, hitPosition.y + hitVelocity.y };
	}
	// 線分の最近傍点を求める
	float t = GetDot(a, e) / GetLength(hitVelocity);
	//float t = GetDot(a, e);
	return { hitPosition.x + (hitVelocity.x * t),hitPosition.y + (hitVelocity.y * t) };
	//return { (1.0f - t) * hitPosition.x + t * (hitPosition.x + hitVelocity.x),(1.0f - t) * hitPosition.y + t * (hitPosition.y + hitVelocity.y) };
}

/// <summary>
/// 点と線分の一番近い点を線分から求める関数
/// </summary>
/// <param name="hitQuad">対象の矩形</param>
/// <param name="hitPosition">線分の始点座標</param>
/// <param name="hitVelocity">線分の長さ</param>
/// <returns>点と線分の最近傍点</returns>
Point BaseMath::GetNearestPosition(Quad hitQuad, Point hitPosition, Point hitVelocity) {
	float t = 10000;
	float length = GetLength(hitVelocity);
	// 線分を正規化
	Point e = GetNormalize(hitVelocity);

	// q1

	// 線分の始点から点までのベクトル
	Point a = { hitQuad.q1.x - hitPosition.x,hitQuad.q1.y - hitPosition.y };
	// 始点より前だったら
	if (GetDot(e, a) < 0) {
		t = 0;
	}
	// 線分の終点から点までのベクトル
	Point b = { hitQuad.q1.x - (hitPosition.x + hitVelocity.x),hitQuad.q1.y - (hitPosition.y + hitVelocity.y) };
	// 終点より後だったら
	if (0 < GetDot(e, b)) {
		if (GetLength(hitVelocity) < t) {
			t = GetLength(hitVelocity);
		}
	}
	// 線分の最近傍点を求める
	if (GetDot(a, e) / GetLength(hitVelocity) < t) {
		t = GetDot(a, e) / GetLength(hitVelocity);
	}

	// q2

	// 線分の始点から点までのベクトル
	a = { hitQuad.q2.x - hitPosition.x,hitQuad.q2.y - hitPosition.y };
	// 始点より前だったら
	if (GetDot(e, a) < 0) {
		t = 0;
	}
	// 線分の終点から点までのベクトル
	b = { hitQuad.q2.x - (hitPosition.x + hitVelocity.x),hitQuad.q2.y - (hitPosition.y + hitVelocity.y) };
	// 終点より後だったら
	if (0 < GetDot(e, b)) {
		if (GetLength(hitVelocity) < t) {
			t = GetLength(hitVelocity);
		}
	}
	// 線分の最近傍点を求める
	if (GetDot(a, e) / GetLength(hitVelocity) < t) {
		t = GetDot(a, e) / GetLength(hitVelocity);
	}

	// q3

	// 線分の始点から点までのベクトル
	a = { hitQuad.q3.x - hitPosition.x,hitQuad.q3.y - hitPosition.y };
	// 始点より前だったら
	if (GetDot(e, a) < 0) {
		t = 0;
	}

	// 線分の終点から点までのベクトル
	b = { hitQuad.q3.x - (hitPosition.x + hitVelocity.x),hitQuad.q3.y - (hitPosition.y + hitVelocity.y) };
	// 終点より後だったら
	if (0 < GetDot(e, b)) {
		if (GetLength(hitVelocity) < t) {
			t = GetLength(hitVelocity);
		}
	}
	// 線分の最近傍点を求める
	if (GetDot(a, e) / GetLength(hitVelocity) < t) {
		t = GetDot(a, e) / GetLength(hitVelocity);
	}

	// q4

	// 線分の始点から点までのベクトル
	a = { hitQuad.q4.x - hitPosition.x,hitQuad.q4.y - hitPosition.y };
	// 始点より前だったら
	if (GetDot(e, a) < 0) {
		t = 0;
	}
	// 線分の終点から点までのベクトル
	b = { hitQuad.q4.x - (hitPosition.x + hitVelocity.x),hitQuad.q4.y - (hitPosition.y + hitVelocity.y) };
	// 終点より後だったら
	if (0 < GetDot(e, b)) {
		if (GetLength(hitVelocity) < t) {
			t = GetLength(hitVelocity);
		}
	}
	// 線分の最近傍点を求める
	if (GetDot(a, e) / GetLength(hitVelocity) < t) {
		t = GetDot(a, e) / GetLength(hitVelocity);
	}
	//float t = GetDot(a, e);
	return { hitPosition.x + (hitVelocity.x * t),hitPosition.y + (hitVelocity.y * t) };
	//return { (1.0f - t) * hitPosition.x + t * (hitPosition.x + hitVelocity.x),(1.0f - t) * hitPosition.y + t * (hitPosition.y + hitVelocity.y) };
}

// その他

/// <summary>
/// 値を min から max の値に収める関数
/// </summary>
/// <param name="a">収める値</param>
/// <param name="min">最小値</param>
/// <param name="max">最大値</param>
/// <returns>範囲内の値</returns>
float BaseMath::Clamp(float a, float min, float max) {
	if (a < min) {
		return min;
	}
	else if (max < a) {
		return max;
	}
	return a;
}


// 最も近い値を格納した配列の添え字を求める
static int getNearestValue(int v) {
	// 変数の宣言
	v = BaseMath::Clamp(v, 0, 360);
	if (v < 45) {
		return 0;
	}
	else if (v < 90 + 45) {
		return 90;
	}
	else if (v < 180 + 45) {
		return 180;
	}
	else if (v < 270 + 45) {
		return 270;
	}
	else {
		return 0;
	}
}