#include "Class/AttackHitBox/ObjectHitBox.h"

// 初期化
void ObjectHitBox::Initialize() {

	// 現在の添え字
	num = 0;

	// 当たり判定のリスト
	//for (int i = 0; i < 256; i++) {
	//	hitBox[i]->centerPosition = NULL;
	//	hitBox[i]->width = NULL;
	//	hitBox[i]->height = NULL;
	//	hitBox[i]->angle = NULL;
	//}
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
int ObjectHitBox::AddHitBox(Point* _centerPosition, float* _width, float* _height, float* _angle, bool* _isAlive) {
	if (num >= 256) {
		return -1;
	}

	centerPosition[num] = _centerPosition;
	width[num] = _width;
	height[num] = _height;
	angle[num] = _angle;
	isAlive[num] = _isAlive;

	return num++;
}

// 当たり判定検証
// 返り値：ヒットしていた場合 -> true、　ヒットしていない場合 -> false
// 引数：
// centerPosition ... 検証する座標
int ObjectHitBox::CheckHitBox(Point _centerPosition, int noCheck) {
	for (int i = 0; i < num; i++) {
		if (centerPosition[i] != NULL) {
			if (*isAlive[i]) {
				if (i != noCheck) {
					if (BaseMath::CheckHitBox(*centerPosition[i], *width[i], *height[i], *angle[i], _centerPosition)) {
						*isAlive[i] = false;
						BaseEffectManager::MakeNewEffectBlockBreak(*centerPosition[i]);
						return true;
					}
				}
			}
		}
	}
	return false;
}



// 現在の添え字
int ObjectHitBox::num;
// 当たり判定のリスト
Point* ObjectHitBox::centerPosition[256];
float* ObjectHitBox::width[256];
float* ObjectHitBox::height[256];
float* ObjectHitBox::angle[256];
bool* ObjectHitBox::isAlive[256];