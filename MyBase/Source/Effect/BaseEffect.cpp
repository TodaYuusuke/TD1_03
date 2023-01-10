#include "MyBase/Include/Effect/BaseEffect.h"

// ������
void BaseEffect::BaseInitialize() {
	// �G�t�F�N�g���I���������ǂ���
	isEnd = true;

	// ���݂̌o�߃t���[��
	elapsedFrame = 0;
	// �`����W
	position = { 0,0 };

	Initialize();
}
// ������
void BaseEffect::BaseInitialize(Point _position) {
	// �G�t�F�N�g���I���������ǂ���
	isEnd = false;	

	// ���݂̌o�߃t���[��
	elapsedFrame = 0;
	// �`����W
	position = _position;

	Initialize();
}
// ������
void BaseEffect::Initialize() {

}

// �X�V
void BaseEffect::BaseUpdate() {
	if (isEnd) {
		return;
	}

	elapsedFrame++;

	Update();
}
// �X�V
void BaseEffect::Update() {

}

// �`��
void BaseEffect::BaseDraw() {
	if (isEnd) {
		return;
	}

	Draw();
}
// �`��
void BaseEffect::Draw() {

}

// �G�t�F�N�g���I��������֐�
// �Ԃ�l�F�Ȃ�
// �����F
void BaseEffect::EndEffect() {
	isEnd = true;
}


// �G�t�F�N�g���I���������ǂ�����Ԃ��֐�
// �Ԃ�l�F�I�������Ȃ�true�A�����łȂ����false
// �����F����
// �G�t�F�N�g���������������`�F�b�N����֐�
bool BaseEffect::isEndEffect() {
	return isEnd;
}