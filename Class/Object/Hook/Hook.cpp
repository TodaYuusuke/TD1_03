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
}
// �X�V
void Hook::Update() {
	if (isAlive) {

	}
}

// �`��
void Hook::Draw() {
	if (isAlive) {
		Point temp = BaseDraw::ScreentoWorld({ centerPosition.x - width / 2.0f, centerPosition.y + height / 2.0f });
		Novice::DrawBox(temp.x, temp.y, width, height, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
	}
}

// �^�C�v���擾
ObjectType Hook::GetType() {
	return typeHook;
}
