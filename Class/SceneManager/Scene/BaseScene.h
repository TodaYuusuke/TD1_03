#pragma once
#include "MyBase/MyBase.h"

class BaseScene {
public: // �����o�֐�

	// ������
	virtual void Initialize() {
		nextScene = sceneNone;
	}
	// �X�V
	virtual void Update() {

	}
	// �`��
	virtual void Draw() {

	}

	// �V�[���ύX��������֐�
	// �Ԃ�l�F�V�[���ύX���Ȃ��ꍇ ... None
	// �@�@�@�@�@�@�@�@�@�@����ꍇ ... �ύX��̃V�[��
	SceneState isGoNextScene() {
		return nextScene;
	}


protected: // �����o�ϐ�

	// ���̃V�[��
	SceneState nextScene;
};