#include "Class/Include/Object/Object.h"

void Object::Initialize() {

	SuccessorInitialize();
 }

void Object::SuccessorInitialize(){

	// ���S���W
	centerPosition = { -10000,-10000 };
	// ���x
	velocity = { 0,0 };
	// �����x
	acceleration = { 0,0 };

	// ��]�p�x�iDegree�j
	angle = 0;
	// ��]���x�iDegree�j
	angleVelocity = 0;

	// �����蔻��̃T�C�Y�i����̓_����̒����j
	width = 0;
	height = 0;

	//�󒆂ɂ��邩�ǂ���
	isFlying = true;
 }

void Object::Update() {

	acceleration = { 0,0 };

	// �����x�⑬�x���p����ŕύX
	SuccessorUpdate();

	if (isFlying) {
		// �����x�ɏd�͂�ǉ�
		acceleration.y -= BaseConst::kPlayerGravitationalAcceleration;
	}

	// �����x��ǉ�
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	// ���x�����ɂ������Ă���ꍇ�A����������
	if (velocity.x > BaseConst::kPlayerVelocityLimit) {
		velocity.x -= 0.02f;
	}
	if (velocity.x < -(BaseConst::kPlayerVelocityLimit)) {
		velocity.x += 0.02f;
	}
	if (velocity.y > BaseConst::kPlayerVelocityLimit) {
		velocity.y -= 0.02f;
	}
	if (velocity.y < -(BaseConst::kPlayerVelocityLimit)) {
		velocity.y += 0.02f;
	}

	// ���x��ǉ�
	centerPosition.x += velocity.x;
	centerPosition.y += velocity.y;


	// ��]���x��ǉ�
	angle += angleVelocity;

	CheckFieldHitBox();
}

void Object::SuccessorUpdate() {

}

void Object::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
}


// �I�u�W�F�N�g�ɑ��x�x�N�g���𑫂��֐�
// �Ԃ�l�F�Ȃ�
// �����F�������x
void Object::AddVelocity(Point _addVelocity) {
	velocity.x += _addVelocity.x;
	velocity.y += _addVelocity.y;
}

// �I�u�W�F�N�g�ɉ�]���x�𑫂��֐�
// �Ԃ�l�F�Ȃ�
// �����F�������x
void Object::AddVelocity(float _addVelocity) {
	angleVelocity += _addVelocity;
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
	bool result = false;
	if (centerPosition.x - width / 2.0f < 0) {
		centerPosition.x = width / 2.0f;
		acceleration.x = 0;
		velocity.x = 0;
		result = true;
	}
	else if(BaseConst::kWindowWidth < centerPosition.x + width / 2.0f) {
		centerPosition.x = BaseConst::kWindowWidth - (width / 2.0f);
		acceleration.x = 0;
		velocity.x = 0;
		result = true;
	}
	// �㉺
	if (centerPosition.y - height / 2.0f < 0) {
		centerPosition.y = height / 2.0f;
		isFlying = false;
		acceleration.y = 0;
		velocity.y = 0;
		result = true;
	}
	else if (BaseConst::kWindowHeight < centerPosition.y + height / 2.0f) {
		centerPosition.y = BaseConst::kWindowHeight - (height / 2.0f);
		acceleration.y = 0;
		velocity.y = 0;
		result = true;
	}
	return false;
}

ObjectType Object::GetType() {
	return typeObject;
}

Point Object::GetCenterPosition() {
	return centerPosition;
}

Point Object::GetVelocity() {
	return velocity;
}