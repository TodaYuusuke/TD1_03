#include "Class/Include/Object/Block/Block.h"

// コンストラクタ
Block::Block(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	width = size.x;
	height = size.y;

}
// デストラクタ
Block::~Block() {

}

// 初期化
void Block::SuccessorInitialize() {

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;

	texture = BaseTexture::kDebugTexture;

}
// 更新
void Block::SuccessorUpdate() {

}
// 描画
void Block::Draw() {
	BaseDraw::DrawQuad(centerPosition, texture, { 100,100 }, 1.0f, 0.0f, WHITE);
}