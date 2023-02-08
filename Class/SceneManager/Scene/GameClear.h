#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class GameClear :
	public BaseScene {
public: // �����o�֐�

	// �R���X�g���N�^
	GameClear();
	// �f�X�g���N�^
	~GameClear();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �V�[���ύX��������֐�
	// �Ԃ�l�F�V�[���ύX���Ȃ��ꍇ ... None
	// �@�@�@�@�@�@�@�@�@�@����ꍇ ... �ύX��̃V�[��
	SceneState isGoNextScene() override {
		if (nextScene != sceneNone) {
			Novice::StopAudio(bgmHandle);
		}
		return nextScene;
	}

private: // �����o�ϐ�

	// �R���g���[�����܂߂����W
	Point reticlePosition;
	Point preMousePosition;
	// �X�^�[�g��I�����Ă��邩
	bool isToTitle;
	bool isToEnd;
	// �I��������
	bool isSelected;

	// �t�F�[�h�A�E�g�p
	int feedOutFlame;
	int feedInFlame;

	const int kFeedInMax = 60;
	const int kFeedOutMax = 60;


	// bgm�n���h��
	static int bgmHandle;
};