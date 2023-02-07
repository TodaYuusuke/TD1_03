#include "Class/AttackHitBox/ObjectHitBox.h"

// ������
void ObjectHitBox::Initialize() {

	// ���݂̓Y����
	num = 0;

	// �����蔻��̃��X�g
	//for (int i = 0; i < 256; i++) {
	//	hitBox[i]->centerPosition = NULL;
	//	hitBox[i]->width = NULL;
	//	hitBox[i]->height = NULL;
	//	hitBox[i]->angle = NULL;
	//}
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
int ObjectHitBox::AddHitBox(Point* _centerPosition, float* _width, float* _height, float* _angle, bool* _isAlive) {
	if (num >= 256) {
		return -1;
	}

	centerPosition[num] = _centerPosition;
	width[num] = _width;
	height[num] = _height;
	angle[num] = _angle;
	isAlive[num] = _isAlive;

	return num++;
}

// �����蔻�茟��
// �Ԃ�l�F�q�b�g���Ă����ꍇ -> true�A�@�q�b�g���Ă��Ȃ��ꍇ -> false
// �����F
// centerPosition ... ���؂�����W
int ObjectHitBox::CheckHitBox(Point _centerPosition, int noCheck) {
	for (int i = 0; i < num; i++) {
		if (centerPosition[i] != NULL) {
			if (*isAlive[i]) {
				if (i != noCheck) {
					if (BaseMath::CheckHitBox(*centerPosition[i], *width[i], *height[i], *angle[i], _centerPosition)) {
						*isAlive[i] = false;
						BaseEffectManager::MakeNewEffectBlockBreak(*centerPosition[i]);
						return true;
					}
				}
			}
		}
	}
	return false;
}



// ���݂̓Y����
int ObjectHitBox::num;
// �����蔻��̃��X�g
Point* ObjectHitBox::centerPosition[256];
float* ObjectHitBox::width[256];
float* ObjectHitBox::height[256];
float* ObjectHitBox::angle[256];
bool* ObjectHitBox::isAlive[256];