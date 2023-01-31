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
	reticlePosition = { BaseConst::kWindowHeight / 2.0f,BaseConst::kWindowHeight / 2.0f };
	int x, y;
	Novice::GetMousePosition(&x, &y);
	preMousePosition = { (float)x,(float)y };

	invincibleFrame = 0;
	// ���݉E�������Ă��邩�ǂ���
	isRight = true;
	screenT = 0;

	// HP
	HP = 6;
	isDrawHP = false;
	drawHPFrame = 0;
}
// �X�V
void Player::SuccessorUpdate() {

	if (invincibleFrame > 0) {
		invincibleFrame--;
	}

	// ��]����ɏ�����
	angle = 0;
	angleVelocity = 0;

	if (!PublicFlag::kisStaging) {
		Move();
		ReticleMove();
		Jump();
		ShotWire();
	}

	// �O�̃t���[���̕��̃}�E�X���W�̎擾
	int x, y;
	Novice::GetMousePosition(&x, &y);
	preMousePosition = { (float)x,(float)y };

	/// HP �̕`��̒���
	if (isDrawHP) {
		drawHPFrame--;
		if (drawHPFrame < 0) {
			drawHPFrame = 0;
			isDrawHP = false;
		}
	}

	if (!PublicFlag::kisStaging) {
		Point screenPos = BaseDraw::GetScreenPosition();

		/// x���W�̒��� ///

		screenPos.x = centerPosition.x - BaseConst::kWindowWidth / 2.0f;

		/// y���W�̒��� ///

		screenPos.y = centerPosition.y + 400;


		// �X�N���[�����W����ʊO�ɍs���Ȃ��悤�ɒ���
		if (screenPos.x < 0) {
			screenPos.x = 0;
		}
		else if (screenPos.x + BaseConst::kWindowWidth > BaseConst::kMapChipSizeWidth * BaseConst::kMapSizeWidth) {
			screenPos.x = BaseConst::kMapChipSizeWidth * BaseConst::kMapSizeWidth - BaseConst::kWindowWidth;
		}
		if (screenPos.y - BaseConst::kWindowHeight < 0) {
			screenPos.y = BaseConst::kWindowHeight;
		}
		else if (screenPos.y > BaseConst::kMapChipSizeHeight * BaseConst::kMapSizeHeight) {
			screenPos.y = BaseConst::kMapChipSizeHeight * BaseConst::kMapSizeHeight;
		}

		//////////�@�@�����Ő��`�⊮�@�@//////////
		// screenPos ... �ړ���̃J����
		// BaseDraw::GetScreenPosition ... ���̃t���[���ł̌��݂̃J�������W

		/*
		//// �O�̃t���[���́A�ړ������̃J�������W���擾
		//static Point prevScreenPos = BaseDraw::GetScreenPosition();

		//// ���`��Ԓ��̃J�����ʒu
		//Point linerScreenPos = BaseDraw::GetScreenPosition();

		//// GetScreenPosition�֐��Ăяo���̂��ʓ|�Ȃ̂ŕϐ��ɓ���܂�
		//Point nowScreenPos = linerScreenPos;

		//if (prevScreenPos.x != screenPos.x || prevScreenPos.y != screenPos.y) {
		//	screenT = 0.0f;
		//}

		//else if (nowScreenPos.x == screenPos.x && nowScreenPos.y == screenPos.y) {
		//	screenT = 0.0f;
		//}

		//screenT += 0.005f;

		//BaseMath::Clamp(screenT, 0.0f, 1.0f);

		//linerScreenPos = {
		//	(1 - screenT) * nowScreenPos.x + screenT * screenPos.x,
		//	(1 - screenT) * nowScreenPos.y + screenT * screenPos.y
		//};
		//// ���̈ړ�����W��ۑ�
		//prevScreenPos = screenPos;
		// �ŏI�I�ɃJ������ݒ肷��
		*/
		BaseDraw::SetScreenPosition(screenPos);

		//////////�@�@�@�����܂Ł@�@�@�@//////////
	}
}
// �`��
void Player::Draw() {
	if (isAlive) {
		if (isDrawHP) {
			Point HPlt = {
				centerPosition.x - 20.0f * 2,centerPosition.y + width / 3.0f * 4.5f
			};
			float padding = 15;
			for (int i = 0; i < HP; i++) {
				if (i % 2 == 0) {
					BaseDraw::DrawSprite({ HPlt.x + i * padding,HPlt.y }, BaseTexture::kDebugTexture, { 10,20 }, 0.0f, RED);
				}
				else {
					BaseDraw::DrawSprite({ HPlt.x + (i - 1) * padding + 10,HPlt.y }, BaseTexture::kDebugTexture, { 10,20 }, 0.0f, RED);
				}
			}
		}

		if (invincibleFrame % 10 == 0) {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kDebugTexture, { width,height }, 0, RED);
		}
		else {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kDebugTexture, { width,height }, 0, 0x550000FF);
		}

		if (!PublicFlag::kisStaging) {

			// �ˏo��̐��\������`��
			Point p1 = BaseDraw::WorldtoScreen(centerPosition);
			Point p2 = reticlePosition;
			// �˒������ȉ��ɂ���
			Point range = BaseMath::GetVector(p1, p2);
			// �ő�˒���艓��������
			float diff = BaseMath::GetLength(range) - BaseConst::kPlayerReticleRange;
			if (0.0f < diff) {
				Point e = BaseMath::GetNormalize(range);
				p2.x = p1.x + e.x * BaseConst::kWireMaxLength;
				p2.y = p1.y + e.y * BaseConst::kWireMaxLength;
			}
			//Point p2 = BaseMath::TurnPoint({ 2000, 0 }, -BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition));
			Novice::DrawLine(p1.x, p1.y, p2.x, p2.y, RED);

			// ���e�B�N����`��
			Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 2, 2, 0, GREEN, kFillModeWireFrame);
			Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 10, 10, 0, GREEN, kFillModeWireFrame);
			Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 11, 11, 0, GREEN, kFillModeWireFrame);
			Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 12, 12, 0, GREEN, kFillModeWireFrame);
		}
	}
}



