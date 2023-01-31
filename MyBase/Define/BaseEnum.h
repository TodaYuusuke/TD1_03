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
	None,
	// タイトル
	Title,
	// OP
	OP,
	// チュートリアルステージ
	TutorialStage,
	// ボスステージ
	BossStage,
	// ゲームクリア
	GameClear,
	// ゲームオーバー
	GameOVer,
	// ゲーム終了（プログラム終了）
	End
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