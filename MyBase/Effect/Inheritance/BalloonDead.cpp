#include "MyBase/Effect/Inheritance/BalloonDead.h"

// コンストラクタ
BalloonDead::BalloonDead(Point startPos, bool isRight) {
	startPos.y += 8;
	this->isRight = isRight;
	BaseInitialize(startPos);
}
// デストラクタ
BalloonDead::~BalloonDead() {

}


// 初期化
void BalloonDead::Initialize() {

}
// 更新
void BalloonDead::Update() {
	if (elapsedFrame >= 6) {
		isEnd = true;
	}
}

// 描画
void BalloonDead::Draw() {
	BaseDraw::DrawQuad(position, BaseTexture::kEnemyBalloonDead[elapsedFrame / 2 + isRight * 3], {80,80}, 1, 0, WHITE);
};