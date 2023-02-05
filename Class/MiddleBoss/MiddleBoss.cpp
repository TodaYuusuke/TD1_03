#include "Class/MiddleBoss/MiddleBoss.h"

/*********************************************
 * ���{�X�N���X
 *
 * ���{�X�֘A�̍s�����ׂĂ��Ǘ�����N���X
 *********************************************/

// �R���X�g���N�^
MiddleBoss::MiddleBoss() {
	// �j�̓����蔻���������
	core = NULL;
}

// ����������
void MiddleBoss::Initialize(ObjectManager* objectManager) {
	// �{�X�̒��S���W�����Z�b�g
	this->centerPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth / 2) + 300.0f,(float)(BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight) + 250.0f };
	// �{�X�̉摜�T�C�Y�ݒ�
	this->textureSize = { 256.0f, 256.0f };

	// �p�x������
	this->degree = 0.0f;
	// 1�t���[���O�̊p�x��������
	this->beforeDegree = 0.0f;

	//�V�F�C�N���Ă��Ȃ���Ԃɖ߂�
	this->shakeVariation = { 0.0f, 0.0f };

	// �J�b�g�V�[���p�J�����ړ��O���W
	this->prevScreenPosition = { 0.0f, 0.0f };
	// �J�b�g�V�[���p�J�����ړ�����W
	this->nextScreenPosition = { 0.0f, 0.0f };

	// ��ʒ����̍��W���Ƃ�֐�
	screenCenterPosition = { 0.0f, 0.0f };

	// �o�C�u���[�V����������
	this->vibInit = false;

	// �U�����Đ��g���K�[��false��
	this->isVibPlaySound = false;

	// �퓬���J�n���邩
	this->doBattleStart = false;
	// �퓬�J�n���Ă��Ȃ���Ԃɂ���
	this->isBattleStart = false;

	// �s���I����Ԃɂ���
	this->t = 0.0f;
	this->spareT = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->inStun = false;
	this->inDamage = false;
	this->actionWayPoint = 0;

	// �_���[�W���󂯂����Ԃɂ���
	this->canTakeDamage = true;

	// �j�̓����蔻���������
	this->core = objectManager->MakeNewObjectCore(centerPosition, textureSize);

	// ����̃T�C�Y���w��i���e�N�X�`���̂��߁A����ς���j
	this->weaponSize = { 0.0f, 0.0f };
	this->weaponTextureSize = { 1.0f, 1.0f };

	// �U���p�^�[��������
	this->prevAttackPattern[0] = NONE;
	this->prevAttackPattern[1] = NONE;
	this->attackPattern = NONE;

	// �ҋ@��
	this->pleaseWait = true;

	// �ҋ@���Ԃ���
	this->waitTime = 1.0f;

	// HP������
	this->HP = MaxHP;

	this->blockSpawnPoint = { 0.0f, 0.0f };

	// �^����_���[�W������
	this->bodyDamage = 0.0f;
	this->bladeDamage = 0.0f;

	// ���S���Ă��Ȃ���Ԃɂ���
	this->inDead = false;

	/// �I�u�W�F�N�g�֘A
	// �I�u�W�F�N�g�𐶐����邩�ǂ���
	this->canGeneratedBlock = false;

	// �I�u�W�F�N�g������
	this->generatedBlockValue = 0;

	// �I�u�W�F�N�g�����Ԋu
	this->generatedBlockInterval = 0.0f;

	// �F�֌W������
	this->color = 0xFFFFFFFF;

	// ���݉��o����
	isPlayingStartAnim = false;

	// ���S�A�j���[�V����
	isPlayingDeadAnim = false;

	// ���S�A�j���[�V�������I�����Ă��邩
	isEndDeadAnim = false;

	// ���ѐ�
	screamSoundHundle = BaseAudio::kBossScream;
	screamVoiceHundle = -1;

}

