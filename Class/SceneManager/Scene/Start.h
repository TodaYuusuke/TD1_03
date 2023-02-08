#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class Start :
	public BaseScene {
public: // �����o�֐�

	// �R���X�g���N�^
	Start();
	// �f�X�g���N�^
	~Start();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	SceneState isGoNextScene() override {
		return sceneTitle;
	}

private: // �����o�ϐ�
};