#include "Class/Object/Enemy/Enemy.h"

// �R���X�g���N�^
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

	// ���ړ�
	if (direct < 0) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x -= 0.5f;
		}
	}
	else if (0 < direct) {
		// �E�ړ�
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
