#include "Class/Object/Player/Player.h"

// コンストラクタ
Player::Player(Point centerPosition, WireManager* _wireManager) {
	this->centerPosition = centerPosition;
	wireManager = _wireManager;

	Initialize();
}
// デストラクタ
Player::~Player() {

}


// 初期化
void Player::SuccessorInitialize() {

	width = 50;
	height = 100;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	angle = 0;
	angleVelocity = 0;

	isFlying = true;
	isAlive = true;
	reticlePosition = { BaseConst::kWindowHeight / 2.0f,BaseConst::kWindowHeight / 2.0f };
	int x, y;
	Novice::GetMousePosition(&x, &y);
	preMousePosition = { (float)x,(float)y };

	invincibleFrame = 0;
	// 現在右を向いているかどうか
	isRight = true;
	screenT = 0;

	// HP
	HP = 6;
	isDrawHP = false;
	drawHPFrame = 0;
}
// 更新
void Player::SuccessorUpdate() {

	if (invincibleFrame > 0) {
		invincibleFrame--;
	}

	// 回転を常に初期化
	angle = 0;
	angleVelocity = 0;

	if (!PublicFlag::kisStaging) {
		Move();
		ReticleMove();
		Jump();
		ShotWire();
	}

	// 前のフレームの分のマウス座標の取得
	int x, y;
	Novice::GetMousePosition(&x, &y);
	preMousePosition = { (float)x,(float)y };

	/// HP の描画の調整
	if (isDrawHP) {
		drawHPFrame--;
		if (drawHPFrame < 0) {
			drawHPFrame = 0;
			isDrawHP = false;
		}
	}

	if (!PublicFlag::kisStaging) {
		Point screenPos = BaseDraw::GetScreenPosition();

		/// x座標の調整 ///

		screenPos.x = centerPosition.x - BaseConst::kWindowWidth / 2.0f;

		/// y座標の調整 ///

		screenPos.y = centerPosition.y + 400;


		// スクリーン座標が画面外に行かないように調整
		if (screenPos.x < 0) {
			screenPos.x = 0;
		}
		else if (screenPos.x + BaseConst::kWindowWidth > BaseConst::kMapChipSizeWidth * BaseConst::kMapSizeWidth) {
			screenPos.x = BaseConst::kMapChipSizeWidth * BaseConst::kMapSizeWidth - BaseConst::kWindowWidth;
		}
		if (screenPos.y - BaseConst::kWindowHeight < 0) {
			screenPos.y = BaseConst::kWindowHeight;
		}
		else if (screenPos.y > BaseConst::kMapChipSizeHeight * BaseConst::kMapSizeHeight) {
			screenPos.y = BaseConst::kMapChipSizeHeight * BaseConst::kMapSizeHeight;
		}

		//////////　　ここで線形補完　　//////////
		// screenPos ... 移動先のカメラ
		// BaseDraw::GetScreenPosition ... このフレームでの現在のカメラ座標

		/*
		//// 前のフレームの、移動する先のカメラ座標を取得
		//static Point prevScreenPos = BaseDraw::GetScreenPosition();

		//// 線形補間中のカメラ位置
		//Point linerScreenPos = BaseDraw::GetScreenPosition();

		//// GetScreenPosition関数呼び出すのが面倒なので変数に入れます
		//Point nowScreenPos = linerScreenPos;

		//if (prevScreenPos.x != screenPos.x || prevScreenPos.y != screenPos.y) {
		//	screenT = 0.0f;
		//}

		//else if (nowScreenPos.x == screenPos.x && nowScreenPos.y == screenPos.y) {
		//	screenT = 0.0f;
		//}

		//screenT += 0.005f;

		//BaseMath::Clamp(screenT, 0.0f, 1.0f);

		//linerScreenPos = {
		//	(1 - screenT) * nowScreenPos.x + screenT * screenPos.x,
		//	(1 - screenT) * nowScreenPos.y + screenT * screenPos.y
		//};
		//// 次の移動先座標を保存
		//prevScreenPos = screenPos;
		// 最終的にカメラを設定する
		*/
		BaseDraw::SetScreenPosition(screenPos);

		//////////　　　ここまで　　　　//////////
	}
}
// 描画
void Player::Draw() {
	if (isAlive) {
		if (isDrawHP) {
			Point HPlt = {
				centerPosition.x - 20.0f * 2,centerPosition.y + width / 3.0f * 4.5f
			};
			float padding = 15;
			for (int i = 0; i < HP; i++) {
				if (i % 2 == 0) {
					BaseDraw::DrawSprite({ HPlt.x + i * padding,HPlt.y }, BaseTexture::kDebugTexture, { 10,20 }, 0.0f, RED);
				}
				else {
					BaseDraw::DrawSprite({ HPlt.x + (i - 1) * padding + 10,HPlt.y }, BaseTexture::kDebugTexture, { 10,20 }, 0.0f, RED);
				}
			}
		}

		if (invincibleFrame % 10 == 0) {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kDebugTexture, { width,height }, 0, RED);
		}
		else {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kDebugTexture, { width,height }, 0, 0x550000FF);
		}

		if (!PublicFlag::kisStaging) {

			// 射出先の線予測線を描画
			Point p1 = BaseDraw::WorldtoScreen(centerPosition);
			Point p2 = reticlePosition;
			// 射程を一定以下にする
			Point range = BaseMath::GetVector(p1, p2);
			// 最大射程より遠かったら
			float diff = BaseMath::GetLength(range) - BaseConst::kPlayerReticleRange;
			if (0.0f < diff) {
				Point e = BaseMath::GetNormalize(range);
				p2.x = p1.x + e.x * BaseConst::kWireMaxLength;
				p2.y = p1.y + e.y * BaseConst::kWireMaxLength;
			}
			//Point p2 = BaseMath::TurnPoint({ 2000, 0 }, -BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition));
			Novice::DrawLine(p1.x, p1.y, p2.x, p2.y, RED);

			// レティクルを描画
			Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 2, 2, 0, GREEN, kFillModeWireFrame);
			Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 10, 10, 0, GREEN, kFillModeWireFrame);
			Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 11, 11, 0, GREEN, kFillModeWireFrame);
			Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 12, 12, 0, GREEN, kFillModeWireFrame);
		}
	}
}



