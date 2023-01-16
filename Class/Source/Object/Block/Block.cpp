#include "Class/Include/Object/Block/Block.h"

// コンストラクタ
Block::Block(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

	Initialize();
}
// デストラクタ
Block::~Block() {

}

// 初期化
void Block::SuccessorInitialize() {

	// 速度
	velocity = { 0,0 };
	// 加速度
	acceleration = { 0,0 };

	// 回転角度（Degree）
	angle = 15;
	// 回転速度（Degree）
	angleVelocity = 0;

	//空中にいるかどうか
	isFlying = true;
}
// 更新
void Block::SuccessorUpdate() {

}
// 描画
void Block::Draw() {
	if (BaseMath::CheckHitBox(centerPosition, width, height, angle, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()))) {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, BLUE);
	}
	else {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { width,height }, 1.0f, angle, WHITE);
	}
}

// タイプを取得
ObjectType Block::GetType() {
	return typeBlock;
}