// �X�V����
void MiddleBoss::Update(Point playerPosition, ObjectManager* objectManager, WireManager* wireManager) {

	// ��ʒ����̍��W���X�V
	screenCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth / 2) + 300.0f,
		(float)(BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight / 2) };

	// �v���C���[�����̋����ȏ�ɋ߂Â�����{�X�Ƃ̐퓬���J�n����
	if (screenCenterPosition.x - playerPosition.x < 650.0f) {
		doBattleStart = true;
	}

	/******** �f�o�b�N���� **********/
	// �f�o�b�O��Ԃ̐؂�ւ�
	if (BaseInput::GetKeyboardState(DIK_H, Press) && BaseInput::GetKeyboardState(DIK_U, Press)) {
		if (BaseInput::GetKeyboardState(DIK_BACKSPACE, Trigger)) {
			if (inDebug == false) {
				// �퓬�J�n��Ԃɂ���
				isBattleStart = true;
				// �p�x������
				degree = 0;

				// �s���I����Ԃ�
				endAction = true;
				inAction = false;
				actionWayPoint = WAYPOINT0;

				// �f�o�b�N��Ԃɂ���
				inDebug = true;
			}
			else
				inDebug = false;
		}
	}
	// �f�o�b�O�֐��̎��s
	if (inDebug == true) {
		Debug();
	}

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

	if (isBattleStart == true && inDead == false) {

		if (HP == 0) {
			attackPattern = NONE;
			endAction = false;
		}

		// ���S��Ԃ̎��̎��s����
		if (HP <= 0) {
			if (isEndDeadAnim == false && isPlayingDeadAnim == false) {

				endAction = true;
				inAction = false;

				inDamage = false;
				inStun = false;
				t = 0.0f;
				actionWayPoint = WAYPOINT0;
				isPlayingDeadAnim = true;
			}
			// HP��0�ȉ��ɂȂ�����{�X�����S��Ԃɂ���
			HP = 0;
		}

		// �s���̕��򏈗�
		if (inDead == false && inDebug == false) {
			if (endAction == true) {

				// �s���̊Ԋu�����
				if (pleaseWait == true) {
					attackPattern = NONE;
				}
				else {
					do {
						// �v���C���[�ƃ{�X�̋��������߂ċ߂����������ōs���𕪊򂳂���
						if (BaseMath::GetLength({ playerPosition.x - centerPosition.x,playerPosition.y - centerPosition.y }) < 500.0f) {

							// �߂�
							attackBranch = BaseMath::Random(Pattern1, Pattern4);
							switch (attackBranch)
							{
							case MiddleBoss::Pattern1:
								attackPattern = RUSH;
								break;
							case MiddleBoss::Pattern2:
								attackPattern = SLASH;
								break;
							case MiddleBoss::Pattern3:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[0] == SEPARATION
									|| prevAttackPattern[1] == APPROACH || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = ROTATE;
								}

								break;
							case MiddleBoss::Pattern4:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[1] == APPROACH) {
									continue;
								}
								else {
									attackPattern = SEPARATION;
								}
								break;
							default:
								attackPattern = NONE;
								break;
							}

						}
						else {

							// ����
							attackBranch = BaseMath::Random(Pattern1, Pattern4);
							switch (attackBranch)
							{
							case MiddleBoss::Pattern1:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[0] == SEPARATION
									|| prevAttackPattern[1] == APPROACH || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = ROTATE;
								}
								break;
							case MiddleBoss::Pattern2:
								attackPattern = SLASH;
								break;
							case MiddleBoss::Pattern3:
								attackPattern = RUSH;
								break;
							case MiddleBoss::Pattern4:
								if (prevAttackPattern[0] == SEPARATION || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = APPROACH;
								}
								break;
							default:
								attackPattern = NONE;
								break;
							}

						}

					} while (prevAttackPattern[0] == attackPattern || prevAttackPattern[1] == attackPattern);
				}

				if (objectManager->GetIsCreatedBlock() == false) {
					attackPattern = FALL;
				}

				// �s���J�n
				inAction = true;
				endAction = false;

			}
		}

		// �s���̎��s����
		if (inAction == true && inStun == false && isPlayingDeadAnim == false) {
			switch (attackPattern)
			{
			case MiddleBoss::NONE:
				None(waitTime);
				break;
			case MiddleBoss::ROTATE:
				Rotate(720, 2.0f, 0.5f, wireManager);
				break;
			case MiddleBoss::RUSH:
				Rush(playerPosition, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case MiddleBoss::SLASH:
				Slash(playerPosition, 0.35f, 0.2f, 1.25f, 1.0f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case MiddleBoss::FALL:
				Fall(0.35f, 1.0f, 0.15f, 0.75f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case MiddleBoss::APPROACH:
				Approach(playerPosition, 1.0f, 0.1f, wireManager);
				break;
			case MiddleBoss::SEPARATION:
				Separation(playerPosition, 1.0f, 0.1f, wireManager);
				break;
			}
		}

		// �X�^������
		if (inStun == true) {
			Stun(1.25f, 1.5f, 3.0f, 0.75f, wireManager);
		}

		// �J���Ă鎞�ɒǏ]
		core->SetCenterPosition(viewPosition);

		if (canTakeDamage == true) {
			// �����ŕԂ�l��true�̂Ƃ��Ƀ_���[�W������s��
			if (objectManager->isHitCore() == true) {
				// �_���[�W��^�����ۂ̌��ʉ��Đ�
				Novice::PlayAudio(BaseAudio::kBossDamage, 0, 0.5f);

				// �_���[�W�A�j���[�V�����p��t������������
				spareT = 0.0f;
				// �_���[�W��^������Ԃɂ���
				inDamage = true;

				// HP��ቺ������
				HP--;
			}
		}
		
		// �_���[�W��^�����ۂ̃A�j���[�V�����Đ�
		if (inDamage == true) {
			playTakeDamageAnim(0.1f, 50);
		}

		degree %= 360;

		float degreeDifference = degree - beforeDegree;

		for (int i = 0; i < 5; i++) {
			// ����̃q�b�g�{�b�N�X
			EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree + (degreeDifference * i), bladeDamage);
		}

		// �{�X�̃q�b�g�{�b�N�X��L���ɂ���
		EnemyAttackHitBox::MakeNewHitBox(centerPosition, textureSize.x, textureSize.y, degree, bodyDamage);

		/// �I�u�W�F�N�g�֌W�̍X�V����

		// �I�u�W�F�N�g��������
		if (canGeneratedBlock == true) {

			// �����Ԋu��0�ɂȂ�Ɛ���
			if (generatedBlockInterval < 0) {
				if (generatedBlockValue > 0) {
					float blockSize = BaseMath::RandomF(20.0f, 60.0f, 0);

					blockSpawnPoint = { BaseMath::RandomF(centerPosition.x - (float)BaseConst::kWindowWidth / 2, centerPosition.x + (float)BaseConst::kWindowWidth / 2, 1),
						(float)BaseConst::kTutorialStageSizeHeight * BaseConst::kMapChipSizeHeight - BaseConst::kMapChipSizeHeight - blockSize };

					// �͈͓��������ꍇ�͍Ē��I
					while (blockSpawnPoint.x + blockSize >= centerPosition.x - textureSize.x / 2.0f && blockSpawnPoint.x - blockSize <= centerPosition.x + textureSize.x / 2.0f)
					{
						blockSpawnPoint = { BaseMath::RandomF(centerPosition.x - (float)BaseConst::kWindowWidth / 2, centerPosition.x + (float)BaseConst::kWindowWidth / 2, 1),
						(float)BaseConst::kTutorialStageSizeHeight* BaseConst::kMapChipSizeHeight - BaseConst::kMapChipSizeHeight - blockSize };
					}
					// �����_���Ȉʒu�ɁA�����_���ȑ傫���̃u���b�N�𐶐�
					objectManager->MakeNewObjectBlock(blockSpawnPoint, { blockSize, blockSize });
					generatedBlockValue--;
				}
				else {
					blockSpawnPoint = { 0.0f, 0.0f };
					canGeneratedBlock = false;
				}
				generatedBlockInterval = BaseMath::RandomF(0.1f, 0.2f, 2);
			}
			else {
				generatedBlockInterval -= 1.0f / 60.0f;
			}
		}

		// �Ō��1�t���[���O�̊p�x���擾
		beforeDegree = degree;

		if (isPlayingDeadAnim == true && isEndDeadAnim == false) {
			PlayDeadAnim(5.0f, 1.0f, 0.75f, 2.5f, wireManager);
		}

	}
	else if (inDead == false && doBattleStart == true) {
		// �J�n�A�j���[�V�����Đ�
		PlayStartAnim(2.5f, 1.25f, 2.0f, 1.5f);

		if (isPlayingStartAnim == true && PublicFlag::kisStaging == false) {
			// ���o�I��
			PublicFlag::kisStaging = false;
			isPlayingStartAnim = false;

			// ������
			centerPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth / 2),
				(float)(BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight / 2) };;

			shakeVariation = { 0.0f, 0.0f };
			isBattleStart = true;
			t = 0.0f;
			actionWayPoint = WAYPOINT0;
		}
	}

}

