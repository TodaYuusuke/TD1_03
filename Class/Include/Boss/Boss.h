#pragma once
#include "MyBase/Include/MyBase.h"

/*********************************************
 * ボスクラス
 *
 * ボス関連の行動すべてを管理するクラス
 *********************************************/

class Boss {
public:

	// コンストラクタ
	Boss();

	// デストラクタ
	~Boss();

	// 初期化
	void Initialize();

	// 更新処理
	void Update(Point playerPosition);

	// 描画処理
	void Draw();

private:

	/*********************************
		メンバ関数
	*********************************/

	/******** 変換関数 **********/
	// ボス左画像の座標を求める
	Point GetLCoverPosition(Point centerPosition);
	// ボス右画像の座標を求める
	Point GetRCoverPosition(Point centerPosition);

	/******** デバッグ関数 **********/
	void Debug();

	/******** 攻撃行動関数 **********/
	// 行動なし（行動間の待機時間）
	void None(int waitTime);
	//回転
	void Rotate();
	// 突進
	void Rush();
	// 斬撃
	void Slash();
	// 射撃
	void Shot();
	// 落下
	void Fall();

	/******** スタン関数 **********/
	void Stun();

	/******** ダメージ **********/
	void Damage();

	/*********************************
		メンバ定数
	*********************************/

	/******** ワイヤーをかけることのできる場所の最大数 **********/
	const static int kmaxWireHang = 2;

	/******** 表示できる弾の最大数 **********/
	const static int kmaxBullet = 50;

	/*********************************
		メンバ変数
	*********************************/

	/******** デバッグに用いる変数 **********/
	//現在デバッグ状態か
	bool inDebug = false;

	/******** 行動パターン(Enum) **********/
	enum Attackpattern
	{
		NONE, // 行動なし
		ROTATE, // 回転
		RUSH, // 突進
		SLASH, // 斬撃
		SHOT, // 射撃
		FALL
	};
	// 攻撃パターンを格納するint型変数
	int attackPattern = NONE;

	/******** 行動中間地点（Enum） **********/
	// 攻撃やスタン等の中間地点到達の際に切り替え
	enum ActionWayPoint 
	{
		WAYPOINT1, // 行動中間地点～
		WAYPOINT2,
		WAYPOINT3,
		WAYPOINT4,
		WAYPOINT5
	};

	/******** 座標関連 **********/
	/// ボス関連
	// 中心座標
	Point centerPosition;
	
	// ボスが左右にどれだけ開くか
	float offset;
	// ボスの回転角（degree°）
	int degree;

	// 核の中心座標（移動させる可能性があるため）
	Point coreCenterPosition;
	// 核の回転角（degree°）
	int coreDegree;

	// ワイヤーが引っかかる中心座標
	Point wireHangPosition[kmaxWireHang];

	/******** サイズ関連 **********/
	/// ボス関連

	// テクスチャサイズ
	Point textureSize;
	// 核のテクスチャサイズ
	Point kernelTextureSize;

	// サイズ
	Point size;
	// 核のサイズ
	Point coreSize;
	
	/******** 行動関連 **********/
	/// 攻撃関連
	// 攻撃中か
	bool inAction;
	// 攻撃が終了しているか
	bool endAction;

	/// スタン関連
	// スタン中か
	bool inStun;
	// スタンする時間
	int stunTime;

	/// ダメージ関連
	// ダメージを受けているのか
	bool inDamage;

	// 核が分離しているか
	bool coreSeparated;

	/******** イージング関連 **********/
	// イージング用t
	float t = 0.0f;

};