#pragma once
#include "MyBase/Include/Define/BaseEnum.h"
#include "MyBase/Include/Define/BaseStruct.h"

#include "MyBase/Include/Effect/BaseEffectManager.h"

#include "MyBase/Include/Resource/BaseTexture.h"
#include "MyBase/Include/Resource/BaseAudio.h"
#include "MyBase/Include/Resource/BaseConst.h"

#include "MyBase/Include/Other/BaseDraw.h"
#include "MyBase/Include/Other/BaseInput.h"
#include "MyBase/Include/Other/BaseMath.h"

#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include <memory>

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

};