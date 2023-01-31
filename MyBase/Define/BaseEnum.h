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
	// �`���[�g���A���X�e�[�W
	TutorialStage,
	// �{�X�X�e�[�W
	BossStage,
	// �Q�[���N���A
	GameClear,
	// �Q�[���I�[�o�[
	GameOVer,
	// �Q�[���I���i�v���O�����I���j
	End
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