// どちらもUpdate()で毎フレーム呼び出すこと

// 移動関連
void Player::Move() {
	// コントローラー左スティック
	Point leftStick = { 0,0 };
	BaseInput::GetControllerLeftJoysState(&leftStick);
	// 左移動
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x -= 0.5f;
			isRight = false;
		}
	}
	else if (leftStick.x < 0.0f) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f * leftStick.x;
			isRight = false;
		}
	}
	else if (velocity.x < 0) {
		velocity.x += 0.1f;
	}
	// 右移動
	if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f;
			isRight = true;
		}
	}
	else if (0.0f < leftStick.x) {
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f * leftStick.x;
			isRight = true;
		}
	}
	else if (velocity.x > 0) {
		velocity.x -= 0.1f;
	}
}

// 照準移動
void Player::ReticleMove() {
	Point rightStick;
	BaseInput::GetControllerRightJoysState(&rightStick);
	int x, y;
	Novice::GetMousePosition(&x, &y);
	// マウスが動いている時
	if (preMousePosition.x != x || preMousePosition.y != y) {
		reticlePosition = BaseInput::GetMousePosition();
	}
	// スティックが入力されている時
	if (BaseMath::GetLength(rightStick) != 0.0f) {
		reticlePosition.x += 20 * rightStick.x;
		reticlePosition.y += 20 * rightStick.y;
	}
	// 照準を画面内に収める
	if (reticlePosition.x < BaseConst::kPlayerReticleSize) {
		reticlePosition.x = BaseConst::kPlayerReticleSize;
	}
	else if (BaseConst::kWindowWidth - BaseConst::kPlayerReticleSize < reticlePosition.x) {
		reticlePosition.x = BaseConst::kWindowWidth - BaseConst::kPlayerReticleSize;
	}
	if (reticlePosition.y < BaseConst::kPlayerReticleSize) {
		reticlePosition.y = BaseConst::kPlayerReticleSize;
	}
	else if (BaseConst::kWindowHeight - BaseConst::kPlayerReticleSize < reticlePosition.y) {
		reticlePosition.y = BaseConst::kWindowHeight - BaseConst::kPlayerReticleSize;
	}
	
	//// 射程を一定以下にする
	//Point range = BaseMath::GetVector(centerPosition, BaseDraw::ScreentoWorld(reticlePosition));
	//// 最大射程より遠かったら
	//float diff = BaseMath::GetLength(range) - BaseConst::kPlayerReticleRange;;
	//if (0.0f < diff) {
	//	Point e = BaseMath::GetNormalize(range);
	//	reticlePosition.x -= e.x * diff;
	//	reticlePosition.y += e.y * diff;
	//}
}


