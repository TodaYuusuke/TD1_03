#pragma once
#include "MyBase/Include/MyBase.h"

#include "Class/Include/Map/MapManager.h"

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
	

	// メンバ変数に作用する関数

	// オブジェクトの中心座標を受け取る関数
	// 返り値：中心座標
	// 引数：なし
	Point GetCenterPosition();

	// オブジェクトの速度を受け取る関数
	// 返り値：速度のベクトル
	// 引数：なし
	Point GetVelocity();

	// オブジェクトが空中かどうかを受け取る関数
	// 返り値：空中ならばtrue
	// 引数：なし
	bool GetisFlying();

	// オブジェクトに速度ベクトルを足す関数
	// 返り値：なし
	// 引数：足す速度のベクトル
	void AddVelocity(Point _addVelocity);

	// オブジェクトに回転速度を足す関数
	// 返り値：なし
	// 引数：足す速度
	void AddVelocity(float _addVelocity);

	
	// 当たり判定関連

	// オブジェクトに対する当たり判定をチェックする関数
	// 返り値：ヒットしていた場合 ... true
	// 引数：チェックするPoint
	bool CheckHitBox(Point hitPosition);

	// 当たり判定をチェックする関数
	// ※　現在angleを考慮した処理になっていないので、使用禁止　※
	// 返り値：ヒットしていた場合 ... true
	// 引数：チェックするBox
	bool CheckHitBox(Box hitPosition);


	// その他

	// タイプを取得する関数
	// 返り値：自身のObjectType
	// 引数：なし
	virtual ObjectType GetType();

protected: // 関数

	// オブジェクト自体の当たり判定をチェックする関数
	virtual void CheckFieldHitBox();
	// 上下左右の当たり判定の関数
	virtual void CheckHitBoxRhombus(Point checkQuadPoint[], Point checkRhombusPoint[]);

	// 最も近い値を格納した配列の添え字を求める
	int GetNearestValue(int v) {
		// 変数の宣言
		//v = BaseMath::Clamp(v, 0, 360);
		if (v < 45) {
			return 0;
		}
		else if (v < 90 + 45) {
			return 90;
		}
		else if (v < 180 + 45) {
			return 180;
		}
		else if (v < 270 + 45) {
			return 270;
		}
		else {
			return 0;
		}
	}

	/// <summary>
	/// 回転角度を取得する関数
	/// </summary>
	/// <returns>angle</returns>
	float GetAngle();

	/// <summary>
	/// 矩形の４点を取得する関数
	/// </summary>
	/// <returns>Quad</returns>
	Quad GetQuad();

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

	// 0 ... 上
	// 1 ... 下
	// 2 ... 左
	// 3 ... 右
	// の4点を用意
	Point checkRhombusPoint[4];

	// 0 ... 左上
	// 1 ... 右上
	// 2 ... 左下
	// 3 ... 右下
	// の4点を用意
	Point checkQuadPoint[4];
};