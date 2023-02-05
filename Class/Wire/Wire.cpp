#include "Class/Wire/Wire.h"

// コンストラクタ
Wire::Wire() {
	Initialize();
}
// デストラクタ
Wire::~Wire() {

}

// 初期化
void Wire::Initialize() {

	// 生存フラグをfalseに（撃たれた時にtrueへ）
	isAlive = false;

	// 前フレームの座標
	prePosition[0] = { -10000.0f, -10000.0f };
	prePosition[1] = { -10000.0f, -10000.0f };
	// 座標
	position[0] = { -10000.0f, -10000.0f };
	position[1] = { -10000.0f, -10000.0f };
	// 着地点のオブジェクト
	object[0] = NULL;
	object[1] = NULL;
	// 着地点のオブジェクトのタイプ
	type[0] = typeObject;
	type[1] = typeObject;
	// ワイヤーの状態
	isShot[0] = false;
	isShot[1] = false;

	// 射出角度（degree）
	shotAngle = 0;
}

// 更新
void Wire::Update(ObjectManager* objectManager) {

	// もしワイヤーの長さが一定以上になった場合 ... 初期化
	if (BaseMath::GetLength({ position[1].x - position[0].x, position[1].y - position[0].y }) >= BaseConst::kWireMaxLength) {
		Initialize();
	}

	for (int i = 0; i < 2; i++) {

		// 発射されている場合の更新処理
		if (isShot[i]) {

			// 100分割して速度を計算することで、トンネリング防止
			for (int j = 0; j < 100; j++) {
				// 速度を追加
				Point p = BaseMath::TurnPoint({ BaseConst::kWireSpeed, 0 }, shotAngle);
				p.x *= 0.01f;
				p.y *= 0.01f;
				position[i].x += p.x;
				position[i].y += p.y;

				// 当たり判定チェック
				if (CheckHitBox(position[i], i, objectManager)) {
					// 壁じゃないときは座標を取る
					if (type[i] != typeWall) {
						//position[i].x = object[i]->GetCenterPosition().x;
						//position[i].y = object[i]->GetCenterPosition().y;
						prePosition[i].x = object[i]->GetCenterPosition().x;
						prePosition[i].y = object[i]->GetCenterPosition().y;
					}
					isShot[i] = false;
					break;
				}
			}
		}
		// 発射されている状態ではない　かつ　壁ではなくオブジェクトにヒットしている場合
		else if (object[i] != NULL) {
			if (type[i] != typeWall) {

				// ワイヤーを切る処理を行っている場合 -> objectがHookの場合切る
				if (PublicFlag::kBossisTurningAndCutWire) {
					if (type[i] == typeHook) {
						Initialize();
						return;
					}
				}

				// オブジェクトが死んだ場合 -> ワイヤーを切る
				if (!object[i]->GetisAlive()) {
					Initialize();
					return;
				}

				position[i].x -= prePosition[i].x - object[i]->GetCenterPosition().x;
				position[i].y -= prePosition[i].y - object[i]->GetCenterPosition().y;
				prePosition[i].x = object[i]->GetCenterPosition().x;
				prePosition[i].y = object[i]->GetCenterPosition().y;
			}
		}

	}
}
// 描画
void Wire::Draw() {

	Point p[2] = { BaseDraw::WorldtoScreen(position[0]),BaseDraw::WorldtoScreen(position[1]) };

	// 線を描画
	Novice::DrawLine(p[0].x, p[0].y, p[1].x, p[1].y, WHITE);
}



// ワイヤーの生存フラグを返す
bool Wire::GetisAlive() {
	return isAlive;
}

// ワイヤーの当たり判定チェック用関数
// 引数：なし
// 返り値：ヒットした場合 ... true
//
// 今回はオブジェクト、もしくはマップチップに当たった場合にヒット判定
bool Wire::CheckHitBox(Point _position, int i, ObjectManager* objectManager) {

	// ボスの外殻に当たっていないか
	if (EnemyAttackHitBox::CheckHitEllipse(_position) != -1) {
		Initialize();
		return false;
	}

	// オブジェクトにヒットしているか検証
	object[i] = objectManager->CheckObjectHitBox(_position);
	if(object[i] != NULL && object[i]->GetType() != typePlayer && object[i] != object[!i] && !(object[i]->GetType() == typeHook && type[!i] == typeHook)) {
		// ヒットしていた場合 -> 戻る
		type[i] = object[i]->GetType();
		object[i]->SetisStub(true);
		// SEを再生
		Novice::PlayAudio(BaseAudio::kWireHit, 0, 0.5f);
		return true;
	}
	// 壁にヒットしているか検証
	else if (MapManager::CheckHitBox(_position)) {
		// ヒットしていた場合
		type[i] = typeWall;
		// SEを再生
		Novice::PlayAudio(BaseAudio::kWireHit, 0, 0.5f);
		return true;
	}


	object[i] = NULL;
	return false;
}

