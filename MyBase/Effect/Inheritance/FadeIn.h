#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

namespace effect {
	class FadeIn :
		public BaseEffect {
	public: // �����o�֐�

		// �R���X�g���N�^
		FadeIn();
		// �f�X�g���N�^
		~FadeIn();


		// ������
		void Initialize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;

	private: // �����o�ϐ�
		
		// ���݂̓����x
		int alpha;
	};
}