// �`�揈��
void MiddleBoss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

	if (inDead == false) {
		// �{�X����摜 ���݂͉��e�N�X�`��
		BaseDraw::DesignationDrawQuad(
			GetWeaponPosition(viewPosition),
			weaponSize,
			BaseTexture::kDebugTexture,
			weaponTextureSize,
			degree,
			0xFFFFFFFF
		);

		// �{�X�����摜
		BaseDraw::DrawQuad(
			viewPosition,
			BaseTexture::kBossCore,
			textureSize,
			1.0f,
			degree,
			color
		);

		if (isBattleStart == true) {
			// �{�XHP�Q�[�W�i���j
			Novice::DrawBox(450, 100, 0 + 100 * HP, 30, 0.0f, 0xdc143cFF, kFillModeSolid);
		}

	}

}

// ����摜�̑��΍��W�����߂�
Point MiddleBoss::GetWeaponPosition(Point centerPosition) {
	// ��]���S����̍��كx�N�g���쐬
	Point p = { 0, weaponSize.y / 2 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// �f�o�b�O�p�֐�
void MiddleBoss::Debug() {

	Novice::ScreenPrintf(0, 0, "DebugMode :: ON");
	Novice::ScreenPrintf(0, 20, "ActionSwitching :: 1 ~ 7");
	Novice::ScreenPrintf(0, 40, "1:NONE  2:SPIN  3:RUSH  4:SLASH  5:FALL  6:  7:");
	Novice::ScreenPrintf(0, 60, "NowAction = %d", attackPattern);
	Novice::ScreenPrintf(0, 80, "8:STUN  9:DAMAGE");

	if (endAction == true) {

		// �s�����J�n������
		if (BaseInput::GetKeyboardState(DIK_F, Trigger)) {
			inAction = true;
			endAction = false;
		}

		//�s���p�^�[���؂�ւ�
		if (BaseInput::GetKeyboardState(DIK_1, Trigger)) {
			attackPattern = NONE;
		}
		else if (BaseInput::GetKeyboardState(DIK_2, Trigger)) {
			attackPattern = ROTATE;
		}
		else if (BaseInput::GetKeyboardState(DIK_3, Trigger)) {
			attackPattern = RUSH;
		}
		else if (BaseInput::GetKeyboardState(DIK_4, Trigger)) {
			attackPattern = SLASH;
		}
		else if (BaseInput::GetKeyboardState(DIK_5, Trigger)) {
			attackPattern = FALL;
		}
		else if (BaseInput::GetKeyboardState(DIK_6, Trigger)) {
			attackPattern = APPROACH;
		}
		else if (BaseInput::GetKeyboardState(DIK_7, Trigger)) {
			attackPattern = SEPARATION;
		}
	}

	// �{�X���X�^��������
	if (BaseInput::GetKeyboardState(DIK_8, Trigger)) {
		actionWayPoint = WAYPOINT0;
		inStun = true;
	}

	if (BaseInput::GetKeyboardState(DIK_UP, Trigger)) {
		actionWayPoint = WAYPOINT0;
		isPlayingDeadAnim = true;
	}

	// �{�X����]������
	if (BaseInput::GetKeyboardState(DIK_L, Press))
		degree++;

	else if (BaseInput::GetKeyboardState(DIK_J, Press))
		degree--;

	// ����̃T�C�Y��ύX
	// x
	if (BaseInput::GetKeyboardState(DIK_O, Press)) {
		weaponSize.x -= 1.0f;
	}
	else if (BaseInput::GetKeyboardState(DIK_P, Press)) {
		weaponSize.x += 1.0f;
	}
	// y
	if (BaseInput::GetKeyboardState(DIK_N, Press)) {
		weaponSize.y -= 1.0f;
	}
	else if (BaseInput::GetKeyboardState(DIK_M, Press)) {
		weaponSize.y += 1.0f;
	}

}

// �V�F�C�N�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// �{�X���V�F�C�N������֐�
void MiddleBoss::Shake(int shakeStrength) {
	shakeVariation.x = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
	shakeVariation.y = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
}

// �V�F�C�N�C�[�Y�A�E�g�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// shakeTime ... �V�F�C�N���鎞��
// �{�X���V�F�C�N�̋������������キ���Ȃ��瓮�����֐�
void MiddleBoss::ShakeEaseOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// �V�F�C�N�C�[�Y�C���A�E�g�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// shakeTime ... �V�F�C�N���鎞��
// �{�X�̃V�F�C�N�̋������������キ���Ȃ��瓮�����֐�
void MiddleBoss::ShakeEaseInOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_InOut(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// �o�C�u���[�V�����֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// vibTime ... �U������b��
// vibRate ... �U������Ԋu
// vibValue ... �U������������
// ���Ԋu�ŁA���b���U��������֐�
void MiddleBoss::vibration(int shakeStrength, float vibTime, float vibRate, int vibValue) {

	static float _vibTime;
	static float _vibRate;
	static bool vibrating;

	// ������
	if (vibInit == false) {
		_vibTime = (vibTime / vibValue) / 2;
		_vibRate = 0;

		isVibPlaySound = false;

		vibInit = true;
	}

	if (_vibRate < 0) {
		vibrating = true;
	}
	else {
		_vibRate -= 1.0f / 60.0f;
	}

	if (vibrating == true) {
		if (_vibTime > 0) {

			if (isVibPlaySound == false) {
				Novice::PlayAudio(BaseAudio::kBossVibration, false, 0.5f);
				isVibPlaySound = true;
			}

			Shake(shakeStrength);
			_vibTime -= 1.0f / 60.0f;
		}
		else {
			isVibPlaySound = false;
			_vibTime = (vibTime / vibValue) / 2;
			_vibRate = (vibTime / vibValue) / 2;
			vibrating = false;
		}
	}

}

/// <summary>
/// �{�X��̊J�n���̃A�j���[�V�����֐�
/// </summary>
/// <param name="cameraMoveTime">�J�����𓮂�������</param>
/// <param name="appearTime">�{�X���ォ��o������</param>
/// <param name="roarTime">���K����</param>
/// <param name="waitTime">�ҋ@����</param>
void MiddleBoss::PlayStartAnim(float cameraMoveTime, float appearTime, float roarTime, float waitTime) {
	switch (actionWayPoint)
	{
		// ������
	case MiddleBoss::WAYPOINT0:

		// ���o���̏�Ԃ�
		PublicFlag::kisStaging = true;
		isPlayingStartAnim = true;

		// �X�N���[�����W�L�^
		prevScreenPosition = BaseDraw::GetScreenPosition();
		nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
			screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) };

		prevCenterPosition = centerPosition;
		nextCenterPosition = { screenCenterPosition.x, screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) };

		// t������
		t = 0.0f;
		// ���̒i�K��
		actionWayPoint++;

		break;
		// �J�������{�X�̂Ƃ���܂œ�����
	case MiddleBoss::WAYPOINT1:
		if (t <= cameraMoveTime) {

			// �X�N���[���𓮂���
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, cameraMoveTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, cameraMoveTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossRush, false, 0.5f);

			// �X�N���[�����W�L�^
			prevCenterPosition = centerPosition;
			nextCenterPosition = screenCenterPosition;

			// ������
			t = 0.0f;
			actionWayPoint++;
		}

		break;
		// �{�X���ォ��o������
	case MiddleBoss::WAYPOINT2:
		if (t <= appearTime) {

			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, appearTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, appearTime);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// ������
			t = 0.0f;
			actionWayPoint++;
		}
		break;
		// �{�X�����K����
	case MiddleBoss::WAYPOINT3:
		if (t <= roarTime) {

			if (t > 1.0f) {

				if (Novice::IsPlayingAudio(screamVoiceHundle) == 0 || screamVoiceHundle == -1) {
					// ���ʉ��Đ�
					screamVoiceHundle = Novice::PlayAudio(screamSoundHundle, false, 0.5f);
				}

				Shake(25);
			}

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// ������
			t = 0.0f;
			actionWayPoint++;

		}
		break;
		// �ҋ@���Ă���{�X��J�n
	case MiddleBoss::WAYPOINT4:
		if (t <= waitTime) {

			// �X�N���[���𓮂���
			/*Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, nextScreenPosition.x, prevScreenPosition.x - nextScreenPosition.x, waitTime);
			screenPosition.y = BaseDraw::Ease_Out(t, nextScreenPosition.y, prevScreenPosition.y - nextScreenPosition.y, waitTime);

			BaseDraw::SetScreenPosition(screenPosition);*/

			// ���̍��W��
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, waitTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, waitTime);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// ���o�I��
			PublicFlag::kisStaging = false;
			isPlayingStartAnim = false;

			// ������
			isBattleStart = true;
			t = 0.0f;
			actionWayPoint = WAYPOINT0;
		}
		break;
	case MiddleBoss::WAYPOINT5:
		break;
	case MiddleBoss::WAYPOINT6:
		break;
	default:
		break;
	}
}

