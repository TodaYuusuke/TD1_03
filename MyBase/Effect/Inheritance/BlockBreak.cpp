#include "MyBase/Effect/Inheritance/BlockBreak.h"

// �R���X�g���N�^
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
// �f�X�g���N�^
BlockBreak::~BlockBreak() {

}


// ������
void BlockBreak::Initialize() {

}
// �X�V
void BlockBreak::Update() {
	for (int i = 0; i < BaseTexture::kBlockScrapAmount; i++) {
		velocity[i].y -= 9.8f / 30.0f;
		angle[i] += 5;

		pos[i].x += velocity[i].x;
		pos[i].y += velocity[i].y;
	}

	// �I������
	if (elapsedFrame > 120) {
		isEnd = true;
	}
};
// �`��
void BlockBreak::Draw() {
	for (int i = 0; i < BaseTexture::kBlockScrapAmount; i++) {
		BaseDraw::DrawQuad(pos[i], BaseTexture::kBlockScrap[i], { 50,50 }, 1, angle[i], WHITE);
	}
};