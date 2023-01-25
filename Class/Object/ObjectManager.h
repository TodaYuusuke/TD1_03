#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/Object.h"

#include "Class/Object/Block/Block.h"
#include "Class/Object/Player/Player.h"
#include "Class/Object/Enemy/Enemy.h"
#include "Class/Object/Hook/Hook.h"
#include "Class/Object/Core/Core.h"

#include "Class/Wire/WireManager.h"

// プログラム内のオブジェクトを全て管理するクラス

class WireManager;

class ObjectManager {

public: // メンバ関数

	// 初期化
	// 全てのオブジェクトの実態を（Objectで）初期化
	void Initialize();
	// 更新
	// 全てのオブジェクトを更新（Updateを呼び出す）
	void Update();
	// 描画
	// 全てのオブジェクトを描画（Drawを呼び出す）
	void Draw();


	// 新しいオブジェクトのインスタンスを生成する関数たち
	// 中の実態がObjectのものを若い数字優先で上書きしていく


	// Block
	void MakeNewObjectBlock(Point position, Point size);

	// Player
	void MakeNewObjectPlayer(Point position, WireManager* wireManager);

	// Hook
	Object* MakeNewObjectHook(Point position, Point size);

	// Hook
	Object* MakeNewObjectCore(Point position, Point size);

	// Enemy
	void MakeNewObjectEnemy(Point position, Point size);

	// オブジェクトの当たり判定をチェックする関数
	// 返り値：そのオブジェクトのポインタ
	// 引数：チェックするPoint
	//
	// ひとつもヒットしていない場合はNULLを返す（この関数を使う場合は必ずNULLチェックをすること！）
	Object* CheckObjectHitBox(Point hitPosition);
	// 線分を受け取って判定
	/// <summary>
	/// オブジェクトの当たり判定をチェックする関数
	/// </summary>
	/// <param name="hitPosition">チェックするPoint</param>
	/// <param name="hitVelocity">線分のベクトル</param>
	/// <returns>そのオブジェクトのポインタ</returns>
	Object* CheckObjectHitBox(Point hitPosition, Point hitVelocity);


	// オブジェクトの当たり判定をチェックする関数
	// 返り値：そのオブジェクトのポインタ
	// 引数：チェックするPoint
	//
	// ひとつもヒットしていない場合はNULLを返す（この関数を使う場合は必ずNULLチェックをすること！）
	Object* CheckObjectHitBox(Box hitPosition);

	/// <summary>
	/// 指定したオブジェクトを取得する関数
	/// </summary>
	/// <param name="objecttype">オブジェクトタイプ</param>
	/// <returns>Object</returns>
	Object* GetSelectObject(ObjectType objecttype);



	// プレイヤーの中心座標を受け取る関数
	Point GetPlayerPosition();

private: // メンバ定数

	const static int kMaxObjectSize = 256;

private: // メンバ変数

	// オブジェクトのポインタ達
	Object* object[kMaxObjectSize];
};