#include "Class/Object/Core/Core.h"

// �R���X�g���N�^
Core::Core(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

	Initialize();
}
// �f�X�g���N�^
Core::~Core() {

}

// ������
void Core::SuccessorInitialize() {

	// ���x
	velocity = { 0,0 };
	// �����x
	acceleration = { 0,0 };

	// ��]�p�x�iDegree�j
	angle = 0;
	// ��]���x�iDegree�j
	angleVelocity = 0;

	//�󒆂ɂ��邩�ǂ���
	isFlying = true;
	isAlive = true;
	isPulled = false;

	pullCount = 0;
}
// �X�V
void Core::Update() {
	if (isAlive) {
		if (isPulled) {
			if (30 < pullCount) {
				// ��������ꂽ����̏���


				pullCount = 0;
				isPulled = false;
			}
			else {
				pullCount++;
			}
		}
	}
}

// �`��
void Core::Draw() {
	if (isAlive) {
		Point temp = BaseDraw::WorldtoScreen({ centerPosition.x - width / 2.0f, centerPosition.y + height / 2.0f });
		if (isPulled) {
			//Novice::DrawBox(temp.x, temp.y, width, height, 0.0f, 0xAA0000FF, kFillModeWireFrame);
		}
		else {
			//Novice::DrawBox(temp.x, temp.y, width, height, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
		}
	}
}

// �^�C�v���擾
ObjectType Core::GetType() {
	return typeCore;
}

// �����蔻��֘A

// �I�u�W�F�N�g�ɑ΂��铖���蔻����`�F�b�N����֐�
// �Ԃ�l�F�q�b�g���Ă����ꍇ ... true
// �����F�`�F�b�N����Point
bool Core::CheckHitBox(Point hitPosition) {
	float f = BaseMath::GetLength(BaseMath::GetVector(centerPosition, hitPosition));

	if (f <= width / 2) {
		return true;
	}

	return false;
}