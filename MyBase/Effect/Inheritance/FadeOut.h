#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

namespace effect {
	class FadeOut :
		public BaseEffect {
	public: // �����o�֐�

		// �R���X�g���N�^
		FadeOut();
		// �f�X�g���N�^
		~FadeOut();


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