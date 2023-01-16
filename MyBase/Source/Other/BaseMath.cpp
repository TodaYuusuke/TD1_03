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
	return { cosf(BaseMath::DegreetoRadian(degree)) * speed.x, -sinf(BaseMath::DegreetoRadian(degree)) * speed.y };
}

/// <summary>
/// from �� to ���󂯎���ăx�N�g���𐶐�����֐�
/// </summary>
/// <param name="from">���W 1</param>
/// <param name="to">���W 2</param>
/// <returns>from ���� to �ւ̃x�N�g��</returns>
Point BaseMath::GetVector(Point from, Point to) {
	return { to.x - from.x,to.y - from.y };
}

/// <summary>
/// ���ς����߂�֐�
/// </summary>
/// <param name="a">�x�N�g�� 1</param>
/// <param name="b">�x�N�g�� 2</param>
/// <returns>����</returns>
float BaseMath::GetDot(Point a, Point b) {
	return a.x * b.x + a.y * b.y;
}

/// <summary>
/// �O�ς����߂�֐�
/// </summary>
/// <param name="a">�x�N�g�� 1</param>
/// <param name="b">�x�N�g�� 2</param>
/// <returns>�O��</returns>
float BaseMath::GetCross(Point a, Point b) {
	return a.x * b.y - a.y * b.y;
}

// �J�v�Z��

/// <summary>
/// �_�Ɛ����̈�ԋ߂��_��������狁�߂�֐�
/// </summary>
/// <param name="hitCenterPosition">�Ώۂ̒��S���W</param>
/// <param name="hitPosition">�����̎n�_���W</param>
/// <param name="hitVelocity">�����̒���</param>
/// <returns>�_�Ɛ����̍ŋߖT�_</returns>
Point BaseMath::GetNearestPosition(Point hitCenterPosition, Point hitPosition, Point hitVelocity) {
	// �����𐳋K��
	Point e = GetNormalize(hitVelocity);
	// �����̎n�_����_�܂ł̃x�N�g��
	Point a = { hitCenterPosition.x - hitPosition.x,hitCenterPosition.y - hitPosition.y };
	if (GetDot(e, a) < 0) {
		return hitPosition;
	}
	// �����̏I�_����_�܂ł̃x�N�g��
	Point b = { hitCenterPosition.x - (hitPosition.x + hitVelocity.x),hitCenterPosition.y - (hitPosition.y + hitVelocity.y) };
	if (0 < GetDot(e, b)) {
		return { hitPosition.x + hitVelocity.x, hitPosition.y + hitVelocity.y };
	}
	// �����̍ŋߖT�_�����߂�
	float t = GetDot(a, e) / GetLength(hitVelocity);
	//float t = GetDot(a, e);
	return { hitPosition.x + (hitVelocity.x * t),hitPosition.y + (hitVelocity.y * t) };
	//return { (1.0f - t) * hitPosition.x + t * (hitPosition.x + hitVelocity.x),(1.0f - t) * hitPosition.y + t * (hitPosition.y + hitVelocity.y) };
}

