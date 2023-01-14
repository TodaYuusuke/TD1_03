#include "Class/Include/Object/Player/Player.h"

// �R���X�g���N�^
Player::Player(Point centerPosition, WireManager* _wireManager) {
	this->centerPosition = centerPosition;
	wireManager = _wireManager;
	ReticlePosition = { -100,-100 };
}
// �f�X�g���N�^
Player::~Player() {

}


// ������
void Player::SuccessorInitialize() {
	centerPosition = { -10000,-10000 };

	width = 1;
	height = 1;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;
	ReticlePosition = { -10000,-10000 };

	//wireManager->Initialize();

}
// �X�V
void Player::SuccessorUpdate() {

	ReticlePosition = BaseInput::GetMousePosition();

	Move();
	//wireManager.Update();
	ShotWire();

}
// �`��
void Player::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
	BaseDraw::DrawQuad(BaseDraw::WorldtoScreen(ReticlePosition), BaseTexture::kDebugTexture, { 20,20 }, 1.0f, 0.0f, WHITE);
	Novice::ScreenPrintf(10, 10, "Reticle:%.2f %.2f", ReticlePosition.x, ReticlePosition.y);
	Novice::ScreenPrintf(10, 30, "center:%.2f %.2f", centerPosition.x, centerPosition.y);
}


// �ǂ����Update()�Ŗ��t���[���Ăяo������

// �ړ��֘A
void Player::Move() {
	// ���ւ̈ړ�
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		acceleration.x -= BaseConst::kPlayerSpeed.x;

	}
	else if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		acceleration.x += BaseConst::kPlayerSpeed.x;
	}
	else if (velocity.x + acceleration.x != 0) {
		velocity.x *= 0.95f;
	}
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger) && !isFlying) {
		velocity.y += BaseConst::kPlayerSpeed.y;
		isFlying = true;
	}

}

// ���C���[���ˏo���铮��
void Player::ShotWire() {
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		ReticlePosition = BaseInput::GetMousePosition();
		//float angle = atan2(centerPosition.y - ReticlePosition.y, centerPosition.x - ReticlePosition.x);

		//wireManager->Shot(centerPosition, BaseMath::RadiantoDegree(angle), this);
		wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), ReticlePosition), this);



	}
}


ObjectType Player::GetType() {
	return typePlayer;
}
