#include "Class/Wire/Wire.h"

// �R���X�g���N�^
Wire::Wire() {
	Initialize();
}
// �f�X�g���N�^
Wire::~Wire() {

}

// ������
void Wire::Initialize() {

	// �����t���O��false�Ɂi�����ꂽ����true�ցj
	isAlive = false;

	// �O�t���[���̍��W
	prePosition[0] = { -10000.0f, -10000.0f };
	prePosition[1] = { -10000.0f, -10000.0f };
	// ���W
	position[0] = { -10000.0f, -10000.0f };
	position[1] = { -10000.0f, -10000.0f };
	// ���n�_�̃I�u�W�F�N�g
	object[0] = NULL;
	object[1] = NULL;
	// ���n�_�̃I�u�W�F�N�g�̃^�C�v
	type[0] = typeObject;
	type[1] = typeObject;
	// ���C���[�̏��
	isShot[0] = false;
	isShot[1] = false;

	// �ˏo�p�x�idegree�j
	shotAngle = 0;
}

// �X�V
void Wire::Update(ObjectManager* objectManager) {

	// �������C���[�̒��������ȏ�ɂȂ����ꍇ ... ������
	if (BaseMath::GetLength({ position[1].x - position[0].x, position[1].y - position[0].y }) >= BaseConst::kWireMaxLength) {
		Initialize();
	}

	for (int i = 0; i < 2; i++) {

		// ���˂���Ă���ꍇ�̍X�V����
		if (isShot[i]) {

			// 100�������đ��x���v�Z���邱�ƂŁA�g���l�����O�h�~
			for (int j = 0; j < 100; j++) {
				// ���x��ǉ�
				Point p = BaseMath::TurnPoint({ BaseConst::kWireSpeed, 0 }, shotAngle);
				p.x *= 0.01f;
				p.y *= 0.01f;
				position[i].x += p.x;
				position[i].y += p.y;

				// �����蔻��`�F�b�N
				if (CheckHitBox(position[i], i, objectManager)) {
					// �ǂ���Ȃ��Ƃ��͍��W�����
					if (type[i] != typeWall) {
						//position[i].x = object[i]->GetCenterPosition().x;
						//position[i].y = object[i]->GetCenterPosition().y;
						prePosition[i].x = object[i]->GetCenterPosition().x;
						prePosition[i].y = object[i]->GetCenterPosition().y;
					}
					isShot[i] = false;
					break;
				}
			}
		}
		// ���˂���Ă����Ԃł͂Ȃ��@���@�ǂł͂Ȃ��I�u�W�F�N�g�Ƀq�b�g���Ă���ꍇ
		else if (object[i] != NULL) {
			if (type[i] != typeWall) {

				// ���C���[��؂鏈�����s���Ă���ꍇ -> object��Hook�̏ꍇ�؂�
				if (PublicFlag::kBossisTurningAndCutWire) {
					if (type[i] == typeHook) {
						Initialize();
						return;
					}
				}

				// �I�u�W�F�N�g�����񂾏ꍇ -> ���C���[��؂�
				if (!object[i]->GetisAlive()) {
					Initialize();
					return;
				}

				position[i].x -= prePosition[i].x - object[i]->GetCenterPosition().x;
				position[i].y -= prePosition[i].y - object[i]->GetCenterPosition().y;
				prePosition[i].x = object[i]->GetCenterPosition().x;
				prePosition[i].y = object[i]->GetCenterPosition().y;
			}
		}

	}
}
// �`��
void Wire::Draw() {

	Point p[2] = { BaseDraw::WorldtoScreen(position[0]),BaseDraw::WorldtoScreen(position[1]) };

	// ����`��
	Novice::DrawLine(p[0].x, p[0].y, p[1].x, p[1].y, WHITE);
}



// ���C���[�̐����t���O��Ԃ�
bool Wire::GetisAlive() {
	return isAlive;
}

// ���C���[�̓����蔻��`�F�b�N�p�֐�
// �����F�Ȃ�
// �Ԃ�l�F�q�b�g�����ꍇ ... true
//
// ����̓I�u�W�F�N�g�A�������̓}�b�v�`�b�v�ɓ��������ꍇ�Ƀq�b�g����
bool Wire::CheckHitBox(Point _position, int i, ObjectManager* objectManager) {

	// �{�X�̊O�k�ɓ������Ă��Ȃ���
	if (EnemyAttackHitBox::CheckHitEllipse(_position) != -1) {
		Initialize();
		return false;
	}

	// �I�u�W�F�N�g�Ƀq�b�g���Ă��邩����
	object[i] = objectManager->CheckObjectHitBox(_position);
	if(object[i] != NULL && object[i]->GetType() != typePlayer && object[i] != object[!i] && !(object[i]->GetType() == typeHook && type[!i] == typeHook)) {
		// �q�b�g���Ă����ꍇ -> �߂�
		type[i] = object[i]->GetType();
		object[i]->SetisStub(true);
		// SE���Đ�
		Novice::PlayAudio(BaseAudio::kWireHit, 0, 0.5f);
		return true;
	}
	// �ǂɃq�b�g���Ă��邩����
	else if (MapManager::CheckHitBox(_position)) {
		// �q�b�g���Ă����ꍇ
		type[i] = typeWall;
		// SE���Đ�
		Novice::PlayAudio(BaseAudio::kWireHit, 0, 0.5f);
		return true;
	}


	object[i] = NULL;
	return false;
}

