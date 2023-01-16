#include "Class/Include/Wire/Wire.h"

// コンストラクタ
Wire::Wire() {

	firstPosition = new Point();
	secondPosition = new Point();
}
// デストラクタ
Wire::~Wire() {

}

// 初期化
void Wire::Initialize() {
	*firstPosition = { -10000.0f, -10000.0f };
	*secondPosition = { -10000.0f, -10000.0f };

	firstObject = NULL;
	secondObject = NULL;

	firstisStab = false;
	secondisStab = false;

	wireState = NoneShot;
}
// 更新
void Wire::Update(ObjectManager* objectManager) {
	// オブジェクトに刺さっている、もしくはプレイヤーの場合に座標を入れる
	// 刺さっておらず、射出されているときは速度を加算する
	if (firstObject != NULL) {
		*firstPosition = firstObject->GetCenterPosition();
	}
	if (secondObject != NULL) {
		*secondPosition = secondObject->GetCenterPosition();
	}
	if (wireState == DoneShot) {
		// 一回目の射出中
		if (!firstisStab) {
			firstPosition->x += cosf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			firstPosition->y += sinf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			// どこかに刺さった場合
			if (CheckHitBox(firstPosition, firstObject, objectManager)) {
				wireState = NoneShot;
				firstisStab = true;
			}
		}
		// 二回目の射出中
		else if (!secondisStab) {
			secondPosition->x += cosf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			secondPosition->y += sinf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed;
			// どこかに刺さった場合
			if (CheckHitBox(secondPosition, secondObject, objectManager)) {
				wireState = NoneShot;
				secondisStab = true;
			}
		}
	}
}
// 描画
void Wire::Draw() {
	Novice::DrawLine(firstPosition->x, BaseDraw::WorldtoScreen(*firstPosition).y, secondPosition->x, BaseDraw::WorldtoScreen(*secondPosition).y, BLACK);
}

// ワイヤーの当たり判定チェック用関数
// 引数：なし
// 返り値：ヒットした場合 ... true
//
// 今回はオブジェクト、もしくは場外に当たった場合にヒット判定
bool Wire::CheckHitBox(Point* _position, Object*& _object, ObjectManager* objectManager) {
	_object = objectManager->CheckObjectHitBox(*_position);
	if (_object != NULL && _object->GetType() != typePlayer) {
		return true;
	}
	// 画面外に出た場合
	if (_position->x < 0 || BaseConst::kWindowWidth < _position->x) {
		return true;
	}
	if (_position->y < 0 || BaseConst::kWindowHeight < _position->y) {
		return true;
	}
	_object = NULL;
	return false;
}

// ワイヤー射出時に呼び出される関数
// 返り値がtrueのパターン：
// ・正常に射出できた場合
// 返り値がfalseのパターン：
// ・現在ワイヤーが射出中（まだ着弾していない）
// ・すでにワイヤーの着弾点が2点決まっている
//
// 引数：
// shotPosition ... ワイヤー射出地点
// shotAngle ... 発射角度（Degree）
//
// この関数が呼び出された後は、Updateにて着弾するまで弾の演算をし続けること。（ワイヤーの速度はBaseConst::kWireSpeed）
bool Wire::Shot(Point shotPosition, float shotAngle, Player* _player) {
	// 撃っていない時	: 初期化処理をして撃つ
	// 撃っている時		: 特に何もしない
	switch (wireState)
	{
	case Wire::NoneShot:
		// 一回目の射出をしていない時、かつ、壁などにくっついていない時
		if (!firstisStab) {
			*firstPosition = shotPosition;
			secondObject = _player;
			ShotAngle = shotAngle;
			wireState = DoneShot;
			return true;
		}
		// 一個目が刺さっている時
		else if (!secondisStab) {
			*secondPosition = shotPosition;
			secondObject = NULL;
			ShotAngle = shotAngle;
			wireState = DoneShot;
			return true;
		}
		break;
	case Wire::DoneShot:
		break;
	default:
		break;
	}
	return false;
}

// ワイヤー縮小時に呼び出される関数
// 返り値：なし
// 引数：なし
// 着弾点のObjectにベクトルを足す
void Wire::Attract() {
	// 一個目が刺さっていない、または、ワイヤーを射出中の時
	if (!firstisStab || wireState == DoneShot) {
		// ここで終わる
		return;
	}
	// 一個目が刺さっている時
	else {
		// 二個目も刺さっている時
		if (secondisStab) {
			// プレイヤーかブロックかを判別して処理を変える
			// ブロックに刺さっておらず、範囲外に刺さっているとき
			if (firstObject == NULL) {
				// 壁と壁に刺さっているとき
				if (secondObject == NULL) {
					// 壁同士、動かないもの同士の時は何もしない
					Initialize();

				}
				// 一個目が壁で二個目が壁以外の時
				else {
					// ブロック側を引き寄せる
					if (secondObject->GetType() == typeBlock) {
						Point velocity = BaseMath::GetVector(*secondPosition, *firstPosition);
						secondObject->AddVelocity(velocity);
						Initialize();
					}
				}
			}
			// 一個目が動くものに刺さっている時
			else {
				// 二個目が壁に刺さっている時
				if (secondObject == NULL) {
					// ブロック側を引き寄せる
					if (firstObject->GetType() == typeBlock) {
						Point velocity = BaseMath::GetVector(*firstPosition, *secondPosition);
						firstObject->AddVelocity(velocity);
						Initialize();
					}
				}
				// どちらも動くものに刺さっている時
				else {
					// ブロック側を引き寄せる
					if (firstObject->GetType() == typeBlock) {
						if (secondObject->GetType() == typeBlock) {
							Point velocity = BaseMath::GetVector(*firstPosition, *secondPosition);
							firstObject->AddVelocity(velocity);
							velocity = BaseMath::GetVector(*secondPosition, *firstPosition);
							secondObject->AddVelocity(velocity);
							Initialize();
						}
					}
				}
			}
		}
		// 一個目が壁に刺さっている時
		else if (firstObject == NULL) {
			// プレイヤー側を引き寄せる
			if (secondObject->GetType() == typePlayer) {
				Point velocity = BaseMath::GetVector(*secondPosition, *firstPosition);
				secondObject->AddVelocity(velocity);
				Initialize();
			}
		}
		// 一個目が動くものに刺さっている時
		else {
			// ブロック側を引き寄せる
			if (firstObject->GetType() == typeBlock) {
				Point velocity = BaseMath::GetVector(*firstPosition, *secondPosition);
				firstObject->AddVelocity(velocity);
				Initialize();
			}
		}
	}
}
