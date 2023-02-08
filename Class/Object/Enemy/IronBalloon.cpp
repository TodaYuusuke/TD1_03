#include "Class/Object/Enemy/IronBalloon.h"

// �R���X�g���N�^
IronBalloon::IronBalloon(Point _centerPosition, Point size,Object* _object) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

	object = _object;

	Initialize();
}

IronBalloon::~IronBalloon() {

}

void IronBalloon::SuccessorInitialize() {

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
	num = ObjectHitBox::AddHitBox(&centerPosition, &width, &height, &angle, &isAlive);
}

void IronBalloon::SuccessorUpdate() {
	// ��]����ɏ�����
	angle = 0;
	angleVelocity = 0;

	if (!isFlying) {
		if (object->GetCenterPosition().x < centerPosition.x) {
			direct = -1;
		}
		else if (centerPosition.x < object->GetCenterPosition().x) {
			direct = 1;
		}
		else {
			direct = 0;
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
		if (BaseMath::CheckHitBox(centerPosition, width, height, angle, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()))) {
			BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, RED);
		}
		else {
			BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, 0x808080FF);
		}
	}
}

ObjectType IronBalloon::GetType() {
	return typeIronBalloon;
}
