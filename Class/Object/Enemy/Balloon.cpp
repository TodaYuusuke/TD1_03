#include "Class/Object/Enemy/Balloon.h"

// �R���X�g���N�^
Balloon::Balloon(Point _centerPosition, Point size,Object* _object) {

	centerPosition = _centerPosition;
	width = 64;
	height = 64;

	object = _object;

	Initialize();
}

Balloon::~Balloon() {

}

void Balloon::SuccessorInitialize() {

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
}

void Balloon::Update() {
	if (isAlive) {

		acceleration = { 0,0 };

		// �����x�⑬�x���p����ŕύX
		SuccessorUpdate();

		// �����x�ɏd�͂�ǉ�
		if (isFlying) {
			if (velocity.y < -(BaseConst::kPlayerVelocityLimit)) {

			}
			// ���x�����ɂ������Ă���Ƃ��͒ǉ����Ȃ�
			else {
				acceleration.y -= BaseConst::kPlayerGravitationalAcceleration;
			}
		}

		// �����x��ǉ�
		velocity.x += acceleration.x;
		velocity.y += acceleration.y;

		// �g���l�����O�h�~�̂��ߕ���
		for (int i = 0; i < 10; i++) {
			// ���x��ǉ�
			centerPosition.x += velocity.x * 0.1f;
			centerPosition.y += velocity.y * 0.1f;

			CheckFieldHitBox();
		}

		// ��]���x��ǉ�
		angle += angleVelocity;

		if (angleVelocity > 0) {
			centerPosition.x -= 0.5f * angleVelocity;
		}
		else if (angleVelocity < 0) {
			centerPosition.x -= 0.5f * angleVelocity;
		}


		// ���x������������������
		if (velocity.x > 0) {
			velocity.x -= 0.02f;
			if (velocity.x < 0) {
				velocity.x = 0;
			}
		}
		else if (velocity.x < 0) {
			velocity.x += 0.02f;
			if (velocity.x > 0) {
				velocity.x = 0;
			}
		}
		if (velocity.y > 0) {
			velocity.y -= 0.02f;
			if (velocity.y < 0) {
				velocity.y = 0;
			}
		}
		else if (velocity.y < 0) {
			velocity.y += 0.02f;
			if (velocity.y > 0) {
				velocity.y = 0;
			}
		}
	}
}
void Balloon::SuccessorUpdate() {
	elapsedFrame++;
	degree+=5;
	if (degree > 360) {
		degree = 0;
	}
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
		if (direct == -1) {
			BaseEffectManager::MakeNewEffectBalloonDead(centerPosition, false);
		}
		else {
			BaseEffectManager::MakeNewEffectBalloonDead(centerPosition, true);
		}
		Novice::PlayAudio(BaseAudio::kEnemyBallonDead,0,BaseAudio::SEvolume);
	}

	EnemyAttackHitBox::MakeNewHitBox(centerPosition, width, height, 0, 1);	
}

void Balloon::Draw() {
	if (isAlive) {
		Point p = centerPosition;
		p.y += BaseMath::TurnPoint({ 0,5 }, degree).y;

		if (direct == -1) {
			BaseDraw::DrawQuad(p, BaseTexture::kEnemyBalloon[elapsedFrame % 10 / 5], { width,height }, 1.0f, angle, WHITE);
		}
		else {
			BaseDraw::DrawQuad(p, BaseTexture::kEnemyBalloon[elapsedFrame % 10 / 5 + 2], { width,height }, 1.0f, angle, WHITE);
		}
	}
}

ObjectType Balloon::GetType() {
	return typeBalloon;
}
