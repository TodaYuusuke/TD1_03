#include "Class/Boss/Boss.h"

/*********************************************
 * �{�X�N���X
 *
 * �{�X�֘A�̍s�����ׂĂ��Ǘ�����N���X
 *********************************************/

// �R���X�g���N�^
Boss::Boss() {
	// �{�X�̈ʒu����ʒ����Ɏ����Ă���
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	// �{�X�̉摜�T�C�Y��ݒ�
	this->textureSize = { 225.0f, 450.0f };
	// �{�X�̃I�t�Z�b�g��������
	this->offset = 0.0f;

	// �p�x������
	this->degree = 0.0f;
	// 1�t���[���O�̊p�x��������
	this->beforeDegree = 0.0f;

	//�V�F�C�N���Ă��Ȃ���Ԃɖ߂�
	this->shakeVariation = { 0.0f, 0.0f };
	this->coreShakeVariation = { 0.0f, 0.0f };

	// �o�C�u���[�V����������
	vibInit = false;

	// �s���I����Ԃɂ���
	this->t = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->actionWayPoint = 0;

	// �j�̓����蔻���������
	core = NULL;

	// �j�̈ʒu��ݒ�
	this->coreCenterPosition = centerPosition;
	// �j�̉摜�T�C�Y��ݒ�
	this->coreTextureSize = { 256.0f, 256.0f };

	// �j�̉摜�T�C�Y��ݒ�
	this->hookTextureSize = { 64.0f, 64.0f };

	// ����̃T�C�Y���w��i���e�N�X�`���̂��߁A����ς���j
	this->weaponSize = { 0.0f, 0.0f };
	this->weaponTextureSize = { 1.0f, 1.0f };

	// �t�b�N�T�C�Y������
	hookSize = { 96.0f, 96.0f };

	// �t�b�N�̏�����
	for (int i = 0; i < kmaxWireHang; i++) {
		this->wireHangPosition[i] = { 0.0f, 0.0f };
		hook[i] = NULL;
	}

	// �U���p�^�[��������
	this->prevAttackPattern[0] = NONE;
	this->prevAttackPattern[1] = NONE;
	this->attackPattern = NONE;

	// �ҋ@��
	pleaseWait = true;

	// �ҋ@���Ԃ���
	this->waitTime = 2.5f;

	// HP������
	this->HP = MaxHP;

	// �^����_���[�W������
	this->bodyDamage = 0.0f;
	this->bladeDamage = 0.0f;

	/// �e�̊֌W������
	for (int i = 0; i < kmaxBullet; i++) {
		// �e�̍��W
		this->bulletCenterPosition[i] = { 0.0f, 0.0f };

		// ���˂��Ă��Ȃ���Ԃɂ���
		this->isShot[i] = false;

		// �e�̔��˕��������Z�b�g����
		this->bulletDirection[i] = 0.0f;

		// �e�̐������Ԃ����Z�b�g����
		this->bulletAliveTime[i] = 0.0f;

		// �e�̃_���[�W������
		this->bulletDamage[i] = 0.0f;

	}

	// �e�̃T�C�Y���w��
	this->bulletSize = { 20.0f, 20.0f };
	// �e�̉摜�T�C�Y���w��i���e�N�X�`���̂��߁A����ς���)
	this->bulletTextureSize = { 1.0f, 1.0f };

	// �e�̔��˃X�s�[�h���w��
	this->bulletSpeed = 7.0f;

	/// �I�u�W�F�N�g�֘A
	// �I�u�W�F�N�g�𐶐����邩�ǂ���
	this->canGeneratedBlock = false;

	// �I�u�W�F�N�g������
	this->generatedBlockValue = 0;

	// �I�u�W�F�N�g�����Ԋu
	this->generatedBlockInterval = 0.0f;
}

// �f�X�g���N�^
Boss::~Boss() {

}

// ����������
void Boss::Initialize(ObjectManager* objectManager) {
	// �{�X�̈ʒu����ʒ����Ɏ����Ă���
	this->centerPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };
	// �{�X�̉摜�T�C�Y��ݒ�
	this->textureSize = { 225.0f, 450.0f };
	// �{�X�̃I�t�Z�b�g��������
	this->offset = 0.0f;

	// �p�x������
	this->degree = 0.0f;
	// 1�t���[���O�̊p�x��������
	this->beforeDegree = 0.0f;

	//�V�F�C�N���Ă��Ȃ���Ԃɖ߂�
	this->shakeVariation = { 0.0f, 0.0f };
	this->coreShakeVariation = { 0.0f, 0.0f };

	// �J�b�g�V�[���p�J�����ړ��O���W
	this->prevScreenPosition = {0.0f, 0.0f};

	// �J�b�g�V�[���p�J�����ړ�����W
	this->nextScreenPosition = {0.0f, 0.0f};

	// �o�C�u���[�V����������
	vibInit = false;

	// �U�����Đ��g���K�[��false��
	isVibPlaySound = false;

	// �퓬�J�n���Ă��Ȃ���Ԃɂ���
	this->isBattleStart = false;

	// �s���I����Ԃɂ���
	this->t = 0.0f;
	this->spareT = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->inStun = false;
	this->canTakeDamage = false;
	this->inDamage = false;
	this->actionWayPoint = 0;

	// �j�̈ʒu��ݒ�
	this->coreCenterPosition = centerPosition;
	// �j�̉摜�T�C�Y��ݒ�
	this->coreTextureSize = { 256.0f, 256.0f };

	// �j�̃T�C�Y
	this->coreSize = { 256.0f, 256.0f };

	coreSeparated = false;

	// �j�̓����蔻���������
	core = objectManager->MakeNewObjectCore(coreCenterPosition, coreTextureSize);

	// �t�b�N�̉摜�T�C�Y��ݒ�
	this->hookTextureSize = { 48.0f, 48.0f };

	// ����̃T�C�Y���w��i���e�N�X�`���̂��߁A����ς���j
	this->weaponSize = { 0.0f, 0.0f };
	this->weaponTextureSize = { 1.0f, 1.0f };

	// �t�b�N�T�C�Y������
	hookSize = { 96.0f, 96.0f };

	for (int i = 0; i < kmaxWireHang; i++) {
		this->wireHangPosition[i] = { 0.0f, 0.0f };
		hook[i] = objectManager->MakeNewObjectHook(wireHangPosition[i], {hookSize.x -20.0f, hookSize.y -20.0f});
	}


	// �U���p�^�[��������
	this->prevAttackPattern[0] = NONE;
	this->prevAttackPattern[1] = NONE;
	this->attackPattern = NONE;

	// �ҋ@��
	pleaseWait = true;

	// �ҋ@���Ԃ���
	this->waitTime = 1.0f;

	// HP������
	this->HP = MaxHP;

	// �^����_���[�W������
	this->bodyDamage = 0.0f;
	this->bladeDamage = 0.0f;

	// ���S���Ă��Ȃ���Ԃɂ���
	this->inDead = false;

	/// �e�̊֌W������
	for (int i = 0; i < kmaxBullet; i++) {
		// �e�̍��W
		this->bulletCenterPosition[i] = { 0.0f, 0.0f };

		// ���˂��Ă��Ȃ���Ԃɂ���
		this->isShot[i] = false;

		// �e�̔��˕��������Z�b�g����
		this->bulletDirection[i] = 0.0f;

		// �e�̐������Ԃ����Z�b�g����
		this->bulletAliveTime[i] = 0.0f;

		// �e�̃_���[�W������
		this->bulletDamage[i] = 0.0f;

	}

	// �e�̃T�C�Y���w��
	this->bulletSize = { 20.0f, 20.0f };
	// �e�̉摜�T�C�Y���w��i���e�N�X�`���̂��߁A����ς���)
	this->bulletTextureSize = { 1.0f, 1.0f };

	// �e�̔��˃X�s�[�h���w��
	this->bulletSpeed = 7.0f;

	/// �I�u�W�F�N�g�֘A
	// �I�u�W�F�N�g�𐶐����邩�ǂ���
	this->canGeneratedBlock = false;

	// �I�u�W�F�N�g������
	this->generatedBlockValue = 0;

	// �I�u�W�F�N�g�����Ԋu
	this->generatedBlockInterval = 0.0f;

	// �F�֌W������
	this->color = 0xFFFFFFFF;
	this->coreColor = 0xFFFFFFFF;

	// ���o�X�L�b�v�p
	LongPressFrame = 0.0f;

	// ���݉��o����
	isPlayingStartAnim = false;

	// ���S�A�j���[�V����
	isPlayingDeadAnim = false;

	// ���S�A�j���[�V�������I�����Ă��邩
	isEndDeadAnim = false;

	PullSoundHundle = BaseAudio::kBossPull;
	PullVoiceHundle = -1;

}

