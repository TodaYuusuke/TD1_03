#include "Class/Object/Enemy/IronBalloon.h"

// �R���X�g���N�^
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

	// ���x
	velocity = { 0,0 };
	// �����x
	acceleration = { 0,0 };

	// ��]�p�x�iDegree�j
	angle = 0.0f;
	// ��]���x�iDegree�j
	angleVelocity = 0;

	//�󒆂ɂ��邩�ǂ���
	isFlying = true;
	isAlive = true;

	direct = -1;

	// �����蔻����O���ɓn��
	num = ObjectHitBox::AddHitBox(&centerPosition, &width, &height, &angle, &isAlive, false);
}

void IronBalloon::SuccessorUpdate() {
	elapsedFrame++;

	degree += 5;
	if (degree > 360) {
		degree = 0;
	}
	// ��]����ɏ�����
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

		// ���ړ�
		if (direct < 0) {
			if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
				acceleration.x -= 0.5f;
			}
		}
		else if (0 < direct) {
			// �E�ړ�
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
