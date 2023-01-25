 #include "Debug.h"

// コンストラクタ
Debug::Debug() {

}
// デストラクタ
Debug::~Debug() {

}


// 初期化
void Debug::Initialize() {
	MapManager::Initialize();
	objectManager.Initialize();
	wireManager.Initialize();
	objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
	boss.Initialize(&objectManager);
}
// 更新
void Debug::Update() {

	// 毎フレーム当たり判定を初期化
	EnemyAttackHitBox::Initialize();

	// Bキーでブロックを生成
	if (BaseInput::GetKeyboardState(DIK_B, Trigger)) {
		objectManager.MakeNewObjectBlock(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 50,50 });
	}

	// Rキーでリセット
	if (BaseInput::GetKeyboardState(DIK_R, Trigger)) {
		MapManager::Initialize();
		objectManager.Initialize();
		wireManager.Initialize();
		objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
		boss.Initialize(&objectManager);
	}

	// Eキーで雑魚的生成
	if (BaseInput::GetKeyboardState(DIK_E, Trigger)) {
		objectManager.MakeNewObjectEnemy(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 50,50 });
	}


	// スクリーン座標の移動量
	Point screenPosMove = BaseDraw::GetScreenPosition();
	if (BaseInput::GetKeyboardState(DIK_UP, Press)) {
		screenPosMove.y += 5;
	}
	if (BaseInput::GetKeyboardState(DIK_DOWN, Press)) {
		screenPosMove.y -= 5;
	}
	if (BaseInput::GetKeyboardState(DIK_RIGHT, Press)) {
		screenPosMove.x += 5;
	}
	if (BaseInput::GetKeyboardState(DIK_LEFT, Press)) {
		screenPosMove.x -= 5;
	}
	BaseDraw::SetScreenPosition(screenPosMove);

	MapManager::Update();
	boss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	objectManager.Update();
	wireManager.Update(&objectManager, &boss);
}
// 描画
void Debug::Draw() {

	MapManager::Draw();
	boss.Draw();
	objectManager.Draw();
	wireManager.Draw();
}