// �X�V����
void Boss::Update(Point playerPosition, ObjectManager* objectManager, WireManager* wireManager) {

	/******** �f�o�b�N���� **********/
	// �f�o�b�O��Ԃ̐؂�ւ�
	if (BaseInput::GetKeyboardState(DIK_H, Press) && BaseInput::GetKeyboardState(DIK_U, Press)) {
		if (BaseInput::GetKeyboardState(DIK_BACKSPACE, Trigger)) {
			if (inDebug == false) {
				// �퓬�J�n��Ԃɂ���
				isBattleStart = true;
				// �I�t�Z�b�g������
				offset = 0;
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

	// �j���������Ă��Ȃ���Ԃł͊j���{�X�ɒǏ]������
	if (coreSeparated == false) {
		coreCenterPosition = centerPosition;
		coreShakeVariation = shakeVariation;
		coreDegree = degree;
	}

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
							case Boss::Pattern1:
								attackPattern = FALL;
								break;
							case Boss::Pattern2:
								attackPattern = SLASH;
								break;
							case Boss::Pattern3:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[0] == SEPARATION
									|| prevAttackPattern[1] == APPROACH || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = ROTATE;
								}

								break;
							case Boss::Pattern4:
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
							attackBranch = BaseMath::Random(Pattern1, Pattern5);
							switch (attackBranch)
							{
							case Boss::Pattern1:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[0] == SEPARATION
									|| prevAttackPattern[1] == APPROACH || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = ROTATE;
								}
								break;
							case Boss::Pattern2:
								attackPattern = SHOT;
								break;
							case Boss::Pattern3:
								attackPattern = SLASH;
								break;
							case Boss::Pattern4:
								attackPattern = RUSH;
								break;
							case Boss::Pattern5:
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

				// �s���J�n
				inAction = true;
				endAction = false;

			}
		}

		// �s���̎��s����
		if (inAction == true && inStun == false && canTakeDamage == false && isPlayingDeadAnim ==false) {
			switch (attackPattern)
			{
			case Boss::NONE:
				None(waitTime);
				break;
			case Boss::ROTATE:
				Rotate(720, 2.0f, 0.5f, wireManager);
				break;
			case Boss::RUSH:
				Rush(playerPosition, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case Boss::SLASH:
				Slash(playerPosition, 0.35f, 0.2f, 1.25f, 1.0f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case Boss::SHOT:
				Shot(playerPosition, 0.35f, 0.75f, 1.0f, 5.0f, 1.0f, 1.0f, 0.2f, 1.0f, wireManager);
				break;
			case Boss::FALL:
				Fall(0.35f, 1.0f, 0.15f, 0.75f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case Boss::APPROACH:
				Approach(playerPosition, 1.0f, 0.1f, wireManager);
				break;
			case Boss::SEPARATION:
				Separation(playerPosition, 1.0f, 0.1f, wireManager);
				break;
			}
		}

		// �X�^������
		if (inStun == true && canTakeDamage == false) {
			Stun(1.25f, 1.5f, 3.0f, 0.75f, wireManager);
		}

		// �_���[�W���󂯂����Ԃɂ��鏈��
		if (canTakeDamage == true && isPlayingDeadAnim == false) {
			MakeDamagePossible(0.15f, 1.5f, 0.1f, 10.0f, 0.75f, 0.25f, wireManager, objectManager);
		}
		else {
			if (hook[0]->GetisPulled() == true && hook[1]->GetisPulled() == true) {
				actionWayPoint = WAYPOINT0;
				canTakeDamage = true;
			}
		}

		// �_���[�W��^�����ۂ̃A�j���[�V�����Đ�
		if (inDamage == true) {
			playTakeDamageAnim(0.1f, 50);
		}

		degree %= 360;

		//�@�R�A�̓����蔻��̒��S���W���Z�b�g��������
		// �{�X���J���Ă��鎞�̓{�X���̂̃q�b�g�{�b�N�X�𖳌��ɂ���
		if (offset > 150) {
			// �J���Ă鎞�ɒǏ]
			core->SetCenterPosition(viewPosition);

			if (isPlayingDeadAnim == false) {
				color = 0x333333FF;
			}

			// �{�X�̃q�b�g�{�b�N�X��L���ɂ���
			EnemyAttackHitBox::MakeNewHitBoxRight({ 10000.0f, 10000.0f }, textureSize.y / 2.0f, degree, bodyDamage);
			EnemyAttackHitBox::MakeNewHitBoxLeft({ 10000.0f, 10000.0f }, textureSize.y / 2.0f, degree, bodyDamage);

		}
		else {
			// �J���Ă��Ȃ��Ƃ��͂��肦�Ȃ��قǂƂ�����
			core->SetCenterPosition({ 10000.0f, 10000.0f });

			if (isPlayingDeadAnim == false) {
				color = 0xFFFFFFFF;
			}

			// �{�X�̃q�b�g�{�b�N�X��L���ɂ���
			EnemyAttackHitBox::MakeNewHitBoxRight(GetRCoverCollision(centerPosition), textureSize.y / 2.0f, degree, bodyDamage);
			EnemyAttackHitBox::MakeNewHitBoxLeft(GetLCoverCollision(centerPosition), textureSize.y / 2.0f, degree, bodyDamage);

		}

		// �t�b�N�̍��W���X�V��������
		wireHangPosition[0] = GetLHookPosition(viewPosition);
		wireHangPosition[1] = GetRHookPosition(viewPosition);

		// �t�b�N�̒��S���W���Z�b�g����
		hook[0]->SetCenterPosition(wireHangPosition[0]);
		hook[1]->SetCenterPosition(wireHangPosition[1]);

		float degreeDifference = degree - beforeDegree;

		for (int i = 0; i < 5; i++) {
			// ����̃q�b�g�{�b�N�X
			EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree + (degreeDifference * i), bladeDamage);
		}

		// ����̃q�b�g�{�b�N�X
		EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree, bladeDamage);
		EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree - 30.0f, bladeDamage);
		EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree + 30.0f, bladeDamage);

		/// �e�֌W�̍X�V����
		// ���˒n�_�̍X�V
		shotPoint = GetShotPosition(centerPosition);

		// �e�����˂���Ă��鎞�̏���
		for (int i = 0; i < kmaxBullet; i++) {

			// �e�̃q�b�g�{�b�N�X
			EnemyAttackHitBox::MakeNewHitBox(bulletCenterPosition[i], bulletSize.x, bulletSize.y, 0.0f, bulletDamage[i]);

			if (isShot[i] == true && bulletAliveTime[i] > 0.0f) {

				// �e�̈ړ�
				bulletCenterPosition[i].x += -cosf(bulletDirection[i]) * bulletSpeed;
				bulletCenterPosition[i].y += -sinf(bulletDirection[i]) * bulletSpeed;

				// �e�̐������Ԃ��}�C�i�X
				bulletAliveTime[i] -= 1.0f / 60.0f;
			}
			else {
				// ���ł��鎞�_���[�W���O��
				bulletDamage[i] = 0.0f;
				isShot[i] = false;
			}
		}

		/// �I�u�W�F�N�g�֌W�̍X�V����

		// �I�u�W�F�N�g��������
		if (canGeneratedBlock == true) {

			// �����Ԋu��0�ɂȂ�Ɛ���
			if (generatedBlockInterval < 0) {
				if (generatedBlockValue > 0) {
					float blockSize = BaseMath::RandomF(20.0f, 60.0f, 0);

					Point spawnPoint = { BaseMath::RandomF(BaseConst::kMapChipSizeWidth + blockSize, BaseConst::kBossStageSizeWidth * BaseConst::kMapChipSizeWidth - blockSize, 1),
						(float)BaseConst::kBossStageSizeHeight * BaseConst::kMapChipSizeHeight - BaseConst::kMapChipSizeHeight - blockSize };

					// �͈͓��������ꍇ�͍Ē��I
					while (spawnPoint.x + blockSize >= centerPosition.x - textureSize.x / 2.0f && spawnPoint.x - blockSize <= centerPosition.x + textureSize.x / 2.0f)
					{
						spawnPoint = { BaseMath::RandomF(BaseConst::kMapChipSizeWidth + blockSize, BaseConst::kBossStageSizeWidth * BaseConst::kMapChipSizeWidth - blockSize, 1),
						(float)BaseConst::kBossStageSizeHeight * BaseConst::kMapChipSizeHeight - BaseConst::kMapChipSizeHeight - blockSize };
					}
					// �����_���Ȉʒu�ɁA�����_���ȑ傫���̃u���b�N�𐶐�
					objectManager->MakeNewObjectBlock(spawnPoint, { blockSize, blockSize });
					generatedBlockValue--;
				}
				else {
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
			PlayDeadAnim(2.5f, 3.0f, 5.0f, 0.45f, 2.0f, wireManager);
		}

	}
	else if (inDead == false) {
		// �J�n�A�j���[�V�����Đ�
		PlayStartAnim(2.5f, 5.0f, 0.25f, 2.5f, 1.0f);

		if (isPlayingStartAnim == true && PublicFlag::kisStaging == false) {
			// ���o�I��
			PublicFlag::kisStaging = false;
			isPlayingStartAnim = false;

			// ������
			offset = 0;
			shakeVariation = { 0.0f, 0.0f };
			isBattleStart = true;
			LongPressFrame = 0.0f;
			t = 0.0f;
			actionWayPoint = WAYPOINT0;
		}
	}
}

