#include "MyBase/Effect/Inheritance/ConcreteDust.h"

// コンストラクタ
ConcreteDust::ConcreteDust(Point startPos) {
	for (int i = 0; i < BaseConst::kConcreteDustNum; i++) {
		pos[i].x = startPos.x;
		pos[i].y = startPos.y;

		float p = rand() % 5 + 5;
		vel[i] = BaseMath::TurnPoint({ p,0 }, rand() % 360);
		size[i] = rand() % 3 + 3;
	}

	BaseInitialize(startPos);
}
// デストラクタ
ConcreteDust::~ConcreteDust() {

}


// 初期化
void ConcreteDust::Initialize() {

}
// 更新
void ConcreteDust::Update() {
	for (int i = 0; i < BaseConst::kConcreteDustNum; i++) {
		vel[i].y -= 9.8f / 30.0f;

		pos[i].x += vel[i].x;
		// マップに当たってるかどうか
		if (MapManager::CheckHitBox(pos[i], false)) {
			vel[i].x = vel[i].x * -0.6f;
		}
		pos[i].y += vel[i].y;
		// マップに当たってるかどうか
		if (MapManager::CheckHitBox(pos[i], false)) {
			vel[i].y = vel[i].y * -0.6f;
		}
	}

	// 終了処理
	if (elapsedFrame > 60) {
		isEnd = true;
	}
};
// 描画
void ConcreteDust::Draw() {
	for (int i = 0; i < BaseTexture::kBlockScrapAmount; i++) {
		BaseDraw::DrawQuad(pos[i], BaseTexture::kDebugTexture, { 1,1 }, size[i], 0.0f, 0x222222FF);
		BaseDraw::DrawQuad(pos[i], BaseTexture::kDebugTexture, {1,1}, size[i] - 2, 0.0f, 0xFFFFFFFF);
	}
};