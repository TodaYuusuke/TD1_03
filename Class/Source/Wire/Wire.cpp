#include "Class/Include/Wire/Wire.h"

// コンストラクタ
Wire::Wire() {

}
// デストラクタ
Wire::~Wire() {
	
}

// 初期化
void Wire::Initialize() {
	*firstPosition = { -10000.0f, -10000.0f };
	*secondPosition = { -10000.0f, -10000.0f };

	firstObject = NULL;
	SecondObject = NULL;
}
// 更新
void Wire::Update(ObjectManager objectManager) {

}
// 描画
void Wire::Draw() {

}

// ワイヤーの当たり判定チェック用関数
// 引数：なし
// 返り値：ヒットした場合 ... true
//
// 今回はオブジェクト、もしくは場外に当たった場合にヒット判定
bool Wire::CheckHitBox(ObjectManager objectManager) {
	
}

// ワイヤー射出時に呼び出される関数
// 返り値がtrueのパターン：
// ・正常に射出できた場合
// 返り値がfalseのパターン：
// ・現在ワイヤーが射出中（まだ着弾していない）
// ・すでにワイヤーの着弾点が2点決まっている
//
// 引数：
// shotPosition ... ワイヤー射出地点
// shotAngle ... 発射角度（Degree）
//
// この関数が呼び出された後は、Updateにて着弾するまで弾の演算をし続けること。（ワイヤーの速度はBaseConst::kWireSpeed）
bool Wire::Shot(Point shotPosition, float shotAngle) {

}

// ワイヤー縮小時に呼び出される関数
// 返り値：なし
// 引数：なし
// 着弾点のObjectにベクトルを足す
void Wire::Attract() {

}