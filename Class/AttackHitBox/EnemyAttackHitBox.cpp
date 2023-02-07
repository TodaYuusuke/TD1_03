#include "EnemyAttackHitBox.h"

// ������
void EnemyAttackHitBox::Initialize() {

	// ���݂̓Y����
	num = 0;

	// �����蔻��̃��X�g
	for (int i = 0; i < 128; i++) {
		hitBox[i].centerPosition = { -15000,-15000 };
		hitBox[i].width = 0;
		hitBox[i].height = 0;
		hitBox[i].angle = 0;
		hitBox[i].atk = 0;
	}

	// ���̔��~�̓����蔻��
	leftEllipse.centerPosition = { -15000,-15000 };
	leftEllipse.radius = 0;
	leftEllipse.angle = 0;
	leftEllipse.atk = 0;
	// �E�̔��~�̓����蔻��
	rightEllipse.centerPosition = { -15000,-15000 };
	rightEllipse.radius = 0;
	rightEllipse.angle = 0;
	rightEllipse.atk = 0;
}
// �X�V
void EnemyAttackHitBox::Update() {
	// �Ȃ�
}
// �`��
void EnemyAttackHitBox::Draw() {
	// �Ȃ�
}



// �V���������蔻���ǉ�����֐��i�l�p�j
// �����F
// centerPosition ... �^�񒆂̍��W
// width ... �q�b�g�{�b�N�X�̉����i����̓_����j
// height ... �q�b�g�{�b�N�X�̏c���i����̓_����j
// angle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
// atk ... �_���[�W��
void EnemyAttackHitBox::MakeNewHitBox(Point centerPosition, float width, float height, float angle, float atk) {
	if (num >= 128) {
		return;
	}

	hitBox[num].centerPosition = centerPosition;
	hitBox[num].width = width;
	hitBox[num].height = height;
	hitBox[num].angle = angle;
	hitBox[num].atk = atk;

	num++;
}

// �V���������蔻���ǉ�����֐��i���̉~�j
// �����F
// centerPosition ... �^�񒆂̍��W
// width ... �q�b�g�{�b�N�X�̉����i����̓_����j
// height ... �q�b�g�{�b�N�X�̏c���i����̓_����j
// angle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
// atk ... �_���[�W��
void EnemyAttackHitBox::MakeNewHitBoxLeft(Point centerPosition, float radius, float angle, float atk) {
	leftEllipse.centerPosition = centerPosition;
	leftEllipse.radius = radius;
	leftEllipse.angle = angle;
	leftEllipse.atk = atk;
}
// �V���������蔻���ǉ�����֐��i�E�̉~�j
// �����F
// centerPosition ... �^�񒆂̍��W
// width ... �q�b�g�{�b�N�X�̉����i����̓_����j
// height ... �q�b�g�{�b�N�X�̏c���i����̓_����j
// angle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
// atk ... �_���[�W��
void EnemyAttackHitBox::MakeNewHitBoxRight(Point centerPosition, float radius, float angle, float atk) {
	rightEllipse.centerPosition = centerPosition;
	rightEllipse.radius = radius;
	rightEllipse.angle = angle;
	rightEllipse.atk = atk;
}


// �����蔻�茟��
// �Ԃ�l�F�q�b�g���Ă����ꍇ -> ��_���[�W�ʁA�@�q�b�g���Ă��Ȃ��ꍇ -> -1
// �����F
// centerPosition ... ���؂�����W
float EnemyAttackHitBox::CheckHitBox(Point centerPosition) {
	for (int i = 0; i < num; i++) {
		if (BaseMath::CheckHitBox(hitBox[i].centerPosition, hitBox[i].width, hitBox[i].height, hitBox[i].angle, centerPosition)) {
			return hitBox[i].atk;
		}
	}
	return -1;
}

