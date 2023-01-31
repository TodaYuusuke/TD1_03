#pragma once
#include "MyBase/Define/BaseStruct.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

///////////////////////////////////////////
/* - �Q�[�����ŋ��ʂň����萔���Ǘ�����N���X - */
///////////////////////////////////////////


class BaseConst
{

public: // �����o�֐�

	// ������
	static void Initialize();


	// ���[�h�֐�
	// �Ԃ�l�F���[�h�����������ꍇ��true
	// �����F����
	// �萔�̃��[�h��100�����ōs���B�S�Ẵ��[�h����������܂ŌĂяo������i����́��͎������Ȃ��A���[�h���邾���j
	static bool Loading();

	// ���[�h�����擾����֐�
	// �Ԃ�l�F���݂̃��[�h���i���j
	// �����F����
	// ���݂̃��[�h�󋵂��擾����֐��B
	static int GetLoadingPercent();



	// string�����֐�
	static std::vector<std::string> split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);
		std::string field;
		std::vector<std::string> result;
		while (getline(stream, field, delimiter)) {
			result.push_back(field);
		}
		return result;
	}


private: // �����o�ϐ�

	// ���݂̃��[�h��
	static int LoadingPercent;
	// ���[�h������������
	static bool isLoadingComplete;


public: // �ÓI�Ȓ萔

#pragma region �𑜓x

	// �E�B���h�E�𑜓x�i�������j
	static int kWindowWidth;
	// �E�B���h�E�𑜓x�i�c�����j
	static int kWindowHeight;

#pragma endregion

#pragma region �u���b�N

	// �u���b�N��������܂ł̃t���[����
	static int kBlockVanishFlame;
	// �u���b�N���_�ł��n�߂�t���[��
	static int kBlockBeVanish;


#pragma endregion

#pragma region �v���C���[

	// �v���C���[�̃T�C�Y
	static Point kPlayerSize;

	// �d�͉����x
	static float kPlayerGravitationalAcceleration;
	// �S�̂̑��x����
	static float kPlayerVelocityLimit;

	// �ړ� //

	// ���s�ړ��̌��E���x
	static float kPlayerWalkVelocityLimit;

	// �W�����v //

	// �W�����v�̑��x
	static Point kPlayerJumpVelocity;
	// �W�����v�̃N�[���^�C��
	static int kPlayerJumpCoolTime;

#pragma endregion

#pragma region ���C���[

	// ���C���[�̒e��
	static float kWireSpeed;

	// ���C���[�̍ő�̒���
	static float kWireMaxLength;
	// ���C���[�̍ő呶�ݐ�
	const static int kWireMaxAmount = 5;

#pragma endregion

#pragma region �}�b�v

	// �}�b�v�̑傫��
	const static int kMapSizeWidth = 75;
	const static int kMapSizeHeight = 35;

	// �}�b�v�`�b�v�̃T�C�Y
	static int kMapChipSizeWidth;
	static int kMapChipSizeHeight;

	// �}�b�v�f�[�^
	static int kMapData[kMapSizeHeight][kMapSizeWidth];

#pragma endregion

};