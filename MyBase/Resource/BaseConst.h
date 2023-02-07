#pragma once
#include "MyBase/Define/BaseEnum.h"
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

	// �Ə� //

	// �Ə��̍ő�˒�
	static int kPlayerReticleRange;

	// �Ə��̑傫��
	static int kPlayerReticleSize;

	// ����A�j���[�V����
	static int kPlayerTextureRunNum;

	// �W�����v�A�j���[�V����
	static int kPlayerTextureJumpNum;

	// �A�j���[�V�����Œ�o�߃t���[��
	static int kPlayerMaxAnimationFlame;

	// �A�j���[�V�������̕`��t���[��
	static int kPlayerAnimationFlame[PlayerState::kPlayerStateCount];

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

	// �}�b�v�`�b�v�̃T�C�Y
	const static int kMapChipSizeWidth = 32;
	const static int kMapChipSizeHeight = 32;

	// �`���[�g���A���X�e�[�W�̑傫��
	const static int kTutorialStageSizeWidth = 500;
	const static int kTutorialStageSizeHeight = 35;
	// �{�X�X�e�[�W�̑傫��
	const static int kBossStageSizeWidth = 75;
	const static int kBossStageSizeHeight = 35;


	// �}�b�v�f�[�^
	static int kTutorialStageData[kTutorialStageSizeHeight][kTutorialStageSizeWidth];
	static int kBossStageData[kBossStageSizeHeight][kBossStageSizeWidth];

#pragma endregion

#pragma region GameOver

	// ���炩���ߕ`�悷�銮���x
	static float kGameOverFirstValue;
	// �Q�[���I�[�o�[���̉��o�ɂ�����t���[��
	const static int kGameOverMaxFlame = 10;
	// �Q�[���I�[�o�[���o�� 1 �t���[���P�ʂł̕K�v�Ȏ���
	static float kGameOverFlame;

	// �u�^�C�g���֖߂�v�e����W
	static Point kGameOverTitleLeftTop;
	static Point kGameOverTitleRightBottom;
	// �u���g���C�v�e����W
	static Point kGameOverRetryLeftTop;
	static Point kGameOverRetryRightBottom;

	// �]��
	const static int kGameOverPadding = 10;

#pragma endregion

#pragma region Effect

	// ���C���[���h���������̕�
	// ���q��
	const static int kConcreteDustNum = 20;


#pragma endregion


};