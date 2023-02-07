#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

namespace effect {
	class WhirlWind :
		public BaseEffect {
	public: // �����o�֐�

		// �R���X�g���N�^
		WhirlWind();
		// �f�X�g���N�^
		~WhirlWind();


		// ������
		void Initialize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;

	private: // �����o�ϐ�

		/* ���͈̔͂̕ϐ��͊��ɐ錾����Ă���̂ŗ��p���Ă���i���ı�Ă͊O���Ȃ��Ă悵�j
		// �`����W
		Point position;
		// ���݂̌o�߃t���[��
		int elapsedFrame;

		// �G�t�F�N�g���I���������ǂ���
		bool isEnd;
		*/
	};
}