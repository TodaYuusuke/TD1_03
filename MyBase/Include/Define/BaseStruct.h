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

	// 四角
	// q1 ... 左上
	// q2 ... 右上
	// q3 ... 左下
	// q4 ... 右下
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