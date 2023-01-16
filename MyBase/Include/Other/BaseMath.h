#pragma once
#include "MyBase/Include/Define/BaseStruct.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "MyBase/Include/Other/BaseDraw.h"

////////////////////////////////////////////////////
/* - �v���O�������Ɏg���S�Ă̐��w�I�֐����Ǘ�����N���X - */
////////////////////////////////////////////////////

class BaseDraw;

class BaseMath
{

public:


	// �p�x�֘A


	// radian����degree�ɕϊ�����֐�
	// �Ԃ�l�Fdegree
	// �����F
	// radian ... radian�̊p�x
	// radian�̊p�x��degree�̊p�x�ɕϊ�����֐��B�����ŗv�������̂͊�{Degree�Ȃ̂ł��܂�g��Ȃ��B
	static float RadiantoDegree(float radian);

	// degree����radian�ɕϊ�����֐�
	// �Ԃ�l�Fradian
	// �����F
	// degree ... degree�̊p�x
	// degree�̊p�x��radian�̊p�x�ɕϊ�����֐��B�����ŗv�������̂͊�{Degree�Ȃ̂Ŋ֐����ł͎g����B
	static float DegreetoRadian(float degree);

	// 2�_�Ԃ̊p�x�idegree�j�����߂�֐�
	// �Ԃ�l�F2�_�̊p�x�idegree�j
	// �����F
	// from ... ���W�P
	// to ... ���W�Q
	// 2�_�̊p�x��Degree�Ŏ󂯎��֐��B
	static float GetDegree(Point from, Point to);


	// ��]����


	// Point�̉�]�v�Z�֐�
	// �Ԃ�l�F��]���Point
	// �����F
	// point ... �v�Z����Points
	// degree ... ��]�p�x�idegree�j
	// ���_���S�̉�]�����s���Ȃ��̂Œ���
	static Point TurnPoint(Point point, float degree);
	
	// Box�̉�]�v�Z�֐�
	// �Ԃ�l�F��]���Box
	// �����F
	// box ... �v�Z����Points
	// degree ... ��]�p�x�idegree�j
	// ���_���S�̉�]�����s���Ȃ��̂Œ���
	static Quad TurnBox(Quad box, float degree);


	// �����蔻�菈��

	// �l�p�`�Ɠ_�̓����蔻��`�F�b�N�i��]���l���\�A�����蔻��̎l�p�`�����g�̒��S�����_�ɉ�]���Ă���O��j
	// �Ԃ�l�F�q�b�g����true�A����ȊO��false
	// �����F
	// hitBoxCenterPosition ... �q�b�g�Ώۂ̎l�p�̒��S���W
	// hitBoxWidth ... �q�b�g�Ώۂ̉���
	// hitBoxHeight ... �q�b�g�Ώۂ̏c��
	// boxAngle ... �q�b�g�Ώۂ̎l�p�̉�]�p�x
	// hitPoisiton ... �q�b�g���Ă��邩���؂�����W
	static bool CheckHitBox(Point hitBoxCenterPosition, float hitBoxWidth, float hitBoxHeight, float boxAngle, Point hitPosition);

	// �l�p���m�̓����蔻��`�F�b�N
	static bool CheckHitBox(Box hitBox1, Box hitBox2);

};

