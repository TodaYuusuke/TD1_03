#pragma once


namespace BaseStruct {
	////////////////////////////////////////////////
	/* - �v���O�������Ɏg���S�Ă̍\���̂��Ǘ�����N���X - */
	////////////////////////////////////////////////


	// ���W
	struct Point
	{
		// x���W
		float x;
		// y���W
		float y;
	};

	// �~
	struct Circle {
		// ���S���W
		Point position;
		// ���a
		float radian;
	};

	// �{�b�N�X
	struct Box {
		// ����̍��W
		Point position;
		// ����
		float width;
		// �c��
		float height;
	};


	// �l�p���m�̓����蔻��`�F�b�N
	static bool CheckHitBox(Box hitBox1, Box hitBox2) {

		// ���S���W�𒲂ׂ�
		Point hitBox1Center = { hitBox1.position.x + (hitBox1.width / 2), hitBox1.position.y + (hitBox1.height / 2) };
		Point hitBox2Center = { hitBox2.position.x + (hitBox2.width / 2), hitBox2.position.y + (hitBox2.height / 2) };

		// ��_�Ԃ̋����𒲂ׂ�
		Point hitBoxDistance = { hitBox1Center.x - hitBox2Center.x,hitBox1Center.y - hitBox2Center.y };
		if (hitBoxDistance.x < 0.0f) {
			hitBoxDistance.x *= -1.0f;
		}
		if (hitBoxDistance.y < 0.0f) {
			hitBoxDistance.y *= -1.0f;
		}

		// �T�C�Y�̘a���Z�o����
		Point hitBoxSize = { (hitBox1.width + hitBox2.width) / 2,(hitBox1.height + hitBox2.height) / 2 };

		// �q�b�g����
		if (hitBoxDistance.x < hitBoxSize.x && hitBoxDistance.y < hitBoxSize.y) {
			return true;
		}

		return false;
	}

	// �l�p
	struct Quad
	{
		// ����
		Point q1;
		// �E��
		Point q2;
		// ����
		Point q3;
		// �E��
		Point q4;
	};

}

using namespace BaseStruct;