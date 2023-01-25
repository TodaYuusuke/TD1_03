#include "Class/Object/Block/Block.h"

// コンストラクタ
Block::Block(Point _centerPosition, Point size) {

	centerPosition = _centerPosition;
	//width = size.x;
	//if (width < 64) {
		width = 64;
	//}
	//height = size.y;
	//if (height < 64) {
		height = 64;
	//}

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
	angle = rand() % 360;
	// 回転速度（Degree）
	angleVelocity = 0;

	//空中にいるかどうか
	isFlying = true;
	isAlive = true;

	// 当たり判定を外部に渡す
	num = ObjectHitBox::AddHitBox(&centerPosition, &width, &height, &angle, &isAlive);
}
// 更新
void Block::SuccessorUpdate() {
	
}
// 描画
void Block::Draw() {
	if (!isAlive) {
		return;
	}

	BaseDraw::DrawQuad(centerPosition, BaseTexture::kBlockTexture, { width,height }, 64.0f / width, angle, WHITE);
}

// タイプを取得
ObjectType Block::GetType() {
	return typeBlock;
}
