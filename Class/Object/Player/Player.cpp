#include "Class/Object/Player/Player.h"

// �R���X�g���N�^
Player::Player(Point centerPosition, WireManager* _wireManager) {
	this->centerPosition = centerPosition;
	wireManager = _wireManager;

	Initialize();
}
// �f�X�g���N�^
Player::~Player() {

}


// ������
void Player::SuccessorInitialize() {

	width = 50;
	height = 100;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	angle = 0;
	angleVelocity = 0;

	isFlying = true;
	isAlive = true;
	reticlePosition = { -10000,-10000 };

	invincibleFrame = 0;
	// ���݉E�������Ă��邩�ǂ���
	isRight = true;
}
// �X�V
void Player::SuccessorUpdate() {

	if (invincibleFrame > 0) {
		invincibleFrame--;
	}

	// ��]����ɏ�����
	angle = 0;
	angleVelocity = 0;

	reticlePosition = BaseInput::GetMousePosition();

	Move();
	Jump();
	ShotWire();


	Point screenPos = BaseDraw::GetScreenPosition();

	/// x���W�̒��� ///

	if (isRight) {
		screenPos.x = centerPosition.x - 300;
	}
	else {
		screenPos.x = centerPosition.x + 300 - BaseConst::kWindowWidth;
	}

	/// y���W�̒��� ///

	if (!isFlying) {
		screenPos.y = centerPosition.y + 900;
	}
	else {

	}


	// �X�N���[�����W����ʊO�ɍs���Ȃ��悤�ɒ���
	if (screenPos.x < 0) {
		screenPos.x = 0;
	}
	else if (screenPos.x + BaseConst::kWindowWidth > BaseConst::kMapChipSizeWidth * BaseConst::kMapSizeWidth) {
		screenPos.x = BaseConst::kMapChipSizeWidth * BaseConst::kMapSizeWidth - BaseConst::kWindowWidth;
	}
	if (screenPos.y - BaseConst::kWindowHeight < 0 ) {
		screenPos.y = BaseConst::kWindowHeight;
	}
	else if (screenPos.y > BaseConst::kMapChipSizeHeight * BaseConst::kMapSizeHeight) {
		screenPos.y = BaseConst::kMapChipSizeHeight * BaseConst::kMapSizeHeight;
	}


	//////////�@�@�����Ő��`�⊮�@�@//////////
	// screenPos ... �ړ���̃J����
	// BaseDraw::GetScreenPosition ... ���̃t���[���ł̌��݂̃J�������W

	BaseDraw::SetScreenPosition(screenPos);

	//////////�@�@�@�����܂Ł@�@�@�@//////////
}
// �`��
void Player::Draw() {
	if (isAlive) {

		if (invincibleFrame % 10 == 0) {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kDebugTexture, { width,height }, 0, RED);
		}
	}
}



// �ǂ����Update()�Ŗ��t���[���Ăяo������

// �ړ��֘A
void Player::Move() {

	// ���ړ�
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x -= 0.5f;
			isRight = false;
		}
	}
	else if(velocity.x < 0) {
		velocity.x += 0.1f;
	}
	// �E�ړ�
	if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f;
			isRight = true;
		}
	}
	else if (velocity.x > 0) {
		velocity.x -= 0.1f;
	}
}

// �W�����v
void Player::Jump() {
	// �X�y�[�X�L�[�������ꂽ�Ƃ�
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		if (!isFlying) {
			// ���xY���}�C�i�X�̂Ƃ� -> 0�Ƀ��Z�b�g���Ă���
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// �W�����v���̑��x�𑫂�
			velocity.y += 9.8f * 1.2f;
		}
	}
}

// ���C���[�֘A
void Player::ShotWire() {
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		reticlePosition = BaseInput::GetMousePosition();

		// �����̃x�N�g��
		Point p = { 7,0 };

		switch (wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition), this))
		{
			// ���C���[�̎ˏo�ɐ��������ꍇ
			case 1:
				// �ˏo�����Ɣ��Ε����̃x�N�g���𑫂�
				p = BaseMath::TurnPoint(p, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition) + 180);

				velocity.x = p.x;
				velocity.y = p.y;
				break;
			// �ˏo���s
			case -1:
				break;
			// ����ȏ�ˏo�ł��Ȃ�
			case -2:
				break;
		}
	}
	if (BaseInput::GetMouseState(RightClick, Trigger)) {
		wireManager->Attract();
	}
}