// ジャンプ
void Player::Jump() {
	// スペースキー || A || LT が押されたとき
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger) || BaseInput::GetControllerState(kControllerButtonA, Trigger) || BaseInput::GetControllerState(kControllerButtonL2, Trigger)) {
		if (!isFlying) {
			// 速度Yがマイナスのとき -> 0にリセットしてから
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// ジャンプ分の速度を足す
			velocity.y += 9.8f * 1.2f;
			// SEを再生
			Novice::PlayAudio(BaseAudio::kPlayerJump, 0, 0.5f);
		}
	}
}

// ワイヤー関連
void Player::ShotWire() {
	// 左クリック || RB || LB
	if (BaseInput::GetMouseState(LeftClick, Trigger) || BaseInput::GetControllerState(kControllerButtonR1, Trigger) || BaseInput::GetControllerState(kControllerButtonL1, Trigger)) {
		//reticlePosition = BaseInput::GetMousePosition();

		// 反動のベクトル
		Point p = { 3,0 };

		switch (wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition), this))
		{
			// ワイヤーの射出に成功した場合
		case 1:
			// 射出方向と反対方向のベクトルを足す
			p = BaseMath::TurnPoint(p, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition) + 180);
			if (isFlying) {
				velocity.x = p.x;
				velocity.y = p.y;
			}
			// SEを再生
			Novice::PlayAudio(BaseAudio::kPlayerShoot, 0, 0.5f);
			break;
			// 射出失敗
		case -1:
			break;
			// これ以上射出できない
		case -2:
			break;
		}
	}
	// 右クリック || RT
	if (BaseInput::GetMouseState(RightClick, Trigger) || BaseInput::GetControllerState(kControllerButtonR2, Trigger)) {
		wireManager->Attract();
	}
}


// 当たり判定をオーバーライド

