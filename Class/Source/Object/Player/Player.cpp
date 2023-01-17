#include "Class/Include/Object/Player/Player.h"

// コンストラクタ
Player::Player(Point centerPosition, WireManager* _wireManager) {
	this->centerPosition = centerPosition;
	wireManager = _wireManager;

	Initialize();
}
// デストラクタ
Player::~Player() {

}


// 初期化
void Player::SuccessorInitialize() {

	width = 50;
	height = 100;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;
	reticlePosition = { -10000,-10000 };

}
// 更新
void Player::SuccessorUpdate() {

	reticlePosition = BaseInput::GetMousePosition();

	Move();
	ShotWire();

}
// 描画
void Player::Draw() {

	Novice::ScreenPrintf(0, 0, "playerPosX %f playerPosY %f",centerPosition.x, centerPosition.y);

	BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y - height / 2 }, BaseTexture::kDebugTexture, { width,height }, 0, RED);
}



// どちらもUpdate()で毎フレーム呼び出すこと

// 移動関連
void Player::Move() {

	// 左移動
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x -= 0.5f;
		}
	}
	else if(velocity.x < 0) {
		velocity.x += 0.5f;
	}
	// 右移動
	if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f;
		}
	}
	else if (velocity.x > 0) {
		velocity.x -= 0.5f;
	}
}

// ワイヤー関連
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