// �`�揈��
void Boss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };
	Point coreViewPosition = { coreCenterPosition.x + coreShakeVariation.x, coreCenterPosition.y + coreShakeVariation.y };

	if (inDead == false) {
		// �{�X����摜 ���݂͉��e�N�X�`��
		BaseDraw::DesignationDrawQuad(
			Boss::GetWeaponPosition(viewPosition),
			weaponSize,
			BaseTexture::kDebugTexture,
			weaponTextureSize,
			degree,
			0xFFFFFFFF
		);

		for (int i = 0; i < kmaxBullet; i++) {
			if (isShot[i] == true) {
				// �e�摜 ���݂͉��e�N�X�`��
				BaseDraw::DesignationDrawQuad(
					bulletCenterPosition[i],
					bulletSize,
					BaseTexture::kDebugTexture,
					bulletTextureSize,
					0.0f,
					0x000000FF
				);
			}
		}

		// �{�X�̃R�A
		BaseDraw::DesignationDrawQuad(
			coreViewPosition,
			coreSize,
			BaseTexture::kBossCore,
			coreTextureSize,
			coreDegree,
			coreColor
		);

		// �{�X�����t�b�N�摜
		BaseDraw::DesignationDrawQuad(
			Boss::GetLHookPosition(viewPosition),
			hookSize,
			BaseTexture::kBossLHook,
			hookTextureSize,
			degree,
			color
		);

		// �{�X�E���t�b�N�摜
		BaseDraw::DesignationDrawQuad(
			Boss::GetRHookPosition(viewPosition),
			hookSize,
			BaseTexture::kBossRHook,
			hookTextureSize,
			degree,
			color
		);

		// �{�X�����摜
		BaseDraw::DrawQuad(
			Boss::GetLCoverPosition(viewPosition),
			BaseTexture::kBossLCover,
			textureSize,
			1.0f,
			degree,
			color
		);

		// �{�X�E���摜
		BaseDraw::DrawQuad(
			Boss::GetRCoverPosition(viewPosition),
			BaseTexture::kBossRCover,
			textureSize,
			1.0f,
			degree,
			color
		);
	}

	if (isBattleStart == true) {
		// �{�XHP�Q�[�W�i���j
		Novice::DrawBox(450, 100, 0 + 100 * HP, 30, 0.0f, 0xdc143cFF, kFillModeSolid);
	}

}

