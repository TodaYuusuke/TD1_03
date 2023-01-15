#include "Class/Include/Object/Player/Player.h"

// �R���X�g���N�^
Player::Player(Point centerPosition, WireManager* _wireManager) {
	this->centerPosition = centerPosition;
	wireManager = _wireManager;
	reticlePosition = { -100,-100 };
}
// �f�X�g���N�^
Player::~Player() {

}


// ������
void Player::SuccessorInitialize() {
	centerPosition = { -10000,-10000 };

	width = 1;
	height = 1;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;
	reticlePosition = { -10000,-10000 };

}
// �X�V
void Player::SuccessorUpdate() {

	reticlePosition = BaseInput::GetMousePosition();

	Move();
	//wireManager.Update();
	ShotWire();

}
// �`��
void Player::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
	BaseDraw::DrawQuad(BaseDraw::WorldtoScreen(reticlePosition), BaseTexture::kDebugTexture, { 20,20 }, 1.0f, 0.0f, WHITE);
	Novice::ScreenPrintf(10, 10, "Reticle:%.2f %.2f", reticlePosition.x, reticlePosition.y);
	Novice::ScreenPrintf(10, 30, "center:%.2f %.2f", centerPosition.x, centerPosition.y);
}



// �ǂ����Update()�Ŗ��t���[���Ăяo������

// �ړ��֘A
void Player::Move() {

	// ���ړ�
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		velocity.x -= 0.2f;
	}
	// �E�ړ�
	if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		velocity.x += 0.2f;
	}
}

// ���C���[�֘A
void Player::ShotWire() {
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		reticlePosition = BaseInput::GetMousePosition();
		//float angle = atan2(centerPosition.y - ReticlePosition.y, centerPosition.x - ReticlePosition.x);

		//wireManager->Shot(centerPosition, BaseMath::RadiantoDegree(angle), this);
		wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition), this);



	}
	if (BaseInput::GetMouseState(RightClick, Trigger)) {
		wireManager->Attract();
	}
}


