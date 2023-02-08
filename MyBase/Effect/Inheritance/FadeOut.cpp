#include "MyBase/Effect/Inheritance/FadeOut.h"

// �R���X�g���N�^
FadeOut::FadeOut() {
	BaseInitialize({ 0,0 });
}
// �f�X�g���N�^
FadeOut::~FadeOut() {

}


// ������
void FadeOut::Initialize() {
	alpha = 0;
}
// �X�V
void FadeOut::Update() {
	alpha += 255 / 60;
	if (alpha > 255) {
		alpha = 255;
		isEnd = true;
	}
}

// �`��
void FadeOut::Draw() {
	Novice::DrawBox(0, 0, 1920, 1080, 0, 0xFFFFFF00 + alpha, kFillModeSolid);
};