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
	// ※　ワイヤーがじわじわ落下しちゃうバグ有り　※
	if (firstObject != NULL) {
		firstPosition->x += firstObject->GetVelocity().x;
		if (firstObject->GetisFlying()) {
			firstPosition->y += firstObject->GetVelocity().y;
		}

	}
	if (secondObject != NULL) {
		if (secondObject->GetType() == typePlayer) {
			*secondPosition = secondObject->GetCenterPosition();
		}
		
		secondPosition->x += secondObject->GetVelocity().x;
		if (secondObject->GetisFlying()) {
			secondPosition->y += secondObject->GetVelocity().y;
		}

	}
	// 刺さっておらず、射出されているときは速度を加算する
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
	Novice::ScreenPrintf(10, 50, "change");

}

// ワイヤーの当たり判定チェック用関数
// 引数：なし
// 返り値：ヒットした場合 ... true
//
// 今回はオブジェクト、もしくはマップチップに当たった場合にヒット判定
bool Wire::CheckHitBox(Point* _position, Object*& _object, ObjectManager* objectManager) {
	// 方向を取得
	Point velocity = { cosf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed,sinf(BaseMath::DegreetoRadian(ShotAngle)) * BaseConst::kWireSpeed };
	// 前フレームの位置を取得
	Point before = { _position->x - velocity.x,_position->y - velocity.y };
	_object = objectManager->CheckObjectHitBox(before, velocity);
	if (_object != NULL) {
		if (_object->GetType() != typePlayer) {
			return true;
		}
	}

	if (_object == NULL && MapManager::CheckHitBox(before)) {
		return true;
	}
	/*
	float variation = 0.01f;
	for (float i = 0; i < BaseConst::kWireSpeed; i += variation) {
		_object = objectManager->CheckObjectHitBox(before);
		if (_object != NULL && _object->GetType() != typePlayer) {
			return true;
		}
		before.x += e.x * variation;
		before.y += e.y * variation;
	}
	*/


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
				*secondPosition = secondObject->GetCenterPosition();
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

	// 一つ目の着弾点にベクトルを足す
	if (firstObject != NULL) {
		// 引き寄せる向きと強さを決定
		Point p = { 20,0 };

		if (firstObject->GetType() == typePlayer) {
			p = { 15,0 };
		}

		p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(*firstPosition, *secondPosition));

		firstObject->AddVelocity(p);
	}

	// 二つめの着弾点にベクトルを足す
	if (secondObject != NULL) {
		// 引き寄せる向きと強さを決定
		Point p = { 20,0 };
		
		if (secondObject->GetType() == typePlayer) {
			p = { 15,0 };
		}

		p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(*secondPosition, *firstPosition));

		secondObject->AddVelocity(p);
	}

	Initialize();

	/*
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
						//Point velocity = BaseMath::GetVector(*secondPosition, *firstPosition);

						// 引き寄せる向きと強さを決定
						Point p = { 10,0 };
						p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(*secondPosition, *firstPosition));

						secondObject->AddVelocity(p);
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
	*/
}
