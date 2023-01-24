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
}
// 更新
void Hook::Update() {

}

// 描画
void Hook::Draw() {
	if (BaseMath::CheckHitBox(centerPosition, width, height, angle, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()))) {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, BLUE);
	}
	else {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, WHITE);
	}
}

// タイプを取得
ObjectType Hook::GetType() {
	return typeHook;
}