// ���C���[�ˏo���ɌĂяo�����֐�
// �Ԃ�l��true�̃p�^�[���F
// �E����Ɏˏo�ł����ꍇ = 1
// �Ԃ�l��false�̃p�^�[���F
// �E���݃��C���[���ˏo���i�܂����e���Ă��Ȃ��j = -1
// �E���łɃ��C���[�̒��e�_��2�_���܂��Ă��� = -2
//
// �����F
// shotPosition ... ���C���[�ˏo�n�_
// shotAngle ... ���ˊp�x�iDegree�j
//
// ���̊֐����Ăяo���ꂽ��́AUpdate�ɂĒ��e����܂Œe�̉��Z���������邱�ƁB�i���C���[�̑��x��BaseConst::kWireSpeed�j
int Wire::Shot(Point shotPosition, float shotAngle, Player* _player) {
	// �����Ă��Ȃ���	: ���������������Č���
	// �����Ă��鎞		: ���ɉ������Ȃ�

	// ���˒���false��Ԃ�
	if (isShot[0] || isShot[1]) {
		return -1;
	}

	// �P���ڂ��܂����˂���Ă��Ȃ��@���@�܂����e���Ă��Ȃ��ꍇ
	if (!isShot[0] && object[0] == NULL && type[0] != typeWall) {
		// �P���ڂ̏�����
		prePosition[0] = shotPosition;
		// ���W
		position[0] = shotPosition;
		// ���C���[�̏��
		isShot[0] = true;
		// �ˏo�p�x�idegree�j
		this->shotAngle = shotAngle;

		// �Q���ڂ̏�����
		prePosition[1] = shotPosition;
		// ���W
		position[1] = shotPosition;
		// �I�u�W�F�N�g
		object[1] = _player;
		// �^�C�v
		type[1] = typePlayer;

		return 1;
	}
	// �P���ڂ����e�ς݁@���@�Q���ڂ��܂����˂���Ă��Ȃ��@���@�Q���ڂ��܂����e���Ă��Ȃ��ꍇ
	//else if ((object[0] != NULL || type[0] == typeWall) && !isShot[1] && object[1]->GetType() == typePlayer) {
	else if ((object[0] != NULL || type[0] == typeWall) && !isShot[1] && ((object[1] == NULL && type[1] != typeWall) || type[1] == typePlayer)) {
		// ���C���[�̏��
		isShot[1] = true;
		// ���e����NULL��
		object[1] = NULL;

		// �ˏo�p�x�idegree�j
		this->shotAngle = shotAngle;

		return 1;
	}

	return -2;
}

// ���C���[�k�����ɌĂяo�����֐�
// �Ԃ�l�F�Ȃ�
// �����F�Ȃ�
// ���e�_��Object�Ƀx�N�g���𑫂�
void Wire::Attract() {

	// �ǂ��炩���ˏo���̏ꍇ -> �߂�
	if (isShot[0] || isShot[1]) {
		return;
	}
	// ���e���Ă��Ȃ��ꍇ -> �߂�
	if (type[0] == typeObject && type[1] == typeObject) {
		return;
	}


	// ���ʂȔ���

	// �����Е����ǂŁA�Е���Hook�̏ꍇ
	if ((type[0] == typeHook && type[1] == typeWall) || (type[1] == typeHook && type[0] == typeWall)) {
		for (int i = 0; i < 2; i++) {
			if (type[i] == typeHook) {
				object[i]->SetisPulled(true);
				object[i]->SetisStub(false);
				return;
			}
		}
	}


	// ��ڂ̃I�u�W�F�N�g�Ƀx�N�g���𑫂�
	if (object[0] != NULL ) {
		// �����񂹂鋭��������
		Point p = { 20,0 };

		if (object[0]->GetType() == typeBlock) {
			p = { 40,0 };
		}

		p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(position[0], position[1]));

		// �x�N�g�����������̏ꍇ -> ������������ɕ␳
		if (type[0] != typePlayer) {
			if (p.y < 3) {
				p.y = 3;
			}
		}

		object[0]->SetisPulled(true);
		object[0]->SetisStub(false);
		object[0]->AddVelocity(p);
	}
	// ��ڂ̃I�u�W�F�N�g�Ƀx�N�g���𑫂�
	if (object[1] != NULL) {
		// �����񂹂鋭��������
		Point p = { 20,0 };

		if (object[1]->GetType() == typeBlock) {
			p = { 40,0 };
		}

		p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(position[1], position[0]));

		// �x�N�g�����������̏ꍇ -> ������������ɕ␳
		if (type[1] != typePlayer) {
			if (p.y < 3) {
				p.y = 3;
			}
		}

		object[1]->SetisPulled(true);
		object[1]->SetisStub(false);
		object[1]->AddVelocity(p);
	}

	// ���C���[��������
	Initialize();
	// SE���Đ�
	Novice::PlayAudio(BaseAudio::kWireCut, 0, 0.5f);
}
