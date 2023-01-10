#pragma once
#include "Base/Include/Define/BaseEnum.h"
#include "Base/Include/Define/BaseStruct.h"

#include "Base/Include/Effect/BaseEffectManager.h"

#include "Base/Include/Resource/BaseTexture.h"
#include "Base/Include/Resource/BaseAudio.h"
#include "Base/Include/Resource/BaseConst.h"

#include "Base/Include/Other/BaseDraw.h"
#include "Base/Include/Other/BaseInput.h"
#include "Base/Include/Other/BaseMath.h"

#include <Novice.h>
#include <time.h>
#include <memory>

////////////////////////////////////
/* - Base�N���X�S�Ă��Ǘ�����N���X - */
////////////////////////////////////


class Base
{

private: // �����o�֐�

	// �R���X�g���N�^�i����J�j
	Base();
	// �f�X�g���N�^�i����J�j
	~Base();

public: // �����o�֐�

	// ������
	static void Initialize();
	// �X�V
	static void Update();
	// �`��
	static void Draw();

};