/// <summary>
/// ���S���̃A�j���[�V�������Đ�����֐�
/// </summary>
///<param name="cameraMoveTime">�J�����𓮂�������</param>
/// <param name="roarTime">���K����</param>
/// <param name="moveTime">�������ɍs��</param>
/// <param name="runAwayTime">�����ď��</param>
/// <param name="cameraBackTime">�J������߂�</param>
void MiddleBoss::PlayDeadAnim(float cameraMoveTime, float moveTime, float runAwayTime, float cameraBackTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// ������
	case MiddleBoss::WAYPOINT0:

		// ���o���̏�Ԃ�
		PublicFlag::kisStaging = true;
		isPlayingDeadAnim = true;

		wireManager->Initialize();

		// �X�N���[�����W�L�^
		prevScreenPosition = BaseDraw::GetScreenPosition();
		nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
			screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) };

		// ����T�C�Y������
		weaponSize = { 0.0f, 0.0f };

		prevCenterPosition = centerPosition;
		nextCenterPosition = screenCenterPosition;

		if (Novice::IsPlayingAudio(screamVoiceHundle) == 0 || screamVoiceHundle == -1) {
			// ���ʉ��Đ�
			screamVoiceHundle = Novice::PlayAudio(screamSoundHundle, false, 0.5f);
		}

		// t������
		t = 0.0f;
		// ���̒i�K��
		actionWayPoint++;

		break;
		// �J�������{�X�̂Ƃ���܂œ�����
	case MiddleBoss::WAYPOINT1:
		if (t <= cameraMoveTime) {

			// �X�N���[���𓮂���
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_In(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, cameraMoveTime);
			screenPosition.y = BaseDraw::Ease_In(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, cameraMoveTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// �{�X�𓮂���
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, cameraMoveTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, cameraMoveTime);

			// �{�X��U��������
			Shake(15);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// �X�N���[�����W�L�^
			prevScreenPosition = BaseDraw::GetScreenPosition();
			nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
				screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) - 150.0f };
			 
			// �{�X�̍��W
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, centerPosition.y - 150.0f };

			// �`���[�W��
			Novice::PlayAudio(BaseAudio::kBossCharge, false, 0.5f);

			// ������
			t = 0.0f;
			actionWayPoint++;
		}

		break;
		// �{�X���������ɍs��
	case MiddleBoss::WAYPOINT2:
		if (t <= moveTime) {

			ShakeEaseOut(15, moveTime);

			// �X�N���[���𓮂���
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, moveTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, moveTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// �{�X�𓮂���
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, moveTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, moveTime);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// �X�N���[�����W�L�^
			prevScreenPosition = BaseDraw::GetScreenPosition();
			nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
				screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) + 250.0f };

			// �{�X�̍��W
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, centerPosition.y + BaseConst::kWindowHeight };

			Novice::PlayAudio(BaseAudio::kBossRush, false, 0.5f);

			// ������
			t = 0.0f;
			actionWayPoint++;
		}
		break;
		// �{�X�����K����
	case MiddleBoss::WAYPOINT3:
		if (t <= runAwayTime) {

			// �X�N���[���𓮂���
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, runAwayTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, runAwayTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// �{�X�𓮂���
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, runAwayTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, runAwayTime);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// �X�N���[�����W�L�^
			prevScreenPosition = BaseDraw::GetScreenPosition();
			nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
				screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) };

			// ������
			t = 0.0f;
			actionWayPoint++;

		}
		break;
		// �ҋ@���Ă���{�X��J�n
	case MiddleBoss::WAYPOINT4:
		if (t <= cameraBackTime) {

			// �X�N���[���𓮂���
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, cameraBackTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, cameraBackTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// ���o�I��
			PublicFlag::kisStaging = false;
			isPlayingDeadAnim = false;

			// ������
			isEndDeadAnim = true;

			inDead = true;

			t = 0.0f;
			actionWayPoint = WAYPOINT0;

		}
		break;
	case MiddleBoss::WAYPOINT5:
		break;
	case MiddleBoss::WAYPOINT6:
		break;
	default:
		break;
	}
}

