#include "Class/Include/Boss/Boss.h"

/*********************************************
 * ボスクラス
 *
 * ボス関連の行動すべてを管理するクラス
 *********************************************/

// コンストラクタ
Boss::Boss() {
	Boss::Initialize();
}

// デストラクタ
Boss::~Boss() {

}

// 初期化処理
void Boss::Initialize() {
	// ボスの位置を画面中央に持っていく
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	// ボスの画像サイズを設定
	this->textureSize = { 225.0f, 450.0f };

	// 行動終了状態にする
	this->endAction = true;

	// 核の位置を設定
	coreCenterPosition = centerPosition;
	// 核の画像サイズを設定
	kernelTextureSize = { 256.0f, 256.0f };
}

// 更新処理
void Boss::Update(Point playerPosition) {
	/******** デバック処理 **********/
	// デバッグ状態の切り替え
	if (BaseInput::GetKeyboardState(DIK_0, Trigger)) {
		if (inDebug == false)
			inDebug = true;

		else
			inDebug = false;
	}

	if (endAction == true) {
		if(BaseInput::GetKeyboardState(DIK_F, Trigger)) {
			inAction = true;
			endAction = false;
		}
	}

	if (inAction == true) {
		Rush(playerPosition, 1, 2, 1);
	}

	// デバッグ関数の実行
	if (inDebug == true) {
		Debug();
	}

	// 核が分離していない状態では核をボスに追従させる
	if (coreSeparated == false) {
		coreCenterPosition = centerPosition;
		coreDegree = degree;
	}	

}

// 描画処理
void Boss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

	// ボス核画像
	BaseDraw::DrawQuad(
		viewPosition,
		BaseTexture::kBossCore,
		kernelTextureSize,
		1.0f,
		coreDegree,
		0xFFFFFFFF
	);

	// ボス左側画像
	BaseDraw::DrawQuad(
		Boss::GetLCoverPosition(viewPosition),
		BaseTexture::kBossLCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	// ボス右側画像
	BaseDraw::DrawQuad(
		Boss::GetRCoverPosition(viewPosition),
		BaseTexture::kBossRCover,
		textureSize,
		1.0f,
		degree,
		0xFFFFFFFF
	);

	Novice::ScreenPrintf(0, 30, "t : %4.2f", t);
	Novice::ScreenPrintf(0, 50, "pos x : %4.2f y : %4.2f", centerPosition.x, centerPosition.y);
	Novice::ScreenPrintf(0, 70, "inAction : %d", inAction);
	Novice::ScreenPrintf(0, 90, "endAction : %d", endAction);
	Novice::ScreenPrintf(0, 110, "ShakeRange : %d", shakeRange);

}

// ボス左画像の相対座標を求める
Point Boss::GetLCoverPosition(Point centerPosition) { 
	// 回転中心からの差異ベクトル作成
	Point p = { -textureSize.x / 2 - offset, 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}
// ボス右画像の相対座標を求める
Point Boss::GetRCoverPosition(Point centerPosition) { 
	// 回転中心からの差異ベクトル作成
	Point p = { textureSize.x / 2 + offset, 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// デバッグ用関数
void Boss::Debug() {
	// すべてをリセットする
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		offset = 0.0f;
		degree = 0;
	}

	// ボスを左右に開かせる
	if (BaseInput::GetKeyboardState(DIK_I, Press))
		offset += 1.0f;

	else if (BaseInput::GetKeyboardState(DIK_K, Press))
		offset -= 1.0f;

	// オフセットが指定の値以下になると0にする
	if (offset < 0) {
		offset = 0;
	}

	// ボスを回転させる
	if (BaseInput::GetKeyboardState(DIK_L, Press))
		degree++;

	else if (BaseInput::GetKeyboardState(DIK_J, Press))
		degree--;
}

// シェイク関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// ボスをシェイクさせる関数
void Boss::Shake(int shakeStrength) {
	shakeVariation.x = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
	shakeVariation.y = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
}

// シェイクイーズアウト関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// shakeTime ... シェイクする時間
// ボスをシェイクの強さを少しずつ弱くしながら動かす関数
void Boss::ShakeEaseOut(int shakeStrength, int shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// 行動なし関数
// 返り値：なし
// 引数：
// waitTime ... 待機する時間
// 行動の合間に挟む関数。waitFrameは秒数ではなくフレーム単位
void Boss::None(int waitFrame) {
	if (t < waitFrame) {
		t += 1.0f;
	}
	else {
		endAction = true;
	}
}

// 回転関数
// 返り値：なし
// 引数：
// endDegree ... 終了時の角度
// rotateTime ... 回転する時間。これは秒数
// ボスを回転させる関数
void Boss::Rotate(float endDegree, int RotateTime) {

	static int startDegree;
	// 初期化処理
	if (init == false) {
		startDegree = degree;
		init = true;
	}

	// t の値が一定以上になるまで足す
	if (t <= RotateTime) {
		inAction = true;
		// イージングを用いて回転
		degree = BaseDraw::Ease_InOut(t, startDegree, endDegree, RotateTime);
		t += 1.0f / 60.0f;
	}
	else {
		//t が一定以上になったら行動終了
		t = 0.0f;
		degree = 0;
		init = false;
		endAction = true;
		inAction = false;
	}
}

// 突進関数
// 返り値：なし
// 引数：
// playerPosition ... プレイヤーの座標
// readyTime ... 突進の準備にかかる秒数
// rushTime ... 突進にかかる秒数
// backTime ... 戻る時にかかる秒数
// ボスをプレイヤーの向きに突進させる関数
void Boss::Rush(Point playerPosition, int readyTime, int rushTime, int backTime) {
	// 初期化処理
	if (init == false) {
		init = true;
	}

	switch (actionWayPoint)
	{
		// 初期化
	case Boss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;
		prePlayerPosition = playerPosition;
		t = 0.0f;
		//次の段階へ
		actionWayPoint++;
		break;
		// 事前動作(震える)
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// 指定された秒数振動する
			ShakeEaseOut(60, readyTime);
			t += 1.0f / 60.0f;
		}
		else {
			t = 0.0f;

			// プレイヤーがいる方向を求める
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// プレイヤーとの距離を求める
			float playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

			if (playerDistance < 500.0f) {
				playerDistance = 500.0f;
			}

			// 突進する座標を求める
			nextCenterPosition = {
				centerPosition.x + (cosf(playerDirection) * playerDistance),
				centerPosition.y + (sinf(playerDirection) * playerDistance)
			};

			//次へ
			actionWayPoint++;
		}
		break;
		// 突進
	case Boss::WAYPOINT2:
		if (t <= rushTime) {
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);
			t += 1.0f / 60.0f;
		}
		else {
			t = 0.0f;
			actionWayPoint++;
			centerPosition = nextCenterPosition;
		}

		break;
		// 元の場所に戻る
	case Boss::WAYPOINT3:
		if (t <= backTime) {
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			centerPosition = prevCenterPosition;
			t = 0.0f;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	case Boss::WAYPOINT4:
		break;
	case Boss::WAYPOINT5:
		break;
	default:
		break;
	}
}


#pragma region コピペ用
//// 初期化処理
//if (init = false) {
//	init = true;
//}
//
//// t の値が一定以上になるまで足す
//if (t < 1.0f) {
//	t += 0.01f;
//
//}
//else {
//	//t が一定以上になったら行動終了
//	t = 0.0f;
//	init = false;
//	endAction = true;
//	inAction = false;
//}
#pragma endregion
