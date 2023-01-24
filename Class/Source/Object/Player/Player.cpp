#include "Class/Include/Object/Player/Player.h"

// �R���X�g���N�^
Player::Player(Point centerPosition, WireManager* _wireManager) {
	this->centerPosition = centerPosition;
	wireManager = _wireManager;

	Initialize();
}
// �f�X�g���N�^
Player::~Player() {

}


// ������
void Player::SuccessorInitialize() {

	width = 50;
	height = 100;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	angle = 0;
	angleVelocity = 0;

	isFlying = true;
	isAlive = true;
	reticlePosition = { -10000,-10000 };

}
// �X�V
void Player::SuccessorUpdate() {
	// ��]����ɏ�����
	angle = 0;
	angleVelocity = 0;

	reticlePosition = BaseInput::GetMousePosition();

	Move();
	ShotWire();

}
// �`��
void Player::Draw() {
	if (isAlive) {
		BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kDebugTexture, { width,height }, 0, RED);
	}
}



// �ǂ����Update()�Ŗ��t���[���Ăяo������

// �ړ��֘A
void Player::Move() {

	// ���ړ�
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x -= 0.5f;
		}
	}
	else if(velocity.x < 0) {
		velocity.x += 0.1f;
	}
	// �E�ړ�
	if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f;
		}
	}
	else if (velocity.x > 0) {
		velocity.x -= 0.1f;
	}
}

// ���C���[�֘A
void Player::ShotWire() {
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		reticlePosition = BaseInput::GetMousePosition();
		//float angle = atan2(centerPosition.y - ReticlePosition.y, centerPosition.x - ReticlePosition.x);

		//wireManager->Shot(centerPosition, BaseMath::RadiantoDegree(angle), this);
		wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition), this);

	}
	if (BaseInput::GetMouseState(RightClick, Trigger)) {
		wireManager->Attract();
	}
}


ObjectType Player::GetType() {
	return typePlayer;
}
