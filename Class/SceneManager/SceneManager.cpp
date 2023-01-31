#include "Class/SceneManager/SceneManager.h"

// �R���X�g���N�^
SceneManager::SceneManager() {
	Initialize();
}
// �f�X�g���N�^
SceneManager::~SceneManager() {

}

// ������
void SceneManager::Initialize() {
	currentScene = new Title();
}
// �X�V
void SceneManager::Update() {

	// �����V�[�����ڂ��s��ꂽ�ꍇ
	switch (currentScene->isGoNextScene())
	{
		case sceneNone:
			break;
		case sceneTitle:
			currentScene = new Title();
			break;
		case sceneOP:
			break;
		case sceneTutorialStage:
			currentScene = new TutorialStage();
			break;
		case sceneBossStage:
			currentScene = new BossStage();
			break;
		case sceneGameClear:
			break;
		case sceneGameOVer:
			currentScene = new GameClear();
			break;
		case sceneEnd:
			break;
		default:
			break;
	}

	// �X�V
	currentScene->Update();
}
// �`��
void SceneManager::Draw() {
	currentScene->Draw();
}