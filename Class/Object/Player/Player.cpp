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

	// アニメーション
	state = playerIdle;
	preState = state;
	buffState = state;

	stateChengeFlame = 0;

	animationFlameCount = 0;
	animationFlame = 0;

	// プレイヤーの移動制限
	isLimitMove = true;

	// 制限する左上座標
	limitLeftTop = { 0,(float)BaseConst::kTutorialStageSizeHeight * BaseConst::kMapChipSizeHeight };
	// 制限する右下座標
	limitRightBottom = { (float)BaseConst::kTutorialStageSizeWidth * BaseConst::kMapChipSizeWidth,0 };

	resqawnPosition = { -1000,-1000 };
	preCenterPosition = { -1000,-1000 };
	preIsFlying = isFlying;
	isRespawn = false;

}

// 更新
void Player::Update() {
	acceleration = { 0,0 };

	// 加速度や速度を継承先で変更
	SuccessorUpdate();

	// 加速度に重力を追加
	if (isFlying) {
		if (velocity.y < -(BaseConst::kPlayerVelocityLimit)) {

		}
		// 速度制限にかかっているときは追加しない
		else {
			acceleration.y -= BaseConst::kPlayerGravitationalAcceleration;
		}
	}

	// 加速度を追加
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	// トンネリング防止のため分割
	for (int i = 0; i < 10; i++) {

		// 速度を追加
		centerPosition.x += velocity.x * 0.1f;
		centerPosition.y += velocity.y * 0.1f;

		CheckFieldHitBox();
	}

	// 回転速度を追加
	angle += angleVelocity;

	if (angleVelocity > 0) {
		centerPosition.x -= 0.5f * angleVelocity;
	}
	else if (angleVelocity < 0) {
		centerPosition.x -= 0.5f * angleVelocity;
	}


	// 速度を少しずつ減速させる
	if (velocity.x > 0) {
		velocity.x -= 0.02f;
		if (velocity.x < 0) {
			velocity.x = 0;
		}
	}
	else if (velocity.x < 0) {
		velocity.x += 0.02f;
		if (velocity.x > 0) {
			velocity.x = 0;
		}
	}

	if (velocity.y > 0) {
		velocity.y -= 0.02f;
		if (velocity.y < 0) {
			velocity.y = 0;
		}
	}
	else if (velocity.y < 0) {
		velocity.y += 0.02f;
		if (velocity.y > 0) {
			velocity.y = 0;
		}
	}

	// 回転速度を減速させていく
	/*if (angleVelocity > BaseConst::kPlayerVelocityLimit) {
		angleVelocity -= 0.05f;
		if (angleVelocity < 0) {
			angleVelocity = 0;
		}
	}
	else if (angleVelocity < -BaseConst::kPlayerVelocityLimit) {
		angleVelocity += 0.05f;
		if (angleVelocity > 0) {
			angleVelocity = 0;
		}
	}*/
}


