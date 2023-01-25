#include "MyBase/Effect/Inheritance/BlockBreak.h"

// コンストラクタ
BlockBreak::BlockBreak(Point startPos) {
	for (int i = 0; i < BaseTexture::kBlockScrapAmount; i++) {
		pos[i].x = startPos.x;
		pos[i].y = startPos.y;

		float p = rand() % 5 + 5;
		velocity[i] = BaseMath::TurnPoint({ p,0 }, rand() % 360);
		angle[i] = rand() % 360;
	}

	BaseInitialize({ 0,0 });
}
// デストラクタ
BlockBreak::~BlockBreak() {

}


// 初期化
void BlockBreak::Initialize() {

}
// 更新
void BlockBreak::Update() {
	for (int i = 0; i < BaseTexture::kBlockScrapAmount; i++) {
		velocity[i].y -= 9.8f / 30.0f;
		angle[i] += 5;

		pos[i].x += velocity[i].x;
		pos[i].y += velocity[i].y;
	}

	// 終了処理
	if (elapsedFrame > 120) {
		isEnd = true;
	}
};
// 描画
void BlockBreak::Draw() {
	for (int i = 0; i < BaseTexture::kBlockScrapAmount; i++) {
		BaseDraw::DrawQuad(pos[i], BaseTexture::kBlockScrap[i], { 50,50 }, 1, angle[i], WHITE);
	}
};