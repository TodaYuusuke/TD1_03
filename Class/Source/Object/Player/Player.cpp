#include "Class/Include/Object/Player/Player.h"

// コンストラクタ
Player::Player(Point centerPosition) {
	this->centerPosition = centerPosition;
	ReticlePosition = { -100,-100 };
}
// デストラクタ
Player::~Player() {

}


// 初期化
void Player::SuccessorInitialize() {
	centerPosition = { -1000,-1000 };

	width = 1;
	height = 1;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;
	ReticlePosition = { -100,-100 };

}
// 更新
void Player::SuccessorUpdate() {

	ReticlePosition = BaseInput::GetMousePosition();

	Move();
	ShotWire();

}
// 描画
void Player::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
	BaseDraw::DrawQuad(BaseDraw::WorldtoScreen(ReticlePosition), BaseTexture::kDebugTexture, {20,20}, 1.0f, 0.0f, WHITE);
	Novice::ScreenPrintf(10, 10, "Reticle:%.2f %.2f", ReticlePosition.x, ReticlePosition.y);
	Novice::ScreenPrintf(10, 30, "center:%.2f %.2f", centerPosition.x, centerPosition.y);
}


// どちらもUpdate()で毎フレーム呼び出すこと

// 移動関連
void Player::Move() {
	// 左への移動
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		velocity.x -= kPlayerSpeedX;
	}
	else if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		velocity.x += kPlayerSpeedX;
	}
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		acceleration.y += kPlayerSpeedY;
		isFlying = true;
	}

}

// ワイヤーを射出する動作
void Player::ShotWire() {

}


ObjectType Player::GetType() {
	return typePlayer;
}
