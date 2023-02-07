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

	// �l�p
	// q1 ... ����
	// q2 ... �E��
	// q3 ... ����
	// q4 ... �E��
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