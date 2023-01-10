#pragma once
#include "Base/Include/Define/BaseStruct.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;

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
	static vector<string> split(string& input, char delimiter)
	{
		istringstream stream(input);
		string field;
		vector<string> result;
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
};