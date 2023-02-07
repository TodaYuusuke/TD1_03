#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"


namespace effect {
	class BlockBreak :
		public BaseEffect {
	public: // �����o�֐�

		// �R���X�g���N�^
		BlockBreak(Point);
		// �f�X�g���N�^
		~BlockBreak();


		// ������
		void Initialize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;

	private: // �����o�ϐ�
		
		// �X�N���b�v�̍��W
		Point pos[BaseTexture::kBlockScrapAmount];
		// ���x
		Point velocity[BaseTexture::kBlockScrapAmount];
		// ��]�p�x
		float angle[BaseTexture::kBlockScrapAmount];
	};
}