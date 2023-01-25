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

	this->degree = 0.0f;

	//�V�F�C�N���Ă��Ȃ���Ԃɖ߂�
	this->shakeVariation = { 0.0f, 0.0f };

	// �o�C�u���[�V����������
	vibInit = false;

	// �s���I����Ԃɂ���
	this->t = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->actionWayPoint = 0;

	// �j�̈ʒu��ݒ�
	this->coreCenterPosition = centerPosition;
	// �j�̉摜�T�C�Y��ݒ�
	this->kernelTextureSize = { 256.0f, 256.0f };

	// �j�̉摜�T�C�Y��ݒ�
	this->hookTextureSize = { 64.0f, 64.0f };

	// ����̃T�C�Y���w��i���e�N�X�`���̂��߁A����ς���j
	this->weaponSize = { 0.0f, 0.0f };
	this->weaponTextureSize = { 1.0f, 1.0f };

	for (int i = 0; i < kmaxWireHang; i++) {
		this->wireHangPosition[i] = { 0.0f, 0.0f };

		hook[i] = NULL;

	}

	this->prevAttackPattern[0] = NONE;
	this->prevAttackPattern[1] = NONE;
	this->attackPattern = NONE;

	pleaseWait = true;

	this->waitTime = 2.5f;

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
	}

	// �e�̃T�C�Y���w��
	this->bulletSize = { 20.0f, 20.0f };
	// �e�̉摜�T�C�Y���w��i���e�N�X�`���̂��߁A����ς���)
	this->bulletTextureSize = { 1.0f, 1.0f };

	// �e�̔��˃X�s�[�h���w��
	this->bulletSpeed = 10.0f;

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
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	// �{�X�̉摜�T�C�Y��ݒ�
	this->textureSize = { 225.0f, 450.0f };
	// �{�X�̃I�t�Z�b�g��������
	this->offset = 0.0f;

	this->degree = 0.0f;

	//�V�F�C�N���Ă��Ȃ���Ԃɖ߂�
	this->shakeVariation = { 0.0f, 0.0f };

	// �o�C�u���[�V����������
	vibInit = false;

	// �s���I����Ԃɂ���
	this->t = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->inStun = false;
	this->inDamage = false;
	this->actionWayPoint = 0;

	// �j�̈ʒu��ݒ�
	this->coreCenterPosition = centerPosition;
	// �j�̉摜�T�C�Y��ݒ�
	this->kernelTextureSize = { 256.0f, 256.0f };

	// �j�̉摜�T�C�Y��ݒ�
	this->hookTextureSize = { 64.0f, 64.0f };

	// ����̃T�C�Y���w��i���e�N�X�`���̂��߁A����ς���j
	this->weaponSize = { 0.0f, 0.0f };
	this->weaponTextureSize = { 1.0f, 1.0f };

	for (int i = 0; i < kmaxWireHang; i++) {
		this->wireHangPosition[i] = { 0.0f, 0.0f };
		hook[i] = objectManager->MakeNewObjectHook(wireHangPosition[i], hookTextureSize);
	}

	this->prevAttackPattern[0] = NONE;
	this->prevAttackPattern[1] = ROTATE;
	this->attackPattern = NONE;

	pleaseWait = true;

	this->waitTime = 1.0f;

	playerDistance = 0.0f;

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
	}

	// �e�̃T�C�Y���w��
	this->bulletSize = { 20.0f, 20.0f };
	// �e�̉摜�T�C�Y���w��i���e�N�X�`���̂��߁A����ς���)
	this->bulletTextureSize = { 1.0f, 1.0f };

	// �e�̔��˃X�s�[�h���w��
	this->bulletSpeed = 10.0f;

	/// �I�u�W�F�N�g�֘A
	// �I�u�W�F�N�g�𐶐����邩�ǂ���
	this->canGeneratedBlock = false;

	// �I�u�W�F�N�g������
	this->generatedBlockValue = 0;

	// �I�u�W�F�N�g�����Ԋu
	this->generatedBlockInterval = 0.0f;

}

