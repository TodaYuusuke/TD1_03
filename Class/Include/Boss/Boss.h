#pragma once
#include "MyBase/Include/MyBase.h"

/*********************************
	ボスクラス
*********************************/

class Boss {
public:

	//コンストラクタ
	Boss();

	//デストラクタ
	~Boss();

	//初期化
	void Initialize();

	//更新処理
	void Update(Point playerPosition);

	//描画処理
	void Draw();

private:
	/******** 行動関数 **********/
	//行動なし（行動間の待機時間）
	void None();
	//回転
	void Rotate();
	//突進
	void Rush();
	//斬撃
	void Slash();
	//射撃
	void Shot();
	//落下
	void Fall();

	/******** 行動パターン(Enum) **********/
	enum Attackpattern
	{
		NONE, //行動なし
		ROTATE, //回転
		RUSH, //突進
		SLASH, //斬撃
		SHOT, //射撃
		FALL
	};
	int attackPattern = NONE;

};