#pragma once
#include "MyBase/Define/BaseEnum.h"
#include "MyBase/Define/BaseStruct.h"

#include "MyBase/Effect/BaseEffectManager.h"

#include "MyBase/Resource/BaseTexture.h"
#include "MyBase/Resource/BaseAudio.h"
#include "MyBase/Resource/BaseConst.h"

#include "MyBase/Other/BaseDraw.h"
#include "MyBase/Other/BaseInput.h"
#include "MyBase/Other/BaseMath.h"

#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include <memory>

#include "Class/PublicFlag/PublicFlag.h"

////////////////////////////////////
/* - Base�N���X�S�Ă��Ǘ�����N���X - */
////////////////////////////////////


class MyBase
{

private: // �����o�֐�

	// �R���X�g���N�^�i����J�j
	MyBase();
	// �f�X�g���N�^�i����J�j
	~MyBase();

public: // �����o�֐�

	// ������
	static void Initialize();
	// �X�V
	static void Update();
	// �`��
	static void Draw();

private: // �����o�ϐ�

	// ���o�p�ϐ�
	static float easingT;
	static float width;

	// ���o�X�L�b�v�p�ϐ�
	static int longPressedFrame;

};