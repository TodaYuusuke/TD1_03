#pragma once
#include "Base/Include/Define/BaseEnum.h"
#include "Base/Include/Define/BaseStruct.h"

#include "Base/Include/Effect/BaseEffect.h"


class BaseEffectManager
{
public: // �����o�֐�

	// ������
	static void Initialize();
	// �X�V
	static void Update();
	// �`��
	static void Draw();


	// �V�K�G�t�F�N�g�o�^�֐�
	// �Ԃ�l�F�G�t�F�N�g���Z�b�g���ꂽ�ԍ�
	// �����F
	// position ... ���S�̃��[���h���W
	// effectType ... �G�t�F�N�g�̎��
	static int MakeNewEffect(Point position, EffectType effectType);

	// �G�t�F�N�g���I��������֐�
	// �Ԃ�l�F�Ȃ�
	// �����F
	// effectNum ... �G�t�F�N�g�ԍ�
	static void EndEffect(int effectNum);

	// �G�t�F�N�g���I���������𒲂ׂ�֐�
	// �Ԃ�l�F�G�t�F�N�g���I���ς� ... true �A �����łȂ��ꍇ ... false
	// �����F
	// effectNum ... �G�t�F�N�g�ԍ�
	static bool isEndEffect(int effectNum);


private: // �����o�ϐ�

	// �G�t�F�N�g�z��̃T�C�Y
	const static int effectArraySize = 1024;

	// �G�t�F�N�g�̔z��
	static BaseEffect* effects[effectArraySize];

	// ���ɒǉ�����G�t�F�N�g�̓Y��
	static int nextIndex;
};

