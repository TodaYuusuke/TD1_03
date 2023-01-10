#include "MyBase/Include/Effect/BaseEffect.h"

// 初期化
void BaseEffect::BaseInitialize() {
	// エフェクトが終了したかどうか
	isEnd = true;

	// 現在の経過フレーム
	elapsedFrame = 0;
	// 描画座標
	position = { 0,0 };

	Initialize();
}
// 初期化
void BaseEffect::BaseInitialize(Point _position) {
	// エフェクトが終了したかどうか
	isEnd = false;	

	// 現在の経過フレーム
	elapsedFrame = 0;
	// 描画座標
	position = _position;

	Initialize();
}
// 初期化
void BaseEffect::Initialize() {

}

// 更新
void BaseEffect::BaseUpdate() {
	if (isEnd) {
		return;
	}

	elapsedFrame++;

	Update();
}
// 更新
void BaseEffect::Update() {

}

// 描画
void BaseEffect::BaseDraw() {
	if (isEnd) {
		return;
	}

	Draw();
}
// 描画
void BaseEffect::Draw() {

}

// エフェクトを終了させる関数
// 返り値：なし
// 引数：
void BaseEffect::EndEffect() {
	isEnd = true;
}


// エフェクトが終了したかどうかを返す関数
// 返り値：終了したならtrue、そうでなければfalse
// 引数：無し
// エフェクトが完了したかをチェックする関数
bool BaseEffect::isEndEffect() {
	return isEnd;
}