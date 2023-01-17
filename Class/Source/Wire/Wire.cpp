#include "Class/Include/Wire/Wire.h"

// �R���X�g���N�^
Wire::Wire() {

	firstPosition = new Point();
	secondPosition = new Point();
}
// �f�X�g���N�^
Wire::~Wire() {

}

// ������
void Wire::Initialize() {
	*firstPosition = { -10000.0f, -10000.0f };
	*secondPosition = { -10000.0f, -10000.0f };

	firstObject = NULL;
	secondObject = NULL;

	firstisStab = false;
	secondisStab = false;

	wireState = NoneShot;
}
// �X�V
void Wire::Update(ObjectManager* objectManager) {
	// �I�u�W�F�N�g�Ɏh�����Ă���A�������̓v���C���[�̏ꍇ�ɍ��W������
	// ���@���C���[�����킶�헎�������Ⴄ�o�O�L��@��
	if (firstObject != NULL) {
		firstPosition->x += firstObject->GetVelocity().x;
		if (firstObject->GetisFlying()) {
			firstPosition->y += firstObject->GetVelocity().y;
		}

	}
	if (secondObject != NULL) {
		if (secondObject->GetType() == typePlayer) {
			*secondPosition = secondObject->GetCenterPosition();
		}
		
		secondPosition->x += secondObject->GetVelocity().x;
		if (secondObject->GetisFlying()) {
			secondPosition->y += secondObject->GetVelocity().y;
		}

	}
	// �h�����Ă��炸�A�ˏo����Ă���Ƃ��͑��x�����Z����
	if (wireState == DoneShot) {
		// ���ڂ̎ˏo��
		if (!firstisStab) {
			firstPosition->x += cosf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			firstPosition->y += sinf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			// �ǂ����Ɏh�������ꍇ
			if (CheckHitBox(firstPosition, firstObject, objectManager)) {
				wireState = NoneShot;
				firstisStab = true;
			}
		}
		// ���ڂ̎ˏo��
		else if (!secondisStab) {
			secondPosition->x += cosf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			secondPosition->y += sinf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			// �ǂ����Ɏh�������ꍇ
			if (CheckHitBox(secondPosition, secondObject, objectManager)) {
				wireState = NoneShot;
				secondisStab = true;
			}
		}
	}
}
// �`��
void Wire::Draw() {

	Novice::DrawLine(firstPosition->x, BaseDraw::WorldtoScreen(*firstPosition).y, secondPosition->x, BaseDraw::WorldtoScreen(*secondPosition).y, BLACK);
	Novice::ScreenPrintf(10, 50, "change");

}

