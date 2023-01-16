#include "Class/Include/Object/Player/Player.h"

// コンストラクタ
Player::Player(Point centerPosition, WireManager* _wireManager) {
	this->centerPosition = centerPosition;
	wireManager = _wireManager;
	reticlePosition = { -100,-100 };
}
// デストラクタ
Player::~Player() {

}


// 初期化
void Player::SuccessorInitialize() {
	centerPosition = { -10000,-10000 };

	width = 100;
	height = 100;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;
	reticlePosition = { -10000,-10000 };

	//wireManager->Initialize();

}
// 更新
void Player::SuccessorUpdate() {

	reticlePosition = BaseInput::GetMousePosition();

	Move();
	ShotWire();

}
// 描画
void Player::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
	BaseDraw::DrawQuad(BaseDraw::WorldtoScreen(reticlePosition), BaseTexture::kDebugTexture, { 20,20 }, 1.0f, 0.0f, WHITE);
	Novice::ScreenPrintf(10, 10, "Reticle:%.2f %.2f", reticlePosition.x, reticlePosition.y);
	Novice::ScreenPrintf(10, 30, "center:%.2f %.2f", centerPosition.x, centerPosition.y);
}


// どちらもUpdate()で毎フレーム呼び出すこと

// 移動関連
void Player::Move() {
	// 左への移動
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

// ワイヤー関連
void Player::ShotWire() {
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		reticlePosition = BaseInput::GetMousePosition();
		wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition), this);


	}
	if (BaseInput::GetMouseState(RightClick, Trigger)) {
		wireManager->Attract();
	}
}


ObjectType Player::GetType() {
	return typePlayer;
}
