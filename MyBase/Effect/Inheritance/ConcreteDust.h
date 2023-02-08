#pragma once
#include "MyBase/MyBase.h"
#include "MyBase/Effect/BaseEffect.h"

#include "Class/Map/MapManager.h"

namespace effect {
	class ConcreteDust :
		public BaseEffect {
	public: // �����o�֐�

		// �R���X�g���N�^
		ConcreteDust(Point);
		// �f�X�g���N�^
		~ConcreteDust();


		// ������
		void Initialize() override;
		// �X�V
		void Update() override;
		// �`��
		void Draw() override;

	private: // �����o�ϐ�
		
		// ���q�̒��S���W
		Point pos[BaseConst::kConcreteDustNum];
		// ���x
		Point vel[BaseConst::kConcreteDustNum];
		// �傫�� 1 �` 3
		float size[BaseConst::kConcreteDustNum];

	};
}