#include "MyBase/Effect/Inheritance/FadeIn.h"

// �R���X�g���N�^
FadeIn::FadeIn() {
	BaseInitialize({ 0,0 });
}
// �f�X�g���N�^
FadeIn::~FadeIn() {

}


// ������
void FadeIn::Initialize() {
	alpha = 0xFF;
}
// �X�V
void FadeIn::Update() {
	alpha -= 255 / 60;
	if (alpha < 0) {
		alpha = 0;
		isEnd = true;
	}
}

// �`��
void FadeIn::Draw() {
	Novice::DrawBox(0, 0, 1920, 1080, 0, 0xFFFFFF00 + alpha, kFillModeSolid);
};