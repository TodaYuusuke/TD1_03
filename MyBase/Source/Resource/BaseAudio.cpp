#include "MyBase/Include/Resource/BaseAudio.h"

// ������
void BaseAudio::Initialize() {
	LoadingPercent = 0;
	isLoadingComplete = false;

	InitializeVolume();
}


// BGM��SE��volume�������ݒ�ɖ߂�
void BaseAudio::InitializeVolume() {
	BGMvolume = 0.3f;
	SEvolume = 0.5f;
}


// ���[�h�֐�
// �Ԃ�l�F���[�h�����������ꍇ��true
// �����F����
// �I�[�f�B�I�̃��[�h��100�����ōs���B�S�Ẵ��[�h����������܂ŌĂяo������i����́��͎������Ȃ��A���[�h���邾���j
bool BaseAudio::Loading() {


	return true;
}


// ���[�h�����擾����֐�
// �Ԃ�l�F���݂̃��[�h���i���j
// �����F����
// ���݂̃��[�h�󋵂��擾����֐��B
int BaseAudio::GetLoadingPercent() {
	return LoadingPercent;
}


//////////////////////////////////
/* - static�����o�ϐ��̎��Ԃ�錾 - */
//////////////////////////////////

// ���݂̃��[�h��
int BaseAudio::LoadingPercent;
// ���[�h������������
bool BaseAudio::isLoadingComplete;
// BGM�n�̉���
float BaseAudio::BGMvolume;
// SE�n�̉���
float BaseAudio::SEvolume;

