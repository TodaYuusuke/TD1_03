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

private: // �����o�ϐ�

	ObjectManager objectManager;
	WireManager wireManager;

	Player* player;

	MiddleBoss middleBoss;
};