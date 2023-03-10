#pragma once


////////////////////////////////////////////////
/* - プログラム中に使う全ての列挙子を管理するクラス - */
////////////////////////////////////////////////


// マウスのボタン
enum MouseButton {
	// 左クリック
	LeftClick,
	// 右クリック
	RightClick,
	// 中クリック
	MiddleClick,
	// サイドキー
	SideKey1,
	SideKey2,
	SideKey3,
	SideKey4,
	SideKey5,
	SideKey6
};

// 入力の状態
enum InputState {
	// 押されていない
	Null,
	// 押された瞬間
	Trigger,
	// 押しっぱなし
	Press,
	// 離された瞬間
	Release
};

// ゲームシーン
enum SceneState {
	// 無し（シーン切り替え無し）
	sceneNone,
	// タイトル
	sceneTitle,
	// OP
	sceneOP,
	// チュートリアルステージ
	sceneTutorialStage,
	// ボスステージ
	sceneBossStage,
	// ゲームクリア
	sceneGameClear,
	// ゲームオーバー
	sceneGameOver,
	// ゲーム終了（プログラム終了）
	sceneEnd
};


enum ObjectType {
	// オブジェクト
	typeObject,
	// ブロック
	typeBlock,
	// プレイヤー
	typePlayer,
	// フック
	typeHook,
	// 敵
	typeEnemy,
	// 壁（ワイヤーの識別用）
	typeWall,
	// ボスの中心部
	typeCore
};

// プレイヤーの状態
enum PlayerState
{
	// 待機
	playerIdle,
	// ダッシュ
	playerRun,
	// ジャンプ
	playerJump,
	// 上昇中
	playerRase,
	// 落下中
	playerFall,
	// 着地
	playerLand,
	// 射出
	playerShot,
	// 縮小
	playerPull,

	kPlayerStateCount
};

// コントローラーボタン
enum ControllerButton {
		kControllerButtonUp,	//!< XInputの場合、十字キー上
		kControllerButtonDown,	//!< XInputの場合、十字キー下
		kControllerButtonLeft,	//!< XInputの場合、十字キー左
		kControllerButtonRight,	//!< XInputの場合、十字キー右
		kControllerButtonStart,	//!< XInputの場合、START
		kControllerButtonBack,	//!< XInputの場合、BACK
		kControllerButtonL3,	//!< XInputの場合、L3
		kControllerButtonR3,	//!< XInputの場合、R3
		kControllerButtonL1,	//!< XInputの場合、L1
		kControllerButtonR1,	//!< XInputの場合、R1
		kControllerButtonL2A,	//!< XInputの場合、L2 & A
		kControllerButtonR2B,	//!< XInputの場合、R2 & B
		kControllerButtonX,		//!< XInputの場合、A?X,
		kControllerButtonY,		//!< XInputの場合、B?Y,
		kControllerButton14,	//!< XInputの場合、X?,
		kControllerButton15,	//!< XInputの場合、Y?,
		kControllerButton16,
		kControllerButton17,
		kControllerButton18,
		kControllerButton19,
};

// Noviceに宣言されているコピペ
//// ゲームパッドボタン
//enum PadButton {
//	kPadButton0,  //!< XInputの場合、十字キー上
//	kPadButton1,  //!< XInputの場合、十字キー下
//	kPadButton2,  //!< XInputの場合、十字キー左
//	kPadButton3,  //!< XInputの場合、十字キー右
//	kPadButton4,  //!< XInputの場合、START
//	kPadButton5,  //!< XInputの場合、BACK
//	kPadButton6,  //!< XInputの場合、L3
//	kPadButton7,  //!< XInputの場合、R3
//	kPadButton8,  //!< XInputの場合、L1
//	kPadButton9,  //!< XInputの場合、R1
//	kPadButton10, //!< XInputの場合、L2
//	kPadButton11, //!< XInputの場合、R2
//	kPadButton12, //!< XInputの場合、A,
//	kPadButton13, //!< XInputの場合、B,
//	kPadButton14, //!< XInputの場合、X,
//	kPadButton15, //!< XInputの場合、Y,
//	kPadButton16,
//	kPadButton17,
//	kPadButton18,
//	kPadButton19,
//};