// �����蔻�茟��
// �Ԃ�l�F�q�b�g���Ă����ꍇ -> ��_���[�W�ʁA�@�q�b�g���Ă��Ȃ��ꍇ -> -1
// �����F
// centerPosition ... ���؂�����W
float EnemyAttackHitBox::CheckHitEllipse(Point centerPosition) {

	// ���~�̂ǂ��炩�Ƀq�b�g���Ă����ꍇ -> atk��Ԃ�

	/// ����

	// �܂��~�̓����蔻������
	float radian = BaseMath::DegreetoRadian(leftEllipse.angle);
	// �؂���Ɛ����ȃx�N�g��
	Point e1 = { cosf(radian),sinf(radian) };
	// �؂���ƕ��s�ȃx�N�g��
	// �����Ȃ��̂�荶�ɉ���Ă���
	Point e2 = { cosf(radian + M_PI / 2.0f),sinf(radian + M_PI / 2.0f) };
	// �~�Ƃ��Ă̒��S�_�����߂�
	Point ellipseCenter = {
		leftEllipse.centerPosition.x + e1.x * (leftEllipse.radius / 2.0f),
		leftEllipse.centerPosition.y + e1.y * (leftEllipse.radius / 2.0f),
	};
	// �~�Ƃ��Ă̒��S����_�ւ̃x�N�g��
	Point EtoH = { centerPosition.x - ellipseCenter.x,centerPosition.y - ellipseCenter.y };
	// ���������߂�
	float distance = BaseMath::GetLength(EtoH);
	if (distance <= leftEllipse.radius) {
		// �~�̒���������O�ς��g���Ĕ��~�̓����蔻������	
		float cross = BaseMath::GetCross(e2, EtoH);
		// cross ���}�C�i�X�̎� ... �E
		// cross ���@�@�[���̎� ... �d�Ȃ��Ă���
		// cross ���@�v���X�̎� ... ��
		if (0 < cross) {
			return leftEllipse.atk;
		}

	}
	
	/// �E��

	// �܂��~�̓����蔻������
	radian = BaseMath::DegreetoRadian(rightEllipse.angle);
	// �؂���Ɛ����ȃx�N�g��
	e1 = { cosf(radian),sinf(radian) };
	// �؂���ƕ��s�ȃx�N�g��
	// �����Ȃ��̂�荶�ɉ���Ă���
	e2 = { cosf(radian + M_PI / 2.0f),sinf(radian + M_PI / 2.0f) };
	// �~�Ƃ��Ă̒��S�_�����߂�
	ellipseCenter = {
		rightEllipse.centerPosition.x - e1.x * (rightEllipse.radius / 2.0f),
		rightEllipse.centerPosition.y - e1.y * (rightEllipse.radius / 2.0f),
	};
	// �~�Ƃ��Ă̒��S����_�ւ̃x�N�g��
	EtoH = { centerPosition.x - ellipseCenter.x,centerPosition.y - ellipseCenter.y };
	// ���������߂�
	distance = BaseMath::GetLength(EtoH);
	if (distance <= rightEllipse.radius) {
		// �~�̒���������O�ς��g���Ĕ��~�̓����蔻������	
		float cross = BaseMath::GetCross(e2, EtoH);
		// cross ���}�C�i�X�̎� ... �E
		// cross ���@�@�[���̎� ... �d�Ȃ��Ă���
		// cross ���@�v���X�̎� ... ��
		if (cross < 0) {
			return rightEllipse.atk;
		}

	}

	// �q�b�g���Ă����ꍇ
	return -1;
}




// ���݂̓Y����
int EnemyAttackHitBox::num;
// �����蔻��̃��X�g
EnemyAttackHitBox::HitBox EnemyAttackHitBox::hitBox[128];
// ���̔��~�̓����蔻��
EnemyAttackHitBox::HitEllipse EnemyAttackHitBox::leftEllipse;
// �E�̔��~�̓����蔻��
EnemyAttackHitBox::HitEllipse EnemyAttackHitBox::rightEllipse;