#include "MyBase/Include/Other/BaseMath.h"



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

// �x�N�g���֘A

/// <summary>
/// �x�N�g���̒��������߂�֐�
/// </summary>
/// <param name="vector">�x�N�g��</param>
/// <returns>�x�N�g���̒���</returns>
float BaseMath::GetLength(Point vector) {
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}


/// <summary>
/// �x�N�g���̐��K��������֐�
/// </summary>
/// <param name="vector">�x�N�g��</param>
/// <returns>���K�����ꂽ�x�N�g��</returns>
Point BaseMath::GetNormalize(Point vector) {
	Point norm = vector;
	float length = GetLength(vector);
	if (length != 0.0f) {
		norm.x /= length;
		norm.y /= length;
	}
	return norm;
}

/// <summary>
/// Degree ���󂯎���ăx�N�g���𐶐�����֐�
/// </summary>
/// <param name="degree">degree</param>
/// <returns>�x�N�g��</returns>
Point BaseMath::GetVector(float degree) {
	return { cosf(BaseMath::DegreetoRadian(degree)),sinf(BaseMath::DegreetoRadian(degree)) };
}
/// <summary>
/// Degree ���󂯎���ăx�N�g���𐶐�����֐�
/// </summary>
/// <param name="degree">degree</param>
/// <param name="speed">�X�s�[�h</param>
/// <returns>���K�����ꂽ�x�N�g���ɃX�s�[�h���|�����x�N�g��</returns>
Point BaseMath::GetVector(float degree, Point speed) {
	return { cosf(BaseMath::DegreetoRadian(degree)) * speed.x,sinf(BaseMath::DegreetoRadian(degree)) * speed.y };
}
