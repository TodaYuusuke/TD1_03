 #include "Debug.h"

// コンストラクタ
Debug::Debug() {

}
// デストラクタ
Debug::~Debug() {

}


// 初期化
void Debug::Initialize() {
	PublicFrag::Initialize();
	ObjectHitBox::Initialize();
	MapManager::Initialize();
	objectManager.Initialize();
	wireManager.Initialize();
	objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
	boss.Initialize(&objectManager);
}
// 更新
void Debug::Update() {

	Novice::ScreenPrintf(0, 0, "Move ... WASD");
	Novice::ScreenPrintf(0, 20, "SPACE ... JAMP");
	Novice::ScreenPrintf(0, 40, "SHOT WIRE ... LEFTCLICK");
	Novice::ScreenPrintf(0, 60, "ATTARACT ... RIGHTCLICK");
	Novice::ScreenPrintf(0, 80, "RESTART ... R");

	// 毎フレーム当たり判定を初期化
	EnemyAttackHitBox::Initialize();

	// Bキーでブロックを生成
	if (BaseInput::GetKeyboardState(DIK_B, Trigger)) {
		//objectManager.MakeNewObjectBlock(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 50,50 });
	}

	// Rキーでリセット
	if (BaseInput::GetKeyboardState(DIK_R, Trigger)) {
		ObjectHitBox::Initialize();
		MapManager::Initialize();
		objectManager.Initialize();
		wireManager.Initialize();
		objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
		boss.Initialize(&objectManager);
	}

	// Eキーで雑魚的生成
	if (BaseInput::GetKeyboardState(DIK_E, Trigger)) {
		//objectManager.MakeNewObjectEnemy(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 50,50 });
	}

	MapManager::Update();
	boss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	objectManager.Update();
	wireManager.Update(&objectManager);
}
// 描画
void Debug::Draw() {

	MapManager::Draw();
	boss.Draw();
	objectManager.Draw();
	wireManager.Draw();

	Novice::DrawEllipse(BaseInput::GetMousePosition().x, BaseInput::GetMousePosition().y, 2, 2, 0, GREEN, kFillModeWireFrame);
	Novice::DrawEllipse(BaseInput::GetMousePosition().x, BaseInput::GetMousePosition().y, 10, 10, 0, GREEN, kFillModeWireFrame);
	Novice::DrawEllipse(BaseInput::GetMousePosition().x, BaseInput::GetMousePosition().y, 11, 11, 0, GREEN, kFillModeWireFrame);
	Novice::DrawEllipse(BaseInput::GetMousePosition().x, BaseInput::GetMousePosition().y, 12, 12, 0, GREEN, kFillModeWireFrame);
}