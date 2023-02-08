#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

namespace effect {
	class IronBalloonDead :
		public BaseEffect {
	public: // �����o�֐�

		// �R���X�g���N�^
		IronBalloonDead(Point, bool);
		// �f�X�g���N�^
		~IronBalloonDead();


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