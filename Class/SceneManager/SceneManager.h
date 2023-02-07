#pragma once
#include "MyBase/MyBase.h"

#include "Class/SceneManager/Scene/BaseScene.h"
#include "Class/SceneManager/Scene/Title.h"
#include "Class/SceneManager/Scene/TutorialStage.h"
#include "Class/SceneManager/Scene/BossStage.h"
#include "Class/SceneManager/Scene/GameClear.h"

class SceneManager {
public: // �����o�֐�

	// �R���X�g���N�^
	SceneManager();
	// �f�X�g���N�^
	~SceneManager();

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Draw();


private: // �����o�ϐ�

	// ���݂̃V�[��
	BaseScene* currentScene;
};