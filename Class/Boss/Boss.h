#pragma once
#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"

/*********************************************
 * ボスクラス
 *
 * ボス関連の行動すべてを管理するクラス
 *********************************************/

class ObjectManager;

class Boss {
public:

	// コンストラクタ
	Boss();

	// デストラクタ
	~Boss();

	// 初期化
	void Initialize(ObjectManager* objectManager);

	// 更新処理
	void Update(Point playerPosition, ObjectManager* objectManager,WireManager* wireManager);

	// 描画処理
	void Draw();

	// ボス自体の当たり判定を返す関数
	// 返り値：当たっている ... true 当たっていない ... false
	// 引数：
	// hitPosition ... 当たった座標
	// 引数で指定したPointがボスの外殻に命中しているかどうかを返す関数
	bool GetBossCollision(Point hitPosition);

private:

	/*********************************
		メンバ関数
	*********************************/

	/******** 変換関数 **********/
	// ボス左画像の座標を求める
	Point GetLCoverPosition(Point centerPosition);
	// ボス右画像の座標を求める
	Point GetRCoverPosition(Point centerPosition);

	// 武器画像の相対座標を求める
	Point GetWeaponPosition(Point centerPosition);

	// 発射地点の相対座標を求める
	Point GetShotPosition(Point centerPosition);

	// 左側フックの相対座標を求める
	Point GetLHookPosition(Point centerPosition);

	// 右側フックの相対座標を求める
	Point GetRHookPosition(Point centerPosition);

	/******** 初期化関数 **********/
	// 選択初期化関数
	// 返り値：なし
	// 引数：
	// cenerPosition ... 座標を初期化するか
	// degree ... 角度を初期化するか
	// offset ... オフセットを初期化するか
	// t ... tを初期化するか
	// weapon ... 武器関係の変数を初期化するか
	// 引数でTrueにしたものだけ初期化する関数
	void SelectionInitialize(bool centerPosition, bool degree, bool offset, bool t, bool weapon);

	/******** デバッグ関数 **********/
	void Debug();

	/******** その他行動関数 **********/

	//イーズアウト（Int型）
	 int IntEaseOut(float t, long int b, long int c) {
		float easeT = 1.0f - powf(1.0f - t, 3.0f);
		return (1.0f - easeT) * b + easeT * c;
	}

	// シェイク関数
	// 返り値：なし
	// 引数：
	// shakeStrength ... シェイクする際の強さ
	// ボスをシェイクさせる関数
	void Shake(int shakeStrength);

	// シェイクイーズアウト関数
	// 返り値：なし
	// 引数：
	// shakeStrength ... シェイクする際の強さ
	// ボスをシェイクの強さを少しずつ弱くしながら動かす関数
	void ShakeEaseOut(int shakeStrength, float shakeTime);

	// シェイクイーズインアウト関数
	// 返り値：なし
	// 引数：
	// shakeStrength ... シェイクする際の強さ
	// ボスをシェイクの強さを少しずつ弱くしながら動かす関数
	void ShakeEaseInOut(int shakeStrength, float shakeTime);

	// バイブレーション関数
	// 返り値：なし
	// 引数：
	// shakeStrength ... シェイクする際の強さ
	// vibTime ... 振動する秒数
	// vibRate ... 振動する間隔
	// vibValue ... 振動させたい回数
	// 一定間隔で、一定秒数振動させる関数
	void vibration(int shakeStrength, float vibTime, float vibRate, int vibValue);

	/******** 攻撃行動関数 **********/
	// 行動なし関数
	// 返り値：なし
	// 引数：
	// waitTime ... 待機する秒数
	// 行動の合間に挟む関数。
	void None(float waitFrame);

	// 回転関数
	// 返り値：なし
	// 引数：
	// endDegree ... 終了時の角度
	// rotateTime ... 回転する時間。これは秒数
	// ボスを回転させる関数
	void Rotate(float endDegree, float RotateTime, WireManager* wireManager);

	// 突進関数
	// 返り値：なし
	// 引数：
	// playerPosition ... プレイヤーの座標
	// readyTime ... 突進の準備にかかる秒数
	// rushTime ... 突進にかかる秒数
	// backTime ... 戻る時にかかる秒数
	// ボスをプレイヤーの向きに突進させる関数
	void Rush(Point playerPosition, float readyTime , float rushTime, float backTime);

