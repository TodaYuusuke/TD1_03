#include "Class/Object/Enemy/IronBalloon.h"

// コンストラクタ
IronBalloon::IronBalloon(Point _centerPosition, Point size,Object* _object) {

	centerPosition = _centerPosition;
	width = 64;
	height = 64;

	object = _object;

	Initialize();
}

IronBalloon::~IronBalloon() {

}

void IronBalloon::SuccessorInitialize() {

	elapsedFrame = 0;
	degree = 0;

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
	isAlive = true;

	direct = -1;

	// 当たり判定を外部に渡す
	num = ObjectHitBox::AddHitBox(&centerPosition, &width, &height, &angle, &isAlive, false);
}

void IronBalloon::SuccessorUpdate() {
	elapsedFrame++;

	degree += 5;
	if (degree > 360) {
		degree = 0;
	}
	// 回転を常に初期化
	angle = 0;
	angleVelocity = 0;

	if (!isFlying) {
		if (object->GetCenterPosition().x < centerPosition.x) {
			direct = -1;
			angle = 0;
		}
		else if (centerPosition.x < object->GetCenterPosition().x) {
			direct = 1;
			angle = 90;
		}
		else {
			direct = 0;
			angle = 0;
		}

		// 左移動
		if (direct < 0) {
			if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
				acceleration.x -= 0.5f;
			}
		}
		else if (0 < direct) {
			// 右移動
			if (velocity.x < BaseConst::kPlayerVelocityLimit) {
				acceleration.x += 0.5f;
			}
		}
		else {

		}
	}

	EnemyAttackHitBox::MakeNewHitBox(centerPosition, width, height, 0, 1);
}

void IronBalloon::Draw() {
	if (isAlive) {
		Point p = centerPosition;
		p.y += BaseMath::TurnPoint({ 0,5 }, degree).y;

		if (direct == -1) {
			BaseDraw::DrawQuad(p, BaseTexture::kEnemyIronBalloon[elapsedFrame % 10 / 5], { width,height }, 1.0f, 0, WHITE);
		}
		else {
			BaseDraw::DrawQuad(p, BaseTexture::kEnemyIronBalloon[elapsedFrame % 10 / 5 + 2], { width,height }, 1.0f, 0, WHITE);
		}
	}
}

ObjectType IronBalloon::GetType() {
	return typeIronBalloon;
}
