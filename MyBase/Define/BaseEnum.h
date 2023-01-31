#pragma once


////////////////////////////////////////////////
/* - �v���O�������Ɏg���S�Ă̗񋓎q���Ǘ�����N���X - */
////////////////////////////////////////////////


// �}�E�X�̃{�^��
enum MouseButton {
	// ���N���b�N
	LeftClick,
	// �E�N���b�N
	RightClick,
	// ���N���b�N
	MiddleClick,
	// �T�C�h�L�[
	SideKey1,
	SideKey2,
	SideKey3,
	SideKey4,
	SideKey5,
	SideKey6
};

// ���͂̏��
enum InputState {
	// ������Ă��Ȃ�
	Null,
	// �����ꂽ�u��
	Trigger,
	// �������ςȂ�
	Press,
	// �����ꂽ�u��
	Release
};

// �Q�[���V�[��
enum SceneState {
	// �����i�V�[���؂�ւ������j
	None,
	// �^�C�g��
	Title,
	// OP
	OP,
	// �X�e�[�W�I��
	StageSelect,
	// �Q�[���v���C
	GamePlay,
	// ���U���g�i�Q�[���I�[�o�[�j
	Result,
	// �Q�[���I���i�v���O�����I���j
	GameEnd
};


enum ObjectType {
	// �I�u�W�F�N�g
	typeObject,
	// �u���b�N
	typeBlock,
	// �v���C���[
	typePlayer,
	// �t�b�N
	typeHook,
	// �G
	typeEnemy,
	// �ǁi���C���[�̎��ʗp�j
	typeWall,
	// �{�X�̒��S��
	typeCore
};

// �R���g���[���[�{�^��
enum ControllerButton {
		kControllerButtonUp,	//!< XInput�̏ꍇ�A�\���L�[��
		kControllerButtonDown,	//!< XInput�̏ꍇ�A�\���L�[��
		kControllerButtonLeft,	//!< XInput�̏ꍇ�A�\���L�[��
		kControllerButtonRight,	//!< XInput�̏ꍇ�A�\���L�[�E
		kControllerButtonStart,	//!< XInput�̏ꍇ�ASTART
		kControllerButtonBack,	//!< XInput�̏ꍇ�ABACK
		kControllerButtonL3,	//!< XInput�̏ꍇ�AL3
		kControllerButtonR3,	//!< XInput�̏ꍇ�AR3
		kControllerButtonL1,	//!< XInput�̏ꍇ�AL1
		kControllerButtonR1,	//!< XInput�̏ꍇ�AR1
		kControllerButtonL2,	//!< XInput�̏ꍇ�AL2
		kControllerButtonR2,	//!< XInput�̏ꍇ�AR2
		kControllerButtonA,		//!< XInput�̏ꍇ�AA,
		kControllerButtonB,		//!< XInput�̏ꍇ�AB,
		kControllerButtonX,		//!< XInput�̏ꍇ�AX,
		kControllerButtonY,		//!< XInput�̏ꍇ�AY,
		kControllerButton16,
		kControllerButton17,
		kControllerButton18,
		kControllerButton19,
};

// Novice�ɐ錾����Ă���R�s�y
//// �Q�[���p�b�h�{�^��
//enum PadButton {
//	kPadButton0,  //!< XInput�̏ꍇ�A�\���L�[��
//	kPadButton1,  //!< XInput�̏ꍇ�A�\���L�[��
//	kPadButton2,  //!< XInput�̏ꍇ�A�\���L�[��
//	kPadButton3,  //!< XInput�̏ꍇ�A�\���L�[�E
//	kPadButton4,  //!< XInput�̏ꍇ�ASTART
//	kPadButton5,  //!< XInput�̏ꍇ�ABACK
//	kPadButton6,  //!< XInput�̏ꍇ�AL3
//	kPadButton7,  //!< XInput�̏ꍇ�AR3
//	kPadButton8,  //!< XInput�̏ꍇ�AL1
//	kPadButton9,  //!< XInput�̏ꍇ�AR1
//	kPadButton10, //!< XInput�̏ꍇ�AL2
//	kPadButton11, //!< XInput�̏ꍇ�AR2
//	kPadButton12, //!< XInput�̏ꍇ�AA,
//	kPadButton13, //!< XInput�̏ꍇ�AB,
//	kPadButton14, //!< XInput�̏ꍇ�AX,
//	kPadButton15, //!< XInput�̏ꍇ�AY,
//	kPadButton16,
//	kPadButton17,
//	kPadButton18,
//	kPadButton19,
//};