// �X�V����
void Boss::Update(Point playerPosition, ObjectManager* objectManager, WireManager* wireManager) {
	/******** �f�o�b�N���� **********/
	// �f�o�b�O��Ԃ̐؂�ւ�
	if (BaseInput::GetKeyboardState(DIK_0, Trigger)) {
		if (inDebug == false)
			inDebug = true;

		else
			inDebug = false;
	}

	if (inDebug == false) {
		// �s���̕���
		if (endAction == true) {

			// �s���̊Ԋu�����
			if (pleaseWait == true) {
				attackPattern = NONE;
			}
			else {
				do{
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
	if (inAction == true && inStun == false && inDamage == false) {
		switch (attackPattern)
		{
		case Boss::NONE:
			None(waitTime);
			break;
		case Boss::ROTATE:
			Rotate(720, 2.0f, wireManager);
			break;
		case Boss::RUSH:
			Rush(playerPosition, 0.5f, 0.95f, 1.0f, wireManager);
			break;
		case Boss::SLASH:
			Slash(playerPosition, 0.35f, 0.2f, 1.0f, 0.75f, 1.0f, wireManager);
			break;
		case Boss::SHOT:
			Shot(playerPosition, 0.35f, 0.75f, 1.0f, 5.0f, 1.0f, 0.1f, wireManager);
			break;
		case Boss::FALL:
			Fall(0.35f, 1.0f, 0.15f, 0.75f, 1.0f, wireManager);
			break;
		case Boss::APPROACH:
			Approach(playerPosition, 1.0f, wireManager);
			break;
		case Boss::SEPARATION:
			Separation(playerPosition, 1.0f, wireManager);
			break;
		}
	}
	
	// �X�^������
	if (inStun == true && inDamage == false) {
		Stun(1.25f, 1.5f, 3.0f, 0.75f, wireManager);
	}

	// �_���[�W���󂯂����Ԃɂ��鏈��
	if (inDamage == true) {
		Damage(0.15f, 1.5f, 0.1f, 5.0f, 0.75f, 0.25f, wireManager);
	}
	else {
		if (hook[0]->GetisPulled() == true && hook[1]->GetisPulled() == true) {
			actionWayPoint = WAYPOINT0;
			inDamage = true;
		}
	}

	degree %= 360;

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

	// �t�b�N�̍��W���X�V��������
	wireHangPosition[0] = GetLHookPosition(viewPosition);
	wireHangPosition[1] = GetRHookPosition(viewPosition);

	// �t�b�N�̒��S���W���Z�b�g����
	hook[0]->SetCenterPosition(wireHangPosition[0]);
	hook[1]->SetCenterPosition(wireHangPosition[1]);

	// �f�o�b�O�֐��̎��s
	if (inDebug == true) {
		Debug();
	}

	// �j���������Ă��Ȃ���Ԃł͊j���{�X�ɒǏ]������
	if (coreSeparated == false) {
		coreCenterPosition = centerPosition;
		coreDegree = degree;
	}

	/// �e�֌W�̍X�V����

	// ���˒n�_�̍X�V
	shotPoint = GetShotPosition(centerPosition);

	// �e�����˂���Ă��鎞�̏���
	for (int i = 0; i < kmaxBullet; i++) {
		if (isShot[i] == true && bulletAliveTime[i] > 0.0f) {

			bulletCenterPosition[i].x += -cosf(bulletDirection[i]) * bulletSpeed;
			bulletCenterPosition[i].y += -sinf(bulletDirection[i]) * bulletSpeed;

			bulletAliveTime[i] -= 1.0f / 60.0f;
		}
		else {
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
				// �����_���Ȉʒu�ɁA�����_���ȑ傫���̃u���b�N�𐶐�
				objectManager->MakeNewObjectBlock({ BaseMath::RandomF(20.0f, 1900.0f, 1), (float)BaseConst::kWindowHeight }, { blockSize, blockSize });
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

}

// �`�揈��
void Boss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

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
				degree,
				0x000000FF
			);
		}
	}

	// �{�X�j�摜
	BaseDraw::DrawQuad(
		viewPosition,
		BaseTexture::kBossCore,
		kernelTextureSize,
		1.0f,
		coreDegree,
		0xFFFFFFFF
	);

	// �{�X�����t�b�N�摜
	BaseDraw::DrawQuad(
		Boss::GetLHookPosition(viewPosition),
		BaseTexture::kBossHook,
		hookTextureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	// �{�X�E���t�b�N�摜
	BaseDraw::DrawQuad(
		Boss::GetRHookPosition(viewPosition),
		BaseTexture::kBossHook,
		hookTextureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	// �{�X�����摜
	BaseDraw::DrawQuad(
		Boss::GetLCoverPosition(viewPosition),
		BaseTexture::kBossLCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	// �{�X�E���摜
	BaseDraw::DrawQuad(
		Boss::GetRCoverPosition(viewPosition),
		BaseTexture::kBossRCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	Novice::ScreenPrintf(0, 0, "attackPattern : %d", attackPattern);
	Novice::ScreenPrintf(0, 20, "prevAttackPattern[0] : %d", prevAttackPattern[0]);
	Novice::ScreenPrintf(0, 40, "prevAttackPattern[1] : %d", prevAttackPattern[1]);
	Novice::ScreenPrintf(0, 60, "attackBranch : %d", attackBranch);
	Novice::ScreenPrintf(0, 80, "inAction : %d", inAction);
	Novice::ScreenPrintf(0, 100, "endAction : %d", endAction);
	Novice::ScreenPrintf(0, 120, "endAction : %4.2f", t);


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

// �I���������֐�
// �Ԃ�l�F�Ȃ�
// �����F
// cenerPosition ... ���W�����������邩
// degree ... �p�x�����������邩
// offset ... �I�t�Z�b�g�����������邩
// t ... t�����������邩
// weapon ... ����֌W�̕ϐ������������邩
// ������True�ɂ������̂�������������֐�
void Boss::SelectionInitialize(bool initCenterPosition, bool initDegree, bool initOffset, bool initT, bool initWeapon) {
	if (initCenterPosition == true) {
		// �{�X�̈ʒu����ʒ����Ɏ����Ă���
		centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	}
	if (initDegree == true) {
		degree = 0;
	}
	if (initOffset == true) {
		offset = 0.0f;
	}
	if (initT == true) {
		t = 0.0f;
	}
	if (initWeapon == true) {
		weaponSize = { 0.0f };
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
		inDamage = true;
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
			Shake(shakeStrength);
			_vibTime -= 1.0f / 60.0f;
		}
		else {
			_vibTime = (vibTime / vibValue) / 2;
			_vibRate = (vibTime / vibValue) / 2;
			vibrating = false;
		}
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
// moveTIme ... ��]���鎞�ԁB����͕b��
// �v���C���[�Ɍ������Đڋ߂���֐�
void Boss::Approach(Point playerPosition, float moveTime, WireManager* wireManager) {
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
			waitTime = 0.1f;
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
// moveTIme ... ��]���鎞�ԁB����͕b��
// �v���C���[���班�������֐�
void Boss::Separation(Point playerPosition, float moveTime, WireManager* wireManager) {
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
			waitTime = 0.1f;
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
// �{�X����]������֐�
void Boss::Rotate(float endDegree, float RotateTime, WireManager* wireManager) {

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
			wireManager->Initialize();
		}

		t += 1.0f / 60.0f;
	}
	else {
		//t �����ȏ�ɂȂ�����s���I��
		prevAttackPattern[1] = prevAttackPattern[0];
		prevAttackPattern[0] = ROTATE;
		pleaseWait = true;
		waitTime = 0.1f;
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
// rushTime ... �ːi�ɂ�����b��
// backTime ... �߂鎞�ɂ�����b��
// �{�X���v���C���[�̌����ɓːi������֐�
void Boss::Rush(Point playerPosition, float readyTime, float rushTime, float backTime, WireManager* wireManager) {

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
				centerPosition.x + (cosf(playerDirection) * playerDistance),
				centerPosition.y + (sinf(playerDirection) * playerDistance)
			};

			// ����
			actionWayPoint++;
		}
		break;
		// �ːi
	case Boss::WAYPOINT2:
		if (t <= rushTime) {
			// �{�X���擾�����v���C���[�̌����Ɍ������ēːi������
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);
			t += 1.0f / 60.0f;
		}
		else {

			// t��������
			t = 0.0f;

			// ���̍s����
			actionWayPoint++;
		}

		break;
		// ���̏ꏊ�ɖ߂�
	case Boss::WAYPOINT3:
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
			waitTime = 0.35f;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	case Boss::WAYPOINT4:
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
// readyTime ... �a���̏����ɂ�����b��
// deployTime ... �u���[�h�̓W�J�ɂ�����b��
// slashTime ... �a���ɂ�����b��
// backTime ... �߂鎞�ɂ�����b��
// �{�X���a�����s���֐�
void Boss::Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime, WireManager* wireManager) {
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
		nextWeaponSize = { weaponSize.x, 350.0f };
		
		// t������
		t = 0.0f;

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

			//����
			actionWayPoint++;
		}
		break;
		// �u���[�h�W�J
	case Boss::WAYPOINT2:
		if (t <= deployTime) {

			// �u���[�h���L�т�
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
				wireManager->Initialize();
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
			waitTime = 0.5f;
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
// fireRate ... ���b�����Ɏˌ����邩
// �{�X���ˌ����s���֐�
void Boss::Shot(Point playerPosition, float readyTime, float deployTime, float preparationTime, float shotTime, float backTime, float fireRate, WireManager* wireManager) {

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
			waitTime = 0.35f;
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
// �{�X���V��ɂԂ���A�j�Ђ𗎉������čU�����s���֐�
void Boss::Fall(float readyTime, float deployTime, float rushTime, float standByTime, float backTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// ������
	case Boss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;
		nextCenterPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };

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
			nextCenterPosition = { centerPosition.x, (float)BaseConst::kWindowHeight};

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

			wireManager->Initialize();

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
			prevCenterPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
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
			nextCenterPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };

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
void Boss::Damage(float readyTime, float deployTime, float openTime, float stanTime, float backTime, float closeTime, WireManager* wireManager) {

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

			prevOffset = offset;
			nextOffset = 100;

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

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT4:
		if (t <= stanTime) {

			vibration(15, stanTime, stanTime, 4);

			// t���v���X����
			t += 1.0f / 60.0f;
		}
		else {

			vibInit = false;

			prevCenterPosition = centerPosition;
			nextCenterPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };

			prevDegree = degree;

			if (degree < 0) {
				nextDegree = 360;
			}
			else {
				nextDegree = -360;
			}

			// t������������
			t = 0.0f;
			// ���̍s����
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT5:
		if (t <= backTime) {

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
			inDamage = false;
			pleaseWait = false;
			actionWayPoint = WAYPOINT0;
		}

		break;
	default:
		break;
	}
}
#pragma region �R�s�y�p
//// ����������
//if (init = false) {
//	init = true;
//}
//
//// t �̒l�����ȏ�ɂȂ�܂ő���
//if (t < 1.0f) {
//	t += 0.01f;
//
//}
//else {
//	//t �����ȏ�ɂȂ�����s���I��
//	t = 0.0f;
//	init = false;
//	endAction = true;
//	inAction = false;
//}
#pragma endregion
