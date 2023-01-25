#include "Class/AttackHitBox/ObjectHitBox.h"

// 初期化
void ObjectHitBox::Initialize() {

	// 現在の添え字
	num = 0;

	// 当たり判定のリスト
	for (int i = 0; i < 256; i++) {
		hitBox[i].centerPosition = NULL;
		hitBox[i].width = 0;
		hitBox[i].height = 0;
		hitBox[i].angle = 0;
	}
}
// 更新
void ObjectHitBox::Update() {
	// なし
}
// 描画
void ObjectHitBox::Draw() {
	// なし
}

// 新しく当たり判定を追加する関数（四角）
// 引数：
// centerPosition ... 真ん中の座標
// width ... ヒットボックスの横幅（左上の点から）
// height ... ヒットボックスの縦幅（左上の点から）
// angle ... ヒット対象の四角の回転角度
int ObjectHitBox::AddHitBox(Point* centerPosition, float* width, float* height, float* angle) {
	if (num >= 256) {
		return -1;
	}

	hitBox[num].centerPosition = centerPosition;
	hitBox[num].width = width;
	hitBox[num].height = height;
	hitBox[num].angle = angle;

	return num++;
}

// 当たり判定検証
// 返り値：ヒットしていた場合 -> true、　ヒットしていない場合 -> false
// 引数：
// centerPosition ... 検証する座標
bool ObjectHitBox::CheckHitBox(Point centerPosition, int noCheck) {
	for (int i = 0; i < num; i++) {
		if (hitBox[i].centerPosition != NULL) {
			if (i != noCheck) {
				if (BaseMath::CheckHitBox(*hitBox[i].centerPosition, *hitBox[i].width, *hitBox[i].height, *hitBox[i].angle, centerPosition)) {
					return true;
				}
			}
		}
	}
	return false;
}



// 現在の添え字
int ObjectHitBox::num;
// 当たり判定のリスト
ObjectHitBox::HitBox ObjectHitBox::hitBox[256];