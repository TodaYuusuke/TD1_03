#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

namespace effect {
	class BalloonDead :
		public BaseEffect {
	public: // �����o�֐�

		// �R���X�g���N�^
		BalloonDead(Point, bool);
		// �f�X�g���N�^
		~BalloonDead();


		// ������
		void Initialize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;

	private: // �����o�ϐ�
		// �E�������ǂ���
		bool isRight;
	};
}