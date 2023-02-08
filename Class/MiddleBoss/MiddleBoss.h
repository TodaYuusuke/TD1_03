#include "MyBase/MyBase.h"
#include "Class/Object/ObjectManager.h"
#include "Class/Wire/WireManager.h"
#include "Class/AttackHitBox/EnemyAttackHitBox.h"
#include "Class/PublicFlag/PublicFlag.h"

/*********************************************
 * 中ボスクラス
 *
 * 中ボス関連の行動すべてを管理するクラス
 *********************************************/

class ObjectManager;
class Object;
class WireManager;

class MiddleBoss {
public:

	// コンストラクタ
	MiddleBoss();

	// 初期化
	void Initialize(ObjectManager* objectManager);

	// 更新処理
	void Update(Point playerPosition, ObjectManager* objectManager, WireManager* wireManager);

	// 描画処理
	void Draw();

private:

	/*********************************
		メンバ関数
	*********************************/

	//イーズアウト（Int型）
	int IntEaseOut(float t, long int b, long int c, float d) {
		float easeT = 1.0f - powf(1.0f - t / d, 3.0f);
		return (1.0f - easeT) * b + easeT * c;
	}

	// カラーイージング
	unsigned int ColorEasing(float t, unsigned int startColor, unsigned int endColor, float easingTime) {
		unsigned int red = IntEaseOut(t, (((startColor & 0xFF000000) >> 24) & 0xFF), (((endColor & 0xFF000000) >> 24) & 0xFF), easingTime);
		unsigned int green = IntEaseOut(t, (((startColor & 0x00FF0000) >> 16) & 0xFF), (((endColor & 0x00FF0000) >> 16) & 0xFF), easingTime);
		unsigned int blue = IntEaseOut(t, (((startColor & 0x0000FF00) >> 8) & 0xFF), (((endColor & 0x0000FF00) >> 8) & 0xFF), easingTime);
		unsigned int alpha = IntEaseOut(t, (((startColor & 0x000000FF)) & 0xFF), (((endColor & 0x000000FF)) & 0xFF), easingTime);

		return (red << 24) + (green << 16) + (blue << 8) + alpha;
	}

	// 武器画像の相対座標を求める
	Point GetWeaponPosition(Point centerPosition);

	/******** デバッグ関数 **********/
	void Debug();

	/******** 行動関数 **********/
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

	/// <summary>
	/// ボス戦の開始時のアニメーション関数
	/// </summary>
	/// <param name="cameraMoveTime">カメラを動かす時間</param>
	/// <param name="appearTime">ボスが上から出現する</param>
	/// <param name="roarTime">咆哮する</param>
	/// <param name="waitTime">カメラが戻る時間</param>
	void PlayStartAnim(float cameraMoveTime, float appearTime, float roarTime, float waitTime);

	/// <summary>
	/// 死亡時のアニメーションを再生する関数
	/// </summary>
	/// /// <param name="cameraMoveTime">カメラを動かす時間</param>
	/// <param name="roarTime">咆哮する</param>
	/// <param name="moveTime">少し下に行く</param>
	/// <param name="runAwayTime">そして上へ</param>
	/// <param name="cameraBackTime">カメラを戻す</param>
	void PlayDeadAnim(float cameraMoveTime, float moveTime,float runAwayTime,float cameraBackTime, WireManager* wireManager);

	// 行動なし関数
	// 返り値：なし
	// 引数：
	// waitTime ... 待機する秒数
	// 行動の合間に挟む関数。
	void None(float waitFrame);

	// 接近関数
	// 返り値：なし
	// 引数：
	// playerPosition ... プレイヤー中心座標
	// moveTIme ... 回転する時間
	// afterWaitTime ... 行動後に発生する待機時間
	// プレイヤーに向かって接近する関数
	void Approach(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager);

	// 離反関数
	// 返り値：なし
	// 引数：
	// playerPosition ... プレイヤー中心座標
	// moveTIme ... 回転する時間。これは秒数
	// afterWaitTime ... 行動後に発生する待機時間
	// プレイヤーに向かって離反する関数
	void Separation(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager);

	// 回転関数
	// 返り値：なし
	// 引数：
	// endDegree ... 終了時の角度
	// rotateTime ... 回転する時間。これは秒数
	// afterWaitTime ... 行動後に発生する待機時間
	// ボスを回転させる関数
	void Rotate(float endDegree, float RotateTime, float afterWaitTime, WireManager* wireManager);

	// 突進関数
	// 返り値：なし
	// 引数：
	// playerPosition ... プレイヤーの座標
	// readyTime ... 突進の準備にかかる秒数
	// chargeTime ... 突進の溜めにかかる秒数
	// rushTime ... 突進にかかる秒数
	// backTime ... 戻る時にかかる秒数
	// afterWaitTime ... 行動後に発生する待機時間
	// damage ... 行動によって発生するダメージ
	// ボスをプレイヤーの向きに突進させる関数
	void Rush(Point playerPosition, float readyTime, float chargeTime, float rushTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager);