/// <summary>
/// �_�Ɛ����̈�ԋ߂��_��������狁�߂�֐�
/// </summary>
/// <param name="hitQuad">�Ώۂ̋�`</param>
/// <param name="hitPosition">�����̎n�_���W</param>
/// <param name="hitVelocity">�����̒���</param>
/// <returns>�_�Ɛ����̍ŋߖT�_</returns>
Point BaseMath::GetNearestPosition(Quad hitQuad, Point hitPosition, Point hitVelocity) {
	float t = 10000;
	float length = GetLength(hitVelocity);
	// �����𐳋K��
	Point e = GetNormalize(hitVelocity);

	// q1

	// �����̎n�_����_�܂ł̃x�N�g��
	Point a = { hitQuad.q1.x - hitPosition.x,hitQuad.q1.y - hitPosition.y };
	// �n�_���O��������
	if (GetDot(e, a) < 0) {
		t = 0;
	}
	// �����̏I�_����_�܂ł̃x�N�g��
	Point b = { hitQuad.q1.x - (hitPosition.x + hitVelocity.x),hitQuad.q1.y - (hitPosition.y + hitVelocity.y) };
	// �I�_���ゾ������
	if (0 < GetDot(e, b)) {
		if (GetLength(hitVelocity) < t) {
			t = GetLength(hitVelocity);
		}
	}
	// �����̍ŋߖT�_�����߂�
	if (GetDot(a, e) / GetLength(hitVelocity) < t) {
		t = GetDot(a, e) / GetLength(hitVelocity);
	}

	// q2

	// �����̎n�_����_�܂ł̃x�N�g��
	a = { hitQuad.q2.x - hitPosition.x,hitQuad.q2.y - hitPosition.y };
	// �n�_���O��������
	if (GetDot(e, a) < 0) {
		t = 0;
	}
	// �����̏I�_����_�܂ł̃x�N�g��
	b = { hitQuad.q2.x - (hitPosition.x + hitVelocity.x),hitQuad.q2.y - (hitPosition.y + hitVelocity.y) };
	// �I�_���ゾ������
	if (0 < GetDot(e, b)) {
		if (GetLength(hitVelocity) < t) {
			t = GetLength(hitVelocity);
		}
	}
	// �����̍ŋߖT�_�����߂�
	if (GetDot(a, e) / GetLength(hitVelocity) < t) {
		t = GetDot(a, e) / GetLength(hitVelocity);
	}

	// q3

	// �����̎n�_����_�܂ł̃x�N�g��
	a = { hitQuad.q3.x - hitPosition.x,hitQuad.q3.y - hitPosition.y };
	// �n�_���O��������
	if (GetDot(e, a) < 0) {
		t = 0;
	}

	// �����̏I�_����_�܂ł̃x�N�g��
	b = { hitQuad.q3.x - (hitPosition.x + hitVelocity.x),hitQuad.q3.y - (hitPosition.y + hitVelocity.y) };
	// �I�_���ゾ������
	if (0 < GetDot(e, b)) {
		if (GetLength(hitVelocity) < t) {
			t = GetLength(hitVelocity);
		}
	}
	// �����̍ŋߖT�_�����߂�
	if (GetDot(a, e) / GetLength(hitVelocity) < t) {
		t = GetDot(a, e) / GetLength(hitVelocity);
	}

	// q4

	// �����̎n�_����_�܂ł̃x�N�g��
	a = { hitQuad.q4.x - hitPosition.x,hitQuad.q4.y - hitPosition.y };
	// �n�_���O��������
	if (GetDot(e, a) < 0) {
		t = 0;
	}
	// �����̏I�_����_�܂ł̃x�N�g��
	b = { hitQuad.q4.x - (hitPosition.x + hitVelocity.x),hitQuad.q4.y - (hitPosition.y + hitVelocity.y) };
	// �I�_���ゾ������
	if (0 < GetDot(e, b)) {
		if (GetLength(hitVelocity) < t) {
			t = GetLength(hitVelocity);
		}
	}
	// �����̍ŋߖT�_�����߂�
	if (GetDot(a, e) / GetLength(hitVelocity) < t) {
		t = GetDot(a, e) / GetLength(hitVelocity);
	}
	//float t = GetDot(a, e);
	return { hitPosition.x + (hitVelocity.x * t),hitPosition.y + (hitVelocity.y * t) };
	//return { (1.0f - t) * hitPosition.x + t * (hitPosition.x + hitVelocity.x),(1.0f - t) * hitPosition.y + t * (hitPosition.y + hitVelocity.y) };
}

// ���̑�

/// <summary>
/// �l�� min ���� max �̒l�Ɏ��߂�֐�
/// </summary>
/// <param name="a">���߂�l</param>
/// <param name="min">�ŏ��l</param>
/// <param name="max">�ő�l</param>
/// <returns>�͈͓��̒l</returns>
float BaseMath::Clamp(float a, float min, float max) {
	if (a < min) {
		return min;
	}
	else if (max < a) {
		return max;
	}
	return a;
}


// �ł��߂��l���i�[�����z��̓Y���������߂�
static int getNearestValue(int v) {
	// �ϐ��̐錾
	v = BaseMath::Clamp(v, 0, 360);
	if (v < 45) {
		return 0;
	}
	else if (v < 90 + 45) {
		return 90;
	}
	else if (v < 180 + 45) {
		return 180;
	}
	else if (v < 270 + 45) {
		return 270;
	}
	else {
		return 0;
	}
}