	// 斬撃関数
	// 返り値：なし
	// 引数：
	// playerPosition ... プレイヤーの座標
	// readyTime ... ボスが開くまでにかかる秒数
	// deployTime ... ブレードの展開にかかる秒数
	// preparationTime　... 攻撃までの待機時間
	// rushTime ... 突進にかかる秒数
	// backTime ... 戻る時にかかる秒数
	// ボスが斬撃を行う関数
	void Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime);
	
	// 射撃関数
	// 返り値：なし
	// 引数：
	// playerPosition ... プレイヤーの座標
	// readyTime ... ボスが開くまでにかかる秒数
	// deployTime ... 銃の展開にかかる秒数
	// preparationTime　... 攻撃までの待機時間
	// shotTime ... 射撃秒数
	// backTime ... 戻る時にかかる秒数
	// fireRate ... 何秒おきに射撃するか
	// ボスが射撃を行う関数
	void Shot(Point playerPosition, float readyTime, float deployTime, float preparationTime, float shotTime, float backTime, float fireRate);

	// オブジェクト落下関数
	// 返り値：なし
	// 引数：
	// readyTime ... ボスの座標を中心に戻す秒数
	// deployTime ... 攻撃準備にかかる秒数
	// rushTime　... 天井に突進するまでにかかる秒数
	// standByTime ... 待機秒数
	// backTime ... 戻る時にかかる秒数
	// ボスが天井にぶつかり、破片を落下させて攻撃を行う関数
	void Fall(float readyTime, float deployTime, float rushTime, float standByTime, float backTime);

	/******** スタン関数 **********/
	// スタン関数
	// 返り値：なし
	// 引数：
	// readyTime ... スタンし始めモーション秒数
	// deployTime ... スタンし始めモーション秒数
	// stanTime　... スタン秒数
	// backTime ... 戻る時にかかる秒数
	// 指定された秒数ボスがスタンする関数
	void Stun(float readyTime, float deployTime, float stanTime, float backTime);

	/******** ダメージ **********/
	// ダメージ関数
	// 返り値：なし
	// 引数：
	// readyTime ... スタンし始めモーション秒数
	// deployTime ... スタンし始めモーション秒数
	// stanTime　... スタン秒数
	// backTime ... 戻る時にかかる秒数
	// ボスに対してダメージが与えられる状態にする関数
	void Damage(float readyTime, float deployTime, float openTime, float stanTime, float backTime, float closeTime);

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
		WAYPOINT0, // 初期化
		WAYPOINT1, // 行動中間地点〜
		WAYPOINT2,
		WAYPOINT3,
		WAYPOINT4,
		WAYPOINT5,
		WAYPOINT6
	};
	//行動がどこまで進んでいるかを格納する変数
	int actionWayPoint = WAYPOINT0;

	/******** 行動分岐(Enum) **********/
	// 行動をランダムに分岐させる。初期値はPattern1
	enum ActionBranch {
		Pattern1, //行動分岐 1~
		Pattern2,
		Pattern3
	};
	// どの行動に分岐させるかを格納する変数
	int actionBranch = Pattern1;

	/******** 座標関連 **********/
	/// ボス関連
	// 中心座標
	Point centerPosition;
	// シェイクするときの座標の変化量
	Point shakeVariation;
	// シェイクする範囲
	int shakeRange;
	
	// ボスが左右にどれだけ開くか
	float offset;
	// ボスの回転角（degree°）
	int degree;

	// 核の中心座標（移動させる可能性があるため）
	Point coreCenterPosition;
	// 核の回転角（degree°）
	int coreDegree;

	// 弾の発射地点
	Point shotPoint;

	// ワイヤーが引っかかる中心座標
	Point wireHangPosition[kmaxWireHang];

	// 行動前座標
	Point prevCenterPosition;
	// 行動後座標
	Point nextCenterPosition;

	// 行動前角度
	int prevDegree;
	// 行動後角度
	int nextDegree;

	// 行動前オフセット
	int prevOffset;
	// 行動後オフセット
	int nextOffset;

	// 参照するプレイヤー座標
	Point prePlayerPosition;

	// プレイヤーへの方向
	float playerDirection;

	/// 弾関連
	// 弾の中心座標
	Point bulletCenterPosition[kmaxBullet];

	// 弾が発射される向き
	float bulletDirection[kmaxBullet];

	// 弾の発射スピード
	float bulletSpeed;

	/******** サイズ関連 **********/
	/// ボス関連

	// テクスチャサイズ
	Point textureSize;
	// 核のテクスチャサイズ
	Point kernelTextureSize;

	// フックのテクスチャサイズ
	Point hookTextureSize;

	// サイズ
	Point size;
	// 核のサイズ
	Point coreSize;

	// フックのテクスチャサイズ
	Point hookSize;

	/// 武器関連
	// 武器のサイズ
	Point weaponSize;

	// 武器のテクスチャサイズ
	Point weaponTextureSize;

	// 行動前武器サイズ
	Point prevWeaponSize;
	// 行動後武器サイズ
	Point nextWeaponSize;

	/// 弾関連
	// 弾のテクスチャサイズ
	Point bulletTextureSize;

	// 弾のサイズ
	Point bulletSize;

	/******** 行動関連 **********/
	/// ボス関連
	// 初期化されているか
	bool init;
	// バイブレーション初期化の際に用いられる変数
	bool vibInit;

	// 攻撃中か
	bool inAction;
	// 攻撃が終了しているか
	bool endAction;

	// スタン中か
	bool inStun;
	// スタンする時間
	int stunTime;

	// ダメージを受けているのか
	bool inDamage;

	// 核が分離しているか
	bool coreSeparated;

	// 弾関連
	// 弾が撃たれているか
	bool isShot[kmaxBullet];

	// 弾の生存時間
	float bulletAliveTime[kmaxBullet];

	/// オブジェクト関連

	// オブジェクトを生成するかどうか
	bool canGeneratedBlock = false;

	// オブジェクト生成個数
	int generatedBlockValue = 0;

	// オブジェクト生成間隔
	float generatedBlockInterval = 0.0f;

	/******** イージング関連 **********/
	// イージング用t
	float t = 0.0f;

	// フックのオブジェクト
	Object* hook[2];

};