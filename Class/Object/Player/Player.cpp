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

	// �A�j���[�V����
	state = playerIdle;
	preState = state;
	buffState = state;

	stateChengeFlame = 0;

	animationFlameCount = 0;
	animationFlame = 0;

	// �v���C���[�̈ړ�����
	isLimitMove = true;

	// �������鍶����W
	limitLeftTop = { 0,(float)BaseConst::kTutorialStageSizeHeight * BaseConst::kMapChipSizeHeight };
	// ��������E�����W
	limitRightBottom = { (float)BaseConst::kTutorialStageSizeWidth * BaseConst::kMapChipSizeWidth,0 };

	resqawnPosition = { -1000,-1000 };
	preCenterPosition = { -1000,-1000 };
	preIsFlying = isFlying;
	isRespawn = false;

}

// �X�V
void Player::Update() {
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
}


// �X�V
void Player::SuccessorUpdate() {
	angle = 0;
	angleVelocity = 0;
	preReticlePosition = reticlePosition;
	if (isAlive) {
		preState = state;
		//// �e�X�g
		//if (BaseInput::GetKeyboardState(DIK_P, Trigger)) {
		//	isLimitMove = !isLimitMove;
		//}


		// ��]����ɏ�����

		if (!PublicFlag::kisStaging) {
			Move();
			ReticleMove();
			Jump();
			ShotWire();
			LimitMovement();
			Respawn();
		}
		else {
			reticlePosition = preReticlePosition;
			velocity.x = 0;
			state = playerIdle;
		}

		Animation();

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

		// �J�����ړ�
		// ���o���ȊO�̎�
		if (!PublicFlag::kisStaging) {
			Point screenPos = BaseDraw::GetScreenPosition();

			/// x���W�̒��� ///

			screenPos.x = centerPosition.x - BaseConst::kWindowWidth / 2.0f;

			/// y���W�̒��� ///

			screenPos.y = centerPosition.y + 400;


			// �X�N���[�����W����ʊO�ɍs���Ȃ��悤�ɒ���
			if (MapManager::GetisBoss()) {
				if (screenPos.x < 0) {
					screenPos.x = 0;
				}
				else if (screenPos.x + BaseConst::kWindowWidth > BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth) {
					screenPos.x = BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth - BaseConst::kWindowWidth;
				}
				if (screenPos.y - BaseConst::kWindowHeight < 0) {
					screenPos.y = BaseConst::kWindowHeight;
				}
				else if (screenPos.y > BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight) {
					screenPos.y = BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight;
				}
			}
			else {
				if (screenPos.x < 0) {
					screenPos.x = 0;
				}
				else if (screenPos.x + BaseConst::kWindowWidth > BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth) {
					screenPos.x = BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth - BaseConst::kWindowWidth;
				}
				if (screenPos.y - BaseConst::kWindowHeight < 0) {
					screenPos.y = BaseConst::kWindowHeight;
				}
				else if (screenPos.y > BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight) {
					screenPos.y = BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight;
				}
			}
			// �ړ�������
			if (isLimitMove) {
				if (screenPos.x < limitLeftTop.x) {
					screenPos.x = limitLeftTop.x;
				}
				else if (limitRightBottom.x < screenPos.x + BaseConst::kWindowWidth) {
					screenPos.x = limitRightBottom.x - BaseConst::kWindowWidth;
				}
				if (screenPos.y - BaseConst::kWindowHeight < limitRightBottom.y) {
					screenPos.y = limitRightBottom.y + BaseConst::kWindowHeight;
				}
				else if (limitLeftTop.y < screenPos.y) {
					screenPos.y = limitLeftTop.y;
				}

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
		preIsFlying = isFlying;
		preCenterPosition = centerPosition;
	}
	if (0 < invincibleFrame) {
		invincibleFrame--;
	}
	// HP�Ǘ�
	if (HP <= 0) {
		HP = 0;
		isAlive = false;
		velocity.x = 0;
		ReticleMove();
		Animation();
		if (invincibleFrame < 5) {
			invincibleFrame = 65;
		}
	}
}
// �`��
void Player::Draw() {
	// HP �̕`��
	if (isDrawHP) {
		Point HPlt = {
			centerPosition.x - 20.0f * 2,centerPosition.y + width / 3.0f * 4.5f
		};
		float padding = 30;
		int fullHp = HP / 2;
		int i = 0;
		for (; i < fullHp; i++) {
			BaseDraw::DrawSprite({ HPlt.x + i * padding,HPlt.y }, BaseTexture::kPlayerHeart[0], { 20 / 256.0f,20 / 256.0f }, 0.0f, WHITE);
		}
		if (HP % 2 == 1) {
			BaseDraw::DrawSprite({ HPlt.x + i * padding,HPlt.y }, BaseTexture::kPlayerHeart[1], { 20 / 256.0f,20 / 256.0f }, 0.0f, WHITE);
		}
	}

	Point lt = { centerPosition.x - width / 2.0f, centerPosition.y + height / 2.0f };
	if (invincibleFrame % 10 == 0) {
		/*if (isRight == true) {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kRPlayerIdle, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
		}
		else {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kLPlayerIdle, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
		}*/
		if (isRight) {
			switch (state)
			{
			case playerIdle:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerIdle, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerRun:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerRun[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerJump:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerRase:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerFall:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerLand:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerShot:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerShot, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerPull:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerPull, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			default:
				break;
			}
		}
		else {
			switch (state)
			{
			case playerIdle:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerIdle, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerRun:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerRun[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerJump:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerRase:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerFall:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerLand:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerShot:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerShot, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerPull:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerPull, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			default:
				break;
			}
		}
	}
	else {
		/*if (isRight == true) {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kRPlayerIdle, { 1.0f,1.0f }, 0, 0x550000FF);
		}
		else {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kLPlayerIdle, { 1.0f,1.0f }, 0, 0x550000FF);
		}*/
		if (isRight) {
			switch (state)
			{
			case playerIdle:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerIdle, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerRun:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerRun[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerJump:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerRase:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerFall:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerLand:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerShot:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerShot, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerPull:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerPull, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			default:
				break;
			}
		}
		else {
			switch (state)
			{
			case playerIdle:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerIdle, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerRun:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerRun[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerJump:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerRase:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerFall:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerLand:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerShot:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerShot, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerPull:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerPull, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			default:
				break;
			}
		}
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
	else if (velocity.x > 0 && isFlying) {
		velocity.x -= 0.1f;
	}
	else if (velocity.x > 0) {
		velocity.x -= 0.5f;
	}
	if (!isFlying && velocity.x != 0.0f) {
		state = playerRun;
	}
	else if (!isFlying && velocity.x == 0.0f) {
		state = playerIdle;
	}
	else {
		state = playerRase;
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
	if (0 < velocity.y) {
		state = playerRase;
	}
	else if (velocity.y < 0) {
		state = playerFall;
	}
	// �X�y�[�X�L�[ || X || Y || L || R �������ꂽ�Ƃ�
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger) || BaseInput::GetControllerState(kControllerButtonX, Trigger) || BaseInput::GetControllerState(kControllerButtonY, Trigger) || BaseInput::GetControllerState(kControllerButtonL1, Trigger) || BaseInput::GetControllerState(kControllerButtonR1, Trigger)) {
		if (!isFlying) {
			// ���xY���}�C�i�X�̂Ƃ� -> 0�Ƀ��Z�b�g���Ă���
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// �W�����v���̑��x�𑫂�
			velocity.y += 9.8f * 1.2f;
			// SE���Đ�
			Novice::PlayAudio(BaseAudio::kPlayerJump, 0, 0.5f);
			state = playerJump;
		}
	}
}

// ���C���[�֘A
void Player::ShotWire() {
	// ���N���b�N || RT
	if (BaseInput::GetMouseState(LeftClick, Trigger) || BaseInput::GetControllerState(kControllerButtonR2B, Trigger)) {
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
				velocity.x += p.x;
				velocity.y += p.y;
			}
			// SE���Đ�
			Novice::PlayAudio(BaseAudio::kPlayerShoot, 0, 0.5f);
			state = playerShot;
			break;
			// �ˏo���s
		case -1:
			break;
			// ����ȏ�ˏo�ł��Ȃ�
		case -2:
			break;
		}
	}
	// �E�N���b�N || LT
	if (BaseInput::GetMouseState(RightClick, Trigger) || BaseInput::GetControllerState(kControllerButtonL2A, Trigger)) {
		wireManager->Attract();
		state = playerPull;
	}
}

// �ړ������֐�
void Player::LimitMovement() {

	Point checkPoint;

	////////////////////////////////
	/// �ړ�����������ꍇ�̏��� ///
	////////////////////////////////


	if (isLimitMove) {
		// �v���C���[�����̓_
		checkPoint = { centerPosition.x,centerPosition.y + height / 2 };
		if (limitLeftTop.y < checkPoint.y) {
			// ���x��0��
			velocity.y = 0;

			// �q�b�g���Ȃ��Ȃ�܂ŉ��֕␳����
			while (limitLeftTop.y < checkPoint.y) {
				// ���W������
				centerPosition.y -= 1;
				// �Čv�Z
				checkPoint.y -= 1;
			}
		}
		// �v���C���[���牺�̓_
		// �u���Ƀ��X�|�[��
		checkPoint = { centerPosition.x,centerPosition.y - height / 2 };
		if (checkPoint.y + height * 2.0f < limitRightBottom.y) {
			// ���X�|�[��
			isRespawn = true;
			HP--;
			invincibleFrame = 30;
			isDrawHP = true;
			drawHPFrame = invincibleFrame + 180;
			// SE���Đ�
			//Novice::PlayAudio(BaseAudio::kPlayerDamage, 0, 0.5f);
		}
		// �v���C���[���獶�̓_
		checkPoint = { centerPosition.x - width / 2,centerPosition.y };
		if (checkPoint.x < limitLeftTop.x) {
			// ���x��0��
			velocity.x = 0;

			// �q�b�g���Ȃ��Ȃ�܂ŉE�֕␳����
			while (checkPoint.x < limitLeftTop.x) {
				// ���W���E��
				centerPosition.x += 1;
				// �Čv�Z
				checkPoint.x += 1;
			}
		}
		// �v���C���[����E�̓_
		checkPoint = { centerPosition.x + width / 2,centerPosition.y };
		if (limitRightBottom.x < checkPoint.x) {
			// ���x��0��
			velocity.x = 0;

			// �q�b�g���Ȃ��Ȃ�܂ō��֕␳����
			while (limitRightBottom.x < checkPoint.x) {
				// ���W������
				centerPosition.x -= 1;
				// �Čv�Z
				checkPoint.x -= 1;
			}
		}

	}

	////////////////////////////////
	///			�����܂�		 ///
	////////////////////////////////

}

void Player::Respawn() {
	// �n�ʂ��痣�ꂽ�u�Ԃ̍��W��ۑ�
	if (isFlying != preIsFlying && preIsFlying == false) {

		resqawnPosition.x = (int)(preCenterPosition.x / BaseConst::kMapChipSizeWidth) * BaseConst::kMapChipSizeWidth + BaseConst::kMapChipSizeWidth / 2.0f;
		resqawnPosition.y = (int)(preCenterPosition.y / BaseConst::kMapChipSizeHeight) * BaseConst::kMapChipSizeHeight + BaseConst::kMapChipSizeHeight / 2.0f;

	}
	/*
	Point r = BaseDraw::WorldtoScreen({ resqawnPosition.x - width / 2.0f,resqawnPosition.y + height / 2.0f });
	Point r1 = BaseDraw::WorldtoScreen({ (centerPosition.x) / BaseConst::kMapChipSizeWidth * BaseConst::kMapChipSizeWidth - width / 2.0f,centerPosition.y / BaseConst::kMapChipSizeHeight * BaseConst::kMapChipSizeHeight + height / 2.0f });
	Point r2 = BaseDraw::WorldtoScreen({ (preCenterPosition.x) / BaseConst::kMapChipSizeWidth * BaseConst::kMapChipSizeWidth - width / 2.0f,preCenterPosition.y / BaseConst::kMapChipSizeHeight * BaseConst::kMapChipSizeHeight + height / 2.0f });
	Novice::DrawBox(r.x, r.y, width, height, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawBox(r1.x, r1.y, width, height, 0.0f, 0xFF0000FF, kFillModeWireFrame);
	Novice::DrawBox(r2.x, r2.y, width, height, 0.0f, 0x0000FFFF, kFillModeWireFrame);
	Novice::ScreenPrintf(10, 20, "%d", isRespawn);
	Novice::ScreenPrintf(10, 40, "%d  %d", BaseConst::kMapChipSizeWidth, BaseConst::kMapChipSizeHeight);
	Novice::ScreenPrintf(10, 60, "%.2f  %.2f", preCenterPosition.x, preCenterPosition.y);
	Novice::ScreenPrintf(10, 80, "%.2f  %.2f", resqawnPosition.x, resqawnPosition.y);
	Novice::ScreenPrintf(10, 100, "%d  %d", (int)(resqawnPosition.x / BaseConst::kMapChipSizeWidth), (int)(resqawnPosition.y / BaseConst::kMapChipSizeHeight));
	Novice::ScreenPrintf(10, 120, "%.2f  %.2f", (int)(resqawnPosition.x / BaseConst::kMapChipSizeWidth) * (float)BaseConst::kMapChipSizeWidth, (int)(resqawnPosition.y / (float)BaseConst::kMapChipSizeHeight) * BaseConst::kMapChipSizeHeight);
	if (BaseInput::GetKeyboardState(DIK_P, Trigger)) {
		isRespawn = !isRespawn;
	}
	//*/
	if (isRespawn) {
		centerPosition = resqawnPosition;
		velocity = { 0,0 };
		acceleration = { 0,0 };
		wireManager->Initialize();
		isFlying = false;
		isRespawn = false;
	}
}

// �A�j���[�V����
void Player::Animation() {
	if (!isAlive) {
		state = playerIdle;
	}
	stateChengeFlame++;
	if (100 < stateChengeFlame) {
		stateChengeFlame = BaseConst::kPlayerAnimationFlame[buffState] + 1;
	}
	else if (stateChengeFlame < BaseConst::kPlayerAnimationFlame[buffState]) {
		state = buffState;
	}
	// �O�̃t���[���ƍ��̃t���[�����Ⴂ�A
	// �ς���Ă���̏�Ԃƍ��̏�Ԃ��Ⴄ��
	if (buffState != state) {
		// ��Ԃ��ς�����Ƃ���
		animationFlame = 0;
		animationFlameCount = 0;
		stateChengeFlame = 0;
		buffState = state;
	}
	else {
		if (buffState != state) {
			buffState = state;
		}
	}
	animationFlameCount++;
	if (BaseConst::kPlayerMaxAnimationFlame < animationFlameCount) {
		animationFlame++;
		animationFlameCount = 0;

	}
	// ��Ԃ��擾
	switch (state)
	{
	case playerIdle:
		animationFlame = 0;
		break;
	case playerRun:
		if (BaseConst::kPlayerTextureRunNum <= animationFlame) {
			animationFlame = 0;
		}
		break;
	case playerJump:
		animationFlame = 0;
		break;
	case playerRase:
		animationFlame = 1;
		break;
	case playerFall:
		animationFlame = 2;
		break;
	case playerLand:
		animationFlame = 3;
		break;
	case playerShot:
		animationFlame = 0;
		break;
	case playerPull:
		animationFlame = 0;
		break;
	default:
		break;
	}
	/*
	Novice::ScreenPrintf(10, 20, "state  pre    buff");
	Novice::ScreenPrintf(10, 60, "%d", animationFlame);
	int a = 10, b = a + 50, c = b + 50;
	switch (state)
	{
	case playerIdle:
		Novice::ScreenPrintf(a, 40, "Idle");
		break;
	case playerRun:
		Novice::ScreenPrintf(a, 40, "Run");
		break;
	case playerJump:
		Novice::ScreenPrintf(a, 40, "Jump");
		break;
	case playerRase:
		Novice::ScreenPrintf(a, 40, "Rase");
		break;
	case playerFall:
		Novice::ScreenPrintf(a, 40, "Fall");
		break;
	case playerLand:
		Novice::ScreenPrintf(a, 40, "Land");
		break;
	case playerShot:
		Novice::ScreenPrintf(a, 40, "Shot");
		break;
	case playerPull:
		Novice::ScreenPrintf(a, 40, "Pull");
		break;
	default:
		break;
	}
	switch (preState)
	{
	case playerIdle:
		Novice::ScreenPrintf(b, 40, "Idle");
		break;
	case playerRun:
		Novice::ScreenPrintf(b, 40, "Run");
		break;
	case playerJump:
		Novice::ScreenPrintf(b, 40, "Jump");
		break;
	case playerRase:
		Novice::ScreenPrintf(b, 40, "Rase");
		break;
	case playerFall:
		Novice::ScreenPrintf(b, 40, "Fall");
		break;
	case playerLand:
		Novice::ScreenPrintf(b, 40, "Land");
		break;
	case playerShot:
		Novice::ScreenPrintf(b, 40, "Shot");
		break;
	case playerPull:
		Novice::ScreenPrintf(b, 40, "Pull");
		break;
	default:
		break;
	}
	switch (buffState)
	{
	case playerIdle:
		Novice::ScreenPrintf(c, 40, "Idle");
		break;
	case playerRun:
		Novice::ScreenPrintf(c, 40, "Run");
		break;
	case playerJump:
		Novice::ScreenPrintf(c, 40, "Jump");
		break;
	case playerRase:
		Novice::ScreenPrintf(c, 40, "Rase");
		break;
	case playerFall:
		Novice::ScreenPrintf(c, 40, "Fall");
		break;
	case playerLand:
		Novice::ScreenPrintf(c, 40, "Land");
		break;
	case playerShot:
		Novice::ScreenPrintf(c, 40, "Shot");
		break;
	case playerPull:
		Novice::ScreenPrintf(c, 40, "Pull");
		break;
	default:
		break;
	}
	//*/
}

// �����蔻����I�[�o�[���C�h

// �I�u�W�F�N�g���̂̓����蔻����`�F�b�N����֐�
void Player::CheckFieldHitBox() {

	// �����蔻����`�F�b�N������W
	Point checkPoint;

#pragma region �㉺���E


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
		state = playerLand;
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
		if (0 < velocity.y) {
			state = playerRase;
		}
		else if (velocity.y == 0.0f) {
			state = playerIdle;
		}
		else {
			state = playerFall;
		}
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

#pragma endregion


#pragma region �l��



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
			state = playerLand;
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
			state = playerIdle;
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
			state = playerLand;
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
			state = playerIdle;
		}
	}

#pragma endregion

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
