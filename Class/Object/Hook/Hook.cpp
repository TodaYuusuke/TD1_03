#include "Class/Object/Hook/Hook.h"

// コンストラクタ
Hook::Hook(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

	Initialize();
}
// デストラクタ
Hook::~Hook() {

}

// 初期化
void Hook::SuccessorInitialize() {

	// 速度
	velocity = { 0,0 };
	// 加速度
	acceleration = { 0,0 };

	// 回転角度（Degree）
	angle = 0;
	// 回転速度（Degree）
	angleVelocity = 0;

	//空中にいるかどうか
	isFlying = true;
	isAlive = true;
}
// 更新
void Hook::Update() {
	if (isAlive) {

	}
}

// 描画
void Hook::Draw() {
	if (isAlive) {
		Point temp = BaseDraw::ScreentoWorld({ centerPosition.x - width / 2.0f, centerPosition.y + height / 2.0f });
		Novice::DrawBox(temp.x, temp.y, width, height, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
	}
}

// タイプを取得
ObjectType Hook::GetType() {
	return typeHook;
}
