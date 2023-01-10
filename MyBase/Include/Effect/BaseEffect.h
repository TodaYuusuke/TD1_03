#pragma once
#include "MyBase/Include/Define/BaseEnum.h"
#include "MyBase/Include/Define/BaseStruct.h"
#include "MyBase/Include/Resource/BaseConst.h"
#include "MyBase/Include/Resource/BaseTexture.h"
#include "MyBase/Include/Resource/BaseAudio.h"

#include "MyBase/Include/Other/BaseDraw.h"

#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

enum EffectType {
	// �G�t�F�N�g����
	NoEffect,
};

namespace effect {
	class BaseEffect
	{

	public: // �����o�֐�

		// �R���X�g���N�^
		//BaseEffect();
		// �f�X�g���N�^
		//~BaseEffect();

		// ������
		void BaseInitialize();
		void BaseInitialize(Point _position);
		virtual void Initialize();
		// �X�V
		void BaseUpdate();
		virtual void Update();
		// �`��
		void BaseDraw();
		virtual void Draw();

		// �G�t�F�N�g���I��������֐�
		// �Ԃ�l�F�Ȃ�
		// �����F
		void EndEffect();

		// �G�t�F�N�g���I���������ǂ�����Ԃ��֐�
		// �Ԃ�l�F�I�������Ȃ�true�A�����łȂ����false
		// �����F����
		// �G�t�F�N�g���������������`�F�b�N����֐�
		bool isEndEffect();



	protected: // �����o�ϐ�

		// �`����W
		Point position;
		// ���݂̌o�߃t���[��
		int elapsedFrame;

		// �G�t�F�N�g���I���������ǂ���
		bool isEnd;
	};
}

using namespace effect;