// �����蔻����I�[�o�[���C�h

// �I�u�W�F�N�g���̂̓����蔻����`�F�b�N����֐�
void Player::CheckFieldHitBox() {

	// �����蔻����`�F�b�N������W
	Point checkPoint;

	// �v���C���[�����̓_
	checkPoint = { centerPosition.x,centerPosition.y + height / 2 };
	// �オ�q�b�g�����Ƃ�
	if (MapManager::CheckHitBox(checkPoint)) {
		// ���x��0��
		velocity.y = 0;

		// �q�b�g���Ȃ��Ȃ�܂ŉ��֕␳����
		while (MapManager::CheckHitBox(checkPoint)) {
			// ���W������
			centerPosition.y -= 1;
			// �Čv�Z
			checkPoint.y -= 1;
		}
	}

	// �v���C���[���牺�̓_
	checkPoint = { centerPosition.x,centerPosition.y - height / 2 };
	// �����q�b�g�����Ƃ�
	if (MapManager::CheckHitBox(checkPoint)) {
		// ���x��0��
		velocity.y = 0;
		// ���ł��Ȃ��̂Ńt���O��߂�
		isFlying = false;

		// �q�b�g���Ȃ��Ȃ�܂ŏ�֕␳����
		while (MapManager::CheckHitBox(checkPoint)) {
			// ���W�����
			centerPosition.y += 1;
			// �Čv�Z
			checkPoint.y += 1;
		}
	}
	// ����̃}�X���q�b�g���Ă��Ȃ��Ƃ��͋󒆂Ƃ������ƂȂ̂Ńt���O��true��
	else if (!MapManager::CheckHitBox({ checkPoint.x ,checkPoint.y - 1 })) {
		isFlying = true;
	}

	// �v���C���[���獶�̓_
	checkPoint = { centerPosition.x - width / 2,centerPosition.y };
	// �����q�b�g�����Ƃ�
	if (MapManager::CheckHitBox(checkPoint)) {
		// ���x��0��
		velocity.x = 0;

		// �q�b�g���Ȃ��Ȃ�܂ŉE�֕␳����
		while (MapManager::CheckHitBox(checkPoint)) {

			// ���W���E��
			centerPosition.x += 1;
			// �Čv�Z
			checkPoint.x += 1;
		}
	}

	// �v���C���[����E�̓_
	checkPoint = { centerPosition.x + width / 2,centerPosition.y };
	// �E���q�b�g�����Ƃ�
	if (MapManager::CheckHitBox(checkPoint)) {
		// ���x��0��
		velocity.x = 0;

		// �q�b�g���Ȃ��Ȃ�܂ō��֕␳����
		while (MapManager::CheckHitBox(checkPoint)) {
			// ���W������
			centerPosition.x -= 1;
			// �Čv�Z
			checkPoint.x -= 1;
		}
	}



	// �v���C���[���獶��̓_
	checkPoint = { centerPosition.x - width / 2,centerPosition.y + height / 2 };
	// ���オ�q�b�g�����Ƃ� -> �␳����
	if (MapManager::CheckHitBox(checkPoint)) {
		// �␳���̍��W
		Point correctionPos = { 0,0 };

		// �E���ɕ␳����
		while (MapManager::CheckHitBox(checkPoint)) {
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
			centerPosition.y += correctionPos.y;
		}
		// x�̂ق���y���Z���ꍇ -> x��K�����Ay�͔j��
		else {
			// ���x���}�C�i�X�̂Ƃ��̂�0��
			if (velocity.x < 0) {
				velocity.x = 0;
			}

			// �␳�����s
			centerPosition.x += correctionPos.x;
		}
	}



	// �v���C���[���獶���̓_
	checkPoint = { centerPosition.x - width / 2,centerPosition.y - height / 2 };
	// �������q�b�g�����Ƃ� -> �␳����
	if (MapManager::CheckHitBox(checkPoint)) {
		// �␳���̍��W
		Point correctionPos = { 0,0 };

		// �E��ɕ␳����
		while (MapManager::CheckHitBox(checkPoint)) {
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
			centerPosition.y += correctionPos.y;
		}
		// x�̂ق���y���Z���ꍇ -> x��K�����Ay�͔j��
		else {
			// ���x���}�C�i�X�̂Ƃ��̂�0��
			if (velocity.x < 0) {
				velocity.x = 0;
			}

			// �␳�����s
			centerPosition.x += correctionPos.x;
		}
	}
	// �����󒆔��肳�ꂽ��̏ꍇ
	else if (isFlying) {
		// ����̃}�X���q�b�g���Ă���Ƃ��͋󒆂ł͂Ȃ��Ƃ������ƂȂ̂Ńt���O��false��
		if (MapManager::CheckHitBox({ checkPoint.x,checkPoint.y - 1 })) {
			// �q�b�g���Ă��Ȃ��Ƃ��͋󒆂Ƃ������ƂȂ̂Ńt���O��true��
			isFlying = false;
		}
	}



	// �v���C���[����E��̓_
	checkPoint = { centerPosition.x + width / 2,centerPosition.y + height / 2 };
	// �E�オ�q�b�g�����Ƃ� -> �␳����
	if (MapManager::CheckHitBox(checkPoint)) {
		// �␳���̍��W
		Point correctionPos = { 0,0 };

		// �����ɕ␳����
		while (MapManager::CheckHitBox(checkPoint)) {
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
			centerPosition.y += correctionPos.y;
		}
		// x�̂ق���y���Z���ꍇ -> x��K�����Ay�͔j��
		else {
			// ���x���v���X�̂Ƃ��̂�0��
			if (velocity.x > 0) {
				velocity.x = 0;
			}

			// �␳�����s
			centerPosition.x += correctionPos.x;
		}
	}



	// �v���C���[����E���̓_
	checkPoint = { centerPosition.x + width / 2,centerPosition.y - height / 2 };
	// �E�����q�b�g�����Ƃ� -> �␳����
	if (MapManager::CheckHitBox(checkPoint)) {
		// �␳���̍��W
		Point correctionPos = { 0,0 };

		// ����ɕ␳����
		while (MapManager::CheckHitBox(checkPoint)) {
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
			centerPosition.y += correctionPos.y;
		}
		// x�̂ق���y���Z���ꍇ -> x��K�����Ay�͔j��
		else {
			// ���x���v���X�̂Ƃ��̂�0��
			if (velocity.x > 0) {
				velocity.x = 0;
			}

			// �␳�����s
			centerPosition.x += correctionPos.x;
		}
	}
	// �����󒆔��肳�ꂽ��̏ꍇ
	else if (isFlying) {
		// ����̃}�X���q�b�g���Ă���Ƃ��͋󒆂ł͂Ȃ��Ƃ������ƂȂ̂Ńt���O��false��
		if (MapManager::CheckHitBox({ checkPoint.x,checkPoint.y - 1 })) {
			// �q�b�g���Ă��Ȃ��Ƃ��͋󒆂Ƃ������ƂȂ̂Ńt���O��true��
			isFlying = false;
		}
	}


	// �U���ɑ΂��铖���蔻�������
	if (EnemyAttackHitBox::CheckHitBox(centerPosition) != 0 && invincibleFrame <= 0) {
		// ���G���Ԃ�ݒ�
		invincibleFrame = 60;
		// �m�b�N�o�b�N
		Point p = { 10,0 };

		if (isRight) {
			p = BaseMath::TurnPoint(p, 90 + 45);
		}
		else {
			p = BaseMath::TurnPoint(p, 45);
		}

		velocity.x = p.x;
		velocity.y = p.y;
	}
}


ObjectType Player::GetType() {
	return typePlayer;
}
