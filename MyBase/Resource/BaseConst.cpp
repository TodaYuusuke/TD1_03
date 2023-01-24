#include "MyBase/Resource/BaseConst.h"

// ������
void BaseConst::Initialize() {
	LoadingPercent = 0;
	isLoadingComplete = false;
}


// ���[�h�֐�
// �Ԃ�l�F���[�h�����������ꍇ��true
// �����F����
// �萔�̃��[�h��100�����ōs���B�S�Ẵ��[�h����������܂ŌĂяo������i����́��͎������Ȃ��A���[�h���邾���j
bool BaseConst::Loading() {

	std::vector<std::string> map;
	std::ifstream mapifs("./Resources/Const/mapSample.csv");
	std::string line;

	int y = 0;

	while (getline(mapifs, line)) {

		std::vector<std::string> strvec = split(line, ',');

		for (int x = 0; x < strvec.size(); x++) {
			kMapData[y][x] = stoi(strvec.at(x));
		}

		y++;
	}

	return true;
}


// ���[�h�����擾����֐�
// �Ԃ�l�F���݂̃��[�h���i���j
// �����F����
// ���݂̃��[�h�󋵂��擾����֐��B
int BaseConst::GetLoadingPercent() {
	return LoadingPercent;
}


//////////////////////////////////
/* - static�����o�ϐ��̎��Ԃ�錾 - */
//////////////////////////////////

int BaseConst::LoadingPercent;
bool BaseConst::isLoadingComplete;


#pragma region �𑜓x

// �E�B���h�E�𑜓x�i�������j
int BaseConst::kWindowWidth = 1920;
// �E�B���h�E�𑜓x�i�c�����j
int BaseConst::kWindowHeight = 1080;

#pragma endregion


#pragma region �v���C���[

// �v���C���[�̃T�C�Y
Point BaseConst::kPlayerSize = { 64,128 };

// �d�͉����x
float BaseConst::kPlayerGravitationalAcceleration = 9.8f / 30.0f;
// �S�̂̑��x����
float BaseConst::kPlayerVelocityLimit = 10.0f;

// �ړ� //

// ���s�ړ��̌��E���x
float BaseConst::kPlayerWalkVelocityLimit = 3.0f;

// �W�����v //

// �W�����v�̑��x
Point BaseConst::kPlayerJumpVelocity = { 0,9.8f };
// �W�����v�̃N�[���^�C��
int BaseConst::kPlayerJumpCoolTime = 40;

#pragma endregion

#pragma region ���C���[

// ���C���[�̒e��
float BaseConst::kWireSpeed = 40;

// ���C���[�̍ő�̒���
float BaseConst::kWireMaxLength = 100.0f;
// ���C���[�̍ő呶�ݐ�
//int BaseConst::kWireMaxAmount = 3;

#pragma endregion

#pragma region �}�b�v

// �}�b�v�`�b�v�̃T�C�Y
int BaseConst::kMapChipSizeWidth = 32;
int BaseConst::kMapChipSizeHeight = 32;

// �}�b�v�f�[�^
int BaseConst::kMapData[kMapSizeHeight][kMapSizeWidth];

#pragma endregion