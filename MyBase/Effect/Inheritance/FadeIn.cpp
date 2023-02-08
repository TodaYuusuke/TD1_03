#include "MyBase/Effect/Inheritance/FadeIn.h"

// コンストラクタ
FadeIn::FadeIn() {
	BaseInitialize({ 0,0 });
}
// デストラクタ
FadeIn::~FadeIn() {

}


// 初期化
void FadeIn::Initialize() {
	alpha = 0xFF;
}
// 更新
void FadeIn::Update() {
	alpha -= 255 / 60;
	if (alpha < 0) {
		alpha = 0;
		isEnd = true;
	}
}

// 描画
void FadeIn::Draw() {
	Novice::DrawBox(0, 0, 1920, 1080, 0, 0xFFFFFF00 + alpha, kFillModeSolid);
};