#include "Class/Object/Hook/Hook.h"

// �R���X�g���N�^
Hook::Hook(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

	Initialize();
}
// �f�X�g���N�^
Hook::~Hook() {

}

// ������
void Hook::SuccessorInitialize() {

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
void Hook::Update() {
	if (isAlive) {
		if (isPulled) {
			if (5 < pullCount) {
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
void Hook::Draw() {
	if (isAlive) {
		Point temp = BaseDraw::WorldtoScreen({ centerPosition.x - width / 2.0f, centerPosition.y + height / 2.0f });
		if (isPulled) {
			Novice::DrawBox(temp.x, temp.y, width, height, 0.0f, 0xAA0000FF, kFillModeWireFrame);
		}
		else {
			Novice::DrawBox(temp.x, temp.y, width, height, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
		}
	}
}

// �^�C�v���擾
ObjectType Hook::GetType() {
	return typeHook;
}
