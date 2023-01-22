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
	// ボスのオフセットを初期化
	this->offset = 0.0f;

	this->degree = 0.0f;

	//シェイクしていない状態に戻す
	this->shakeVariation = { 0.0f, 0.0f };

	// 行動終了状態にする
	this->t = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->actionWayPoint = 0;

	// 核の位置を設定
	coreCenterPosition = centerPosition;
	// 核の画像サイズを設定
	kernelTextureSize = { 256.0f, 256.0f };

	// 武器のサイズを指定（仮テクスチャのため、今後変える）
	weaponSize = { 0.0f, 0.0f };
	weaponTextureSize = { 1.0f, 1.0f };

	// 弾の関係初期化
	for (int i = 0; i < kmaxBullet; i++) {
		// 弾の座標
		bulletCenterPosition[i] = { 0.0f, 0.0f };

		// 発射していない状態にする
		isShot[i] = false;

		// 弾の発射方向をリセットする
		bulletDirection[i] = 0.0f;

		// 弾の生存時間をリセットする
		bulletAliveTime[i] = 0.0f;
	}

	// 弾のサイズを指定
	bulletSize = { 20.0f, 20.0f };
	// 弾の画像サイズを指定（仮テクスチャのため、今後変える)
	bulletTextureSize = { 1.0f, 1.0f };

	// 弾の発射スピードを指定
	bulletSpeed = 10.0f;
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

	// 行動の実行処理
	if (inAction == true && inStun == false && inDamage == false) {
		switch (attackPattern)
		{
		case Boss::NONE:
			None(1.0f);
			break;
		case Boss::ROTATE:
			Rotate(720, 2.0f);
			break;
		case Boss::RUSH:
			Rush(playerPosition, 0.5f, 1.5f, 1.0f);
			break;
		case Boss::SLASH:
			Slash(playerPosition, 0.35f, 0.2f, 1.0f, 0.75f, 1.0f);
			break;
		case Boss::SHOT:
			Shot(playerPosition, 0.35f, 0.75f, 1.0f, 5.0f, 1.0f, 0.1f);
			break;
		case Boss::FALL:
			break;
		}
	}

	degree %= 360;

	// デバッグ関数の実行
	if (inDebug == true) {
		Debug();
	}

	// 核が分離していない状態では核をボスに追従させる
	if (coreSeparated == false) {
		coreCenterPosition = centerPosition;
		coreDegree = degree;
	}	

	/// 弾関係の更新処理

	// 発射地点の更新
	shotPoint = GetShotPosition(centerPosition);

	// 弾が発射されている時の処理
	for (int i = 0; i < kmaxBullet; i++) {
		if (isShot[i] == true && bulletAliveTime[i] > 0.0f) {

			// 場外判定を入れる　現状はわからないので割愛
			/*if () {

			}*/

			bulletCenterPosition[i].x += -cosf(bulletDirection[i]) * bulletSpeed;
			bulletCenterPosition[i].y += -sinf(bulletDirection[i]) * bulletSpeed;

			bulletAliveTime[i] -= 1.0f / 60.0f;
		}
		else {
			isShot[i] = false;
		}
	}

}

// 描画処理
void Boss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

	// ボス武器画像 現在は仮テクスチャ
	BaseDraw::DesignationDrawQuad(
		Boss::GetWeaponPosition(viewPosition),
		weaponSize,
		BaseTexture::kDebugTexture,
		weaponTextureSize,
		degree,
		0xFFFFFFFF
	);

	for (int i = 0; i < kmaxBullet; i++) {
		if (isShot[i] == true) {
			// 弾画像 現在は仮テクスチャ
			BaseDraw::DesignationDrawQuad(
				bulletCenterPosition[i],
				bulletSize,
				BaseTexture::kDebugTexture,
				bulletTextureSize,
				degree,
				0x000000FF
			);
		}
	}

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
	Novice::ScreenPrintf(0, 110, "actionWayPoint : %d", actionWayPoint);
	Novice::ScreenPrintf(0, 130, "actionBranch : %d", actionBranch);
	Novice::ScreenPrintf(0, 150, "isShot : %d", isShot[0]);
	Novice::ScreenPrintf(0, 190, "bulletPos * x : %4.2f y : %4.2f", bulletCenterPosition[0].x, bulletCenterPosition[0].y);

}

