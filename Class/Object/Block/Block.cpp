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

	// 消滅フラグ
	vanishFlame = BaseConst::kBlockVanishFlame;

	// 当たり判定を外部に渡す
	num = ObjectHitBox::AddHitBox(&centerPosition, &width, &height, &angle, &isAlive);
}
// 更新
void Block::SuccessorUpdate() {
	if (!isAlive) {
		return;
	}
	// ワイヤーが刺さったら初期化
	if (isStub) {
		vanishFlame = BaseConst::kBlockVanishFlame;
	}
	// 刺さってなかったら減らす
	else {
		vanishFlame--;
	}
	if (vanishFlame < 0) {
		isAlive = false;
	}

}
// 描画
void Block::Draw() {
	if (!isAlive) {
		return;
	}
	// 三分の一以下なら 10 フレーム毎に点滅
	if (vanishFlame < BaseConst::kBlockBeVanish && vanishFlame % 10 == 0) {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kBlockTexture, { width,height }, 64.0f / width, angle, 0x777777FF);
	}
	else {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kBlockTexture, { width,height }, 64.0f / width, angle, WHITE);
	}
}

// タイプを取得
ObjectType Block::GetType() {
	return typeBlock;
}
