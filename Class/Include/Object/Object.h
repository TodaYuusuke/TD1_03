#include "MyBase/Include/MyBase.h"


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

protected: // メンバ変数

	/* 定数として扱うのでInitialize以外のプログラム中で書き換え禁止！！ */

	// 重力加速度
	float kGravitationalAcceleration;

	/* 定数ここまで */


	// 中心座標
	Point centerPosition;

	// 当たり判定のサイズ（左上の点からの長さ）
	float width;
	float height;

	// 速度
	Point velocity;
	
	// 加速度
	Point acceleration;

	// 空中にいるかどうか
	bool isFlying;

	// テクスチャハンドル
	int texture;

};