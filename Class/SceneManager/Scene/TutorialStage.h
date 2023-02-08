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
	void Initialize(int);
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

	// �V�[���ύX��������֐�
	// �Ԃ�l�F�V�[���ύX���Ȃ��ꍇ ... None
	// �@�@�@�@�@�@�@�@�@�@����ꍇ ... �ύX��̃V�[��
	SceneState isGoNextScene() override {
		if (nextScene != sceneNone) {
			if (BaseEffectManager::isEndEffect(fadeEnd)) {
				Novice::StopAudio(bgmHandle);
				return nextScene;
			}
		}
		return sceneNone;
	}

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


	// �O��̃X�N���[�����W
	float preScrollPositionX;
	// �w�i�X�N���[���p
	float backGroundPositionX[3];


	// ���X�|�[���n�_�̃t���O
	int respawnProgress;
	// ���o�p�̃t���O
	int gimmickProgress;
	// �l�I���p�o�߃t���[��
	int neonFrame;
	
	// �R���g���[�����܂߂����W
	Point reticlePosition;
	Point preMousePosition;

	// �Q�[���I�[�o�[���ǂ���
	bool isGameOver;
	// �Q�[���I�[�o�[���̔w�i
	int gameOverColor;
	// ���S����傫���Ȃ邽�߂̕ϐ�
	// 0 �` 1
	float gameOverT;
	// �^�C�g���ց`��I�����Ă��邩
	bool isToTitle;
	// ���g���C��I�����Ă��邩
	bool isToRetry;

	// �t�F�[�h�C���A�E�g�m�F�p�t���O
	int fadeEnd;
	// bgm�n���h��
	static int bgmHandle;
};