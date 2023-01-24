#include "Class/Object/ObjectManager.h"

// コンストラクタ
ObjectManager::ObjectManager() {
	
}
// デストラクタ
ObjectManager::~ObjectManager() {

}

// 初期化
// 全てのオブジェクトの実態を（Objectで）初期化
void ObjectManager::Initialize() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		object[i] = new Object();
		object[i]->Initialize();
	}
	wireManager = new WireManager();
	wireManager->Initialize();
}
// 更新
// 全てのオブジェクトを更新（Updateを呼び出す）
void ObjectManager::Update(Boss* boss) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() != typeObject) {
			object[i]->Update();
		}
	}
	wireManager->Update(this, boss);
}
// 描画
// 全てのオブジェクトを描画（Drawを呼び出す）
void ObjectManager::Draw() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() != typeObject) {
			object[i]->Draw();
		}
	}
	wireManager->Draw();
}


// 新しいオブジェクトのインスタンスを生成する関数たち
// 中の実態がObjectのものを若い数字優先で上書きしていく


// Block
void ObjectManager::MakeNewObjectBlock(Point position, Point size) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			object[i] = new Block(position, size);
			object[i]->Initialize();
			break;
		}
	}
}

// Player
void ObjectManager::MakeNewObjectPlayer(Point position) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		// 生成されていたら生成しない
		if (object[i]->GetType() == typePlayer) {
			break;
		}
		if (object[i]->GetType() == typeObject) {
			object[i] = new Player(position, wireManager);
			object[i]->Initialize();
			break;
		}
	}
}


// Hook
void ObjectManager::MakeNewObjectHook(Point position, Point size) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			object[i] = new Hook(position, { 50,50 });
			object[i]->Initialize();
			break;
		}
	}
}


// Enemy
void ObjectManager::MakeNewObjectEnemy(Point position,Point size) {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typeObject) {
			object[i] = new Enemy(position, { 50,50 }, GetSelectObject(typePlayer));
			object[i]->Initialize();
			break;
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

// プレイヤーの中心座標を受け取る関数
Point ObjectManager::GetPlayerPosition() {
	for (int i = 0; i < kMaxObjectSize; i++) {
		if (object[i]->GetType() == typePlayer) {
			return object[i]->GetCenterPosition();
		}
	}

	return { -10000,-10000 };
}