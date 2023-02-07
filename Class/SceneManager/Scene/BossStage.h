#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class BossStage :
	public BaseScene{
public: // �����o�֐�

	// �R���X�g���N�^
	BossStage();
	// �f�X�g���N�^
	~BossStage();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private: // �����o�֐�

	// �Q�[���I�[�o�[���̏���
	void GameOverUpdate();
	// �Q�[���I�[�o�[���̏���
	void GameOverDraw();


private: // �����o�ϐ�

	ObjectManager objectManager;
	WireManager wireManager;
	Boss boss;

	// �Q�[���I�[�o�[���ǂ���
	bool isGameOver;
	// �Q�[���I�[�o�[���̔w�i
	int gameOverColor;
	// ���S����傫���Ȃ邽�߂̕ϐ�
	// 0 �` 1
	float gameOverT;
};