// �s���Ȃ��֐�
// �Ԃ�l�F�Ȃ�
// �����F
// waitTime ... �ҋ@����b��
// �s���̍��Ԃɋ��ފ֐��B
void MiddleBoss::None(float waitFrame) {
	if (t <= waitFrame) {
		t += 1.0f / 60.0f;
	}
	else {
		pleaseWait = false;
		t = 0.0f;
		endAction = true;
		inAction = false;
	}
}

// �ڋߊ֐�
// �Ԃ�l�F�Ȃ�
// �����F
// playerPosition ... �v���C���[���S���W
// moveTIme ... ��]���鎞��
// afterWaitTime ... �s����ɔ�������ҋ@����
// �v���C���[�Ɍ������Đڋ߂���֐�
void MiddleBoss::Approach(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case MiddleBoss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;

		// �v���C���[�̍��W���擾
		prePlayerPosition = playerPosition;

		// �v���C���[�Ƃ̋��������߂�
		playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

		// �v���C���[��������������߂�
		playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

		// �ːi������W�����߂�
		nextCenterPosition = {
			centerPosition.x + (cosf(playerDirection) * playerDistance / 4),
			centerPosition.y + (sinf(playerDirection) * playerDistance / 4)
		};

		// t������
		t = 0.0f;

		// ���̒i�K��
		actionWayPoint++;
		break;
	case MiddleBoss::WAYPOINT1:
		if (t <= moveTime) {

			// �{�X���擾�����v���C���[�̌����Ɍ������ēːi������
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, (nextCenterPosition.x) - prevCenterPosition.x, moveTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, (nextCenterPosition.y) - prevCenterPosition.y, moveTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			//t �����ȏ�ɂȂ�����s���I��
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = APPROACH;
			pleaseWait = true;
			waitTime = afterWaitTime;
			t = 0.0f;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}

		break;
	}
}

// �����֐�
// �Ԃ�l�F�Ȃ�
// �����F
// playerPosition ... �v���C���[���S���W
// moveTIme ... ��]���鎞�ԁB����͕b��
// afterWaitTime ... �s����ɔ�������ҋ@����
// �v���C���[�Ɍ������ė�������֐�
void MiddleBoss::Separation(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case MiddleBoss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;

		// �v���C���[�̍��W���擾
		prePlayerPosition = playerPosition;

		// �v���C���[��������������߂�
		playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

		// �v���C���[�Ƃ̋��������߂�
		playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

		// �ːi������W�����߂�
		nextCenterPosition = {
			centerPosition.x + (cosf(playerDirection) * playerDistance / 4),
			centerPosition.y + (sinf(playerDirection) * playerDistance / 4)
		};

		// t������
		t = 0.0f;

		// ���̒i�K��
		actionWayPoint++;
		break;
	case MiddleBoss::WAYPOINT1:

		if (t <= moveTime) {

			// �{�X���擾�����v���C���[�̌����Ɍ������ēːi������
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, -(nextCenterPosition.x - prevCenterPosition.x), moveTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, -(nextCenterPosition.y - prevCenterPosition.y), moveTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			//t �����ȏ�ɂȂ�����s���I��
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = SEPARATION;
			pleaseWait = true;
			waitTime = afterWaitTime;
			t = 0.0f;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}

		break;
	}
}