// ワイヤー射出時に呼び出される関数
// 返り値がtrueのパターン：
// ・正常に射出できた場合 = 1
// 返り値がfalseのパターン：
// ・現在ワイヤーが射出中（まだ着弾していない） = -1
// ・すでにワイヤーの着弾点が2点決まっている = -2
//
// 引数：
// shotPosition ... ワイヤー射出地点
// shotAngle ... 発射角度（Degree）
//
// この関数が呼び出された後は、Updateにて着弾するまで弾の演算をし続けること。（ワイヤーの速度はBaseConst::kWireSpeed）
int Wire::Shot(Point shotPosition, float shotAngle, Player* _player) {
	// 撃っていない時	: 初期化処理をして撃つ
	// 撃っている時		: 特に何もしない

	// 発射中はfalseを返す
	if (isShot[0] || isShot[1]) {
		return -1;
	}

	// １発目がまだ発射されていない　かつ　まだ着弾していない場合
	if (!isShot[0] && object[0] == NULL && type[0] != typeWall) {
		// １発目の初期化
		prePosition[0] = shotPosition;
		// 座標
		position[0] = shotPosition;
		// ワイヤーの状態
		isShot[0] = true;
		// 射出角度（degree）
		this->shotAngle = shotAngle;

		// ２発目の初期化
		prePosition[1] = shotPosition;
		// 座標
		position[1] = shotPosition;
		// オブジェクト
		object[1] = _player;
		// タイプ
		type[1] = typePlayer;

		return 1;
	}
	// １発目が着弾済み　かつ　２発目がまだ発射されていない　かつ　２発目がまだ着弾していない場合
	//else if ((object[0] != NULL || type[0] == typeWall) && !isShot[1] && object[1]->GetType() == typePlayer) {
	else if ((object[0] != NULL || type[0] == typeWall) && !isShot[1] && ((object[1] == NULL && type[1] != typeWall) || type[1] == typePlayer)) {
		// ワイヤーの状態
		isShot[1] = true;
		// 着弾情報をNULLに
		object[1] = NULL;

		// 射出角度（degree）
		this->shotAngle = shotAngle;

		return 1;
	}

	return -2;
}

// ワイヤー縮小時に呼び出される関数
// 返り値：なし
// 引数：なし
// 着弾点のObjectにベクトルを足す
void Wire::Attract() {

	// どちらかが射出中の場合 -> 戻る
	if (isShot[0] || isShot[1]) {
		return;
	}
	// 着弾していない場合 -> 戻る
	if (type[0] == typeObject && type[1] == typeObject) {
		return;
	}


	// 特別な判定

	// もし片方が壁で、片方がHookの場合
	if ((type[0] == typeHook && type[1] == typeWall) || (type[1] == typeHook && type[0] == typeWall)) {
		for (int i = 0; i < 2; i++) {
			if (type[i] == typeHook) {
				object[i]->SetisPulled(true);
				object[i]->SetisStub(false);
				return;
			}
		}
	}


	// 一つ目のオブジェクトにベクトルを足す
	if (object[0] != NULL ) {
		// 引き寄せる強さを決定
		Point p = { 20,0 };

		if (object[0]->GetType() == typeBlock) {
			p = { 40,0 };
		}

		p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(position[0], position[1]));

		// ベクトルが下方向の場合 -> すこし上方向に補正
		if (type[0] != typePlayer) {
			if (p.y < 3) {
				p.y = 3;
			}
		}

		object[0]->SetisPulled(true);
		object[0]->SetisStub(false);
		object[0]->AddVelocity(p);
	}
	// 二つ目のオブジェクトにベクトルを足す
	if (object[1] != NULL) {
		// 引き寄せる強さを決定
		Point p = { 20,0 };

		if (object[1]->GetType() == typeBlock) {
			p = { 40,0 };
		}

		p = BaseMath::TurnPoint(p, -BaseMath::GetDegree(position[1], position[0]));

		// ベクトルが下方向の場合 -> すこし上方向に補正
		if (type[1] != typePlayer) {
			if (p.y < 3) {
				p.y = 3;
			}
		}

		object[1]->SetisPulled(true);
		object[1]->SetisStub(false);
		object[1]->AddVelocity(p);
	}

	// ワイヤーを初期化
	Initialize();
	// SEを再生
	Novice::PlayAudio(BaseAudio::kWireCut, 0, 0.5f);
}