// 更新
void Player::SuccessorUpdate() {
	angle = 0;
	angleVelocity = 0;
	preReticlePosition = reticlePosition;
	if (isAlive) {
		preState = state;
		//// テスト
		//if (BaseInput::GetKeyboardState(DIK_P, Trigger)) {
		//	isLimitMove = !isLimitMove;
		//}


		// 回転を常に初期化

		if (!PublicFlag::kisStaging) {
			Move();
			ReticleMove();
			Jump();
			ShotWire();
			LimitMovement();
			Respawn();
		}
		else {
			reticlePosition = preReticlePosition;
			velocity.x = 0;
			state = playerIdle;
		}

		Animation();

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

		// カメラ移動
		// 演出中以外の時
		if (!PublicFlag::kisStaging) {
			Point screenPos = BaseDraw::GetScreenPosition();

			/// x座標の調整 ///

			screenPos.x = centerPosition.x - BaseConst::kWindowWidth / 2.0f;

			/// y座標の調整 ///

			screenPos.y = centerPosition.y + 400;


			// スクリーン座標が画面外に行かないように調整
			if (MapManager::GetisBoss()) {
				if (screenPos.x < 0) {
					screenPos.x = 0;
				}
				else if (screenPos.x + BaseConst::kWindowWidth > BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth) {
					screenPos.x = BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth - BaseConst::kWindowWidth;
				}
				if (screenPos.y - BaseConst::kWindowHeight < 0) {
					screenPos.y = BaseConst::kWindowHeight;
				}
				else if (screenPos.y > BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight) {
					screenPos.y = BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight;
				}
			}
			else {
				if (screenPos.x < 0) {
					screenPos.x = 0;
				}
				else if (screenPos.x + BaseConst::kWindowWidth > BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth) {
					screenPos.x = BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth - BaseConst::kWindowWidth;
				}
				if (screenPos.y - BaseConst::kWindowHeight < 0) {
					screenPos.y = BaseConst::kWindowHeight;
				}
				else if (screenPos.y > BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight) {
					screenPos.y = BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight;
				}
			}
			// 移動制限中
			if (isLimitMove) {
				if (screenPos.x < limitLeftTop.x) {
					screenPos.x = limitLeftTop.x;
				}
				else if (limitRightBottom.x < screenPos.x + BaseConst::kWindowWidth) {
					screenPos.x = limitRightBottom.x - BaseConst::kWindowWidth;
				}
				if (screenPos.y - BaseConst::kWindowHeight < limitRightBottom.y) {
					screenPos.y = limitRightBottom.y + BaseConst::kWindowHeight;
				}
				else if (limitLeftTop.y < screenPos.y) {
					screenPos.y = limitLeftTop.y;
				}

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
		preIsFlying = isFlying;
		preCenterPosition = centerPosition;
	}
	if (0 < invincibleFrame) {
		invincibleFrame--;
	}
	// HP管理
	if (HP <= 0) {
		HP = 0;
		isAlive = false;
		velocity.x = 0;
		ReticleMove();
		Animation();
		if (invincibleFrame < 5) {
			invincibleFrame = 65;
		}
	}
}
// 描画
void Player::Draw() {
	// HP の描画
	if (isDrawHP) {
		Point HPlt = {
			centerPosition.x - 20.0f * 2,centerPosition.y + width / 3.0f * 4.5f
		};
		float padding = 30;
		int fullHp = HP / 2;
		int i = 0;
		for (; i < fullHp; i++) {
			BaseDraw::DrawSprite({ HPlt.x + i * padding,HPlt.y }, BaseTexture::kPlayerHeart[0], { 20 / 256.0f,20 / 256.0f }, 0.0f, WHITE);
		}
		if (HP % 2 == 1) {
			BaseDraw::DrawSprite({ HPlt.x + i * padding,HPlt.y }, BaseTexture::kPlayerHeart[1], { 20 / 256.0f,20 / 256.0f }, 0.0f, WHITE);
		}
	}

	Point lt = { centerPosition.x - width / 2.0f, centerPosition.y + height / 2.0f };
	if (invincibleFrame % 10 == 0) {
		/*if (isRight == true) {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kRPlayerIdle, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
		}
		else {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kLPlayerIdle, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
		}*/
		if (isRight) {
			switch (state)
			{
			case playerIdle:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerIdle, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerRun:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerRun[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerJump:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerRase:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerFall:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerLand:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerShot:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerShot, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerPull:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerPull, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			default:
				break;
			}
		}
		else {
			switch (state)
			{
			case playerIdle:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerIdle, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerRun:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerRun[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerJump:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerRase:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerFall:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerLand:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerShot:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerShot, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			case playerPull:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerPull, { 1.0f,1.0f }, 0, 0xFFFFFFFF);
				break;
			default:
				break;
			}
		}
	}
	else {
		/*if (isRight == true) {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kRPlayerIdle, { 1.0f,1.0f }, 0, 0x550000FF);
		}
		else {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kLPlayerIdle, { 1.0f,1.0f }, 0, 0x550000FF);
		}*/
		if (isRight) {
			switch (state)
			{
			case playerIdle:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerIdle, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerRun:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerRun[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerJump:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerRase:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerFall:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerLand:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerShot:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerShot, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerPull:
				BaseDraw::DrawSprite(lt, BaseTexture::kRPlayerPull, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			default:
				break;
			}
		}
		else {
			switch (state)
			{
			case playerIdle:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerIdle, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerRun:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerRun[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerJump:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerRase:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerFall:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerLand:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerJump[animationFlame], { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerShot:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerShot, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			case playerPull:
				BaseDraw::DrawSprite(lt, BaseTexture::kLPlayerPull, { 1.0f,1.0f }, 0, 0xFFAAAAFF);
				break;
			default:
				break;
			}
		}
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
	else if (velocity.x > 0 && isFlying) {
		velocity.x -= 0.1f;
	}
	else if (velocity.x > 0) {
		velocity.x -= 0.5f;
	}
	if (!isFlying && velocity.x != 0.0f) {
		state = playerRun;
	}
	else if (!isFlying && velocity.x == 0.0f) {
		state = playerIdle;
	}
	else {
		state = playerRase;
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
	if (0 < velocity.y) {
		state = playerRase;
	}
	else if (velocity.y < 0) {
		state = playerFall;
	}
	// スペースキー || X || Y || L || R が押されたとき
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger) || BaseInput::GetControllerState(kControllerButtonX, Trigger) || BaseInput::GetControllerState(kControllerButtonY, Trigger) || BaseInput::GetControllerState(kControllerButtonL1, Trigger) || BaseInput::GetControllerState(kControllerButtonR1, Trigger)) {
		if (!isFlying) {
			// 速度Yがマイナスのとき -> 0にリセットしてから
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// ジャンプ分の速度を足す
			velocity.y += 9.8f * 1.2f;
			// SEを再生
			Novice::PlayAudio(BaseAudio::kPlayerJump, 0, 0.5f);
			state = playerJump;
		}
	}
}

// ワイヤー関連
void Player::ShotWire() {
	// 左クリック || RT
	if (BaseInput::GetMouseState(LeftClick, Trigger) || BaseInput::GetControllerState(kControllerButtonR2B, Trigger)) {
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
				velocity.x += p.x;
				velocity.y += p.y;
			}
			// SEを再生
			Novice::PlayAudio(BaseAudio::kPlayerShoot, 0, 0.5f);
			state = playerShot;
			break;
			// 射出失敗
		case -1:
			break;
			// これ以上射出できない
		case -2:
			break;
		}
	}
	// 右クリック || LT
	if (BaseInput::GetMouseState(RightClick, Trigger) || BaseInput::GetControllerState(kControllerButtonL2A, Trigger)) {
		wireManager->Attract();
		state = playerPull;
	}
}

// 移動制限関数
void Player::LimitMovement() {

	Point checkPoint;

	////////////////////////////////
	/// 移動制限がある場合の処理 ///
	////////////////////////////////


	if (isLimitMove) {
		// プレイヤーから上の点
		checkPoint = { centerPosition.x,centerPosition.y + height / 2 };
		if (limitLeftTop.y < checkPoint.y) {
			// 速度は0に
			velocity.y = 0;

			// ヒットしなくなるまで下へ補正する
			while (limitLeftTop.y < checkPoint.y) {
				// 座標を下に
				centerPosition.y -= 1;
				// 再計算
				checkPoint.y -= 1;
			}
		}
		// プレイヤーから下の点
		// 瞬時にリスポーン
		checkPoint = { centerPosition.x,centerPosition.y - height / 2 };
		if (checkPoint.y + height * 2.0f < limitRightBottom.y) {
			// リスポーン
			isRespawn = true;
			HP--;
			invincibleFrame = 30;
			isDrawHP = true;
			drawHPFrame = invincibleFrame + 180;
			// SEを再生
			//Novice::PlayAudio(BaseAudio::kPlayerDamage, 0, 0.5f);
		}
		// プレイヤーから左の点
		checkPoint = { centerPosition.x - width / 2,centerPosition.y };
		if (checkPoint.x < limitLeftTop.x) {
			// 速度は0に
			velocity.x = 0;

			// ヒットしなくなるまで右へ補正する
			while (checkPoint.x < limitLeftTop.x) {
				// 座標を右へ
				centerPosition.x += 1;
				// 再計算
				checkPoint.x += 1;
			}
		}
		// プレイヤーから右の点
		checkPoint = { centerPosition.x + width / 2,centerPosition.y };
		if (limitRightBottom.x < checkPoint.x) {
			// 速度は0に
			velocity.x = 0;

			// ヒットしなくなるまで左へ補正する
			while (limitRightBottom.x < checkPoint.x) {
				// 座標を左に
				centerPosition.x -= 1;
				// 再計算
				checkPoint.x -= 1;
			}
		}

	}

	////////////////////////////////
	///			ここまで		 ///
	////////////////////////////////

}

void Player::Respawn() {
	// 地面から離れた瞬間の座標を保存
	if (isFlying != preIsFlying && preIsFlying == false) {

		resqawnPosition.x = (int)(preCenterPosition.x / BaseConst::kMapChipSizeWidth) * BaseConst::kMapChipSizeWidth + BaseConst::kMapChipSizeWidth / 2.0f;
		resqawnPosition.y = (int)(preCenterPosition.y / BaseConst::kMapChipSizeHeight) * BaseConst::kMapChipSizeHeight + BaseConst::kMapChipSizeHeight / 2.0f;

	}
	/*
	Point r = BaseDraw::WorldtoScreen({ resqawnPosition.x - width / 2.0f,resqawnPosition.y + height / 2.0f });
	Point r1 = BaseDraw::WorldtoScreen({ (centerPosition.x) / BaseConst::kMapChipSizeWidth * BaseConst::kMapChipSizeWidth - width / 2.0f,centerPosition.y / BaseConst::kMapChipSizeHeight * BaseConst::kMapChipSizeHeight + height / 2.0f });
	Point r2 = BaseDraw::WorldtoScreen({ (preCenterPosition.x) / BaseConst::kMapChipSizeWidth * BaseConst::kMapChipSizeWidth - width / 2.0f,preCenterPosition.y / BaseConst::kMapChipSizeHeight * BaseConst::kMapChipSizeHeight + height / 2.0f });
	Novice::DrawBox(r.x, r.y, width, height, 0.0f, GREEN, kFillModeWireFrame);
	Novice::DrawBox(r1.x, r1.y, width, height, 0.0f, 0xFF0000FF, kFillModeWireFrame);
	Novice::DrawBox(r2.x, r2.y, width, height, 0.0f, 0x0000FFFF, kFillModeWireFrame);
	Novice::ScreenPrintf(10, 20, "%d", isRespawn);
	Novice::ScreenPrintf(10, 40, "%d  %d", BaseConst::kMapChipSizeWidth, BaseConst::kMapChipSizeHeight);
	Novice::ScreenPrintf(10, 60, "%.2f  %.2f", preCenterPosition.x, preCenterPosition.y);
	Novice::ScreenPrintf(10, 80, "%.2f  %.2f", resqawnPosition.x, resqawnPosition.y);
	Novice::ScreenPrintf(10, 100, "%d  %d", (int)(resqawnPosition.x / BaseConst::kMapChipSizeWidth), (int)(resqawnPosition.y / BaseConst::kMapChipSizeHeight));
	Novice::ScreenPrintf(10, 120, "%.2f  %.2f", (int)(resqawnPosition.x / BaseConst::kMapChipSizeWidth) * (float)BaseConst::kMapChipSizeWidth, (int)(resqawnPosition.y / (float)BaseConst::kMapChipSizeHeight) * BaseConst::kMapChipSizeHeight);
	if (BaseInput::GetKeyboardState(DIK_P, Trigger)) {
		isRespawn = !isRespawn;
	}
	//*/
	if (isRespawn) {
		centerPosition = resqawnPosition;
		velocity = { 0,0 };
		acceleration = { 0,0 };
		wireManager->Initialize();
		isFlying = false;
		isRespawn = false;
	}
}

// アニメーション
void Player::Animation() {
	if (!isAlive) {
		state = playerIdle;
	}
	stateChengeFlame++;
	if (100 < stateChengeFlame) {
		stateChengeFlame = BaseConst::kPlayerAnimationFlame[buffState] + 1;
	}
	else if (stateChengeFlame < BaseConst::kPlayerAnimationFlame[buffState]) {
		state = buffState;
	}
	// 前のフレームと今のフレームが違い、
	// 変わってからの状態と今の状態が違う時
	if (buffState != state) {
		// 状態が変わったとする
		animationFlame = 0;
		animationFlameCount = 0;
		stateChengeFlame = 0;
		buffState = state;
	}
	else {
		if (buffState != state) {
			buffState = state;
		}
	}
	animationFlameCount++;
	if (BaseConst::kPlayerMaxAnimationFlame < animationFlameCount) {
		animationFlame++;
		animationFlameCount = 0;

	}
	// 状態を取得
	switch (state)
	{
	case playerIdle:
		animationFlame = 0;
		break;
	case playerRun:
		if (BaseConst::kPlayerTextureRunNum <= animationFlame) {
			animationFlame = 0;
		}
		break;
	case playerJump:
		animationFlame = 0;
		break;
	case playerRase:
		animationFlame = 1;
		break;
	case playerFall:
		animationFlame = 2;
		break;
	case playerLand:
		animationFlame = 3;
		break;
	case playerShot:
		animationFlame = 0;
		break;
	case playerPull:
		animationFlame = 0;
		break;
	default:
		break;
	}
	/*
	Novice::ScreenPrintf(10, 20, "state  pre    buff");
	Novice::ScreenPrintf(10, 60, "%d", animationFlame);
	int a = 10, b = a + 50, c = b + 50;
	switch (state)
	{
	case playerIdle:
		Novice::ScreenPrintf(a, 40, "Idle");
		break;
	case playerRun:
		Novice::ScreenPrintf(a, 40, "Run");
		break;
	case playerJump:
		Novice::ScreenPrintf(a, 40, "Jump");
		break;
	case playerRase:
		Novice::ScreenPrintf(a, 40, "Rase");
		break;
	case playerFall:
		Novice::ScreenPrintf(a, 40, "Fall");
		break;
	case playerLand:
		Novice::ScreenPrintf(a, 40, "Land");
		break;
	case playerShot:
		Novice::ScreenPrintf(a, 40, "Shot");
		break;
	case playerPull:
		Novice::ScreenPrintf(a, 40, "Pull");
		break;
	default:
		break;
	}
	switch (preState)
	{
	case playerIdle:
		Novice::ScreenPrintf(b, 40, "Idle");
		break;
	case playerRun:
		Novice::ScreenPrintf(b, 40, "Run");
		break;
	case playerJump:
		Novice::ScreenPrintf(b, 40, "Jump");
		break;
	case playerRase:
		Novice::ScreenPrintf(b, 40, "Rase");
		break;
	case playerFall:
		Novice::ScreenPrintf(b, 40, "Fall");
		break;
	case playerLand:
		Novice::ScreenPrintf(b, 40, "Land");
		break;
	case playerShot:
		Novice::ScreenPrintf(b, 40, "Shot");
		break;
	case playerPull:
		Novice::ScreenPrintf(b, 40, "Pull");
		break;
	default:
		break;
	}
	switch (buffState)
	{
	case playerIdle:
		Novice::ScreenPrintf(c, 40, "Idle");
		break;
	case playerRun:
		Novice::ScreenPrintf(c, 40, "Run");
		break;
	case playerJump:
		Novice::ScreenPrintf(c, 40, "Jump");
		break;
	case playerRase:
		Novice::ScreenPrintf(c, 40, "Rase");
		break;
	case playerFall:
		Novice::ScreenPrintf(c, 40, "Fall");
		break;
	case playerLand:
		Novice::ScreenPrintf(c, 40, "Land");
		break;
	case playerShot:
		Novice::ScreenPrintf(c, 40, "Shot");
		break;
	case playerPull:
		Novice::ScreenPrintf(c, 40, "Pull");
		break;
	default:
		break;
	}
	//*/
}

// 当たり判定をオーバーライド

// オブジェクト自体の当たり判定をチェックする関数
void Player::CheckFieldHitBox() {

	// 当たり判定をチェックする座標
	Point checkPoint;

#pragma region 上下左右


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
		state = playerLand;
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
		if (0 < velocity.y) {
			state = playerRase;
		}
		else if (velocity.y == 0.0f) {
			state = playerIdle;
		}
		else {
			state = playerFall;
		}
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

#pragma endregion


#pragma region 四隅



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
			state = playerLand;
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
			state = playerIdle;
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
			state = playerLand;
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
			state = playerIdle;
		}
	}

#pragma endregion

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
