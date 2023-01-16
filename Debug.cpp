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
}
// 更新
void Debug::Update() {

	// 中クリックでブロックを生成
	if (BaseInput::GetMouseState(MiddleClick, Trigger)) {
		objectManager.MakeNewObjectBlock(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 50,50 });
	}
	// 左クリックでワイヤーを射出（射出地点は100,100で固定）
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		//wireManager.Shot({ 100,100 }, BaseMath::GetDegree({ 100,100 }, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition())),);
	}

	if (BaseInput::GetKeyboardState(DIK_Q, Trigger)) {
		objectManager.MakeNewObjectPlayer({ 200,200 });
	}

	// Rキーでリセット
	if (BaseInput::GetKeyboardState(DIK_R, Trigger)) {
		MapManager::Initialize();
		objectManager.Initialize();
		wireManager.Initialize();
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
	objectManager.Update();
	wireManager.Update(&objectManager);
}
// 描画
void Debug::Draw() {

	MapManager::Draw();
	objectManager.Draw();
	wireManager.Draw();
}