#pragma once
#include "MyBase/MyBase.h"

// ボスの生成する当たり判定を管理するクラス

class ObjectHitBox {
public: // メンバ関数

	// 初期化
	static void Initialize();
	// 更新
	static void Update();
	// 描画
	static void Draw();

	// 新しく当たり判定を追加する関数（四角）
	// 引数：
	// centerPosition ... 真ん中の座標
	// width ... ヒットボックスの横幅（左上の点から）
	// height ... ヒットボックスの縦幅（左上の点から）
	// angle ... ヒット対象の四角の回転角度
	static int AddHitBox(Point* _centerPosition, float* _width, float* _height, float* _angle);

	// 当たり判定検証
	// 返り値：ヒットしていた場合 -> true、　ヒットしていない場合 -> false
	// 引数：
	// centerPosition ... 検証する座標
	// num ... 検証しない添え字
	static bool CheckHitBox(Point _centerPosition, int noCheck);

private: // メンバ変数

	// 現在の添え字
	static int num;
	// 当たり判定のリスト
	static Point* centerPosition[256];
	static float* width[256];
	static float* height[256];
	static float* angle[256];
	
};