// ��]�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// endDegree ... �I�����̊p�x
// rotateTime ... ��]���鎞�ԁB����͕b��
// afterWaitTime ... �s����ɔ�������ҋ@����
// �{�X����]������֐�
void MiddleBoss::Rotate(float endDegree, float RotateTime, float afterWaitTime, WireManager* wireManager) {

	static int startDegree;
	// ����������
	if (init == false) {
		startDegree = degree;

		// ���ʉ��Đ�
		Novice::PlayAudio(BaseAudio::kBossClose, false, 0.5f);

		init = true;
	}

	// t �̒l�����ȏ�ɂȂ�܂ő���
	if (t <= RotateTime) {
		inAction = true;
		// �C�[�W���O��p���ĉ�]
		degree = BaseDraw::Ease_InOut(t, startDegree, endDegree, RotateTime);

		if (t >= (RotateTime / 2)) {
			// ���C���[������
			PublicFlag::kBossisTurningAndCutWire = true;
		}

		t += 1.0f / 60.0f;
	}
	else {

		// ���C���[��������Ȃ�����
		PublicFlag::kBossisTurningAndCutWire = false;

		//t �����ȏ�ɂȂ�����s���I��
		prevAttackPattern[1] = prevAttackPattern[0];
		prevAttackPattern[0] = ROTATE;
		pleaseWait = true;
		waitTime = afterWaitTime;
		t = 0.0f;
		degree = 0;
		init = false;
		endAction = true;
		inAction = false;
	}
}

