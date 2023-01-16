#pragma once
#include "MyBase/Include/MyBase.h"

enum ObjectType {
	// オブジェクト
	typeObject,
	// ブロック
	typeBlock,
	// プレイヤー
	typePlayer
};


// 全てのオブジェクトに共通する処理を実装する

/*

・重力による加速

*/



class Object {

public: // メンバ関数

	// コンストラクタ
	//Object();
	// デストラクタ
	//~Object();

	// 初期化 ... Objdctに定義されてる定数を初期化
	// ※コード内に必ずSuccessorInitializeを呼び出すこと
	virtual void Initialize();
	// 継承先の初期化 ... 継承元と継承先に定義されてる変数を初期化
	virtual void SuccessorInitialize();
	
	// 更新 ... 全オブジェクト共通の処理
	// ※コード内に必ずSuccessorUpdateを呼び出すこと
	virtual void Update();
	// 継承先の更新 ... 継承先特有の処理
	virtual void SuccessorUpdate();
	
	// 描画
	virtual void Draw();
	

	// オブジェクトに速度ベクトルを足す関数
	// 返り値：なし
	// 引数：足す速度
	void AddVelocity(Point _addVelocity);

	// オブジェクトに回転速度を足す関数
	// 返り値：なし
	// 引数：足す速度
	void AddVelocity(float _addVelocity);

	// 当たり判定をチェックする関数
	// 返り値：ヒットしていた場合 ... true
	// 引数：チェックするPoint
	bool CheckHitBox(Point hitPosition);

	// 当たり判定をチェックする関数
	// 返り値：ヒットしていた場合 ... true
	// 引数：チェックするBox
	bool CheckHitBox(Box hitPosition);

	/// <summary>
	/// フィールド外への移動をチェックする関数
	/// </summary>
	/// <returns>フィールド外に出た場合 ... true</returns>
	bool CheckFieldHitBox();

	/// <summary>
	/// タイプを取得する関数
	/// </summary>
	/// <returns>オブジェクトのタイプ</returns>
	virtual ObjectType GetType();

	/// <summary>
	/// 座標を取得する関数
	/// </summary>
	/// <returns>centerPosition</returns>
	Point GetCenterPosition();

	/// <summary>
	/// 速度を取得する関数
	/// </summary>
	/// <returns>velocity</returns>
	Point GetVelocity();

protected: // メンバ変数

	// 中心座標
	Point centerPosition;
	// 速度
	Point velocity;
	// 加速度
	Point acceleration;

	// 回転角度（Degree）
	float angle;
	// 回転速度（Degree）
	float angleVelocity;

	// 当たり判定のサイズ（左上の点からの長さ）
	float width;
	float height;

	//空中にいるかどうか
	bool isFlying;


};