#include "EnemyAttackHitBox.h"

// 初期化
void EnemyAttackHitBox::Initialize() {

	// 現在の添え字
	num = 0;

	// 当たり判定のリスト
	for (int i = 0; i < 128; i++) {
		hitBox[i].centerPosition = { -15000,-15000 };
		hitBox[i].width = 0;
		hitBox[i].height = 0;
		hitBox[i].angle = 0;
		hitBox[i].atk = 0;
	}

	// 左の半円の当たり判定
	leftEllipse.centerPosition = { -15000,-15000 };
	leftEllipse.radius = 0;
	leftEllipse.angle = 0;
	leftEllipse.atk = 0;
	// 右の半円の当たり判定
	rightEllipse.centerPosition = { -15000,-15000 };
	rightEllipse.radius = 0;
	rightEllipse.angle = 0;
	rightEllipse.atk = 0;
}
// 更新
void EnemyAttackHitBox::Update() {
	// なし
}
// 描画
void EnemyAttackHitBox::Draw() {
	// なし
	// 
	// デバッグ用
	// 当たり判定のリスト
	for (int i = 0; i < num; i++) {
		Novice::DrawBox(
			BaseDraw::WorldtoScreen(hitBox[i].centerPosition).x,
			BaseDraw::WorldtoScreen(hitBox[i].centerPosition).y,
			hitBox[i].width,
			hitBox[i].height,
			hitBox[i].angle,
			WHITE,
			kFillModeWireFrame
		);
	}
}



// 新しく当たり判定を追加する関数（四角）
// 引数：
// centerPosition ... 真ん中の座標
// width ... ヒットボックスの横幅（左上の点から）
// height ... ヒットボックスの縦幅（左上の点から）
// angle ... ヒット対象の四角の回転角度
// atk ... ダメージ量
void EnemyAttackHitBox::MakeNewHitBox(Point centerPosition, float width, float height, float angle, float atk) {
	if (num >= 128) {
		return;
	}
	
	hitBox[num].centerPosition = centerPosition;
	hitBox[num].width = width;
	hitBox[num].height = height;
	hitBox[num].angle = angle;
	hitBox[num].atk = atk;

	num++;
}

// 新しく当たり判定を追加する関数（左の円）
// 引数：
// centerPosition ... 真ん中の座標
// width ... ヒットボックスの横幅（左上の点から）
// height ... ヒットボックスの縦幅（左上の点から）
// angle ... ヒット対象の四角の回転角度
// atk ... ダメージ量
void EnemyAttackHitBox::MakeNewHitBoxLeft(Point centerPosition, float radius, float angle, float atk) {
	leftEllipse.centerPosition = centerPosition;
	leftEllipse.radius = radius;
	leftEllipse.angle = angle;
	leftEllipse.atk = atk;
}
// 新しく当たり判定を追加する関数（右の円）
// 引数：
// centerPosition ... 真ん中の座標
// width ... ヒットボックスの横幅（左上の点から）
// height ... ヒットボックスの縦幅（左上の点から）
// angle ... ヒット対象の四角の回転角度
// atk ... ダメージ量
void EnemyAttackHitBox::MakeNewHitBoxRight(Point centerPosition, float radius, float angle, float atk) {
	rightEllipse.centerPosition = centerPosition;
	rightEllipse.radius = radius;
	rightEllipse.angle = angle;
	rightEllipse.atk = atk;
}


// 当たり判定検証
// 返り値：ヒットしていた場合 -> 被ダメージ量、　ヒットしていない場合 -> -1
// 引数：
// centerPosition ... 検証する座標
float EnemyAttackHitBox::CheckHitBox(Point centerPosition) {
	for (int i = 0; i < num; i++) {
		if (BaseMath::CheckHitBox(hitBox[i].centerPosition, hitBox[i].width, hitBox[i].height, hitBox[i].angle, centerPosition)) {
			return hitBox[i].atk;
		}
	}
	return -1;
}

// 当たり判定検証
// 返り値：ヒットしていた場合 -> 被ダメージ量、　ヒットしていない場合 -> -1
// 引数：
// centerPosition ... 検証する座標
float EnemyAttackHitBox::CheckHitEllipse(Point centerPosition) {

	// 半円のどちらかにヒットしていた場合 -> atkを返す


	// ヒットしていた場合
	return -1;
}




// 現在の添え字
int EnemyAttackHitBox::num;
// 当たり判定のリスト
EnemyAttackHitBox::HitBox EnemyAttackHitBox::hitBox[128];
// 左の半円の当たり判定
EnemyAttackHitBox::HitEllipse EnemyAttackHitBox::leftEllipse;
// 右の半円の当たり判定
EnemyAttackHitBox::HitEllipse EnemyAttackHitBox::rightEllipse;