/*
// �㉺���E�̓����蔻��̊֐�
void Player::CheckHitBoxRhombus() {

	// �����蔻����`�F�b�N������W
	Point checkPoint;


	// �v���C���[�����̓_
	checkPoint = { position.x,position.y + 24 / 2 };
	// �オ�q�b�g�����Ƃ�
	if (Map::isHittingBlock(checkPoint)) {
		// ���x��0��
		velocity.y = 0;

		// �q�b�g���Ȃ��Ȃ�܂ŉ��֕␳����
		while (Map::isHittingBlock(checkPoint)) {
			// ���W������
			position.y -= 1;
			// �Čv�Z
			checkPoint.y -= 1;
		}
	}



	// �v���C���[���牺�̓_
	checkPoint = { position.x,position.y - 24 / 2 };
	// �����q�b�g�����Ƃ�
	if (Map::isHittingBlock(checkPoint)) {
		// ���x��0��
		velocity.y = 0;
		// ���ł��Ȃ��̂Ńt���O��߂�
		isFlying = false;
		BaseEffectManager::MakeNewEffect(position, EffectType::JumpDust);

		// �q�b�g���Ȃ��Ȃ�܂ŏ�֕␳����
		while (Map::isHittingBlock(checkPoint)) {
			// ���W�����
			position.y += 1;
			// �Čv�Z
			checkPoint.y += 1;
		}
	}
	// ����̃}�X���q�b�g���Ă��Ȃ��Ƃ��͋󒆂Ƃ������ƂȂ̂Ńt���O��true��
	else if (!Map::isHittingBlock({ checkPoint.x ,checkPoint.y - 1 })) {
		isFlying = true;
	}



	// �v���C���[���獶�̓_
	checkPoint = { position.x - 24 / 2,position.y };
	// �����q�b�g�����Ƃ�
	if (Map::isHittingBlock(checkPoint)) {
		// ���x��0��
		velocity.x = 0;
		// ���[�V�������łȂ��ꍇ ���� �n�ʂɂ��Ă��Ȃ��ꍇ -> �Ǌ���t���O��true��
		if (!isJumping && !isDashing && !isKickedWall && isFlying) {
			isSlipingLeftWall = true;
			setPlayerToMouseAngle();
		}

		// �q�b�g���Ȃ��Ȃ�܂ŉE�֕␳����
		while (Map::isHittingBlock(checkPoint)) {

			// ���W���E��
			position.x += 1;
			// �Čv�Z
			checkPoint.x += 1;
		}
	}
	// ����̃}�X���q�b�g���Ă��Ȃ��Ƃ��͕Ǌ���I���Ƃ������ƂȂ̂Ńt���O��true��
	else if (!Map::isHittingBlock({ checkPoint.x - 32,checkPoint.y })) {
		isSlipingLeftWall = false;
	}
	// �n�ʂɂ����ꍇ���t���O��false��
	else if (!isFlying) {
		isSlipingLeftWall = false;
	}

	// �������ɕǂ�����ꍇ -> ���x������
	if (Map::isHittingBlock({ checkPoint.x - 1 ,checkPoint.y })) {
		if (velocity.x < 0) {
			velocity.x = 0;
		}
	}



	// �v���C���[����E�̓_
	checkPoint = { position.x + 24 / 2,position.y };
	// �E���q�b�g�����Ƃ�
	if (Map::isHittingBlock(checkPoint)) {
		// ���x��0��
		velocity.x = 0;
		// ���[�V�������łȂ��ꍇ ���� �n�ʂɂ��Ă��Ȃ��ꍇ -> �Ǌ���t���O��true��
		if (!isJumping && !isDashing && !isKickedWall && isFlying) {
			isSlipingRightWall = true;
			setPlayerToMouseAngle();
		}

		// �q�b�g���Ȃ��Ȃ�܂ō��֕␳����
		while (Map::isHittingBlock(checkPoint)) {
			// ���W������
			position.x -= 1;
			// �Čv�Z
			checkPoint.x -= 1;
		}
	}
	// ��E�̃}�X���q�b�g���Ă��Ȃ��Ƃ��͕Ǌ���I���Ƃ������ƂȂ̂Ńt���O��true��
	else if (!Map::isHittingBlock({ checkPoint.x + 32,checkPoint.y })) {
		isSlipingRightWall = false;
	}
	// �n�ʂɂ����ꍇ���t���O��false��
	else if (!isFlying) {
		isSlipingRightWall = false;
	}

	// �����E�ɕǂ�����ꍇ -> ���x������
	if (Map::isHittingBlock({ checkPoint.x + 1 ,checkPoint.y })) {
		if (velocity.x > 0) {
			velocity.x = 0;
		}
	}
}

// ����A�����A�E��A�E���̓����蔻��̊֐�
void Player::CheckHitBoxQuad() {

	// �����蔻����`�F�b�N������W
	Point checkPoint;



	// �v���C���[���獶��̓_
	checkPoint = { position.x - 24 / 2,position.y + 24 / 2 };
	// ���オ�q�b�g�����Ƃ� -> �␳����
	if (Map::isHittingBlock(checkPoint)) {
		// �␳���̍��W
		Point correctionPos = { 0,0 };

		// �E���ɕ␳����
		while (Map::isHittingBlock(checkPoint)) {
			correctionPos.x += 1;
			correctionPos.y -= 1;
			checkPoint.x += 1;
			checkPoint.y -= 1;
		}

		// �␳�I����A��苗�����Z���ق��݂̂�K�����A�����ق��͔j������

		// y�̂ق���x���Z��or�����̏ꍇ -> y��K�����Ax�͔j��
		if (-correctionPos.y <= correctionPos.x) {
			// ���x���v���X�̂Ƃ��̂�0��
			if (velocity.y > 0) {
				velocity.y = 0;
			}

			// �␳�����s
			position.y += correctionPos.y;
		}
		// x�̂ق���y���Z���ꍇ -> x��K�����Ay�͔j��
		else {
			// ���x���}�C�i�X�̂Ƃ��̂�0��
			if (velocity.x < 0) {
				velocity.x = 0;
			}

			// �␳�����s
			position.x += correctionPos.x;
		}
	}



	// �v���C���[���獶���̓_
	checkPoint = { position.x - 24 / 2,position.y - 24 / 2 };
	// �������q�b�g�����Ƃ� -> �␳����
	if (Map::isHittingBlock(checkPoint)) {
		// �␳���̍��W
		Point correctionPos = { 0,0 };

		// �E��ɕ␳����
		while (Map::isHittingBlock(checkPoint)) {
			correctionPos.x += 1;
			correctionPos.y += 1;
			checkPoint.x += 1;
			checkPoint.y += 1;
		}

		// �␳�I����A��苗�����Z���ق��݂̂�K�����A�����ق��͔j������

		// y�̂ق���x���Z��or�����̏ꍇ -> y��K�����Ax�͔j��
		if (correctionPos.y <= correctionPos.x) {
			// ���x���}�C�i�X�̂Ƃ��̂�0��
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// ���ł��Ȃ��̂Ńt���O��߂�
			isFlying = false;

			// �␳�����s
			position.y += correctionPos.y;
		}
		// x�̂ق���y���Z���ꍇ -> x��K�����Ay�͔j��
		else {
			// ���x���}�C�i�X�̂Ƃ��̂�0��
			if (velocity.x < 0) {
				velocity.x = 0;
			}

			// �␳�����s
			position.x += correctionPos.x;
		}
	}
	// �����󒆔��肳�ꂽ��̏ꍇ
	else if (isFlying) {
		// ����̃}�X���q�b�g���Ă���Ƃ��͋󒆂ł͂Ȃ��Ƃ������ƂȂ̂Ńt���O��false��
		if (Map::isHittingBlock({ checkPoint.x,checkPoint.y - 1 })) {
			// �q�b�g���Ă��Ȃ��Ƃ��͋󒆂Ƃ������ƂȂ̂Ńt���O��true��
			isFlying = false;
		}
	}



	// �v���C���[����E��̓_
	checkPoint = { position.x + 24 / 2,position.y + 24 / 2 };
	// �E�オ�q�b�g�����Ƃ� -> �␳����
	if (Map::isHittingBlock(checkPoint)) {
		// �␳���̍��W
		Point correctionPos = { 0,0 };

		// �����ɕ␳����
		while (Map::isHittingBlock(checkPoint)) {
			correctionPos.x -= 1;
			correctionPos.y -= 1;
			checkPoint.x -= 1;
			checkPoint.y -= 1;
		}

		// �␳�I����A��苗�����Z���ق��݂̂�K�����A�����ق��͔j������

		// y�̂ق���x���Z��or�����̏ꍇ -> y��K�����Ax�͔j��
		if (-correctionPos.y >= -correctionPos.x) {
			// ���x���v���X�̂Ƃ��̂�0��
			if (velocity.y > 0) {
				velocity.y = 0;
			}

			// �␳�����s
			position.y += correctionPos.y;
		}
		// x�̂ق���y���Z���ꍇ -> x��K�����Ay�͔j��
		else {
			// ���x���v���X�̂Ƃ��̂�0��
			if (velocity.x > 0) {
				velocity.x = 0;
			}

			// �␳�����s
			position.x += correctionPos.x;
		}
	}



	// �v���C���[����E���̓_
	checkPoint = { position.x + 24 / 2,position.y - 24 / 2 };
	// �E�����q�b�g�����Ƃ� -> �␳����
	if (Map::isHittingBlock(checkPoint)) {
		// �␳���̍��W
		Point correctionPos = { 0,0 };

		// ����ɕ␳����
		while (Map::isHittingBlock(checkPoint)) {
			correctionPos.x -= 1;
			correctionPos.y += 1;
			checkPoint.x -= 1;
			checkPoint.y += 1;
		}

		// �␳�I����A��苗�����Z���ق��݂̂�K�����A�����ق��͔j������

		// y�̂ق���x���Z��or�����̏ꍇ -> y��K�����Ax�͔j��
		if (correctionPos.y <= -correctionPos.x) {
			// ���x���}�C�i�X�̂Ƃ��̂�0��
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// ���ł��Ȃ��̂Ńt���O��߂�
			isFlying = false;

			// �␳�����s
			position.y += correctionPos.y;
		}
		// x�̂ق���y���Z���ꍇ -> x��K�����Ay�͔j��
		else {
			// ���x���v���X�̂Ƃ��̂�0��
			if (velocity.x > 0) {
				velocity.x = 0;
			}

			// �␳�����s
			position.x += correctionPos.x;
		}
	}
	// �����󒆔��肳�ꂽ��̏ꍇ
	else if (isFlying) {
		// ����̃}�X���q�b�g���Ă���Ƃ��͋󒆂ł͂Ȃ��Ƃ������ƂȂ̂Ńt���O��false��
		if (Map::isHittingBlock({ checkPoint.x,checkPoint.y - 1 })) {
			// �q�b�g���Ă��Ȃ��Ƃ��͋󒆂Ƃ������ƂȂ̂Ńt���O��true��
			isFlying = false;
		}
	}
}
*/

ObjectType Player::GetType() {
	return typePlayer;
}
