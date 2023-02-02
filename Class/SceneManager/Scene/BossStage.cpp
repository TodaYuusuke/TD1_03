#include "Class/SceneManager/Scene/BossStage.h"

// コンストラクタ
BossStage::BossStage() {
	Initialize();
}
// デストラクタ
BossStage::~BossStage() {

}



// 初期化
void BossStage::Initialize() {
	nextScene = sceneNone;

	PublicFlag::Initialize();
	ObjectHitBox::Initialize();
	MapManager::BossInitialize();
	objectManager.Initialize();
	wireManager.Initialize();
	objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
	boss.Initialize(&objectManager);
}
// 更新
void BossStage::Update() {
	// 当たり判定が更新
	EnemyAttackHitBox::Initialize();

	MapManager::Update();
	boss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	objectManager.Update();
	wireManager.Update(&objectManager);
}
// 描画
void BossStage::Draw() {

	MapManager::Draw();
	boss.Draw();
	objectManager.Draw();
	wireManager.Draw();

	// デバックの操作方法テクスチャ
	int debugMoveTex = Novice::LoadTexture("./Resources/Texture/Debug/Move.png");
	int debugShotTex = Novice::LoadTexture("./Resources/Texture/Debug/Shot.png");
	int debugJumpTex = Novice::LoadTexture("./Resources/Texture/Debug/Jump.png");
	int debugAttractTex = Novice::LoadTexture("./Resources/Texture/Debug/Attract.png");
	int debugBGTex = Novice::LoadTexture("./Resources/Texture/Debug/BG.png");
	int debugHPTex = Novice::LoadTexture("./Resources/Texture/Debug/HP.png");

	Novice::DrawSprite(1280, 10, debugBGTex, 10, 0.5f, 0, WHITE);
	// 動作方法
	Novice::DrawSprite(1280, 10, debugMoveTex, 0.25f, 0.25f, 0.0f, WHITE);
	Novice::DrawSprite(1600, 10, debugJumpTex, 0.25f, 0.25f, 0.0f, WHITE);
	Novice::DrawSprite(1280, 42, debugShotTex, 0.25f, 0.25f, 0.0f, WHITE);
	Novice::DrawSprite(1600, 42, debugAttractTex, 0.25f, 0.25f, 0.0f, WHITE);

	Novice::DrawSprite(620, 10, debugHPTex, 0.5f, 0.5f, 0, WHITE);
}