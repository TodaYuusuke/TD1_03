#include "Base/Include/Other/BaseMath.h"



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