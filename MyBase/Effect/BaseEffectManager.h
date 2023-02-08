#pragma once
#include "MyBase/Define/BaseEnum.h"
#include "MyBase/Define/BaseStruct.h"

#include "MyBase/Effect/BaseEffect.h"

#include "MyBase/Effect/Inheritance/BlockBreak.h"
#include "MyBase/Effect/Inheritance/ConcreteDust.h"
#include "MyBase/Effect/Inheritance/BalloonDead.h"


class BaseEffectManager
{
public: // �����o�֐�

	// ������
	static void Initialize();
	// �X�V
	static void Update();
	// �`��
	static void Draw();


	// �󂢂Ă���G�t�F�N�g�̘g���󂯎��֐�
	static void GetEmptyID();

	// �V�K�G�t�F�N�g�o�^�֐�
	// �Ԃ�l�F�G�t�F�N�g���Z�b�g���ꂽ�ԍ�
	// �����F���ꂼ��
	static int MakeNewEffectBlockBreak(Point);
	static int MakeNewEffectConcreteDust(Point);
	static int MakeNewEffectBalloonDead(Point, bool);


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
	const static int effectArraySize = 128;

	// �G�t�F�N�g�̔z��
	static BaseEffect* effects[effectArraySize];

	// ���ɒǉ�����G�t�F�N�g�̓Y��
	static int nextIndex;
};

