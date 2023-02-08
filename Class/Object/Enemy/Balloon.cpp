#include "Class/Object/Enemy/Balloon.h"

// �R���X�g���N�^
Balloon::Balloon(Point _centerPosition, Point size,Object* _object) {

	centerPosition = _centerPosition;
	width = 50;
	height = 50;

	object = _object;

	Initialize();
}

Balloon::~Balloon() {

}

void Balloon::SuccessorInitialize() {

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

}

void Balloon::SuccessorUpdate() {
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

	// �����蔻�� -> �q�b�g�����S
	if (isStub) {
		isAlive = false;
		Novice::PlayAudio(BaseAudio::kEnemyBallonDead,0,BaseAudio::SEvolume);
	}

	EnemyAttackHitBox::MakeNewHitBox(centerPosition, width, height, 0, 1);	
}

void Balloon::Draw() {
	if (isAlive) {
		if (BaseMath::CheckHitBox(centerPosition, width, height, angle, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()))) {
			BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, RED);
		}
		else {
			BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, 0x770000FF);
		}
	}
}

ObjectType Balloon::GetType() {
	return typeBalloon;
}
