#pragma once
#include "MyBase/Include/MyBase.h"
#include "Class/Include/Object/ObjectManager.h"

// ワイヤーのクラス

class Wire {
public: // メンバ関数

	// コンストラクタ
	Wire();
	// デストラクタ
	~Wire();
	// 初期化（最初は存在しないものとして扱うので、変数はデタラメで）
	void Initialize();
	// 更新
	void Update(ObjectManager objectManager);
	// 描画
	void Draw();


	// ワイヤーの当たり判定チェック用関数
	// 引数：なし
	// 返り値：ヒットした場合 ... true
	//
	// 今回はオブジェクト、もしくは場外に当たった場合にヒット判定
	bool CheckHitBox(Point* _position, Object*& _object, ObjectManager objectManager);


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

	//ワイヤーの状態
	enum WireState {
		// 射出していない
		NoneShot,
		// 射出中
		DoneShot
	};
	WireState wireState;

	// 1点目の座標
	Point* firstPosition;
	// 2点目の座標
	Point* secondPosition;

	// 1点目の着地点にあったオブジェクト
	Object* firstObject;
	// 2点目の着地点にあったオブジェクト
	Object* secondObject;

	// 射出角度
	float ShotAngle;

};