// �ːi�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// playerPosition ... �v���C���[�̍��W
// readyTime ... �ːi�̏����ɂ�����b��
// chargeTime ... �ːi�̗��߂ɂ�����b��
// rushTime ... �ːi�ɂ�����b��
// backTime ... �߂鎞�ɂ�����b��
// afterWaitTime ... �s����ɔ�������ҋ@����
// damage ... �s���ɂ���Ĕ�������_���[�W
// �{�X���v���C���[�̌����ɓːi������֐�
void MiddleBoss::Rush(Point playerPosition, float readyTime, float chargeTime, float rushTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {

	switch (actionWayPoint)
	{
		// ������
	case MiddleBoss::WAYPOINT0:

		// ���ʉ��Đ�
		Novice::PlayAudio(BaseAudio::kBossCharge, false, 0.5f);

		// ���S���W�擾
		prevCenterPosition = centerPosition;

		// t������
		t = 0.0f;

		// ���̒i�K��
		actionWayPoint++;
		break;
		// ���O����(�k����)
	case MiddleBoss::WAYPOINT1:
		if (t <= readyTime) {
			// �w�肳�ꂽ�b���U������
			ShakeEaseOut(60, readyTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			// t������
			t = 0.0f;

			// �v���C���[�̍��W���擾
			prePlayerPosition = playerPosition;

			// �v���C���[��������������߂�
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// �v���C���[�Ƃ̋��������߂�
			playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

			if (playerDistance < 500.0f) {
				playerDistance = 500.0f;
			}

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossVibration, false, 0.5f);

			// �ːi������W�����߂�
			nextCenterPosition = {
				centerPosition.x + (cosf(playerDirection) * -300.0f),
				centerPosition.y + (sinf(playerDirection) * -300.0f)
			};

			// ����
			actionWayPoint++;
		}
		break;
		// ����
	case MiddleBoss::WAYPOINT2:

		if (t <= chargeTime) {

			// �{�X���擾�����v���C���[�̌����Ɍ������ēːi������
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			// t������
			t = 0.0f;

			// �v���C���[�̍��W���擾
			prePlayerPosition = playerPosition;

			// �v���C���[��������������߂�
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// �v���C���[�Ƃ̋��������߂�
			playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

			if (playerDistance < 500.0f) {
				playerDistance = 500.0f;
			}

			prevCenterPosition = centerPosition;

			// �ːi������W�����߂�
			nextCenterPosition = {
				centerPosition.x + (cosf(playerDirection) * playerDistance),
				centerPosition.y + (sinf(playerDirection) * playerDistance)
			};

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossRush, false, 0.7f);

			// ����
			actionWayPoint++;
		}

		break;
		// �ːi
	case MiddleBoss::WAYPOINT3:
		if (t <= rushTime) {

			// �{�X���擾�����v���C���[�̌����Ɍ������ēːi������
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);

			// �_���[�W��^������悤�ɂ���
			bodyDamage = damage;

			t += 1.0f / 60.0f;
		}
		else {

			// �_���[�W��^�����Ȃ�����
			bodyDamage = 0.0f;

			// �ːi������W�����߂�
			prevCenterPosition = {
				prevCenterPosition.x + (cosf(playerDirection) * 300.0f),
				prevCenterPosition.y + (sinf(playerDirection) * 300.0f)
			};

			// t��������
			t = 0.0f;

			// ���̍s����
			actionWayPoint++;
		}
		break;
		// �߂�
	case MiddleBoss::WAYPOINT4:
		if (t <= backTime) {
			// �{�X�����̍��W�ɖ߂�
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {

			// �{�X�̍��W�����̈ʒu�ɖ߂��i�ꉞ�j
			centerPosition = prevCenterPosition;

			// t������
			t = 0.0f;

			// �s���I��
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = RUSH;
			pleaseWait = true;
			waitTime = afterWaitTime;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	case MiddleBoss::WAYPOINT5:
		break;
	default:
		break;
	}
}

// �a���֐�
// �Ԃ�l�F�Ȃ�
// �����F
// playerPosition ... �v���C���[�̍��W
// readyTime ... �{�X���J���܂łɂ�����b��
// deployTime ... �u���[�h�̓W�J�ɂ�����b��
// preparationTime�@... �U���܂ł̑ҋ@����
// rushTime ... �ːi�ɂ�����b��
// backTime ... �߂鎞�ɂ�����b��
// afterWaitTime ... �s����ɔ�������ҋ@����
// damage ... �s���ɂ���Ĕ�������_���[�W
// �{�X���a�����s���֐�
void MiddleBoss::Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// ������
	case MiddleBoss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;

		// ������ǂꂾ���傫�����邩�����߂�
		weaponSize = { 40, 0 };
		prevWeaponSize = weaponSize;
		nextWeaponSize = { weaponSize.x, 400.0f };

		// t������
		t = 0.0f;

		// ���ʉ��Đ�
		Novice::PlayAudio(BaseAudio::kBossOpen, 0, 0.35f);

		//���̒i�K��
		actionWayPoint++;
		break;
		// ���O����(�k���ă{�X���J��)
	case MiddleBoss::WAYPOINT1:
		if (t <= readyTime) {
			// �w�肳�ꂽ�b���U������
			ShakeEaseOut(60, readyTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			// t�����Z�b�g
			t = 0.0f;

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossDeployBlade, 0, 0.5f);

			//����
			actionWayPoint++;
		}
		break;
		// �u���[�h�W�J
	case MiddleBoss::WAYPOINT2:
		if (t <= deployTime) {

			// �u���[�h���L�т�
			weaponSize.y = BaseDraw::Ease_InOut(t, prevWeaponSize.y, nextWeaponSize.y - prevWeaponSize.y, deployTime);

			bladeDamage = 1.0f;

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// t��������
			t = 0.0f;

			// �����p�x��ݒ�
			prevDegree = degree;

			//���̍s���������_���ɐݒ肵�ĕ���
			actionBranch = BaseMath::Random(Pattern1, Pattern2);
			switch (actionBranch)
			{
				// �E��]
			case MiddleBoss::Pattern1:
				// �������ɓ�����
				nextDegree = prevDegree - 30;
				break;
				// ����]
			case MiddleBoss::Pattern2:
				// �E�����ɓ�����
				nextDegree = prevDegree + 30;
				break;
				// ��]�؂�
				break;
			default:
				break;
			}

			// ���̒i�K
			actionWayPoint++;
		}

		break;
		// �a������
	case MiddleBoss::WAYPOINT3:
		if (t <= preparationTime) {
			//�{�X����]������
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);
			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			// t��������
			t = 0.0f;

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossSlash, 0, 0.25f);

			//�v���C���[���W�擾
			prePlayerPosition = playerPosition;

			// �v���C���[��������������߂�
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// �v���C���[�Ƃ̋��������߂�
			float playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

			// �v���C���[�Ƃ̋��������ȉ��Ȃ炻�̏�Ŏa�����s��
			if (playerDistance < 200.0f) {
				playerDistance = 0.0f;
			}
			else {
			}

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossRush, 0, 0.6f);

			// �ːi������W�����߂�
			nextCenterPosition = {
				centerPosition.x + (cosf(playerDirection) * playerDistance / 1.25f),
				centerPosition.y + (sinf(playerDirection) * playerDistance / 1.25f)
			};

			// �����p�x��ݒ�
			prevDegree = degree;

			// �s������Ɋ�Â��ĉ�]�p�̐ݒ�
			switch (actionBranch)
			{
				// �E��]
			case MiddleBoss::Pattern1:
				nextDegree = prevDegree + 360;
				break;
				// ����]
			case MiddleBoss::Pattern2:
				nextDegree = prevDegree - 360;
				break;
			default:
				break;
			}

			// ����
			actionWayPoint++;
		}
		break;
		// �a��
	case MiddleBoss::WAYPOINT4:
		if (t <= slashTime) {

			// �{�X����]������
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, slashTime);

			// �{�X���擾�����p�x�����ɓːi������
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, slashTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, slashTime);

			if (t >= (slashTime / 2)) {
				// ���C���[������
				PublicFlag::kBossisTurningAndCutWire = true;
			}

			// ����F��]�a��ȊO�̏ꍇ��t�Ƀv���X����l������������������
			t += 1.0f / 60.0f;
		}
		else {

			// ���C���[������
			PublicFlag::kBossisTurningAndCutWire = false;

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossClose, 0, 0.35f);

			// t��������
			t = 0.0f;
			// ����
			actionWayPoint++;
		}
		break;
		// ���̏ꏊ�ɖ߂�
	case MiddleBoss::WAYPOINT5:
		if (t <= backTime) {

			// �ʒu��p�x�A����̃T�C�Y�����ɖ߂�
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			degree = BaseDraw::Ease_InOut(t, nextDegree, -nextDegree, backTime);
			weaponSize.y = BaseDraw::Ease_InOut(t, nextWeaponSize.y, -nextWeaponSize.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {

			// �{�X���W���������i�ꉞ�j
			centerPosition = prevCenterPosition;

			// �_���[�W��^�����Ȃ��悤��
			bladeDamage = 0.0f;

			// �p�x������
			degree = 0;
			prevDegree = 0;
			nextDegree = 0;

			// t������
			t = 0.0f;

			// �s���I��
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = SLASH;
			waitTime = afterWaitTime;
			pleaseWait = true;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	default:
		break;
	}
}

// �I�u�W�F�N�g�����֐�
// �Ԃ�l�F�Ȃ�
// �����F
// readyTime ... �{�X�̍��W�𒆐S�ɖ߂��b��
// deployTime ... �U�������ɂ�����b��
// rushTime�@... �V��ɓːi����܂łɂ�����b��
// standByTime ... �ҋ@�b��
// backTime ... �߂鎞�ɂ�����b��
// damage ... �s���ɂ���Ĕ�������_���[�W
// �{�X���V��ɂԂ���A�j�Ђ𗎉������čU�����s���֐�
void MiddleBoss::Fall(float readyTime, float deployTime, float rushTime, float standByTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// ������
	case MiddleBoss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;
		nextCenterPosition = screenCenterPosition;

		// t������
		t = 0.0f;

		//���̒i�K��
		actionWayPoint++;
		break;
		// �{�X�𒆐S���W�ɖ߂�
	case MiddleBoss::WAYPOINT1:
		if (t <= readyTime) {

			// ��ʒ����֖߂�
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, readyTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, readyTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossCharge, false, 0.5f);

			// t�����Z�b�g
			t = 0.0f;

			// ���W�ݒ�
			prevCenterPosition = centerPosition;
			nextCenterPosition = { screenCenterPosition.x, screenCenterPosition.y - 200 };

			//����
			actionWayPoint++;
		}
		break;
		// ����
	case MiddleBoss::WAYPOINT2:
		if (t <= deployTime) {

			// �኱���ɉ�����
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, deployTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, deployTime);

			ShakeEaseOut(50, deployTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossRush, false, 0.5f);

			// t��������
			t = 0.0f;

			// ���W�ݒ�
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, screenCenterPosition.y + ((float)BaseConst::kTutorialStageSizeHeight * ((float)BaseConst::kMapChipSizeHeight) / 2) - (textureSize.y / 2)};

			// ���̒i�K
			actionWayPoint++;
		}

		break;
		// �V��ɓːi
	case MiddleBoss::WAYPOINT3:
		if (t <= rushTime) {

			// �ːi
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			// t��������
			t = 0.0f;

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossVibration, false, 0.5f);
			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossStrike, false, 0.5f);


			canGeneratedBlock = true;
			generatedBlockValue = BaseMath::Random(3, 5);

			// ����
			actionWayPoint++;
		}
		break;
		// �ҋ@
	case MiddleBoss::WAYPOINT4:
		if (t <= standByTime) {

			// ���ˎ��V�F�C�N
			ShakeEaseOut(50, standByTime);

			// t���v���X����
			t += 1.0f / 60.0f;

		}
		else {

			// ���݂̍��W���L�^����
			prevCenterPosition = screenCenterPosition;
			nextCenterPosition = centerPosition;

			// t��������
			t = 0.0f;
			// ����
			actionWayPoint++;
		}
		break;
		// ���̏ꏊ�ɖ߂�
	case MiddleBoss::WAYPOINT5:
		if (t <= backTime) {
			// �ʒu��p�x�A����̃T�C�Y�����ɖ߂�
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			// �{�X���W���������i�ꉞ�j
			centerPosition = prevCenterPosition;

			// �p�x������
			degree = 0;
			prevDegree = 0;
			nextDegree = 0;

			// t������
			t = 0.0f;

			// �s���I��
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = FALL;
			waitTime = 0.25f;
			pleaseWait = true;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	default:
		break;
	}
}

