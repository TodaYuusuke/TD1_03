#include "MyBase/Include/Other/BaseMath.h"

#include <Novice.h>

// �p�x�֘A


// radian����degree�ɕϊ�����֐�
// �Ԃ�l�Fdegree
// �����F
// radian ... radian�̊p�x
// radian�̊p�x��degree�̊p�x�ɕϊ�����֐��B�����ŗv�������̂͊�{Degree�Ȃ̂ł��܂�g��Ȃ��B
float BaseMath::RadiantoDegree(float radian) {
	return radian * (180.0f / M_PI);
}

// degree����radian�ɕϊ�����֐�
// �Ԃ�l�Fradian
// �����F
// degree ... degree�̊p�x
// degree�̊p�x��radian�̊p�x�ɕϊ�����֐��B�����ŗv�������̂͊�{Degree�Ȃ̂Ŋ֐����ł͎g����B
float BaseMath::DegreetoRadian(float degree) {
	return degree * (M_PI / 180.0f);
}

// 2�_�Ԃ̊p�x�idegree�j�����߂�֐�
// �Ԃ�l�F2�_�̊p�x�idegree�j
// �����F
// from ... ���W�P
// to ... ���W�Q
// 2�_�̊p�x��Degree�Ŏ󂯎��֐��B
float BaseMath::GetDegree(Point from, Point to) {

	// �p�x���v�Z
	float radian = atan2(to.y - from.y, to.x - from.x);

	// 180�������̏ꍇ
	if (radian <= 0) {
		radian *= -1;
	}
	else {
		float def = M_PI - radian;

		radian = def + M_PI;
	}

	return BaseMath::RadiantoDegree(radian);
}


// ��]�֘A


// Point�̉�]�v�Z�֐�
// �Ԃ�l�F��]���Point
// �����F
// point ... �v�Z����Points
// degree ... ��]�p�x�idegree�j
// ���_���S�̉�]�����s���Ȃ��̂Œ���
Point BaseMath::TurnPoint(Point point, float degree) {
	// ���W��ۑ��i�v�Z�p�j
	float preX = point.x;
	float preY = point.y;

	// ��]�p�x�iradian�j
	float radian = DegreetoRadian(degree);

	// �v�Z�i��]������j
	point.x = preX * cosf(radian) - preY * sinf(radian);
	point.y = preY * cosf(radian) + preX * sinf(radian);

	return point;
}

// Box�̉�]�v�Z�֐�
// �Ԃ�l�F��]���Box
// �����F
// box ... �v�Z����Points
// degree ... ��]�p�x�idegree�j
// ���_���S�̉�]�����s���Ȃ��̂Œ���
Quad BaseMath::TurnBox(Quad box, float degree) {

	// �v�Z�itheta��]������j
	box.q1 = TurnPoint(box.q1, degree);
	box.q2 = TurnPoint(box.q2, degree);
	box.q3 = TurnPoint(box.q3, degree);
	box.q4 = TurnPoint(box.q4, degree);

	return box;
}


// �����蔻�菈��


// �l�p�`�Ɠ_�̓����蔻��`�F�b�N�i��]���l������j
// �Ԃ�l�F�q�b�g����true�A����ȊO��false
// �����F
// hitBoxCenterPosition ... �q�b�g�Ώۂ̎l�p�̒��S���W
// hitBoxWidth ... �q�b�g�Ώۂ̉���
// hitBoxHeight ... �q�b�g�Ώۂ̏c��
// boxAngle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
// hitPoisiton ... �q�b�g���Ă��邩���؂�����W
bool BaseMath::CheckHitBox(Point hitBoxCenterPosition, float hitBoxWidth, float hitBoxHeight, float boxAngle, Point hitPosition) {

	//hitBoxCenterPosition = BaseDraw::WorldtoScreen(hitBoxCenterPosition);
	//hitPosition = BaseDraw::WorldtoScreen(hitPosition);

	// hitPosition���q�b�g�Ώۂ̎l�p�̒��S�����_�ɉ�]�����Ė߂�
	Point pos = { hitPosition.x - hitBoxCenterPosition.x, hitPosition.y - hitBoxCenterPosition.y };
	hitPosition = BaseMath::TurnPoint(pos, -boxAngle);
	hitPosition = { hitPosition.x + hitBoxCenterPosition.x, hitPosition.y + hitBoxCenterPosition.y };

	// �_����ӂ�艺��
	if (hitPosition.y > hitBoxCenterPosition.y - hitBoxHeight / 2) {
		Novice::ScreenPrintf(0, 0, "1");
		// �_�����ӂ����
		if (hitPosition.y < hitBoxCenterPosition.y + hitBoxHeight / 2) {
			Novice::ScreenPrintf(0, 20, "2");
			// �_�����ӂ��E��
			if (hitPosition.x > hitBoxCenterPosition.x - hitBoxWidth / 2) {
				Novice::ScreenPrintf(0, 40, "3");
				// �_���E�ӂ�荶�̏ꍇ -> �q�b�g���Ă���
				if (hitPosition.x < hitBoxCenterPosition.x + hitBoxWidth / 2) {
					Novice::ScreenPrintf(0, 60, "4");
					return true;
				}
			}
		}
	}

	return false;
}


// �l�p���m�̓����蔻��`�F�b�N
bool BaseMath::CheckHitBox(Box hitBox1, Box hitBox2) {

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