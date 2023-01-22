#include "Class/Include/Boss/Boss.h"

/*********************************************
 * �{�X�N���X
 *
 * �{�X�֘A�̍s�����ׂĂ��Ǘ�����N���X
 *********************************************/

// �R���X�g���N�^
Boss::Boss() {
	Boss::Initialize();
}

// �f�X�g���N�^
Boss::~Boss() {

}

// ����������
void Boss::Initialize() {
	// �{�X�̈ʒu����ʒ����Ɏ����Ă���
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	// �{�X�̉摜�T�C�Y��ݒ�
	this->textureSize = { 225.0f, 450.0f };
	// �{�X�̃I�t�Z�b�g��������
	this->offset = 0.0f;

	this->degree = 0.0f;

	//�V�F�C�N���Ă��Ȃ���Ԃɖ߂�
	this->shakeVariation = { 0.0f, 0.0f };

	// �s���I����Ԃɂ���
	this->t = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->actionWayPoint = 0;

	// �j�̈ʒu��ݒ�
	coreCenterPosition = centerPosition;
	// �j�̉摜�T�C�Y��ݒ�
	kernelTextureSize = { 256.0f, 256.0f };

	// ����̃T�C�Y���w��i���e�N�X�`���̂��߁A����ς���j
	weaponSize = { 0.0f, 0.0f };
	weaponTextureSize = { 1.0f, 1.0f };

	// �e�̊֌W������
	for (int i = 0; i < kmaxBullet; i++) {
		// �e�̍��W
		bulletCenterPosition[i] = { 0.0f, 0.0f };

		// ���˂��Ă��Ȃ���Ԃɂ���
		isShot[i] = false;

		// �e�̔��˕��������Z�b�g����
		bulletDirection[i] = 0.0f;

		// �e�̐������Ԃ����Z�b�g����
		bulletAliveTime[i] = 0.0f;
	}

	// �e�̃T�C�Y���w��
	bulletSize = { 20.0f, 20.0f };
	// �e�̉摜�T�C�Y���w��i���e�N�X�`���̂��߁A����ς���)
	bulletTextureSize = { 1.0f, 1.0f };

	// �e�̔��˃X�s�[�h���w��
	bulletSpeed = 10.0f;
}

// �X�V����
void Boss::Update(Point playerPosition) {
	/******** �f�o�b�N���� **********/
	// �f�o�b�O��Ԃ̐؂�ւ�
	if (BaseInput::GetKeyboardState(DIK_0, Trigger)) {
		if (inDebug == false)
			inDebug = true;

		else
			inDebug = false;
	}

	// �s���̎��s����
	if (inAction == true && inStun == false && inDamage == false) {
		switch (attackPattern)
		{
		case Boss::NONE:
			None(1.0f);
			break;
		case Boss::ROTATE:
			Rotate(720, 2.0f);
			break;
		case Boss::RUSH:
			Rush(playerPosition, 0.5f, 1.5f, 1.0f);
			break;
		case Boss::SLASH:
			Slash(playerPosition, 0.35f, 0.2f, 1.0f, 0.75f, 1.0f);
			break;
		case Boss::SHOT:
			Shot(playerPosition, 0.35f, 0.75f, 1.0f, 5.0f, 1.0f, 0.1f);
			break;
		case Boss::FALL:
			break;
		}
	}

	degree %= 360;

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

			// ��O���������@����͂킩��Ȃ��̂Ŋ���
			/*if () {

			}*/

			bulletCenterPosition[i].x += -cosf(bulletDirection[i]) * bulletSpeed;
			bulletCenterPosition[i].y += -sinf(bulletDirection[i]) * bulletSpeed;

			bulletAliveTime[i] -= 1.0f / 60.0f;
		}
		else {
			isShot[i] = false;
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

	Novice::ScreenPrintf(0, 30, "t : %4.2f", t);
	Novice::ScreenPrintf(0, 50, "pos x : %4.2f y : %4.2f", centerPosition.x, centerPosition.y);
	Novice::ScreenPrintf(0, 70, "inAction : %d", inAction);
	Novice::ScreenPrintf(0, 90, "endAction : %d", endAction);
	Novice::ScreenPrintf(0, 110, "actionWayPoint : %d", actionWayPoint);
	Novice::ScreenPrintf(0, 130, "actionBranch : %d", actionBranch);
	Novice::ScreenPrintf(0, 150, "isShot : %d", isShot[0]);
	Novice::ScreenPrintf(0, 190, "bulletPos * x : %4.2f y : %4.2f", bulletCenterPosition[0].x, bulletCenterPosition[0].y);

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

// �f�o�b�O�p�֐�
void Boss::Debug() {
	// ���ׂĂ����Z�b�g����
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		Boss::Initialize();
	}

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

// �s���Ȃ��֐�
// �Ԃ�l�F�Ȃ�
// �����F
// waitTime ... �ҋ@����b��
// �s���̍��Ԃɋ��ފ֐��B
void Boss::None(float waitFrame) {
	if (t < waitFrame) {
		t += 1.0f / 60.0f;
	}
	else {
		endAction = true;
	}
}

// ��]�֐�
// �Ԃ�l�F�Ȃ�
// �����F
// endDegree ... �I�����̊p�x
// rotateTime ... ��]���鎞�ԁB����͕b��
// �{�X����]������֐�
void Boss::Rotate(float endDegree, float RotateTime) {

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
		t += 1.0f / 60.0f;
	}
	else {
		//t �����ȏ�ɂȂ�����s���I��
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
void Boss::Rush(Point playerPosition, float readyTime, float rushTime, float backTime) {

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
			float playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

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
void Boss::Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime) {
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
void Boss::Shot(Point playerPosition, float readyTime, float deployTime, float preparationTime, float shotTime, float backTime, float fireRate) {

	// �{�X���v���C���[�ɒǏ]���ĉ�]���鎞�ɗp����J�E���g�ϐ�
	static int count;

	// �{�X�̔��˃��[�g���Ǘ�����ϐ�
	static float fireRateCount;

	Novice::ScreenPrintf(0, 170, "nextDegree : %4.2f", fireRateCount);

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
