#include "MyBase/Effect/Inheritance/BalloonDead.h"

// �R���X�g���N�^
BalloonDead::BalloonDead(Point startPos, bool isRight) {
	startPos.y += 8;
	this->isRight = isRight;
	BaseInitialize(startPos);
}
// �f�X�g���N�^
BalloonDead::~BalloonDead() {

}


// ������
void BalloonDead::Initialize() {

}
// �X�V
void BalloonDead::Update() {
	if (elapsedFrame >= 6) {
		isEnd = true;
	}
}

// �`��
void BalloonDead::Draw() {
	BaseDraw::DrawQuad(position, BaseTexture::kEnemyBalloonDead[elapsedFrame / 2 + isRight * 3], {80,80}, 1, 0, WHITE);
};