	// 斬撃関数
	// 返り値：なし
	// 引数：
	// playerPosition ... プレイヤーの座標
	// readyTime ... ボスが開くまでにかかる秒数
	// deployTime ... ブレードの展開にかかる秒数
	// preparationTime　... 攻撃までの待機時間
	// rushTime ... 突進にかかる秒数
	// backTime ... 戻る時にかかる秒数
	// afterWaitTime ... 行動後に発生する待機時間
	// damage ... 行動によって発生するダメージ
	// ボスが斬撃を行う関数
	void Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime, float afterWaitTIme, float damage, WireManager* wireManager);

	// オブジェクト落下関数
	// 返り値：なし
	// 引数：
	// readyTime ... ボスの座標を中心に戻す秒数
	// deployTime ... 攻撃準備にかかる秒数
	// rushTime　... 天井に突進するまでにかかる秒数
	// standByTime ... 待機秒数
	// backTime ... 戻る時にかかる秒数
	// damage ... 行動によって発生するダメージ
	// ボスが天井にぶつかり、破片を落下させて攻撃を行う関数
	void Fall(float readyTime, float deployTime, float rushTime, float standByTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager);

	/******** スタン関数 **********/
	// スタン関数
	// 返り値：なし
	// 引数：
	// readyTime ... スタンし始めモーション秒数
	// deployTime ... スタンし始めモーション秒数
	// stanTime　... スタン秒数
	// backTime ... 戻る時にかかる秒数
	// 指定された秒数ボスがスタンする関数
	void Stun(float readyTime, float deployTime, float stanTime, float backTime, WireManager* wireManager);

	/******** ダメージアニメーション **********/
	// ダメージアニメーション関数
	// 返り値：なし
	// 引数：
	// readyTime ... 振動する時間
	// shakeStrength ... 振動する強さ
	// ダメージが与えられた時のアニメーションを再生する関数
	void playTakeDamageAnim(float animTime, float shakeStrength);

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
		FALL, // オブジェクト落下攻撃
		APPROACH, // 接近
		SEPARATION // 離反
	};
	// 攻撃パターンを格納するint型変数
	int attackPattern = NONE;
	int prevAttackPattern[2] = { NONE };

	/******** 行動中間地点（Enum） **********/
	// 攻撃やスタン等の中間地点到達の際に切り替え
	enum ActionWayPoint
	{
		WAYPOINT0, // 初期化
		WAYPOINT1, // 行動中間地点～
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
		Pattern3,
		Pattern4,
		Pattern5
	};

	// 行動時にどの行動に分岐させるかを格納する変数
	int actionBranch = Pattern1;

	// 攻撃時にどの攻撃に分岐させるかを格納する変数
	int attackBranch = Pattern1;

	// 行動間の待機時間
	float waitTime;

	// 待機するか
	bool pleaseWait;

	// 現在演出中か
	// 開始アニメーション
	bool isPlayingStartAnim;
	// 死亡アニメーション
	bool isPlayingDeadAnim;

	// 死亡アニメーションが終了しているか
	bool isEndDeadAnim;

	/******** HP関連 **********/
	// HP(ここで初期化)
	const float MaxHP = 10.0f;
	float HP;

	/******** ダメージ関連 **********/
	// ボス自体のダメージ
	float bodyDamage;

	// 剣のダメージ
	float bladeDamage;

	/******** 座標関連 **********/
	/// ボス関連
	// 中心座標
	Point centerPosition;
	// シェイクするときの座標の変化量
	Point shakeVariation;
	// シェイクする範囲
	int shakeRange;

	// ボスの回転角（degree°）
	int degree;

	// 画面中央の座標
	Point screenCenterPosition;

	// 行動前座標
	Point prevCenterPosition;
	// 行動後座標
	Point nextCenterPosition;

	// 行動前角度
	int prevDegree;
	// 行動後角度
	int nextDegree;

	// 1フレーム前の角度
	int beforeDegree;

	// 参照するプレイヤー座標
	Point prePlayerPosition;

	// プレイヤーとの距離
	float playerDistance;
	// プレイヤーへの方向
	float playerDirection;

	// カットシーン用カメラ移動前座標
	Point prevScreenPosition;

	// カットシーン用カメラ移動後座標
	Point nextScreenPosition;

	// ブロック生成用座標
	Point blockSpawnPoint;

	/******** サイズ関連 **********/
	/// ボス関連

	// テクスチャサイズ
	Point textureSize;
	// サイズ
	Point size;

	/// 武器関連

	// 武器のサイズ
	Point weaponSize;

	// 武器のテクスチャサイズ
	Point weaponTextureSize;

	// 行動前武器サイズ
	Point prevWeaponSize;
	// 行動後武器サイズ
	Point nextWeaponSize;

	/******** 行動関連 **********/
	/// ボス関連
	// 初期化されているか
	bool init;
	// バイブレーション初期化の際に用いられる変数
	bool vibInit;

	// 振動音再生を管理する
	bool isVibPlaySound;

	// 戦闘を開始するか
	bool doBattleStart;

	// 戦闘が開始しているか
	bool isBattleStart;

	// 攻撃中か
	bool inAction;
	// 攻撃が終了しているか
	bool endAction;

	// スタン中か
	bool inStun;
	// スタンする時間
	int stunTime;

	// ダメージを受けたか
	bool inDamage;
	// ダメージを受けられる状態か
	bool canTakeDamage;

	// ボスが死亡しているか
	bool inDead;

	/// オブジェクト関連

	// オブジェクトを生成するかどうか
	bool canGeneratedBlock = false;

	// オブジェクト生成個数
	int generatedBlockValue = 0;

	// オブジェクト生成間隔
	float generatedBlockInterval = 0.0f;

	// 敵を生成するかどうか
	bool canGeneratedEnemy = false;

	// 敵生成個数
	int generatedEnemyValue = 0;

	// 敵生成間隔
	float generatedEnemyInterval = 0.0f;


	/******** イージング関連 **********/
	// イージング用t
	float t = 0.0f;

	// 予備用t 上のtとは別のtを使いたい時に使う
	float spareT = 0.0f;

	// 当たり判定
	Object* core;

	/******** 色関連 **********/
	// 殻の色
	unsigned int color;

	// 行動前色
	unsigned int prevColor;
	// 行動後色
	unsigned int nextColor;

	/// 音関係
	// 咆哮音
	int screamSoundHundle;
	int screamVoiceHundle;

};