#include "MyBase/Effect/Inheritance/IronBalloonDead.h"

// コンストラクタ
IronBalloonDead::IronBalloonDead(Point startPos, bool isRight) {
	startPos.y += 8;
	this->isRight = isRight;
	BaseInitialize(startPos);
}
// デストラクタ
IronBalloonDead::~IronBalloonDead() {

}


// 初期化
void IronBalloonDead::Initialize() {

}
// 更新
void IronBalloonDead::Update() {
	if (elapsedFrame >= 6) {
		isEnd = true;
	}
}

// 描画
void IronBalloonDead::Draw() {
	BaseDraw::DrawQuad(position, BaseTexture::kEnemyIronBalloonDead[elapsedFrame / 2 + isRight * 3], {80,80}, 1, 0, WHITE);
};