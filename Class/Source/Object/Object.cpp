#include "Class/Include/Object/Object.h"

void Object::Initialize() {

	SuccessorInitialize();

	CheckFieldHitBox();
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

	if (angleVelocity > 0) {
		centerPosition.x -= 0.5f * angleVelocity;
	}
	else if (angleVelocity < 0) {
		centerPosition.x -= 0.5f * angleVelocity;
	}

	// ��]���x�����������Ă���
	/*if (angleVelocity > BaseConst::kPlayerVelocityLimit) {
		angleVelocity -= 0.05f;
		if (angleVelocity < 0) {
			angleVelocity = 0;
		}
	}
	else if (angleVelocity < -BaseConst::kPlayerVelocityLimit) {
		angleVelocity += 0.05f;
		if (angleVelocity > 0) {
			angleVelocity = 0;
		}
	}*/


	CheckFieldHitBox();
}

void Object::SuccessorUpdate() {

}

void Object::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
}


// �����o�ϐ��Ɋ֗^����֐�

// �I�u�W�F�N�g�̒��S���W���󂯎��֐�
// �Ԃ�l�F���S���W
// �����F�Ȃ�
Point Object::GetCenterPosition() {
	return centerPosition;
}

// �I�u�W�F�N�g�̑��x���󂯎��֐�
// �Ԃ�l�F���x�̃x�N�g��
// �����F�Ȃ�
Point Object::GetVelocity() {
	return { velocity.x - 0.5f * angleVelocity, velocity.y };
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


// �����蔻��֘A

bool Object::CheckHitBox(Point hitPosition) {
	return BaseMath::CheckHitBox(centerPosition, width, height, angle, hitPosition);
}

bool Object::CheckHitBox(Box hitPosition) {
	if (BaseMath::CheckHitBox({ BaseDraw::WorldtoScreen(centerPosition),width,height }, { BaseDraw::WorldtoScreen(hitPosition.position),hitPosition.width,hitPosition.height })){
		return true;
	}
	else {
		return false;
	}
}


// ���̑�

ObjectType Object::GetType() {
	return typeObject;
}


// �֐�

// �I�u�W�F�N�g���̂̓����蔻����`�F�b�N����֐�
void Object::CheckFieldHitBox() {

	// 0 ... ��
	// 1 ... ��
	// 2 ... ��
	// 3 ... �E
	// ��4�_��p��
	checkRhombusPoint[0] = BaseMath::TurnPoint({ 0, +height / 2 }, angle);
	checkRhombusPoint[1] = BaseMath::TurnPoint({ 0, -height / 2 }, angle);
	checkRhombusPoint[2] = BaseMath::TurnPoint({ -width / 2, 0 }, angle);
	checkRhombusPoint[3] = BaseMath::TurnPoint({ +width / 2, 0 }, angle);

	// 0 ... ����
	// 1 ... �E��
	// 2 ... ����
	// 3 ... �E��
	// ��4�_��p��
	checkQuadPoint[0] = BaseMath::TurnPoint({ -width / 2, +height / 2 }, angle);
	checkQuadPoint[1] = BaseMath::TurnPoint({ +width / 2, +height / 2 }, angle);
	checkQuadPoint[2] = BaseMath::TurnPoint({ -width / 2, -height / 2 }, angle);
	checkQuadPoint[3] = BaseMath::TurnPoint({ +width / 2, -height / 2 }, angle);


	// centerPosition��ǉ�
	for (int i = 0; i < 4; i++) {
		checkRhombusPoint[i].x += centerPosition.x;
		checkRhombusPoint[i].y += centerPosition.y;
		checkQuadPoint[i].x += centerPosition.x;
		checkQuadPoint[i].y += centerPosition.y;
	}


	// N-1�񑀍�
	for (int i = 0; i < 4 - 1; i++) {
		// �E����\�[�g�i��������ƕϐ���1������j
		for (int j = 4 - 1; i < j; j--) {
			if (checkRhombusPoint[j].y < checkRhombusPoint[j - 1].y) { // ���̐��l����������Ό���
				// �X���b�v
				Point p = checkRhombusPoint[j];
				checkRhombusPoint[j] = checkRhombusPoint[j - 1];
				checkRhombusPoint[j - 1] = p;
			}
			if (checkQuadPoint[j].y < checkQuadPoint[j - 1].y) { // ���̐��l����������Ό���
				// �X���b�v
				Point p = checkQuadPoint[j];
				checkQuadPoint[j] = checkQuadPoint[j - 1];
				checkQuadPoint[j - 1] = p;
			}
		}
	}

	// X���W�������̕���[1]�ɁA�E���̕���[2]�ɑ��
	if (checkRhombusPoint[1].x < checkRhombusPoint[2].x) { // ���̐��l����������Ό���
		// �X���b�v
		Point p = checkRhombusPoint[1];
		checkRhombusPoint[1] = checkRhombusPoint[2];
		checkRhombusPoint[2] = p;
	}
	if (checkQuadPoint[1].x < checkQuadPoint[2].x) { // ���̐��l����������Ό���
		// �X���b�v
		Point p = checkQuadPoint[1];
		checkQuadPoint[1] = checkQuadPoint[2];
		checkQuadPoint[2] = p;
	}


	// �㉺���E�̃q�b�g�{�b�N�X�`�F�b�N
	CheckHitBoxRhombus(checkQuadPoint, checkRhombusPoint);
	// ����A�����A�E��A�E���̃q�b�g�{�b�N�X�`�F�b�N
	//CheckHitBoxQuad(checkQuadPoint);

}

// �㉺���E�̓����蔻��̊֐�
void Object::CheckHitBoxRhombus(Point checkQuadPoint[], Point checkRhombusPoint[]) {

	// 4�p�̍��W�����؂��q�b�g���Ă���W���m�F

	float kAddAngleVelocity = 0.3f;

	// ��_���q�b�g���Ă���ꍇ
	if (MapManager::CheckHitBox(checkQuadPoint[0]) && MapManager::CheckHitBox(checkQuadPoint[1]) || MapManager::CheckHitBox(checkQuadPoint[0]) && MapManager::CheckHitBox(checkQuadPoint[2])) {
		// �������Ȃ�
		velocity.y = 0;
		isFlying = false;

		// �q�b�g���Ȃ��Ȃ�܂ŏ�֕␳����
		while (MapManager::CheckHitBox(checkQuadPoint[0])) {
			// ���W�����
			centerPosition.y += 1;
			// �Čv�Z
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}
		}

		if (((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -1 && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < 1) ||
			((int)checkQuadPoint[0].y - (int)checkQuadPoint[2].y > -1 && (int)checkQuadPoint[0].y - (int)checkQuadPoint[2].y < 1) ) {
			angle = GetNearestValue(angle);
			angleVelocity = 0;
		}
	}
	// ���̏ꍇ
	else if (MapManager::CheckHitBox(checkQuadPoint[0])) {

		// �q�b�g���Ȃ��Ȃ�܂ŏ�֕␳����
		while (MapManager::CheckHitBox(checkQuadPoint[0])) {
			// ���W�����
			centerPosition.y += 1;
			// �Čv�Z
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}
		}

		// ���̓_�̕���y���W�����̏ꍇ -> ����]�̃x�N�g���𑫂�
		if (checkQuadPoint[1].y < checkQuadPoint[2].y) {
			if ((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -1 && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < 1) {
				angle = GetNearestValue(angle);
				angleVelocity = 0;
			}
			else {
				angleVelocity -= kAddAngleVelocity;
			}
		}
		// �E�̓_�̕���y���W�����̏ꍇ -> �E��]�̃x�N�g���𑫂�
		else {
			if ((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -1 && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < 1) {
				angle = GetNearestValue(angle);
				angleVelocity = 0;
			}
			else {
				angleVelocity += kAddAngleVelocity;
			}
		}

		velocity.y = 0;
		isFlying = false;
	}
	// ��ԉ��̒��S���G��Ă���ꍇ
	else if (MapManager::CheckHitBox(checkRhombusPoint[0])) {

		// �q�b�g���Ȃ��Ȃ�܂ŏ�֕␳����
		while (MapManager::CheckHitBox(checkRhombusPoint[0])) {
			// ���W�����
			centerPosition.y += 1;
			// �Čv�Z
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}
		}

		if (angleVelocity > 0) {
			angleVelocity += kAddAngleVelocity;
		}
		else if (angleVelocity < 0) {
			angleVelocity -= kAddAngleVelocity;
		}
		else {
			if (checkQuadPoint[0].x < checkRhombusPoint[0].x) {
				angleVelocity += kAddAngleVelocity;
			}
			else {
				angleVelocity -= kAddAngleVelocity;
			}
		}

		velocity.y = 0;
		isFlying = false;
	}
	else {
		isFlying = true;

		// ���̏ꍇ
		if (MapManager::CheckHitBox(checkQuadPoint[1])) {
			// �ړ���
			int move = 0;
			// �q�b�g���Ȃ��Ȃ�܂ŏ�֕␳����
			while (MapManager::CheckHitBox(checkQuadPoint[1])) {
				move += 1;
				// ���W�����
				centerPosition.y += 1;
				// �Čv�Z
				for (int i = 0; i < 4; i++) {
					checkQuadPoint[i].y += 1;
					checkRhombusPoint[i].y += 1;
				}

				// ����������x��܂ŕ␳���Ȃ��ƃ_���ȏꍇ�A�␳���C�����E�����ɕ␳
				if (move > BaseConst::kMapChipSizeHeight) {
					// ���W������
					centerPosition.y -= move;
					// �Čv�Z
					for (int i = 0; i < 4; i++) {
						checkQuadPoint[i].y -= move;
						checkRhombusPoint[i].y -= move;
					}

					while (MapManager::CheckHitBox(checkQuadPoint[1])) {
						// ���W���E��
						centerPosition.x -= 1;
						// �Čv�Z
						for (int i = 0; i < 4; i++) {
							checkQuadPoint[i].x -= 1;
							checkRhombusPoint[i].x -= 1;
						}
					}

					angleVelocity *= -0.9f;

					break;
				}
			}
			angleVelocity += kAddAngleVelocity;
		}
		// �E�̏ꍇ
		else if (MapManager::CheckHitBox(checkQuadPoint[2])) {

			// �ړ���
			int move = 0;
			// �q�b�g���Ȃ��Ȃ�܂ŏ�֕␳����
			while (MapManager::CheckHitBox(checkQuadPoint[2])) {
				move += 1;
				// ���W�����
				centerPosition.y += 1;
				// �Čv�Z
				for (int i = 0; i < 4; i++) {
					checkQuadPoint[i].y += 1;
					checkRhombusPoint[i].y += 1;
				}

				// ����������x��܂ŕ␳���Ȃ��ƃ_���ȏꍇ�A�␳���C�����E�����ɕ␳
				if (move > BaseConst::kMapChipSizeHeight) {
					// ���W������
					centerPosition.y -= move;
					// �Čv�Z
					for (int i = 0; i < 4; i++) {
						checkQuadPoint[i].y -= move;
						checkRhombusPoint[i].y -= move;
					}

					while (MapManager::CheckHitBox(checkQuadPoint[2])) {
						// ���W���E��
						centerPosition.x += 1;
						// �Čv�Z
						for (int i = 0; i < 4; i++) {
							checkQuadPoint[i].x += 1;
							checkRhombusPoint[i].x += 1;
						}
					}

					angleVelocity *= -0.9f;

					break;
				}
			}
			angleVelocity -= kAddAngleVelocity;
		}
		// ��̏ꍇ
		else if (MapManager::CheckHitBox(checkQuadPoint[3])) {

		}
	}




	/*

	// �����蔻����`�F�b�N������W
	Point checkPoint;

	// ���̓_�i��ԉ��̓_�j
	checkPoint = checkPosition[0];
	// �����q�b�g�����Ƃ�
	if (MapManager::CheckHitBox(checkPoint)) {
		// ���x��0��
		velocity.y = 0;
		// ���ł��Ȃ��̂Ńt���O��߂�
		isFlying = false;

		// �q�b�g���Ȃ��Ȃ�܂ŏ�֕␳����
		while (MapManager::CheckHitBox(checkPoint)) {
			// ���W�����
			//centerPosition.y += 1;
			// �Čv�Z
			checkPoint.y += 1;
		}
	}
	// ����̃}�X���q�b�g���Ă��Ȃ��Ƃ��͋󒆂Ƃ������ƂȂ̂Ńt���O��true��
	else if (!MapManager::CheckHitBox({ checkPoint.x ,checkPoint.y - 1 })) {
		isFlying = true;
	}

	// �����q�b�g�����Ƃ�
	if (MapManager::CheckHitBox(checkPosition[1])) {
		// ���x��0��
		velocity.x = 0;

		// �q�b�g���Ȃ��Ȃ�܂ŉE�֕␳����
		while (MapManager::CheckHitBox(checkPosition[1])) {
			// ���W���E��
			//centerPosition.x += 1;
			// �Čv�Z
			checkPosition[1].x += 1;
		}
	}

	// �E�̓_
	checkPoint = checkPosition[2];
	// �E���q�b�g�����Ƃ�
	if (MapManager::CheckHitBox(checkPoint)) {
		// ���x��0��
		velocity.x = 0;

		// �q�b�g���Ȃ��Ȃ�܂ō��֕␳����
		while (MapManager::CheckHitBox(checkPoint)) {
			// ���W������
			//centerPosition.x -= 1;
			// �Čv�Z
			checkPoint.x -= 1;
		}
	}

	// ��̓_�i��ԏ�̓_�j
	checkPoint = checkPosition[3];
	// �オ�q�b�g�����Ƃ�
	if (MapManager::CheckHitBox(checkPoint)) {
		// ���x��0��
		velocity.y = 0;

		// �q�b�g���Ȃ��Ȃ�܂ŉ��֕␳����
		while (MapManager::CheckHitBox(checkPoint)) {
			// ���W������
			//centerPosition.y -= 1;
			// �Čv�Z
			checkPoint.y -= 1;
		}
	}



	*/

}
