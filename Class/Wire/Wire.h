#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"

#include "Class/Map/MapManager.h"

// ワイヤーのクラス

class ObjectManager;
class Player;

class Wire {
public: // メンバ関数

	// コンストラクタ
	Wire();
	// デストラクタ
	~Wire();
	// 初期化（最初は存在しないものとして扱うので、変数はデタラメで）
	void Initialize();
	// 更新
	void Update(ObjectManager* objectManager);
	// 描画
	void Draw();

	// ワイヤーの生存フラグを返す
	bool GetisAlive();

	// ワイヤーの当たり判定チェック用関数
	// 引数：なし
	// 返り値：ヒットした場合 ... true
	//
	// 今回はオブジェクト、もしくは場外に当たった場合にヒット判定
	bool CheckHitBox(Point _position, int i, ObjectManager* objectManager);


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
	bool Shot(Point shotPosition, float shotAngle, Player* _player);

	// ワイヤー縮小時に呼び出される関数
	// 返り値：なし
	// 引数：なし
	// 着弾点のObjectにベクトルを足す
	void Attract();


private: // メンバ変数

	// 0 ... １発目（First）
	// 1 ... ２発目（Second）

	// 前フレームの座標
	Point prePosition[2];
	// 座標
	Point position[2];
	// 着地点のオブジェクト
	Object* object[2];
	// 着地点のオブジェクトのタイプ
	ObjectType type[2];
	// ワイヤーの状態
	bool isShot[2];

	// 射出角度（degree）
	float shotAngle;

	// ワイヤーの生存フラグ
	bool isAlive;
};