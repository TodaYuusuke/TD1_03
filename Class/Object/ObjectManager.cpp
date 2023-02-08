#include "Class/Object/ObjectManager.h"

// 初期化
// 全てのオブジェクトの実態を（Objectで）初期化
void ObjectManager::Initialize() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		object[i] = new Object();
		object[i]->Initialize();
	}
}
// 更新
// 全てのオブジェクトを更新（Updateを呼び出す）
void ObjectManager::Update() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() != typeObject && object[i]->GetType() != typePlayer) {
			object[i]->Update();
		}
	}

	// プレイヤーの更新は最後に行う
	Player* p = (Player*)GetSelectObject(typePlayer);
	p->Update();
}
// 描画
// 全てのオブジェクトを描画（Drawを呼び出す）
void ObjectManager::Draw() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() != typeObject && object[i]->GetType() != typePlayer) {
			object[i]->Draw();
		}
	}

	// プレイヤーの更新は最後に行う
	Player* p = (Player*)GetSelectObject(typePlayer);
	p->Draw();
}



// 新しいオブジェクトのインスタンスを生成する関数たち
// 中の実態がObjectのものを若い数字優先で上書きしていく


// Block
void ObjectManager::MakeNewObjectBlock(Point position, Point size) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (!object[i]->GetisAlive()) {
			object[i] = new Block(position, size);
			object[i]->Initialize();
			break;
		}
	}
}
void ObjectManager::MakeNewObjectFallBlock(Point position, bool isCanStub) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (!object[i]->GetisAlive()) {
			object[i] = new FallBlock(position, isCanStub);
			object[i]->Initialize();
			break;
		}
	}
}


// Player
void ObjectManager::MakeNewObjectPlayer(Point position, WireManager* wireManager) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		// 生成されていたら生成しない
		if (object[i]->GetType() == typePlayer) {
			break;
		}
		if (!object[i]->GetisAlive()) {
			object[i] = new Player(position, wireManager);
			object[i]->Initialize();
			break;
		}
	}
}


// Hook
Object* ObjectManager::MakeNewObjectHook(Point position, Point size) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (!object[i]->GetisAlive()) {
			object[i] = new Hook(position, size);
			object[i]->Initialize();
			return object[i];
		}
	}
	return NULL;

}

// Core
Object* ObjectManager::MakeNewObjectCore(Point position, Point size) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (!object[i]->GetisAlive()) {
			object[i] = new Core(position, size);
			object[i]->Initialize();
			return object[i];
		}
	}
	return NULL;

}


// Enemy
void ObjectManager::MakeNewObjectBalloon(Point position) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (!object[i]->GetisAlive()) {
			object[i] = new Balloon(position, { 50,50 }, GetSelectObject(typePlayer));
			object[i]->Initialize();
			break;
		}
	}
}
void ObjectManager::MakeNewObjectIronBalloon(Point position) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (!object[i]->GetisAlive()) {
			object[i] = new IronBalloon(position, { 50,50 }, GetSelectObject(typePlayer));
			object[i]->Initialize();
			break;
		}
	}
}


// 全ての雑魚敵を消去する
void ObjectManager::DeleteAllEnemy() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeBalloon || object[i]->GetType() == typeIronBalloon) {
			object[i]->SetisAlive(false);
		}
	}
}


// オブジェクトの当たり判定をチェックする関数
// 返り値：そのオブジェクトのポインタ
// 引数：チェックするPoint
//
// ひとつもヒットしていない場合はNULLを返す（この関数を使う場合は必ずNULLチェックをすること！）
Object* ObjectManager::CheckObjectHitBox(Point hitPosition) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			continue;
		}
		if (object[i]->CheckHitBox(hitPosition)) {
			return object[i];
		}
	}
	return NULL;
}

/// <summary>
/// オブジェクトの当たり判定をチェックする関数
/// </summary>
/// <param name="hitPosition">チェックするPoint</param>
/// <param name="hitVelocity">線分のベクトル</param>
/// <returns>そのオブジェクトのポインタ</returns>
Object* ObjectManager::CheckObjectHitBox(Point hitPosition, Point hitVelocity) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			continue;
		}
		// ４点を用いた当たり判定
		// 普通に処理が間違ってるので動作しない
		/*if (object[i]->CheckHitBox(BaseMath::GetNearestPosition(object[i]->GetQuad(), hitPosition, hitVelocity))) {
			return object[i];
		}*/
		// 中心点を用いた当たり判定
		// 円みたいになっちゃう
		if (object[i]->CheckHitBox(BaseMath::GetNearestPosition(object[i]->GetCenterPosition(), hitPosition, hitVelocity))) {
			return object[i];
		}
	}
	return NULL;
}