// 選択初期化関数
// 返り値：なし
// 引数：
// cenerPosition ... 座標を初期化するか
// degree ... 角度を初期化するか
// offset ... オフセットを初期化するか
// t ... tを初期化するか
// weapon ... 武器関係の変数を初期化するか
// 引数でTrueにしたものだけ初期化する関数
void Boss::SelectionInitialize(bool initCenterPosition, bool initDegree, bool initOffset, bool initT, bool initWeapon) {
	if (initCenterPosition == true) {
		// ボスの位置を画面中央に持っていく
		centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	}
	if (initDegree == true) {
		degree = 0;
	}
	if (initOffset == true) {
		offset = 0.0f;
	}
	if (initT == true) {
		t = 0.0f;
	}
	if (initWeapon == true) {
		weaponSize = { 0.0f };
	}
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

// 武器画像の相対座標を求める
Point Boss::GetWeaponPosition(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { 0, weaponSize.y / 2 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// 発射地点の相対座標を求める
Point Boss::GetShotPosition(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { 0, weaponSize.y };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// デバッグ用関数
void Boss::Debug() {
	// すべてをリセットする
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		Boss::Initialize();
	}

	if (endAction == true) {

		// 行動を開始させる
		if (BaseInput::GetKeyboardState(DIK_F, Trigger)) {
			inAction = true;
			endAction = false;
		}

		//行動パターン切り替え
		if (BaseInput::GetKeyboardState(DIK_1, Trigger)) {
			attackPattern = NONE;
		}
		else if (BaseInput::GetKeyboardState(DIK_2, Trigger)) {
			attackPattern = ROTATE;
		}
		else if (BaseInput::GetKeyboardState(DIK_3, Trigger)) {
			attackPattern = RUSH;
		}
		else if (BaseInput::GetKeyboardState(DIK_4, Trigger)) {
			attackPattern = SLASH;
		}
		else if (BaseInput::GetKeyboardState(DIK_5, Trigger)) {
			attackPattern = SHOT;
		}

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

	// 武器のサイズを変更
	// x
	if (BaseInput::GetKeyboardState(DIK_O, Press)) {
		weaponSize.x -= 1.0f;
	}
	else if(BaseInput::GetKeyboardState(DIK_P, Press)) {
		weaponSize.x += 1.0f;
	}
	// y
	if (BaseInput::GetKeyboardState(DIK_N, Press)) {
		weaponSize.y -= 1.0f;
	}
	else if (BaseInput::GetKeyboardState(DIK_M, Press)) {
		weaponSize.y += 1.0f;
	}

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
void Boss::ShakeEaseOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// シェイクイーズインアウト関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// shakeTime ... シェイクする時間
// ボスのシェイクの強さを少しずつ弱くしながら動かす関数
void Boss::ShakeEaseInOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_InOut(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// 行動なし関数
// 返り値：なし
// 引数：
// waitTime ... 待機する秒数
// 行動の合間に挟む関数。
void Boss::None(float waitFrame) {
	if (t < waitFrame) {
		t += 1.0f / 60.0f;
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
void Boss::Rotate(float endDegree, float RotateTime) {

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
void Boss::Rush(Point playerPosition, float readyTime, float rushTime, float backTime) {

	switch (actionWayPoint)
	{
		// 初期化
	case Boss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;

		// t初期化
		t = 0.0f;

		// 次の段階へ
		actionWayPoint++;
		break;
		// 事前動作(震える)
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// 指定された秒数振動する
			ShakeEaseOut(60, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// t初期化
			t = 0.0f;

			// プレイヤーの座標を取得
			prePlayerPosition = playerPosition;

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

			// 次へ
			actionWayPoint++;
		}
		break;
		// 突進
	case Boss::WAYPOINT2:
		if (t <= rushTime) {
			// ボスを取得したプレイヤーの向きに向かって突進させる
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化
			t = 0.0f;

			// 次の行動へ
			actionWayPoint++;
		}

		break;
		// 元の場所に戻る
	case Boss::WAYPOINT3:
		if (t <= backTime) {
			// ボスを元の座標に戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {

			// ボスの座標を元の位置に戻す（一応）
			centerPosition = prevCenterPosition;

			// t初期化
			t = 0.0f;

			// 行動終了
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

// 斬撃関数
// 返り値：なし
// 引数：
// playerPosition ... プレイヤーの座標
// readyTime ... 斬撃の準備にかかる秒数
// deployTime ... ブレードの展開にかかる秒数
// slashTime ... 斬撃にかかる秒数
// backTime ... 戻る時にかかる秒数
// ボスが斬撃を行う関数
void Boss::Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime) {
	switch (actionWayPoint)
	{
	// 初期化
	case Boss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;

		// ボスがどれだけ開くかを決める
		prevOffset = offset;
		nextOffset = 20;

		// 武器をどれだけ大きくするかを決める
		weaponSize = { 40, 0 };
		prevWeaponSize = weaponSize;
		nextWeaponSize = { weaponSize.x, 350.0f };
		
		// t初期化
		t = 0.0f;

		//次の段階へ
		actionWayPoint++;
		break;
	// 事前動作(震えてボスが開く)
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// 指定された秒数振動する
			ShakeEaseOut(60, readyTime);

			// ボスが少しづつ開く
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tをリセット
			t = 0.0f;

			//次へ
			actionWayPoint++;
		}
		break;
		// ブレード展開
	case Boss::WAYPOINT2:
		if (t <= deployTime) {

			// ブレードが伸びる
			weaponSize.y = BaseDraw::Ease_InOut(t, prevWeaponSize.y, nextWeaponSize.y - prevWeaponSize.y, deployTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化
			t = 0.0f;

			// 初期角度を設定
			prevDegree = degree;

			//次の行動をランダムに設定して分岐
			actionBranch = BaseMath::Random(0, 2);
			switch (actionBranch)
			{
				// 右回転
			case Boss::Pattern1:
				// 左向きに動かす
				nextDegree = prevDegree - 30;
				break;
				// 左回転
			case Boss::Pattern2:
				// 右向きに動かす
				
				nextDegree = prevDegree + 30;
				break;
				// 回転切り
			case Boss::Pattern3:
				break;
			default:
				break;
			}

			// 次の段階
			actionWayPoint++;
		}

		break;
		// 斬撃準備
	case Boss::WAYPOINT3:
		if (t <= preparationTime) {
			//ボスを回転させる
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);

			// 分岐：回転斬りの場合は振動させる
			if (actionBranch == Pattern3)
				ShakeEaseInOut(30, preparationTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tを初期化
			t = 0.0f;

			//プレイヤー座標取得
			prePlayerPosition = playerPosition;

			// プレイヤーがいる方向を求める
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// プレイヤーとの距離を求める
			float playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

			// プレイヤーとの距離が一定以下ならその場で斬撃を行う
			if (playerDistance < 200.0f) {
				playerDistance = 0.0f;
			}

			// 突進する座標を求める
			nextCenterPosition = {
				centerPosition.x + (cosf(playerDirection) * playerDistance / 1.25f),
				centerPosition.y + (sinf(playerDirection) * playerDistance / 1.25f)
			};

			// 初期角度を設定
			prevDegree = degree;

			// 行動分岐に基づいて回転角の設定
			switch (actionBranch)
			{
				// 右回転
			case Boss::Pattern1:
				nextDegree = prevDegree + 360;
				break;
				// 左回転
			case Boss::Pattern2:
				nextDegree = prevDegree - 360;
				break;
				// 回転切り
			case Boss::Pattern3:
				nextDegree = prevDegree + 720;
				break;
			default:
				break;
			}

			// 次へ
			actionWayPoint++;
		}
		break;
		// 斬撃
	case Boss::WAYPOINT4:
		if (t <= slashTime) {

			// ボスを回転させる
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, slashTime);
			
			// ボスを取得した角度を元に突進させる
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, slashTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, slashTime);

			// 分岐：回転斬り以外の場合はtにプラスする値を少しだけ多くする
			if (actionBranch == 2) {
				t += 0.75f / 60.0f;
			}
			else {
				t += 1.0f / 60.0f;
			}
		}
		else {
			// tを初期化
			t = 0.0f;
			// 次へ
			actionWayPoint++;
		}
		break;
	// 元の場所に戻る
	case Boss::WAYPOINT5:
		if (t <= backTime) {
			// 位置や角度、武器のサイズを元に戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			degree = BaseDraw::Ease_InOut(t, nextDegree, -nextDegree, backTime);
			weaponSize.y = BaseDraw::Ease_InOut(t, nextWeaponSize.y, -nextWeaponSize.y, backTime);
			offset = BaseDraw::Ease_InOut(t, nextOffset, -nextOffset, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			// ボス座標を初期化（一応）
			centerPosition = prevCenterPosition;

			// オフセット初期化
			offset = 0;

			// 角度初期化
			degree = 0;
			prevDegree = 0;
			nextDegree = 0;

			// t初期化
			t = 0.0f;

			// 行動終了
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	default:
		break;
	}
}

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
void Boss::Shot(Point playerPosition, float readyTime, float deployTime, float preparationTime, float shotTime, float backTime, float fireRate) {

	// ボスがプレイヤーに追従して回転する時に用いるカウント変数
	static int count;

	// ボスの発射レートを管理する変数
	static float fireRateCount;

	Novice::ScreenPrintf(0, 170, "nextDegree : %4.2f", fireRateCount);

	switch (actionWayPoint)
	{
		// 初期化
	case Boss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;
		nextCenterPosition = centerPosition;

		// ボスがどれだけ開くかを決める
		prevOffset = offset;
		nextOffset = 20;

		// 武器をどれだけ大きくするかを決める
		weaponSize = { 40, 0 };
		prevWeaponSize = weaponSize;
		nextWeaponSize = { weaponSize.x, 250.0f };

		// t初期化
		t = 0.0f;

		// カウンター系初期化
		count = 0;
		fireRateCount = 0;

		//次の段階へ
		actionWayPoint++;
		break;
		// 事前動作(震えてボスが開く)
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// 指定された秒数振動する
			ShakeEaseOut(60, readyTime);

			// ボスが少しづつ開く
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tをリセット
			t = 0.0f;

			//次へ
			actionWayPoint++;
		}
		break;
		// 銃展開
	case Boss::WAYPOINT2:
		if (t <= deployTime) {

			// 銃が伸びる
			weaponSize.y = BaseDraw::Ease_InOut(t, prevWeaponSize.y, nextWeaponSize.y - prevWeaponSize.y, deployTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化
			t = 0.0f;

			// 初期角度を設定
			prevDegree = degree;

			//次の行動をランダムに設定して分岐
			actionBranch = BaseMath::Random(0, 2);
			switch (actionBranch)
			{
				// 右回転
			case Boss::Pattern1:
				// 左向きに動かす
				nextDegree = prevDegree - 30;
				break;
				// 左回転
			case Boss::Pattern2:
				// 右向きに動かす
				nextDegree = prevDegree + 30;
				break;
				// 追従射撃
			case Boss::Pattern3:
				break;
			default:
				break;
			}

			// 次の段階
			actionWayPoint++;
		}

		break;
		// 射撃準備
	case Boss::WAYPOINT3:
		if (t <= preparationTime) {

			if (actionBranch == Pattern3) {

				// プレイヤー座標取得
				prePlayerPosition = playerPosition;

				// プレイヤーがいる方向を求める
				playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

				// プレイヤーのいる角度を取得
				nextDegree = BaseMath::RadiantoDegree(playerDirection) - 90;

				float absDegree = nextDegree - degree;

				degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);
			}
			else {
				// ボスを回転させる
				degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);
			}

			// 分岐：回転斬りの場合は振動させる
			if (actionBranch == Pattern3)
				ShakeEaseInOut(30, preparationTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tを初期化
			t = 0.0f;

			// 初期角度を設定
			prevDegree = degree;

			// 行動分岐に基づいて回転角の設定
			switch (actionBranch)
			{
				// 右回転
			case Boss::Pattern1:
				nextDegree = prevDegree + 720;
				break;
				// 左回転
			case Boss::Pattern2:
				nextDegree = prevDegree - 720;
				break;
				// 追従射撃
			case Boss::Pattern3:
				
				break;
			default:
				break;
			}

			// プレイヤー座標取得
			prePlayerPosition = playerPosition;

			// プレイヤーがいる方向を求める
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// 次へ
			actionWayPoint++;
		}
		break;
		// 射撃
	case Boss::WAYPOINT4:
		if (t <= shotTime) {

			if (actionBranch == Pattern3) {

				// プレイヤー座標取得
				prePlayerPosition = playerPosition;

				// プレイヤーがいる方向を求める
				playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

				// 初期角度を設定
				/*prevDegree = degree;*/

				// プレイヤーのいる角度を取得
				nextDegree = BaseMath::RadiantoDegree(playerDirection) - 90;

				float absDegree = nextDegree - degree;

				if (count == 0) {
					// ボスを回転させる
					if (absDegree < 0) {
						degree -= 1;
					}
					else if (absDegree > 0) {
						degree += 1;
					}
					count = 0;
				}
				else {
					count++;
				}
			}
			else {
				// ボスを回転させる
				degree = BaseDraw::Linear(t, prevDegree, nextDegree - prevDegree, shotTime);
			}

			// 射撃時に振動させる
			Shake(10);

			if (fireRateCount <= fireRate) {
				fireRateCount += 1.0 / 60.0f;
			}
			else {
				for (int i = 0; i < kmaxBullet; i++) {
					if (isShot[i] == false) {
						// 座標を発射地点まで移す
						bulletCenterPosition[i] = shotPoint;
						// 弾の発射向きを変更する
						bulletDirection[i] = BaseMath::DegreetoRadian(degree - 90);

						// 弾の生存時間を決める
						bulletAliveTime[i] = 5.0f;

						// 弾を発射した状態にする
						isShot[i] = true;

						// カウンター初期化
						fireRateCount = 0.0f;
						// 処理を抜ける
						break;
					}
				}
			}

			// tをプラスする
			t += 1.0f / 60.0f;

		}
		else {

			// 現在の座標を記録する
			nextCenterPosition = centerPosition;

			// 現在の角度を決める
			nextDegree = degree;

			// tを初期化
			t = 0.0f;
			// 次へ
			actionWayPoint++;
		}
		break;
		// 元の場所に戻る
	case Boss::WAYPOINT5:
		if (t <= backTime) {
			// 位置や角度、武器のサイズを元に戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);
			degree = BaseDraw::Ease_InOut(t, nextDegree, -nextDegree, backTime);
			weaponSize.y = BaseDraw::Ease_InOut(t, nextWeaponSize.y, -nextWeaponSize.y, backTime);
			offset = BaseDraw::Ease_InOut(t, nextOffset, -nextOffset, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			// ボス座標を初期化（一応）
			centerPosition = prevCenterPosition;

			// オフセット初期化
			offset = 0;

			// 角度初期化
			degree = 0;
			prevDegree = 0;
			nextDegree = 0;

			// t初期化
			t = 0.0f;

			// 行動終了
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
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
