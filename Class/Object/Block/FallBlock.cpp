#include "Class/Object/Block/FallBlock.h"

// コンストラクタ
FallBlock::FallBlock(Point _centerPosition, bool isCanStub) {

	centerPosition = _centerPosition;
	//width = size.x;
	//if (width < 64) {
	width = 64;
	//}
	//height = size.y;
	//if (height < 64) {
	height = 64;
	//}
	this->isCanStub = isCanStub;

	Initialize();
}
// デストラクタ
FallBlock::~FallBlock() {

}

// 初期化
void FallBlock::SuccessorInitialize() {

	// 速度
	velocity = { 0,-22 };
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
void FallBlock::SuccessorUpdate() {
	if (!isAlive) {
		return;
	}

	// ワイヤーが刺さったら初期化
	if (isStub) {
		vanishFlame = BaseConst::kBlockVanishFlame;
		// ワイヤーが刺さらない場合の処理
		if (!isCanStub) {
			isStub = false;
		}
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
void FallBlock::Draw() {
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
ObjectType FallBlock::GetType() {
	return typeFallBlock;
}