// ���C���[�̓����蔻��`�F�b�N�p�֐�
// �����F�Ȃ�
// �Ԃ�l�F�q�b�g�����ꍇ ... true
//
// ����̓I�u�W�F�N�g�A�������̓}�b�v�`�b�v�ɓ��������ꍇ�Ƀq�b�g����
bool Wire::CheckHitBox(Point* _position, Object*& _object, ObjectManager* objectManager) {
	// �������擾
	Point velocity = { cosf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed,sinf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed };
	// �O�t���[���̈ʒu���擾
	Point before = { _position->x - velocity.x,_position->y - velocity.y };
	_object = objectManager->CheckObjectHitBox(before, velocity);
	if (_object != NULL) {
		if (_object->GetType() != typePlayer) {
			return true;
		}
	}

	if (_object == NULL && MapManager::CheckHitBox(before)) {
		return true;
	}
	/*
	float variation = 0.01f;
	for (float i = 0; i < BaseConst::kWireSpeed; i += variation) {
		_object = objectManager->CheckObjectHitBox(before);
		if (_object != NULL && _object->GetType() != typePlayer) {
			return true;
		}
		before.x += e.x * variation;
		before.y += e.y * variation;
	}
	*/


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
			if (!firstisStab) {
				*firstPosition = shotPosition;
				secondObject = _player;
				*secondPosition = secondObject->GetCenterPosition();
				ShotAngle = shotAngle;
				wireState = DoneShot;
				return true;
			}
			// ��ڂ��h�����Ă��鎞
			else if (!secondisStab) {
				*secondPosition = shotPosition;
				secondObject = NULL;
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

	// ��ڂ��h�����Ă��Ȃ��A�܂��́A���C���[���ˏo���̎�
	if (!firstisStab || wireState == DoneShot) {
		// �����ŏI���
		return;
	}

	// ��ڂ̒��e�_�Ƀx�N�g���𑫂�
	if (firstObject != NULL) {
		// �����񂹂�����Ƌ���������
		Point p = { 20,0 };

		if (firstObject->GetType() == typePlayer) {
			p = { 15,0 };
		}

		p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(*firstPosition, *secondPosition));

		firstObject->AddVelocity(p);
	}

	// ��߂̒��e�_�Ƀx�N�g���𑫂�
	if (secondObject != NULL) {
		// �����񂹂�����Ƌ���������
		Point p = { 20,0 };
		
		if (secondObject->GetType() == typePlayer) {
			p = { 15,0 };
		}

		p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(*secondPosition, *firstPosition));

		secondObject->AddVelocity(p);
	}

	Initialize();

	/*
	// ��ڂ��h�����Ă��Ȃ��A�܂��́A���C���[���ˏo���̎�
	if (!firstisStab || wireState == DoneShot) {
		// �����ŏI���
		return;
	}
	// ��ڂ��h�����Ă��鎞
	else {
		// ��ڂ��h�����Ă��鎞
		if (secondisStab) {
			// �v���C���[���u���b�N���𔻕ʂ��ď�����ς���
			// �u���b�N�Ɏh�����Ă��炸�A�͈͊O�Ɏh�����Ă���Ƃ�
			if (firstObject == NULL) {
				// �ǂƕǂɎh�����Ă���Ƃ�
				if (secondObject == NULL) {
					// �Ǔ��m�A�����Ȃ����̓��m�̎��͉������Ȃ�
					Initialize();

				}
				// ��ڂ��ǂœ�ڂ��ǈȊO�̎�
				else {
					// �u���b�N���������񂹂�
					if (secondObject->GetType() == typeBlock) {
						//Point velocity = BaseMath::GetVector(*secondPosition, *firstPosition);

						// �����񂹂�����Ƌ���������
						Point p = { 10,0 };
						p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(*secondPosition, *firstPosition));

						secondObject->AddVelocity(p);
						Initialize();
					}
				}
			}
			// ��ڂ��������̂Ɏh�����Ă��鎞
			else {
				// ��ڂ��ǂɎh�����Ă��鎞
				if (secondObject == NULL) {
					// �u���b�N���������񂹂�
					if (firstObject->GetType() == typeBlock) {
						Point velocity = BaseMath::GetVector(*firstPosition, *secondPosition);
						firstObject->AddVelocity(velocity);
						Initialize();
					}
				}
				// �ǂ�����������̂Ɏh�����Ă��鎞
				else {
					// �u���b�N���������񂹂�
					if (firstObject->GetType() == typeBlock) {
						if (secondObject->GetType() == typeBlock) {
							Point velocity = BaseMath::GetVector(*firstPosition, *secondPosition);
							firstObject->AddVelocity(velocity);
							velocity = BaseMath::GetVector(*secondPosition, *firstPosition);
							secondObject->AddVelocity(velocity);
							Initialize();
						}
					}
				}
			}
		}
		// ��ڂ��ǂɎh�����Ă��鎞
		else if (firstObject == NULL) {
			// �v���C���[���������񂹂�
			if (secondObject->GetType() == typePlayer) {
				Point velocity = BaseMath::GetVector(*secondPosition, *firstPosition);
				secondObject->AddVelocity(velocity);
				Initialize();
			}
		}
		// ��ڂ��������̂Ɏh�����Ă��鎞
		else {
			// �u���b�N���������񂹂�
			if (firstObject->GetType() == typeBlock) {
				Point velocity = BaseMath::GetVector(*firstPosition, *secondPosition);
				firstObject->AddVelocity(velocity);
				Initialize();
			}
		}
	}
	*/
}
