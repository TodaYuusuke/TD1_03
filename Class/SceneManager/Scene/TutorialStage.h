#pragma once
#include "MyBase/MyBase.h"
#include "Class/SceneManager/Scene/BaseScene.h"

class TutorialStage :
	public BaseScene{
public: // �����o�֐�

	// �R���X�g���N�^
	TutorialStage();
	// �f�X�g���N�^
	~TutorialStage();

	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private: // �֐�

	void CheckPlayerProgress();

	// �Q�[���I�[�o�[���̏���
	void GameOverUpdate();
	// �Q�[���I�[�o�[���̏���
	void GameOverDraw();

private: // �����o�ϐ�

	ObjectManager objectManager;
	WireManager wireManager;

	Player* player;

	MiddleBoss middleBoss;


	// �v���C���[�̐i�s�x�t���O
	int playerProgress;

	// �Q�[���I�[�o�[���ǂ���
	bool isGameOver;
	// �Q�[���I�[�o�[���̔w�i
	int gameOverColor;
	// ���S����傫���Ȃ邽�߂̕ϐ�
	// 0 �` 1
	float gameOverT;

};