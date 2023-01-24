#include "Class/Object/Enemy/Enemy.h"

// コンストラクタ
Enemy::Enemy(Point _centerPosition, Point size,Object* _object) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

	object = _object;

	Initialize();
}

Enemy::~Enemy() {

}

void Enemy::SuccessorInitialize() {

	// 速度
	velocity = { 0,0 };
	// 加速度
	acceleration = { 0,0 };

	// 回転角度（Degree）
	angle = 0.0f;
	// 回転速度（Degree）
	angleVelocity = 0;

	//空中にいるかどうか
	isFlying = true;

	direct = -1;

}

void Enemy::SuccessorUpdate() {

	if (object->GetCenterPosition().x < centerPosition.x) {
		direct = -1;
	}
	else if(centerPosition.x < object->GetCenterPosition().x){
		direct = 1;
	}
	else {
		direct = 0;
	}

	// 左移動
	if (direct < 0) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x -= 0.5f;
		}
	}
	else if (0 < direct) {
		// 右移動
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f;
		}
	}
	else {
		
	}
}

void Enemy::Draw() {
	if (BaseMath::CheckHitBox(centerPosition, width, height, angle, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()))) {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, RED);
	}
	else {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, 0x770000FF);
	}

}

ObjectType Enemy::GetType() {
	return typeEnemy;
}
