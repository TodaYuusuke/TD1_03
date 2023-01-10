#pragma once


namespace BaseStruct {
	////////////////////////////////////////////////
	/* - プログラム中に使う全ての構造体を管理するクラス - */
	////////////////////////////////////////////////


	// 座標
	struct Point
	{
		// x座標
		float x;
		// y座標
		float y;
	};

	// 円
	struct Circle {
		// 中心座標
		Point position;
		// 半径
		float radian;
	};

	// ボックス
	struct Box {
		// 左上の座標
		Point position;
		// 横幅
		float width;
		// 縦幅
		float height;
	};


	// 四角同士の当たり判定チェック
	static bool CheckHitBox(Box hitBox1, Box hitBox2) {

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

	// 四角
	struct Quad
	{
		// 左上
		Point q1;
		// 右上
		Point q2;
		// 左下
		Point q3;
		// 右下
		Point q4;
	};

}

using namespace BaseStruct;