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

	// �s���I����Ԃɂ���
	this->endAction = true;

	// �j�̈ʒu��ݒ�
	coreCenterPosition = centerPosition;
	// �j�̉摜�T�C�Y��ݒ�
	kernelTextureSize = { 256.0f, 256.0f };
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

	if (endAction == true) {
		if(BaseInput::GetKeyboardState(DIK_F, Trigger)) {
			inAction = true;
			endAction = false;
		}
	}

	if (inAction == true) {
		Rush(playerPosition, 1, 2, 1);
	}

	// �f�o�b�O�֐��̎��s
	if (inDebug == true) {
		Debug();
	}

	// �j���������Ă��Ȃ���Ԃł͊j���{�X�ɒǏ]������
	if (coreSeparated == false) {
		coreCenterPosition = centerPosition;
		coreDegree = degree;
	}	

}

// �`�揈��
void Boss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

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
	Novice::ScreenPrintf(0, 110, "ShakeRange : %d", shakeRange);

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

// �f�o�b�O�p�֐�
void Boss::Debug() {
	// ���ׂĂ����Z�b�g����
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		offset = 0.0f;
		degree = 0;
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
void Boss::ShakeEaseOut(int shakeStrength, int shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// �s���Ȃ��֐�
// �Ԃ�l�F�Ȃ�
// �����F
// waitTime ... �ҋ@���鎞��
// �s���̍��Ԃɋ��ފ֐��BwaitFrame�͕b���ł͂Ȃ��t���[���P��
void Boss::None(int waitFrame) {
	if (t < waitFrame) {
		t += 1.0f;
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
void Boss::Rotate(float endDegree, int RotateTime) {

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
void Boss::Rush(Point playerPosition, int readyTime, int rushTime, int backTime) {
	// ����������
	if (init == false) {
		init = true;
	}

	switch (actionWayPoint)
	{
		// ������
	case Boss::WAYPOINT0:
		// ���S���W�擾
		prevCenterPosition = centerPosition;
		prePlayerPosition = playerPosition;
		t = 0.0f;
		//���̒i�K��
		actionWayPoint++;
		break;
		// ���O����(�k����)
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// �w�肳�ꂽ�b���U������
			ShakeEaseOut(60, readyTime);
			t += 1.0f / 60.0f;
		}
		else {
			t = 0.0f;

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

			//����
			actionWayPoint++;
		}
		break;
		// �ːi
	case Boss::WAYPOINT2:
		if (t <= rushTime) {
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);
			t += 1.0f / 60.0f;
		}
		else {
			t = 0.0f;
			actionWayPoint++;
			centerPosition = nextCenterPosition;
		}

		break;
		// ���̏ꏊ�ɖ߂�
	case Boss::WAYPOINT3:
		if (t <= backTime) {
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			centerPosition = prevCenterPosition;
			t = 0.0f;
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