// �ǂ����Update()�Ŗ��t���[���Ăяo������

// �ړ��֘A
void Player::Move() {
	// �R���g���[���[���X�e�B�b�N
	Point leftStick = { 0,0 };
	BaseInput::GetControllerLeftJoysState(&leftStick);
	// ���ړ�
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x -= 0.5f;
			isRight = false;
		}
	}
	else if (leftStick.x < 0.0f) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f * leftStick.x;
			isRight = false;
		}
	}
	else if (velocity.x < 0) {
		velocity.x += 0.1f;
	}
	// �E�ړ�
	if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f;
			isRight = true;
		}
	}
	else if (0.0f < leftStick.x) {
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f * leftStick.x;
			isRight = true;
		}
	}
	else if (velocity.x > 0) {
		velocity.x -= 0.1f;
	}
}

// �Ə��ړ�
void Player::ReticleMove() {
	Point rightStick;
	BaseInput::GetControllerRightJoysState(&rightStick);
	int x, y;
	Novice::GetMousePosition(&x, &y);
	// �}�E�X�������Ă��鎞
	if (preMousePosition.x != x || preMousePosition.y != y) {
		reticlePosition = BaseInput::GetMousePosition();
	}
	// �X�e�B�b�N�����͂���Ă��鎞
	if (BaseMath::GetLength(rightStick) != 0.0f) {
		reticlePosition.x += 20 * rightStick.x;
		reticlePosition.y += 20 * rightStick.y;
	}
	// �Ə�����ʓ��Ɏ��߂�
	if (reticlePosition.x < BaseConst::kPlayerReticleSize) {
		reticlePosition.x = BaseConst::kPlayerReticleSize;
	}
	else if (BaseConst::kWindowWidth - BaseConst::kPlayerReticleSize < reticlePosition.x) {
		reticlePosition.x = BaseConst::kWindowWidth - BaseConst::kPlayerReticleSize;
	}
	if (reticlePosition.y < BaseConst::kPlayerReticleSize) {
		reticlePosition.y = BaseConst::kPlayerReticleSize;
	}
	else if (BaseConst::kWindowHeight - BaseConst::kPlayerReticleSize < reticlePosition.y) {
		reticlePosition.y = BaseConst::kWindowHeight - BaseConst::kPlayerReticleSize;
	}
	
	//// �˒������ȉ��ɂ���
	//Point range = BaseMath::GetVector(centerPosition, BaseDraw::ScreentoWorld(reticlePosition));
	//// �ő�˒���艓��������
	//float diff = BaseMath::GetLength(range) - BaseConst::kPlayerReticleRange;;
	//if (0.0f < diff) {
	//	Point e = BaseMath::GetNormalize(range);
	//	reticlePosition.x -= e.x * diff;
	//	reticlePosition.y += e.y * diff;
	//}
}


