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
}
// �X�V
void Hook::Update() {

}

// �`��
void Hook::Draw() {
	if (BaseMath::CheckHitBox(centerPosition, width, height, angle, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()))) {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, BLUE);
	}
	else {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, WHITE);
	}
}

// �^�C�v���擾
ObjectType Hook::GetType() {
	return typeHook;
}
