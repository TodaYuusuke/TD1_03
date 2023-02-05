#include "Class/SceneManager/Scene/TutorialStage.h"

// コンストラクタ
TutorialStage::TutorialStage() {
	Initialize();
}
// デストラクタ
TutorialStage::~TutorialStage() {

}



// 初期化
void TutorialStage::Initialize() {
	nextScene = sceneNone;

	PublicFlag::Initialize();

	ObjectHitBox::Initialize();
	MapManager::TutorialInitialize();
	objectManager.Initialize();
	wireManager.Initialize();

	objectManager.MakeNewObjectPlayer({ 100,700 }, &wireManager);

	middleBoss.Initialize(&objectManager);
}
// 更新
void TutorialStage::Update() {
	// 当たり判定の初期化
	EnemyAttackHitBox::Initialize();

	// デバッグ用
	if (BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
		nextScene = sceneBossStage;
	}
	// 定数のホットリロード
	if (BaseInput::GetKeyboardState(DIK_F1, Trigger)) {
		PublicFlag::Initialize();

		ObjectHitBox::Initialize();
		MapManager::TutorialInitialize();
	}

	MapManager::Update();
	//middleBoss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	objectManager.Update();
	wireManager.Update(&objectManager);
}
// 描画
void TutorialStage::Draw() {
	// デバッグ用
	Novice::ScreenPrintf(0, 0, "Push ENTER to Skip Stage");

	Point screenPosition = BaseDraw::GetScreenPosition();

	// 背景
	BaseDraw::DrawQuad({screenPosition.x + BaseConst::kWindowWidth / 2, screenPosition.y - BaseConst::kWindowHeight / 2 },
		BaseTexture::kBackGroundCity, {1920, 1080}, 1.1f, 0.0f, 0xFFFFFFFF);

	BaseDraw::DrawQuad({screenPosition.x + BaseConst::kWindowWidth / 2, screenPosition.y - BaseConst::kWindowHeight / 2 },
		BaseTexture::kBackGroundForest, {1920, 1080}, 1.1f, 0.0f, 0xFFFFFFFF);

	BaseDraw::DrawSprite(screenPosition, BaseTexture::kBackGroundFrame, {1.0f, 1.0f}, 0.0f, 0xFFFFFFFF);

	MapManager::Draw();

	middleBoss.Draw();

	objectManager.Draw();
	wireManager.Draw();
}