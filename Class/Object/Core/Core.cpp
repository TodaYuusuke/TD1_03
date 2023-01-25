#include "Class/Object/Core/Core.h"

// コンストラクタ
Core::Core(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

	Initialize();
}
// デストラクタ
Core::~Core() {

}

// 初期化
void Core::SuccessorInitialize() {

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
	isPulled = false;

	pullCount = 0;
}
// 更新
void Core::Update() {
	if (isAlive) {
		if (isPulled) {
			if (30 < pullCount) {
				// 引っ張られた直後の処理


				pullCount = 0;
				isPulled = false;
			}
			else {
				pullCount++;
			}
		}
	}
}

// 描画
void Core::Draw() {
	if (isAlive) {
		Point temp = BaseDraw::WorldtoScreen({ centerPosition.x - width / 2.0f, centerPosition.y + height / 2.0f });
		if (isPulled) {
			Novice::DrawBox(temp.x, temp.y, width, height, 0.0f, 0xAA0000FF, kFillModeWireFrame);
		}
		else {
			Novice::DrawBox(temp.x, temp.y, width, height, 0.0f, 0xFFFFFFFF, kFillModeWireFrame);
		}
	}
}

// タイプを取得
ObjectType Core::GetType() {
	return typeCore;
}
