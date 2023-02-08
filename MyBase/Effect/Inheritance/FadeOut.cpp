#include "MyBase/Effect/Inheritance/FadeOut.h"

// コンストラクタ
FadeOut::FadeOut() {
	BaseInitialize({ 0,0 });
}
// デストラクタ
FadeOut::~FadeOut() {

}


// 初期化
void FadeOut::Initialize() {
	alpha = 0;
}
// 更新
void FadeOut::Update() {
	alpha += 255 / 60;
	if (alpha > 255) {
		alpha = 255;
		isEnd = true;
	}
}

// 描画
void FadeOut::Draw() {
	Novice::DrawBox(0, 0, 1920, 1080, 0, 0xFFFFFF00 + alpha, kFillModeSolid);
};