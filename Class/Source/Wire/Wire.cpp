#include "Class/Include/Wire/Wire.h"

// �R���X�g���N�^
Wire::Wire() {

}
// �f�X�g���N�^
Wire::~Wire() {

}

// ������
void Wire::Initialize() {
	firstPosition = new Point();
	*firstPosition = { -10000.0f, -10000.0f };
	secondPosition = new Point();
	*secondPosition = { -10000.0f, -10000.0f };

	firstObject = NULL;
	secondObject = NULL;
	wireState = NoneShot;
}
// �X�V
void Wire::Update(ObjectManager* objectManager) {
	// �I�u�W�F�N�g�Ɏh�����Ă���A�������̓v���C���[�̏ꍇ�ɍ��W������
	// �h�����Ă��炸�A�ˏo����Ă���Ƃ��͑��x�����Z����
	if (firstObject != NULL) {
		*firstPosition = firstObject->GetCenterPosition();
	}
	if (secondObject != NULL) {
		*secondPosition = secondObject->GetCenterPosition();
	}
	if (wireState == DoneShot) {
		// ���ڂ̎ˏo��
		if (firstObject == NULL) {
			firstPosition->x += cosf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			firstPosition->y += sinf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			// �ǂ����Ɏh�������ꍇ
			if (CheckHitBox(firstPosition, firstObject, objectManager)) {
				wireState = NoneShot;
			}
		}
		// ���ڂ̎ˏo��
		else if (secondObject == NULL) {
			secondPosition->x += cosf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			secondPosition->y += sinf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			// �ǂ����Ɏh�������ꍇ
			if (CheckHitBox(secondPosition, secondObject, objectManager)) {
				wireState = NoneShot;
			}
		}
	}
}
// �`��
void Wire::Draw() {
	Novice::DrawLine(firstPosition->x, BaseDraw::WorldtoScreen(*firstPosition).y, secondPosition->x, BaseDraw::WorldtoScreen(*secondPosition).y, BLACK);
}

// ���C���[�̓����蔻��`�F�b�N�p�֐�
// �����F�Ȃ�
// �Ԃ�l�F�q�b�g�����ꍇ ... true
//
// ����̓I�u�W�F�N�g�A�������͏�O�ɓ��������ꍇ�Ƀq�b�g����
bool Wire::CheckHitBox(Point* _position,Object*& _object, ObjectManager* objectManager) {
	_object = objectManager->CheckObjectHitBox(*_position);
	if (_object != NULL && _object->GetType() != typePlayer) {
		return true;
	}
	// ��ʊO�ɏo���ꍇ
	if (_position->x < 0 || BaseConst::kWindowWidth < _position->x) {
		return true;
	}
	if (_position->y < 0 || BaseConst::kWindowHeight < _position->y) {
		return true;
	}
	_object = NULL;
	return false;
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
bool Wire::Shot(Point shotPosition, float shotAngle, Player* _player) {
	// �����Ă��Ȃ���	: ���������������Č���
	// �����Ă��鎞		: ���ɉ������Ȃ�
	switch (wireState)
	{
	case Wire::NoneShot:
		// ���ڂ̎ˏo�����Ă��Ȃ����A���A�ǂȂǂɂ������Ă��Ȃ���
		if (firstObject == NULL && (firstPosition->x == -10000.0f && firstPosition->y == -10000.0f)) {
			*firstPosition = shotPosition;
			secondObject = _player;
			ShotAngle = shotAngle;
			wireState = DoneShot;
			return true;
		}
		break;
	case Wire::DoneShot:
		break;
	default:
		break;
	}
	return false;
}

// ���C���[�k�����ɌĂяo�����֐�
// �Ԃ�l�F�Ȃ�
// �����F�Ȃ�
// ���e�_��Object�Ƀx�N�g���𑫂�
void Wire::Attract() {

}