// �X�^���֐�
// �Ԃ�l�F�Ȃ�
// �����F
// readyTime ... �X�^�����n�߃��[�V�����b��
// deployTime ... �X�^�����n�߃��[�V�����b��
// stanTime�@... �X�^���b��
// backTime ... �߂鎞�ɂ�����b��
// �w�肳�ꂽ�b���{�X���X�^������֐�
void MiddleBoss::Stun(float readyTime, float deployTime, float stanTime, float backTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case MiddleBoss::WAYPOINT0:

		// �O�̂��߈�x������
		// ���W�擾
		prevCenterPosition = { 0.0f, 0.0f };
		nextCenterPosition = { 0.0f, 0.0f };

		// �p�x�擾
		prevDegree = 0;
		nextDegree = 0;

		t = 0.0f;
		endAction = true;
		inAction = false;

		// ����T�C�Y������
		weaponSize = { 0.0f, 0.0f };

		// ���W�擾
		prevCenterPosition = centerPosition;
		nextCenterPosition = { centerPosition.x, centerPosition.y + 100.0f };

		// �p�x�擾
		prevDegree = degree;
		nextDegree = degree + 20;

		// ���̍s����
		actionWayPoint++;
		break;
		// 
	case MiddleBoss::WAYPOINT1:
		if (t <= readyTime) {
			// ���W�֘A���C�[�W���O
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, readyTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, readyTime);

			// �p�x�֘A���C�[�W���O
			degree = BaseDraw::Ease_Out(t, prevDegree, nextDegree - prevDegree, readyTime);

			ShakeEaseOut(30, readyTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// ���W�擾
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, centerPosition.y - 150.0f };

			// �p�x�擾
			prevDegree = degree;
			nextDegree = degree - 40;

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case MiddleBoss::WAYPOINT2:
		if (t <= deployTime) {
			// ���W�֘A���C�[�W���O
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, deployTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, deployTime);

			// �p�x�֘A���C�[�W���O
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, deployTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case MiddleBoss::WAYPOINT3:
		if (t <= stanTime) {

			// ���b���U��
			vibration(10, stanTime, stanTime, 3);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			prevCenterPosition = centerPosition;
			nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };

			prevDegree = degree;

			vibInit = false;

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case MiddleBoss::WAYPOINT4:
		if (t <= backTime) {

			// ���W�֘A���C�[�W���O
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);

			// �p�x�֘A���C�[�W���O
			degree = BaseDraw::Ease_InOut(t, prevDegree, -prevDegree, backTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// t������������
			t = 0.0f;
			// �s���I��
			inStun = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	case MiddleBoss::WAYPOINT5:
		break;
	default:
		break;
	}
}

/******** �_���[�W�A�j���[�V���� **********/
// �_���[�W�A�j���[�V�����֐�
// �Ԃ�l�F�Ȃ�
// �����F
// readyTime ... �U�����鎞��
// shakeStrength ... �U�����鋭��
// �_���[�W���^����ꂽ���̃A�j���[�V�������Đ�����֐�
void MiddleBoss::playTakeDamageAnim(float animTime, float shakeStrength) {
	if (spareT <= animTime) {
		shakeRange = BaseDraw::Ease_Out(spareT, shakeStrength, -shakeStrength, animTime);

		shakeVariation.x = BaseMath::RandomF(-shakeStrength / 2, shakeStrength / 2, 0);
		shakeVariation.y = BaseMath::RandomF(-shakeStrength / 2, shakeStrength / 2, 0);

		// t���v���X����
		spareT += 1.0f / 60.0f;
	}
	else {

		//t��������
		spareT = 0.0f;
		inDamage = false;
	}
}