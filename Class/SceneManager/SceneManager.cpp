#include "Class/SceneManager/SceneManager.h"

// コンストラクタ
SceneManager::SceneManager() {
	Initialize();
}
// デストラクタ
SceneManager::~SceneManager() {

}

// 初期化
void SceneManager::Initialize() {
	currentScene = new Title();
	isEnd = false;
}
// 更新
void SceneManager::Update() {

	// もしシーン推移が行われた場合
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
			currentScene = new GameClear();
			break;
		case sceneGameOver:
			break;
		case sceneEnd:
			isEnd = true;
			break;
		default:
			break;
	}

	// 更新
	currentScene->Update();
}
// 描画
void SceneManager::Draw() {
	currentScene->Draw();
}