#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"
#include "Class/Wire/Wire.h"
#include "Class/Boss/Boss.h"

class ObjectManager;
class Player;
class Wire;

class WireManager {
public: // メンバ関数

	// コンストラクタ
	WireManager();
	// デストラクタ
	~WireManager();

	// 初期化
	void Initialize();
	// 更新
	void Update(ObjectManager* objectManager);
	// 描画
	void Draw();

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
	// Wireクラスのshotの返り値で正常に射出できたかを判断すること。
	int Shot(Point shotPosition, float shotAngle,Player* _player);

	// ワイヤー縮小時に呼び出される関数
	// 返り値：なし
	// 引数：なし
	// 着弾点のObjectにベクトルを足す
	//
	// 全てのWireのAttract()を呼び出すだけ
	void Attract();

private: // メンバ変数

	// 現在のインデックス
	int index;

	Wire* wires[BaseConst::kWireMaxAmount];

};