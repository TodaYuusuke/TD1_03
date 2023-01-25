#include "Class/AttackHitBox/ObjectHitBox.h"

// ������
void ObjectHitBox::Initialize() {

	// ���݂̓Y����
	num = 0;

	// �����蔻��̃��X�g
	for (int i = 0; i < 256; i++) {
		hitBox[i].centerPosition = NULL;
		hitBox[i].width = 0;
		hitBox[i].height = 0;
		hitBox[i].angle = 0;
	}
}
// �X�V
void ObjectHitBox::Update() {
	// �Ȃ�
}
// �`��
void ObjectHitBox::Draw() {
	// �Ȃ�
}

// �V���������蔻���ǉ�����֐��i�l�p�j
// �����F
// centerPosition ... �^�񒆂̍��W
// width ... �q�b�g�{�b�N�X�̉����i����̓_����j
// height ... �q�b�g�{�b�N�X�̏c���i����̓_����j
// angle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
int ObjectHitBox::AddHitBox(Point* centerPosition, float* width, float* height, float* angle) {
	if (num >= 256) {
		return -1;
	}

	hitBox[num].centerPosition = centerPosition;
	hitBox[num].width = width;
	hitBox[num].height = height;
	hitBox[num].angle = angle;

	return num++;
}

// �����蔻�茟��
// �Ԃ�l�F�q�b�g���Ă����ꍇ -> true�A�@�q�b�g���Ă��Ȃ��ꍇ -> false
// �����F
// centerPosition ... ���؂�����W
bool ObjectHitBox::CheckHitBox(Point centerPosition, int noCheck) {
	for (int i = 0; i < num; i++) {
		if (hitBox[i].centerPosition != NULL) {
			if (i != noCheck) {
				if (BaseMath::CheckHitBox(*hitBox[i].centerPosition, *hitBox[i].width, *hitBox[i].height, *hitBox[i].angle, centerPosition)) {
					return true;
				}
			}
		}
	}
	return false;
}



// ���݂̓Y����
int ObjectHitBox::num;
// �����蔻��̃��X�g
ObjectHitBox::HitBox ObjectHitBox::hitBox[256];