// オブジェクトの当たり判定をチェックする関数
// 返り値：そのオブジェクトのポインタ
// 引数：チェックするPoint
//
// ひとつもヒットしていない場合はNULLを返す（この関数を使う場合は必ずNULLチェックをすること！）
Object* ObjectManager::CheckObjectHitBox(Box hitPosition) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			continue;
		}
		if (object[i]->CheckHitBox(hitPosition)) {
			return object[i];
		}
	}
	return NULL;
}

/// <summary>
/// 指定したオブジェクトを取得する関数
/// </summary>
/// <param name="objecttype">オブジェクトタイプ</param>
/// <returns>Object</returns>
Object* ObjectManager::GetSelectObject(ObjectType objecttype) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == objecttype) {
			return object[i];
		}
	}
	return NULL;
}

/// <summary>
/// 全オブジェクト中にブロックが生成されているかどうかを取得する関数
/// </summary>
/// <returns></returns>
bool ObjectManager::GetIsCreatedBlock() {
	// 全てのオブジェクトの中からブロックを探す
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeBlock && object[i]->GetisAlive() == true) {
			// ある場合はtrue
			return true;
		}
	}
	// ない場合はfalse
	return false;
}
bool ObjectManager::GetIsCreatedIronBalloon() {
	// 全てのオブジェクトの中からブロックを探す
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeIronBalloon && object[i]->GetisAlive() == true) {
			// ある場合はtrue
			return true;
		}
	}
	// ない場合はfalse
	return false;
}

// プレイヤーの中心座標を受け取る関数
Point ObjectManager::GetPlayerPosition() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typePlayer) {
			return object[i]->GetCenterPosition();
		}
	}

	return { -10000,-10000 };
}
// プレイヤーに範囲制限を切り替える関数
// 左上座標、右下座標
bool ObjectManager::SetPlayerMoveLimit(Point leftTop, Point rightBottom) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typePlayer) {
			Player* p = (Player*)object[i];
			p->SetIsLimitMove(true);
			p->SetLimitLeftTop(leftTop);
			p->SetLimitRightBottom(rightBottom);

			// 成功
			return true;
		}
	}

	// 失敗
	return false;
}
// プレイヤーの範囲制限を消す関数
void ObjectManager::DeletePlayerMoveLimit() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typePlayer) {
			Player* p = (Player*)object[i];
			p->SetIsLimitMove(false);
		}
	}
}

// プレイヤーの生存フラグを取得
bool ObjectManager::GetPlayerisAlive() {
	Player* p = (Player*)GetSelectObject(typePlayer);
	if (p != NULL) {
		return p->GetisAlive();
	}
	return false;
}

// コアにブロックがヒットしたかを返す関数
bool ObjectManager::isHitCore() {
	int i = 0;
	for (i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeCore) {
			break;
		}
	}

	// コアのサイズ
	float width = 256 / 2;
	float height = 256 / 2;

	// 8つ角の座標を含めた9点
	//  0-- 1-- 2-- 3-- 4
	//  5-- 6-- 7-- 8-- 9
	// 10--11--12--13--14
	// 15--16--17--18--19
	// 20--21--22--23--24
	Point hitPos[25];
	for (int j = 0; j < 25; j++) {
		hitPos[j] = object[i]->GetCenterPosition();
	}
	for (int d = 0; d < 5; d++) {
		hitPos[0 + 5 * d].x -= width;
		hitPos[1 + 5 * d].x -= width / 2;
		hitPos[3 + 5 * d].x += width / 2;
		hitPos[4 + 5 * d].x += width;
	}
	for (int d = 0; d < 5; d++) {
		hitPos[0 + d].y += height;
		hitPos[5 + d].y += height / 2;
		hitPos[15 + d].y -= height / 2;
		hitPos[20 + d].y -= height;
	}


	for (int j = 0; j < 25; j++) {
		if (ObjectHitBox::CheckHitBox(hitPos[j], i)) {
			return true;
		}
	}
	
	return false;
}