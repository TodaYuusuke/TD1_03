#include "Class/Include/Wire/Wire.h"

// �R���X�g���N�^
Wire::Wire() {

}
// �f�X�g���N�^
Wire::~Wire() {
	
}

// ������
void Wire::Initialize() {
	*firstPosition = { -10000.0f, -10000.0f };
	*secondPosition = { -10000.0f, -10000.0f };

	firstObject = NULL;
	SecondObject = NULL;
}
// �X�V
void Wire::Update(ObjectManager objectManager) {

}
// �`��
void Wire::Draw() {

}

// ���C���[�̓����蔻��`�F�b�N�p�֐�
// �����F�Ȃ�
// �Ԃ�l�F�q�b�g�����ꍇ ... true
//
// ����̓I�u�W�F�N�g�A�������͏�O�ɓ��������ꍇ�Ƀq�b�g����
bool Wire::CheckHitBox(ObjectManager objectManager) {
	
}

// ���C���[�ˏo���ɌĂяo�����֐�
// �Ԃ�l��true�̃p�^�[���F
// �E����Ɏˏo�ł����ꍇ
// �Ԃ�l��false�̃p�^�[���F
// �E���݃��C���[���ˏo���i�܂����e���Ă��Ȃ��j
// �E���łɃ��C���[�̒��e�_��2�_���܂��Ă���
//
// �����F
// shotPosition ... ���C���[�ˏo�n�_
// shotAngle ... ���ˊp�x�iDegree�j
//
// ���̊֐����Ăяo���ꂽ��́AUpdate�ɂĒ��e����܂Œe�̉��Z���������邱�ƁB�i���C���[�̑��x��BaseConst::kWireSpeed�j
bool Wire::Shot(Point shotPosition, float shotAngle) {

}

// ���C���[�k�����ɌĂяo�����֐�
// �Ԃ�l�F�Ȃ�
// �����F�Ȃ�
// ���e�_��Object�Ƀx�N�g���𑫂�
void Wire::Attract() {

}