// オブジェクト自体の当たり判定をチェックする関数
void Player::CheckFieldHitBox() {

	// 当たり判定をチェックする座標
	Point checkPoint;

	// プレイヤーから上の点
	checkPoint = { centerPosition.x,centerPosition.y + height / 2 };
	// 上がヒットしたとき
	if (MapManager::CheckHitBox(checkPoint)) {
		// 速度は0に
		velocity.y = 0;

		// ヒットしなくなるまで下へ補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			// 座標を下に
			centerPosition.y -= 1;
			// 再計算
			checkPoint.y -= 1;
		}
	}

	// プレイヤーから下の点
	checkPoint = { centerPosition.x,centerPosition.y - height / 2 };
	// 下がヒットしたとき
	if (MapManager::CheckHitBox(checkPoint)) {
		// 速度は0に
		velocity.y = 0;
		// 飛んでいないのでフラグを戻す
		isFlying = false;

		// ヒットしなくなるまで上へ補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			// 座標を上に
			centerPosition.y += 1;
			// 再計算
			checkPoint.y += 1;
		}
	}
	// 一個下のマスがヒットしていないときは空中ということなのでフラグをtrueに
	else if (!MapManager::CheckHitBox({ checkPoint.x ,checkPoint.y - 1 })) {
		isFlying = true;
	}

	// プレイヤーから左の点
	checkPoint = { centerPosition.x - width / 2,centerPosition.y };
	// 左がヒットしたとき
	if (MapManager::CheckHitBox(checkPoint)) {
		// 速度は0に
		velocity.x = 0;

		// ヒットしなくなるまで右へ補正する
		while (MapManager::CheckHitBox(checkPoint)) {

			// 座標を右に
			centerPosition.x += 1;
			// 再計算
			checkPoint.x += 1;
		}
	}

	// プレイヤーから右の点
	checkPoint = { centerPosition.x + width / 2,centerPosition.y };
	// 右がヒットしたとき
	if (MapManager::CheckHitBox(checkPoint)) {
		// 速度は0に
		velocity.x = 0;

		// ヒットしなくなるまで左へ補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			// 座標を左に
			centerPosition.x -= 1;
			// 再計算
			checkPoint.x -= 1;
		}
	}



	// プレイヤーから左上の点
	checkPoint = { centerPosition.x - width / 2,centerPosition.y + height / 2 };
	// 左上がヒットしたとき -> 補正する
	if (MapManager::CheckHitBox(checkPoint)) {
		// 補正分の座標
		Point correctionPos = { 0,0 };

		// 右下に補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			correctionPos.x += 1;
			correctionPos.y -= 1;
			checkPoint.x += 1;
			checkPoint.y -= 1;
		}

		// 補正終了後、より距離が短いほうのみを適応し、長いほうは破棄する

		// yのほうがxより短いor同じの場合 -> yを適応し、xは破棄
		if (-correctionPos.y <= correctionPos.x) {
			// 速度がプラスのときのみ0に
			if (velocity.y > 0) {
				velocity.y = 0;
			}

			// 補正を実行
			centerPosition.y += correctionPos.y;
		}
		// xのほうがyより短い場合 -> xを適応し、yは破棄
		else {
			// 速度がマイナスのときのみ0に
			if (velocity.x < 0) {
				velocity.x = 0;
			}

			// 補正を実行
			centerPosition.x += correctionPos.x;
		}
	}



	// プレイヤーから左下の点
	checkPoint = { centerPosition.x - width / 2,centerPosition.y - height / 2 };
	// 左下がヒットしたとき -> 補正する
	if (MapManager::CheckHitBox(checkPoint)) {
		// 補正分の座標
		Point correctionPos = { 0,0 };

		// 右上に補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			correctionPos.x += 1;
			correctionPos.y += 1;
			checkPoint.x += 1;
			checkPoint.y += 1;
		}

		// 補正終了後、より距離が短いほうのみを適応し、長いほうは破棄する

		// yのほうがxより短いor同じの場合 -> yを適応し、xは破棄
		if (correctionPos.y <= correctionPos.x) {
			// 速度がマイナスのときのみ0に
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// 飛んでいないのでフラグを戻す
			isFlying = false;

			// 補正を実行
			centerPosition.y += correctionPos.y;
		}
		// xのほうがyより短い場合 -> xを適応し、yは破棄
		else {
			// 速度がマイナスのときのみ0に
			if (velocity.x < 0) {
				velocity.x = 0;
			}

			// 補正を実行
			centerPosition.x += correctionPos.x;
		}
	}
	// もし空中判定された後の場合
	else if (isFlying) {
		// 一個下のマスがヒットしているときは空中ではないということなのでフラグをfalseに
		if (MapManager::CheckHitBox({ checkPoint.x,checkPoint.y - 1 })) {
			// ヒットしていないときは空中ということなのでフラグをtrueに
			isFlying = false;
		}
	}



	// プレイヤーから右上の点
	checkPoint = { centerPosition.x + width / 2,centerPosition.y + height / 2 };
	// 右上がヒットしたとき -> 補正する
	if (MapManager::CheckHitBox(checkPoint)) {
		// 補正分の座標
		Point correctionPos = { 0,0 };

		// 左下に補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			correctionPos.x -= 1;
			correctionPos.y -= 1;
			checkPoint.x -= 1;
			checkPoint.y -= 1;
		}

		// 補正終了後、より距離が短いほうのみを適応し、長いほうは破棄する

		// yのほうがxより短いor同じの場合 -> yを適応し、xは破棄
		if (-correctionPos.y >= -correctionPos.x) {
			// 速度がプラスのときのみ0に
			if (velocity.y > 0) {
				velocity.y = 0;
			}

			// 補正を実行
			centerPosition.y += correctionPos.y;
		}
		// xのほうがyより短い場合 -> xを適応し、yは破棄
		else {
			// 速度がプラスのときのみ0に
			if (velocity.x > 0) {
				velocity.x = 0;
			}

			// 補正を実行
			centerPosition.x += correctionPos.x;
		}
	}



	// プレイヤーから右下の点
	checkPoint = { centerPosition.x + width / 2,centerPosition.y - height / 2 };
	// 右下がヒットしたとき -> 補正する
	if (MapManager::CheckHitBox(checkPoint)) {
		// 補正分の座標
		Point correctionPos = { 0,0 };

		// 左上に補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			correctionPos.x -= 1;
			correctionPos.y += 1;
			checkPoint.x -= 1;
			checkPoint.y += 1;
		}

		// 補正終了後、より距離が短いほうのみを適応し、長いほうは破棄する

		// yのほうがxより短いor同じの場合 -> yを適応し、xは破棄
		if (correctionPos.y <= -correctionPos.x) {
			// 速度がマイナスのときのみ0に
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// 飛んでいないのでフラグを戻す
			isFlying = false;

			// 補正を実行
			centerPosition.y += correctionPos.y;
		}
		// xのほうがyより短い場合 -> xを適応し、yは破棄
		else {
			// 速度がプラスのときのみ0に
			if (velocity.x > 0) {
				velocity.x = 0;
			}

			// 補正を実行
			centerPosition.x += correctionPos.x;
		}
	}
	// もし空中判定された後の場合
	else if (isFlying) {
		// 一個下のマスがヒットしているときは空中ではないということなのでフラグをfalseに
		if (MapManager::CheckHitBox({ checkPoint.x,checkPoint.y - 1 })) {
			// ヒットしていないときは空中ということなのでフラグをtrueに
			isFlying = false;
		}
	}

	//////////////////////////
	///　　当たり判定チェック　　//
	//////////////////////////

	// 無敵時間の場合 -> 当たり判定を検証しない
	while (invincibleFrame <= 0) {
		int atk;
		// 攻撃に対する当たり判定を実装
		atk = EnemyAttackHitBox::CheckHitBox(centerPosition);
		if (atk != -1) {
			// ノックバック
			Point p = { 10,0 };

			if (isRight) {
				p = BaseMath::TurnPoint(p, 90 + 45);
			}
			else {
				p = BaseMath::TurnPoint(p, 45);
			}

			velocity.x = p.x;
			velocity.y = p.y;
			// 無敵時間を設定
			invincibleFrame = 60;
			// SEを再生
			Novice::PlayAudio(BaseAudio::kPlayerDamage, 0, 0.5f);
			// HP を減らす
			HP -= atk;
			// HP 表示
			isDrawHP = true;
			drawHPFrame = invincibleFrame + 180;

			break;
		}
		// 外殻に対する当たり判定
		atk = EnemyAttackHitBox::CheckHitEllipse(centerPosition);
		if (atk != -1) {
			// ノックバック
			Point p = { 20,0 };

			if (isRight) {
				p = BaseMath::TurnPoint(p, 90 + 45);
			}
			else {
				p = BaseMath::TurnPoint(p, 45);
			}

			velocity.x = p.x;
			velocity.y = p.y;
			// 無敵時間を設定
			invincibleFrame = 30;
			// SEを再生
			Novice::PlayAudio(BaseAudio::kPlayerDamage, 0, 0.5f);
			// HP を減らす
			HP -= atk;
			// HP 表示
			isDrawHP = true;
			drawHPFrame = invincibleFrame + 180;

			break;
		}
		break;
	}

	////////////////////////
	///　　　　ここまで　　　　//
	////////////////////////
}


ObjectType Player::GetType() {
	return typePlayer;
}