// �W�����v
void Player::Jump() {
	// �X�y�[�X�L�[ || A || LT �������ꂽ�Ƃ�
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger) || BaseInput::GetControllerState(kControllerButtonA, Trigger) || BaseInput::GetControllerState(kControllerButtonL2, Trigger)) {
		if (!isFlying) {
			// ���xY���}�C�i�X�̂Ƃ� -> 0�Ƀ��Z�b�g���Ă���
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// �W�����v���̑��x�𑫂�
			velocity.y += 9.8f * 1.2f;
			// SE���Đ�
			Novice::PlayAudio(BaseAudio::kPlayerJump, 0, 0.5f);
		}
	}
}

// ���C���[�֘A
void Player::ShotWire() {
	// ���N���b�N || RB || LB
	if (BaseInput::GetMouseState(LeftClick, Trigger) || BaseInput::GetControllerState(kControllerButtonR1, Trigger) || BaseInput::GetControllerState(kControllerButtonL1, Trigger)) {
		//reticlePosition = BaseInput::GetMousePosition();

		// �����̃x�N�g��
		Point p = { 3,0 };

		switch (wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition), this))
		{
			// ���C���[�̎ˏo�ɐ��������ꍇ
		case 1:
			// �ˏo�����Ɣ��Ε����̃x�N�g���𑫂�
			p = BaseMath::TurnPoint(p, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition) + 180);
			if (isFlying) {
				velocity.x = p.x;
				velocity.y = p.y;
			}
			// SE���Đ�
			Novice::PlayAudio(BaseAudio::kPlayerShoot, 0, 0.5f);
			break;
			// �ˏo���s
		case -1:
			break;
			// ����ȏ�ˏo�ł��Ȃ�
		case -2:
			break;
		}
	}
	// �E�N���b�N || RT
	if (BaseInput::GetMouseState(RightClick, Trigger) || BaseInput::GetControllerState(kControllerButtonR2, Trigger)) {
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

	//////////////////////////
	///�@�@�����蔻��`�F�b�N�@�@//
	//////////////////////////

	// ���G���Ԃ̏ꍇ -> �����蔻������؂��Ȃ�
	while (invincibleFrame <= 0) {
		int atk;
		// �U���ɑ΂��铖���蔻�������
		atk = EnemyAttackHitBox::CheckHitBox(centerPosition);
		if (atk != -1) {
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
			// ���G���Ԃ�ݒ�
			invincibleFrame = 60;
			// SE���Đ�
			Novice::PlayAudio(BaseAudio::kPlayerDamage, 0, 0.5f);
			// HP �����炷
			HP -= atk;
			// HP �\��
			isDrawHP = true;
			drawHPFrame = invincibleFrame + 180;

			break;
		}
		// �O�k�ɑ΂��铖���蔻��
		atk = EnemyAttackHitBox::CheckHitEllipse(centerPosition);
		if (atk != -1) {
			// �m�b�N�o�b�N
			Point p = { 20,0 };

			if (isRight) {
				p = BaseMath::TurnPoint(p, 90 + 45);
			}
			else {
				p = BaseMath::TurnPoint(p, 45);
			}

			velocity.x = p.x;
			velocity.y = p.y;
			// ���G���Ԃ�ݒ�
			invincibleFrame = 30;
			// SE���Đ�
			Novice::PlayAudio(BaseAudio::kPlayerDamage, 0, 0.5f);
			// HP �����炷
			HP -= atk;
			// HP �\��
			isDrawHP = true;
			drawHPFrame = invincibleFrame + 180;

			break;
		}
		break;
	}

	////////////////////////
	///�@�@�@�@�����܂Ł@�@�@�@//
	////////////////////////
}


ObjectType Player::GetType() {
	return typePlayer;
}
