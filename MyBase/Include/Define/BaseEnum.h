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