// �{�X���̂̓����蔻���Ԃ��֐�
// �Ԃ�l�F�������Ă��� ... true �������Ă��Ȃ� ... false
// �����F
// hitPosition ... �����������W
// �����Ŏw�肵��Point���{�X�̊O�k�ɖ������Ă��邩�ǂ�����Ԃ��֐�
bool Boss::GetBossCollision(Point hitPosition) {
	
	// ���������߂�
	float x = centerPosition.x - hitPosition.x;
	float y = centerPosition.y - hitPosition.y;
	float d = sqrt(pow(x, 2) + pow(y, 2));

	// �{�X���J���Ă��鎞�͓�����Ȃ�
	if (offset > 0) {
		return false;
	}
	else {
		// �~�ɖ��������ꍇtrue��Ԃ�
		if (d <= textureSize.y / 2) {
			return true;
		}
		else {
			return false;
		}
	}
}

// �{�X���摜�̑��΍��W�����߂�
Point Boss::GetLCoverPosition(Point centerPosition) { 
	// ��]���S����̍��كx�N�g���쐬
	Point p = { -textureSize.x / 2 - offset, 0 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}
// �{�X�E�摜�̑��΍��W�����߂�
Point Boss::GetRCoverPosition(Point centerPosition) { 
	// ��]���S����̍��كx�N�g���쐬
	Point p = { textureSize.x / 2 + offset, 0 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// �{�X���摜�̓����蔻������߂�
Point Boss::GetLCoverCollision(Point centerPosition) {
	// ��]���S����̍��كx�N�g���쐬
	Point p = { -textureSize.x / 2 - offset, 0 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}
// �{�X�E�摜�̓����蔻������߂�
Point Boss::GetRCoverCollision(Point centerPosition) {
	// ��]���S����̍��كx�N�g���쐬
	Point p = { textureSize.x / 2 + offset, 0 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// ����摜�̑��΍��W�����߂�
Point Boss::GetWeaponPosition(Point centerPosition) {
	// ��]���S����̍��كx�N�g���쐬
	Point p = { 0, weaponSize.y / 2 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// ���˒n�_�̑��΍��W�����߂�
Point Boss::GetShotPosition(Point centerPosition) {
	// ��]���S����̍��كx�N�g���쐬
	Point p = { 0, weaponSize.y };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// �����t�b�N�̑��΍��W�����߂�
Point Boss::GetLHookPosition(Point centerPosition) {
	// ��]���S����̍��كx�N�g���쐬
	Point p = { -textureSize.x - offset , 0 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// �E���t�b�N�̑��΍��W�����߂�
Point Boss::GetRHookPosition(Point centerPosition) {
	// ��]���S����̍��كx�N�g���쐬
	Point p = { textureSize.x + offset , 0 };
	// �x�N�g���v�Z
	p = BaseMath::TurnPoint(p, degree);
	// �v�Z�����l��Ԃ�
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// �f�o�b�O�p�֐�
void Boss::Debug() {

	Novice::ScreenPrintf(0, 0, "DebugMode :: ON");
	Novice::ScreenPrintf(0, 20, "ActionSwitching :: 1 ~ 6");
	Novice::ScreenPrintf(0, 40, "1:NONE  2:SPIN  3:RUSH  4:SLASH  5:SHOT  6:FALL");
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
			attackPattern = SHOT;
		}
		else if (BaseInput::GetKeyboardState(DIK_6, Trigger)) {
			attackPattern = FALL;
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

	// �{�X���X�^��������
	if (BaseInput::GetKeyboardState(DIK_9, Trigger)) {
		actionWayPoint = WAYPOINT0;
		canTakeDamage = true;
	}

	if (BaseInput::GetKeyboardState(DIK_UP, Trigger)) {
		actionWayPoint = WAYPOINT0;
		isPlayingDeadAnim = true;
	}

	// �{�X�����E�ɊJ������
	if (BaseInput::GetKeyboardState(DIK_I, Press))
		offset += 1.0f;

	else if (BaseInput::GetKeyboardState(DIK_K, Press))
		offset -= 1.0f;

	// �I�t�Z�b�g���w��̒l�ȉ��ɂȂ��0�ɂ���
	if (offset < 0) {
		offset = 0;
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
	else if(BaseInput::GetKeyboardState(DIK_P, Press)) {
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
void Boss::Shake(int shakeStrength) {
	shakeVariation.x = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
	shakeVariation.y = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
}

// �V�F�C�N�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// �{�X���V�F�C�N������֐�
void Boss::CoreShake(int shakeStrength) {
	coreShakeVariation.x = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
	coreShakeVariation.y = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
}

// �V�F�C�N�C�[�Y�A�E�g�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// shakeTime ... �V�F�C�N���鎞��
// �{�X���V�F�C�N�̋������������キ���Ȃ��瓮�����֐�
void Boss::ShakeEaseOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// �V�F�C�N�C�[�Y�A�E�g�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// shakeTime ... �V�F�C�N���鎞��
// �{�X���V�F�C�N�̋������������キ���Ȃ��瓮�����֐�
void Boss::CoreShakeEaseOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	coreShakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	coreShakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// �V�F�C�N�C�[�Y�C���A�E�g�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// shakeStrength ... �V�F�C�N����ۂ̋���
// shakeTime ... �V�F�C�N���鎞��
// �{�X�̃V�F�C�N�̋������������キ���Ȃ��瓮�����֐�
void Boss::ShakeEaseInOut(int shakeStrength, float shakeTime) {
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
void Boss::vibration(int shakeStrength, float vibTime, float vibRate, int vibValue) {

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
/// �퓬�J�n���̃A�j���[�V�������Đ�����֐�
/// </summary>
/// <param name="cameraMoveTime">�U�����鎞��</param>
/// <param name="vibTime">�U�����鎞��</param>
/// <param name="closeTime1">�{�X���r���܂ŕ���̂ɂ����鎞��</param>
/// <param name="roarTime">���K���鎞��</param>
/// <param name="closeTime2">�{�X�����S�ɕ��鎞��</param>
void Boss::PlayStartAnim(float cameraMoveTime, float vibTime, float closeTime1, float roarTime, float closeTime2) {
	switch (actionWayPoint)
	{
		// ������
	case Boss::WAYPOINT0:

		// ���o���̏�Ԃ�
		PublicFlag::kisStaging = true;
		isPlayingStartAnim = true;

		// �X�N���[�����W�L�^
		prevScreenPosition = BaseDraw::GetScreenPosition();
		nextScreenPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2) - (float)(BaseConst::kWindowWidth / 2),
			(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) + (float)(BaseConst::kWindowHeight / 2) };

		// �I�t�Z�b�g��������
		offset = 100;

		// t������
		t = 0.0f;
		// ���̒i�K��
		actionWayPoint++;

		break;
		// �U������
	case Boss::WAYPOINT1:
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

			// �I�t�Z�b�g�̊J�n�l�ƏI�[�l�����Z�b�g
			prevOffset = offset;
			nextOffset = 110;

			// ������
			t = 0.0f;
			actionWayPoint++;
		}

		break;
		// �r���܂ŕ���
	case Boss::WAYPOINT2:
		if (t <= vibTime) {

			// ����I�ɐU��������
			vibration(t * 2, vibTime, vibTime, 3);

			// �I�t�Z�b�g�����������傫������
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, vibTime);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// �I�t�Z�b�g�̊J�n�l�ƏI�[�l�����Z�b�g
			prevOffset = offset;
			nextOffset = 20;

			// ������
			t = 0.0f;
			actionWayPoint++;
		}
		break;

		// ���K (�U��)
	case Boss::WAYPOINT3:
		if (t <= closeTime1) {

			// ����Ƃ��ɐU��������
			ShakeEaseOut(40, closeTime1);

			// �I�t�Z�b�g���k�߂�
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, closeTime1);

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {
			// ������
			t = 0.0f;
			actionWayPoint++;
		}
		
		break;
		// ���S�ɕ���
	case Boss::WAYPOINT4:
		if (t <= roarTime) {

			if (t > 1.0f) {
				Shake(25);
			}

			// t�����Z����
			t += 1.0f / 60.0f;
		}
		else {

			// �I�t�Z�b�g�̊J�n�l�ƏI�[�l�����Z�b�g
			prevOffset = offset;
			nextOffset = 0;

			// ������
			t = 0.0f;
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT5:
		if (t <= closeTime2) {

			// �I�t�Z�b�g���k�߂�
			offset = BaseDraw::Ease_InOut(t, prevOffset, -prevOffset, closeTime2);

			// �X�N���[���𓮂���
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, nextScreenPosition.x, prevScreenPosition.x - nextScreenPosition.x, closeTime2);
			screenPosition.y = BaseDraw::Ease_Out(t, nextScreenPosition.y, prevScreenPosition.y - nextScreenPosition.y, closeTime2);

			BaseDraw::SetScreenPosition(screenPosition);

			// ���S���W�ɖ߂�
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, closeTime2);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, closeTime2);
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
	case Boss::WAYPOINT6:
		break;
	default:
		break;
	}
}

/// <summary>
/// ���S���̃A�j���[�V�������Đ�����֐�
/// </summary>
/// <param name="cameraMoveTime">�J�����ƃ{�X�𒆐S�Ɏ����Ă�������</param>
/// <param name="separationTime">�j�Ɗk����������̂ɂ����鎞��</param>
/// <param name="vibTime">�U�����Ȃ���k�ގ���</param>
/// <param name="explosiveTime">�T�C�Y��傫�����Ĕ�������</param>
/// <param name="cameraBackTime">�J���������̈ʒu�ɋA��܂ł̎���</param>
void Boss::PlayDeadAnim(float cameraMoveTime, float separationTime, float vibTime, float explosiveTime, float cameraBackTime, WireManager* wireManager){
	switch (actionWayPoint)
	{
		// ������
	case Boss::WAYPOINT0:

		// ���o���̏�Ԃ�
		PublicFlag::kisStaging = true;
		isPlayingDeadAnim = true;

		wireManager->Initialize();

		// �X�N���[�����W�L�^
		prevScreenPosition = BaseDraw::GetScreenPosition();
		nextScreenPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2) - (float)(BaseConst::kWindowWidth / 2),
			(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) + (float)(BaseConst::kWindowHeight / 2) - 250.0f };

		// ���S���W�擾
		prevCenterPosition = centerPosition;
		nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) - 250.0f };

		prevOffset = offset;
		nextOffset = 175;

		// �p�x�擾
		prevDegree = degree;

		// ������
		t = 0.0f;
		actionWayPoint++;

		break;
		// �J�����ƃ{�X�𒆐S�Ɏ����Ă���
	case Boss::WAYPOINT1:
		if (t <= cameraMoveTime) {

			// �X�N���[���𓮂���
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_InOut(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, cameraMoveTime);
			screenPosition.y = BaseDraw::Ease_InOut(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, cameraMoveTime);

			Shake(15);

			BaseDraw::SetScreenPosition(screenPosition);

			// ��ʒ����֖߂�
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, cameraMoveTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, cameraMoveTime);

			// �p�x��0��
			degree = BaseDraw::Ease_Out(t, prevDegree, -prevDegree, cameraMoveTime);

			// �I�t�Z�b�g�J��
			offset = BaseDraw::Ease_Out(t, prevOffset, nextOffset - prevOffset, cameraMoveTime);

			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, cameraMoveTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, cameraMoveTime);

			// t�������Âv���X����
			t += 1.0f / 60.0f;
		}
		else {

			// �X�N���[�����W�L�^
			prevScreenPosition = BaseDraw::GetScreenPosition();
			nextScreenPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2) - (float)(BaseConst::kWindowWidth / 2),
				(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) + (float)(BaseConst::kWindowHeight / 2) };

			// �R�A�ƃ{�X�𕪗�������
			coreSeparated = true;

			// �R�A�̍��W��ݒ�
			prevCoreCenterPosition = coreCenterPosition;
			nextCoreCenterPosition = { coreCenterPosition.x, (float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };

			// �F���擾
			color = 0x333333FF;
			prevColor = color;
			nextColor = 0x33333300;

			// ���S���W�擾
			prevCenterPosition = centerPosition;
			nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) - 1000.0f };

			// �I�t�Z�b�g��ݒ�
			prevOffset = offset;
			nextOffset = 250;

			// �p�x��ݒ�
			prevDegree = degree;
			nextDegree = 190;

			// ���̍s����
			t = 0.0f;
			actionWayPoint++;

		}
		break;
		// �j�Ɗk����������
	case Boss::WAYPOINT2:
		if (t <= separationTime) {

			// �X�N���[���𓮂���
			Point screenPosition;

			// �J�����ړ�
			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, separationTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, separationTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// �U��
			ShakeEaseOut(20, separationTime);
			CoreShakeEaseOut(20, separationTime);

			// ��ʒ����֖߂�
			coreCenterPosition.x = BaseDraw::Ease_InOut(t, prevCoreCenterPosition.x, nextCoreCenterPosition.x - prevCoreCenterPosition.x, separationTime);
			coreCenterPosition.y = BaseDraw::Ease_InOut(t, prevCoreCenterPosition.y, nextCoreCenterPosition.y - prevCoreCenterPosition.y, separationTime);

			color = ColorEasing(t, prevColor, nextColor, separationTime);

			// ��ʒ����֖߂�
			centerPosition.x = BaseDraw::Ease_In(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, separationTime);
			centerPosition.y = BaseDraw::Ease_In(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, separationTime);

			// �p�x��0��
			degree = BaseDraw::Ease_In(t, prevDegree, nextDegree - prevDegree, separationTime);

			// �I�t�Z�b�g�J��
			offset = BaseDraw::Ease_In(t, prevOffset, nextOffset - prevOffset, separationTime);

			// t�������Âv���X����
			t += 1.0f / 60.0f;
		}
		else {

			// �R�A�̃T�C�Y��ݒ�
			prevCoreSize = coreSize;
			nextCoreSize = { 64, 64 };

			// ���̍s����
			t = 0.0f;
			actionWayPoint++;

		}

		break;
		// �U�����Ȃ���k��
	case Boss::WAYPOINT3:
		if (t <= vibTime) {

			CoreShake(15);

			coreSize.x = BaseDraw::Ease_InOut(t, prevCoreSize.x, nextCoreSize.x - prevCoreSize.x, vibTime);
			coreSize.y = BaseDraw::Ease_InOut(t, prevCoreSize.y, nextCoreSize.y - prevCoreSize.y, vibTime);

			// t�������Âv���X����
			t += 1.0f / 60.0f;
		}
		else {

			prevCoreSize = coreSize;
			nextCoreSize = { 512, 512 };

			prevColor = coreColor;
			nextColor = 0xFFFFFF00;

			// ���̍s����
			t = 0.0f;
			actionWayPoint++;

		}

		break;
		// �T�C�Y��傫�����Ĕ���
	case Boss::WAYPOINT4:
		if (t <= explosiveTime) {

			CoreShake(20);

			coreSize.x = BaseDraw::Ease_InOut(t, prevCoreSize.x, nextCoreSize.x - prevCoreSize.x, explosiveTime);
			coreSize.y = BaseDraw::Ease_InOut(t, prevCoreSize.y, nextCoreSize.y - prevCoreSize.y, explosiveTime);

			coreColor = ColorEasing(t - explosiveTime / 2, prevColor, nextColor, explosiveTime - explosiveTime / 2);

			// t�������Âv���X����
			t += 1.0f / 60.0f;
		}
		else {

			// ���̍s����
			t = 0.0f;
			actionWayPoint++;

		}
		break;
		// �J���������̈ʒu�ɖ߂�
	case Boss::WAYPOINT5:
		if (t <= cameraBackTime) {
			// t�������Âv���X����
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
	case Boss::WAYPOINT6:

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
void Boss::None(float waitFrame) {
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
void Boss::Approach(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case Boss::WAYPOINT0:
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
	case Boss::WAYPOINT1:
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
void Boss::Separation(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case Boss::WAYPOINT0:
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
	case Boss::WAYPOINT1:

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
void  Boss::Rotate(float endDegree, float RotateTime, float afterWaitTime, WireManager* wireManager) {

	static int startDegree;
	// ����������
	if (init == false) {
		startDegree = degree;
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
void Boss::Rush(Point playerPosition, float readyTime, float chargeTime, float rushTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {

	switch (actionWayPoint)
	{
		// ������
	case Boss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;

		// t������
		t = 0.0f;

		// ���̒i�K��
		actionWayPoint++;
		break;
		// ���O����(�k����)
	case Boss::WAYPOINT1:
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
	case Boss::WAYPOINT2:
		
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
	case Boss::WAYPOINT3:
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
	case Boss::WAYPOINT4:
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
	case Boss::WAYPOINT5:
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
void Boss::Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	// ������
	case Boss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;

		// �{�X���ǂꂾ���J���������߂�
		prevOffset = offset;
		nextOffset = 20;

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
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// �w�肳�ꂽ�b���U������
			ShakeEaseOut(60, readyTime);

			// �{�X�������ÂJ��
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, readyTime);

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
	case Boss::WAYPOINT2:
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
			actionBranch = BaseMath::Random(0, 2);
			switch (actionBranch)
			{
				// �E��]
			case Boss::Pattern1:
				// �������ɓ�����
				nextDegree = prevDegree - 30;
				break;
				// ����]
			case Boss::Pattern2:
				// �E�����ɓ�����
				nextDegree = prevDegree + 30;
				break;
				// ��]�؂�
			case Boss::Pattern3:
				nextDegree = prevDegree;
				break;
			default:
				break;
			}

			// ���̒i�K
			actionWayPoint++;
		}

		break;
		// �a������
	case Boss::WAYPOINT3:
		if (t <= preparationTime) {
			//�{�X����]������
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);

			// ����F��]�a��̏ꍇ�͐U��������
			if (actionBranch == Pattern3)
				ShakeEaseInOut(30, preparationTime);

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
			Novice::PlayAudio(BaseAudio::kBossRush, 0, 0.4f);

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
			case Boss::Pattern1:
				nextDegree = prevDegree + 360;
				break;
				// ����]
			case Boss::Pattern2:
				nextDegree = prevDegree - 360;
				break;
				// ��]�؂�
			case Boss::Pattern3:
				nextDegree = prevDegree + 720;
				break;
			default:
				break;
			}

			// ����
			actionWayPoint++;
		}
		break;
		// �a��
	case Boss::WAYPOINT4:
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
			if (actionBranch == 2) {
				t += 0.75f / 60.0f;
			}
			else {
				t += 1.0f / 60.0f;
			}
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
	case Boss::WAYPOINT5:
		if (t <= backTime) {
			// �ʒu��p�x�A����̃T�C�Y�����ɖ߂�
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			degree = BaseDraw::Ease_InOut(t, nextDegree, -nextDegree, backTime);
			weaponSize.y = BaseDraw::Ease_InOut(t, nextWeaponSize.y, -nextWeaponSize.y, backTime);
			offset = BaseDraw::Ease_InOut(t, nextOffset, -nextOffset, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			// �{�X���W���������i�ꉞ�j
			centerPosition = prevCenterPosition;

			// �_���[�W��^�����Ȃ��悤��
			bladeDamage = 0.0f;

			// �I�t�Z�b�g������
			offset = 0;

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

// �ˌ��֐�
// �Ԃ�l�F�Ȃ�
// �����F
// playerPosition ... �v���C���[�̍��W
// readyTime ... �{�X���J���܂łɂ�����b��
// deployTime ... �e�̓W�J�ɂ�����b��
// preparationTime�@... �U���܂ł̑ҋ@����
// shotTime ... �ˌ��b��
// backTime ... �߂鎞�ɂ�����b��
// afterWaitTime ... �s����ɔ�������ҋ@����
// fireRate ... ���b�����Ɏˌ����邩
// damage ... �s���ɂ���Ĕ�������_���[�W
// �{�X���ˌ����s���֐�
void Boss::Shot(Point playerPosition, float readyTime, float deployTime, float preparationTime, float shotTime, float backTime, float afterWaitTime, float fireRate, float damage, WireManager* wireManager) {

	// �{�X���v���C���[�ɒǏ]���ĉ�]���鎞�ɗp����J�E���g�ϐ�
	static int count;

	// �{�X�̔��˃��[�g���Ǘ�����ϐ�
	static float fireRateCount;

	switch (actionWayPoint)
	{
		// ������
	case Boss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;
		nextCenterPosition = centerPosition;

		// �{�X���ǂꂾ���J���������߂�
		prevOffset = offset;
		nextOffset = 20;

		// ������ǂꂾ���傫�����邩�����߂�
		weaponSize = { 40, 0 };
		prevWeaponSize = weaponSize;
		nextWeaponSize = { weaponSize.x, 250.0f };

		// t������
		t = 0.0f;

		// �J�E���^�[�n������
		count = 0;
		fireRateCount = 0;

		// ���ʉ��Đ�
		Novice::PlayAudio(BaseAudio::kBossOpen, 0, 0.35f);

		//���̒i�K��
		actionWayPoint++;
		break;
		// ���O����(�k���ă{�X���J��)
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// �w�肳�ꂽ�b���U������
			ShakeEaseOut(60, readyTime);

			// �{�X�������ÂJ��
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, readyTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			// t�����Z�b�g
			t = 0.0f;

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossPickGun, 0, 0.45f);

			//����
			actionWayPoint++;
		}
		break;
		// �e�W�J
	case Boss::WAYPOINT2:
		if (t <= deployTime) {

			// �e���L�т�
			weaponSize.y = BaseDraw::Ease_InOut(t, prevWeaponSize.y, nextWeaponSize.y - prevWeaponSize.y, deployTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// t��������
			t = 0.0f;

			// �����p�x��ݒ�
			prevDegree = degree;

			//���̍s���������_���ɐݒ肵�ĕ���
			actionBranch = BaseMath::Random(0, 2);
			switch (actionBranch)
			{
				// �E��]
			case Boss::Pattern1:
				// �������ɓ�����
				nextDegree = prevDegree - 30;
				break;
				// ����]
			case Boss::Pattern2:
				// �E�����ɓ�����
				nextDegree = prevDegree + 30;
				break;
				// �Ǐ]�ˌ�
			case Boss::Pattern3:
				break;
			default:
				break;
			}

			// ���̒i�K
			actionWayPoint++;
		}

		break;
		// �ˌ�����
	case Boss::WAYPOINT3:
		if (t <= preparationTime) {

			if (actionBranch == Pattern3) {

				// �v���C���[���W�擾
				prePlayerPosition = playerPosition;

				// �v���C���[��������������߂�
				playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

				// �v���C���[�̂���p�x���擾
				nextDegree = BaseMath::RadiantoDegree(playerDirection) - 90;

				float absDegree = nextDegree - degree;

				degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);
			}
			else {
				// �{�X����]������
				degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);
			}

			// ����F��]�a��̏ꍇ�͐U��������
			if (actionBranch == Pattern3)
				ShakeEaseInOut(30, preparationTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			// t��������
			t = 0.0f;

			// �����p�x��ݒ�
			prevDegree = degree;

			// �s������Ɋ�Â��ĉ�]�p�̐ݒ�
			switch (actionBranch)
			{
				// �E��]
			case Boss::Pattern1:
				nextDegree = prevDegree + 720;
				break;
				// ����]
			case Boss::Pattern2:
				nextDegree = prevDegree - 720;
				break;
				// �Ǐ]�ˌ�
			case Boss::Pattern3:
				
				break;
			default:
				break;
			}

			// �v���C���[���W�擾
			prePlayerPosition = playerPosition;

			// �v���C���[��������������߂�
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// ����
			actionWayPoint++;
		}
		break;
		// �ˌ�
	case Boss::WAYPOINT4:
		if (t <= shotTime) {

			if (actionBranch == Pattern3) {

				// �v���C���[���W�擾
				prePlayerPosition = playerPosition;

				// �v���C���[��������������߂�
				playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

				// �����p�x��ݒ�
				/*prevDegree = degree;*/

				// �v���C���[�̂���p�x���擾
				nextDegree = BaseMath::RadiantoDegree(playerDirection) - 90;

				float absDegree = nextDegree - degree;

				if (count == 0) {
					// �{�X����]������
					if (absDegree < 0) {
						degree -= 1;
					}
					else if (absDegree > 0) {
						degree += 1;
					}
					count = 0;
				}
				else {
					count++;
				}
			}
			else {
				// �{�X����]������
				degree = BaseDraw::Linear(t, prevDegree, nextDegree - prevDegree, shotTime);
			}

			// �ˌ����ɐU��������
			Shake(10);

			if (fireRateCount <= fireRate) {
				fireRateCount += 1.0 / 60.0f;
			}
			else {
				for (int i = 0; i < kmaxBullet; i++) {
					if (isShot[i] == false) {

						Novice::PlayAudio(BaseAudio::kBossShot, 0, 0.55f);

						// �_���[�W������l��
						bulletDamage[i] = damage;

						// ���W�𔭎˒n�_�܂ňڂ�
						bulletCenterPosition[i] = shotPoint;
						// �e�̔��ˌ�����ύX����
						bulletDirection[i] = BaseMath::DegreetoRadian(degree - 90);

						// �e�̐������Ԃ����߂�
						bulletAliveTime[i] = 5.0f;

						// �e�𔭎˂�����Ԃɂ���
						isShot[i] = true;

						// �J�E���^�[������
						fireRateCount = 0.0f;
						// �����𔲂���
						break;
					}
				}
			}

			// t���v���X����
			t += 1.0f / 60.0f;

		}
		else {

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossClose, 0, 0.35f);

			// ���݂̍��W���L�^����
			nextCenterPosition = centerPosition;

			// ���݂̊p�x�����߂�
			nextDegree = degree;

			// t��������
			t = 0.0f;
			// ����
			actionWayPoint++;
		}
		break;
		// ���̏ꏊ�ɖ߂�
	case Boss::WAYPOINT5:
		if (t <= backTime) {
			// �ʒu��p�x�A����̃T�C�Y�����ɖ߂�
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);
			degree = BaseDraw::Ease_InOut(t, nextDegree, -nextDegree, backTime);
			weaponSize.y = BaseDraw::Ease_InOut(t, nextWeaponSize.y, -nextWeaponSize.y, backTime);
			offset = BaseDraw::Ease_InOut(t, nextOffset, -nextOffset, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			// �{�X���W���������i�ꉞ�j
			centerPosition = prevCenterPosition;

			// �I�t�Z�b�g������
			offset = 0;

			// �p�x������
			degree = 0;
			prevDegree = 0;
			nextDegree = 0;

			// t������
			t = 0.0f;

			// �s���I��
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = SHOT;
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
void Boss::Fall(float readyTime, float deployTime, float rushTime, float standByTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// ������
	case Boss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;
		nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };

		// t������
		t = 0.0f;

		//���̒i�K��
		actionWayPoint++;
		break;
		// �{�X�𒆐S���W�ɖ߂�
	case Boss::WAYPOINT1:
		if (t <= readyTime) {

			// ��ʒ����֖߂�
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, readyTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, readyTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {
			// t�����Z�b�g
			t = 0.0f;

			// ���W�ݒ�
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, centerPosition.y - 200 };

			//����
			actionWayPoint++;
		}
		break;
		// ����
	case Boss::WAYPOINT2:
		if (t <= deployTime) {

			// �኱���ɉ�����
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, deployTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, deployTime);

			ShakeEaseOut(50, deployTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// t��������
			t = 0.0f;

			// ���W�ݒ�
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, ((float)BaseConst::kBossStageSizeHeight * (float)BaseConst::kMapChipSizeHeight - (float)BaseConst::kMapChipSizeHeight) - (textureSize.y / 2) };

			// ���̒i�K
			actionWayPoint++;
		}

		break;
		// �V��ɓːi
	case Boss::WAYPOINT3:
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

			canGeneratedBlock = true;
			generatedBlockValue = BaseMath::Random(3, 5);

			// ����
			actionWayPoint++;
		}
		break;
		// �ҋ@
	case Boss::WAYPOINT4:
		if (t <= standByTime) {

			// ���ˎ��V�F�C�N
			ShakeEaseOut(50, standByTime);

			// t���v���X����
			t += 1.0f / 60.0f;

		}
		else {

			// ���݂̍��W���L�^����
			prevCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };
			nextCenterPosition = centerPosition;

			// t��������
			t = 0.0f;
			// ����
			actionWayPoint++;
		}
		break;
		// ���̏ꏊ�ɖ߂�
	case Boss::WAYPOINT5:
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

			// �I�t�Z�b�g������
			offset = 0;

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
void Boss::Stun(float readyTime, float deployTime, float stanTime, float backTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case Boss::WAYPOINT0:

		// �O�̂��߈�x������
		// ���W�擾
		prevCenterPosition = {0.0f, 0.0f};
		nextCenterPosition = { 0.0f, 0.0f };

		// �p�x�擾
		prevDegree = 0;
		nextDegree = 0;

		prevOffset = 0;
		nextOffset = 0;

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

		prevOffset = offset;
		nextOffset = 0;

		// ���̍s����
		actionWayPoint++;
		break;
		// 
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// ���W�֘A���C�[�W���O
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, readyTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, readyTime);

			// �p�x�֘A���C�[�W���O
			degree = BaseDraw::Ease_Out(t, prevDegree, nextDegree - prevDegree, readyTime);

			// �I�t�Z�b�g��0��
			offset = BaseDraw::Ease_InOut(t, prevOffset, -prevOffset, readyTime);

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
	case Boss::WAYPOINT2:
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
	case Boss::WAYPOINT3:
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
	case Boss::WAYPOINT4:
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
	case Boss::WAYPOINT5:
		break;
	default:
		break;
	}
}

/******** �_���[�W **********/
// �_���[�W�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// readyTime ... �X�^�����n�߃��[�V�����b��
// deployTime ... �X�^�����n�߃��[�V�����b��
// openTime ... �J���܂łɂ����鎞��
// stanTime�@... �X�^���b��
// backTime ... �߂鎞�ɂ�����b��
// closeTime ... ����܂łɂ����鎞��
// �{�X�ɑ΂��ă_���[�W���^�������Ԃɂ���֐�
void Boss::MakeDamagePossible(float readyTime, float deployTime, float openTime, float stanTime, float backTime, float closeTime, WireManager* wireManager, ObjectManager* objectManager) {

	switch (actionWayPoint)
	{
	case Boss::WAYPOINT0:

		// �O�̂��߈�x������
		// ���W�擾
		prevCenterPosition = { 0.0f, 0.0f };
		nextCenterPosition = { 0.0f, 0.0f };

		// �p�x�擾
		prevDegree = 0;
		nextDegree = 0;

		prevOffset = 0;
		nextOffset = 0;

		t = 0.0f;
		endAction = true;
		inAction = false;
		inStun = false;

		// ����T�C�Y������
		weaponSize = { 0.0f, 0.0f };

		// ���W�擾
		prevCenterPosition = centerPosition;
		nextCenterPosition = centerPosition;

		prevOffset = offset;
		nextOffset = 5;

		// ���̍s����
		actionWayPoint++;
		break;
		// 
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// �I�t�Z�b�g��0��
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, readyTime);

			ShakeEaseOut(30, readyTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			if (Novice::IsPlayingAudio(PullVoiceHundle) == 0 || PullVoiceHundle == -1) {
				// ���ʉ��Đ�
				PullVoiceHundle = Novice::PlayAudio(PullSoundHundle, true, 0.5f);
			}

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT2:
		if (t <= deployTime) {
			// ���W�֘A���C�[�W���O
			Shake(10);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			Novice::StopAudio(PullVoiceHundle);

			prevOffset = offset;
			nextOffset = 175;

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossHardOpen, false, 0.5f);

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT3:
		if (t <= openTime) {

			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, openTime);

			ShakeEaseInOut(20, openTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			canGeneratedBlock = true;
			generatedBlockValue = 5;

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT4:
		if (t <= stanTime) {

			vibration(15, stanTime, stanTime, 4);

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

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			vibInit = false;

			prevCenterPosition = centerPosition;
			nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };

			prevDegree = degree;

			if (degree < 0) {
				nextDegree = 360;
			}
			else {
				nextDegree = -360;
			}

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossReboot, false, 0.5f);

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT5:
		if (t <= backTime) {

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

			// ���W�֘A���C�[�W���O
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);

			if (t >= (backTime / 2)) {
				wireManager->Initialize();
			}

			// �p�x�֘A���C�[�W���O
			degree = BaseDraw::Ease_InOut(t, prevDegree, -prevDegree + nextDegree, backTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// ���ʉ��Đ�
			Novice::PlayAudio(BaseAudio::kBossOpen, false, 0.35f);

			prevOffset = offset;

			degree = 0;

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case WAYPOINT6:

		if (t <= closeTime) {

			offset = BaseDraw::Ease_InOut(t, prevOffset, -prevOffset, closeTime);
			ShakeEaseOut(30, closeTime);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			// t������������
			waitTime = 1.0f;
			t = 0.0f;
			// �s���I��
			canTakeDamage = false;
			pleaseWait = false;
			actionWayPoint = WAYPOINT0;
		}

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
void Boss::playTakeDamageAnim(float animTime, float shakeStrength) {
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