#include "Debug.h"

// コンストラクタ
Debug::Debug() {

}
// デストラクタ
Debug::~Debug() {

}


// 初期化
void Debug::Initialize() {
	object.Initialize();
}
// 更新
void Debug::Update() {
	object.Update();
}
// 描画
void Debug::Draw() {
	object.Draw();
}