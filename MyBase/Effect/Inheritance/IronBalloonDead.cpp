#include "MyBase/Effect/Inheritance/IronBalloonDead.h"

// �R���X�g���N�^
IronBalloonDead::IronBalloonDead(Point startPos, bool isRight) {
	startPos.y += 8;
	this->isRight = isRight;
	BaseInitialize(startPos);
}
// �f�X�g���N�^
IronBalloonDead::~IronBalloonDead() {

}


// ������
void IronBalloonDead::Initialize() {

}
// �X�V
void IronBalloonDead::Update() {
	if (elapsedFrame >= 6) {
		isEnd = true;
	}
}

// �`��
void IronBalloonDead::Draw() {
	BaseDraw::DrawQuad(position, BaseTexture::kEnemyIronBalloonDead[elapsedFrame / 2 + isRight * 3], {80,80}, 1, 0, WHITE);
};