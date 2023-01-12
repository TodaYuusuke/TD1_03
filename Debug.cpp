#include "Debug.h"

// コンストラクタ
Debug::Debug() {

}
// デストラクタ
Debug::~Debug() {

}


// 初期化
void Debug::Initialize() {
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
	// 右クリックでブロックを生成
	if (BaseInput::GetMouseState(MiddleClick, Trigger)) {
		wireManager.Attract();
	}

	if (BaseInput::GetKeyboardState(DIK_Q, Trigger)) {
		objectManager.MakeNewObjectPlayer({ 200,200 });
	}

	objectManager.Update();
	wireManager.Update(objectManager);
}
// 描画
void Debug::Draw() {
	objectManager.Draw();
	wireManager.Draw();
}