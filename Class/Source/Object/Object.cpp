#include "Class/Include/Object/Object.h"

void Object::Initialize() {
	kGravitationalAcceleration = 9.8f;
	SuccessorInitialize();
 }

void Object::SuccessorInitialize(){

	centerPosition = { 100,100 };

	width = 100;
	height = 100;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;

	texture = BaseTexture::kDebugTexture;

 }

void Object::Update() {

	// �����x�⑬�x���p����ŕύX
	SuccessorUpdate();

	if (isFlying) {
		// �����x�ɏd�͂�ǉ�
		acceleration.y -= kGravitationalAcceleration;
	}

	// �ύX���������x��ǉ�
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	// ���W�ɑ��x���ړ�������
	centerPosition.x += velocity.x;
	centerPosition.y += velocity.y;


	CheckFieldHitBox();

}

void Object::SuccessorUpdate() {

}

void Object::Draw() {
	BaseDraw::DrawQuad(centerPosition, texture, { 100,100 }, 1.0f, 0.0f, WHITE);
}

bool Object::CheckHitBox(Point hitPosition) {
	// ���E
	if (centerPosition.x - width / 2.0f < hitPosition.x && hitPosition.x < centerPosition.x + width / 2.0f) {
		// �㉺
		if (centerPosition.y - height / 2.0f < hitPosition.y && hitPosition.y < centerPosition.y + height / 2.0f) {
			return true;
		}
	}
	return false;
}

bool Object::CheckHitBox(Box hitPosition) {
	if (BaseMath::CheckHitBox({ BaseDraw::WorldtoScreen(centerPosition),width,height }, { BaseDraw::WorldtoScreen(hitPosition.position),hitPosition.width,hitPosition.height })){
		return true;
	}
	else {
		return false;
	}
}

bool Object::CheckFieldHitBox() {
	// �t�B�[���h�O�ɏo�����̏���
	// ���E
	if (centerPosition.x - width / 2.0f < 0) {
		centerPosition.x -= centerPosition.x - width / 2.0f;
		return true;
	}
	else if(1920 < centerPosition.x + width / 2.0f) {
		centerPosition.x += 1920 - (centerPosition.x + width / 2.0f);
		return true;
	}
	// �㉺
	if (centerPosition.y - height / 2.0f < 0) {
		centerPosition.y -= centerPosition.y - height / 2.0f;
		isFlying = false;
		return true;
	}
	else if (1080 < centerPosition.y + height / 2.0f) {
		centerPosition.y += 1080 - (centerPosition.y + height / 2.0f);
		return true;
	}
}
