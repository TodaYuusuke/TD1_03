#pragma once

////////////////////////////////////////////////////////////////////////////////
/////�@�@�N���X���m�Ȃǂŏ��̎󂯓n�����߂�ǂ������Ƃ��ɖ������󂯓n������N���X�@�@/////
////////////////////////////////////////////////////////////////////////////////

class PublicFlag {
public: // �S��static��public
	// �������iinline�L�q�j
	static void Initialize() {
		kBossisTurningAndCutWire = false;
		kisStaging = false;
		kBrokenConcretePlaySE = false;
	}

	// ���o���t���O
	static bool kisStaging;
	// �{�X����]���ŁA���C���[���؂鏈����ON�̊�true�ɂ���
	static bool kBossisTurningAndCutWire;
	// �}�b�v�`�b�v�j��SE�Đ��p�̃t���O
	static bool kBrokenConcretePlaySE;
};