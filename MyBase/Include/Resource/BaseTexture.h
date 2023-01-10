#pragma once
#include <Novice.h>


///////////////////////////////////////////////////////
/* - �Q�[�����Ŏg���S�Ẵe�N�X�`���t�@�C�����Ǘ�����N���X - */
///////////////////////////////////////////////////////


class BaseTexture
{

public: // �����o�֐�

	// ������
	static void Initialize();


	// ���[�h�֐�
	// �Ԃ�l�F���[�h�����������ꍇ��true
	// �����F����
	// �e�N�X�`���̃��[�h��100�����ōs���B�S�Ẵ��[�h����������܂ŌĂяo������i����́��͎������Ȃ��A���[�h���邾���j
	static bool Loading();

	// ���[�h�����擾����֐�
	// �Ԃ�l�F���݂̃��[�h���i���j
	// �����F����
	// ���݂̃��[�h�󋵂��擾����֐��B
	static int GetLoadingPercent();


private: // �����o�ϐ�

	// ���݂̃��[�h��
	static int LoadingPercent;
	// ���[�h������������
	static bool isLoadingComplete;


public: // �ÓI�ȃe�N�X�`���̕ϐ�

	// �f�o�b�O�p�e�N�X�`��
	static int kDebugTexture;

};