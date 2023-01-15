#include "Class/Include/Object/Player/Player.h"

// コンストラクタ
Player::Player(Point centerPosition, WireManager* _wireManager) {
	this->centerPosition = centerPosition;
	wireManager = _wireManager;
	reticlePosition = { -100,-100 };
}
// デストラクタ
Player::~Player() {

}


// 初期化
void Player::SuccessorInitialize() {
	centerPosition = { -10000,-10000 };

	width = 1;
	height = 1;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;
	reticlePosition = { -10000,-10000 };

}
// 更新
void Player::SuccessorUpdate() {

	reticlePosition = BaseInput::GetMousePosition();

	Move();
	//wireManager.Update();
	ShotWire();

}
// 描画
void Player::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
	BaseDraw::DrawQuad(BaseDraw::WorldtoScreen(reticlePosition), BaseTexture::kDebugTexture, { 20,20 }, 1.0f, 0.0f, WHITE);
	Novice::ScreenPrintf(10, 10, "Reticle:%.2f %.2f", reticlePosition.x, reticlePosition.y);
	Novice::ScreenPrintf(10, 30, "center:%.2f %.2f", centerPosition.x, centerPosition.y);
}



// どちらもUpdate()で毎フレーム呼び出すこと

// 移動関連
void Player::Move() {

	// 左移動
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		velocity.x -= 0.2f;
	}
	// 右移動
	if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		velocity.x += 0.2f;
	}
}

// ワイヤー関連
void Player::ShotWire() {
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		reticlePosition = BaseInput::GetMousePosition();
		//float angle = atan2(centerPosition.y - ReticlePosition.y, centerPosition.x - ReticlePosition.x);

		//wireManager->Shot(centerPosition, BaseMath::RadiantoDegree(angle), this);
		wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition), this);



	}
	if (BaseInput::GetMouseState(RightClick, Trigger)) {
		wireManager->Attract();
	}
}


/*
// 上下左右の当たり判定の関数
void Player::CheckHitBoxRhombus() {

	// 当たり判定をチェックする座標
	Point checkPoint;


	// プレイヤーから上の点
	checkPoint = { position.x,position.y + 24 / 2 };
	// 上がヒットしたとき
	if (Map::isHittingBlock(checkPoint)) {
		// 速度は0に
		velocity.y = 0;

		// ヒットしなくなるまで下へ補正する
		while (Map::isHittingBlock(checkPoint)) {
			// 座標を下に
			position.y -= 1;
			// 再計算
			checkPoint.y -= 1;
		}
	}



	// プレイヤーから下の点
	checkPoint = { position.x,position.y - 24 / 2 };
	// 下がヒットしたとき
	if (Map::isHittingBlock(checkPoint)) {
		// 速度は0に
		velocity.y = 0;
		// 飛んでいないのでフラグを戻す
		isFlying = false;
		BaseEffectManager::MakeNewEffect(position, EffectType::JumpDust);

		// ヒットしなくなるまで上へ補正する
		while (Map::isHittingBlock(checkPoint)) {
			// 座標を上に
			position.y += 1;
			// 再計算
			checkPoint.y += 1;
		}
	}
	// 一個下のマスがヒットしていないときは空中ということなのでフラグをtrueに
	else if (!Map::isHittingBlock({ checkPoint.x ,checkPoint.y - 1 })) {
		isFlying = true;
	}



	// プレイヤーから左の点
	checkPoint = { position.x - 24 / 2,position.y };
	// 左がヒットしたとき
	if (Map::isHittingBlock(checkPoint)) {
		// 速度は0に
		velocity.x = 0;
		// モーション中でない場合 かつ 地面についていない場合 -> 壁滑りフラグをtrueに
		if (!isJumping && !isDashing && !isKickedWall && isFlying) {
			isSlipingLeftWall = true;
			setPlayerToMouseAngle();
		}

		// ヒットしなくなるまで右へ補正する
		while (Map::isHittingBlock(checkPoint)) {

			// 座標を右に
			position.x += 1;
			// 再計算
			checkPoint.x += 1;
		}
	}
	// 一個左のマスがヒットしていないときは壁滑り終了ということなのでフラグをtrueに
	else if (!Map::isHittingBlock({ checkPoint.x - 32,checkPoint.y })) {
		isSlipingLeftWall = false;
	}
	// 地面についた場合もフラグをfalseに
	else if (!isFlying) {
		isSlipingLeftWall = false;
	}

	// すぐ左に壁がある場合 -> 速度を消す
	if (Map::isHittingBlock({ checkPoint.x - 1 ,checkPoint.y })) {
		if (velocity.x < 0) {
			velocity.x = 0;
		}
	}



	// プレイヤーから右の点
	checkPoint = { position.x + 24 / 2,position.y };
	// 右がヒットしたとき
	if (Map::isHittingBlock(checkPoint)) {
		// 速度は0に
		velocity.x = 0;
		// モーション中でない場合 かつ 地面についていない場合 -> 壁滑りフラグをtrueに
		if (!isJumping && !isDashing && !isKickedWall && isFlying) {
			isSlipingRightWall = true;
			setPlayerToMouseAngle();
		}

		// ヒットしなくなるまで左へ補正する
		while (Map::isHittingBlock(checkPoint)) {
			// 座標を左に
			position.x -= 1;
			// 再計算
			checkPoint.x -= 1;
		}
	}
	// 一個右のマスがヒットしていないときは壁滑り終了ということなのでフラグをtrueに
	else if (!Map::isHittingBlock({ checkPoint.x + 32,checkPoint.y })) {
		isSlipingRightWall = false;
	}
	// 地面についた場合もフラグをfalseに
	else if (!isFlying) {
		isSlipingRightWall = false;
	}

	// すぐ右に壁がある場合 -> 速度を消す
	if (Map::isHittingBlock({ checkPoint.x + 1 ,checkPoint.y })) {
		if (velocity.x > 0) {
			velocity.x = 0;
		}
	}
}

// 左上、左下、右上、右下の当たり判定の関数
void Player::CheckHitBoxQuad() {

	// 当たり判定をチェックする座標
	Point checkPoint;



	// プレイヤーから左上の点
	checkPoint = { position.x - 24 / 2,position.y + 24 / 2 };
	// 左上がヒットしたとき -> 補正する
	if (Map::isHittingBlock(checkPoint)) {
		// 補正分の座標
		Point correctionPos = { 0,0 };

		// 右下に補正する
		while (Map::isHittingBlock(checkPoint)) {
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
			position.y += correctionPos.y;
		}
		// xのほうがyより短い場合 -> xを適応し、yは破棄
		else {
			// 速度がマイナスのときのみ0に
			if (velocity.x < 0) {
				velocity.x = 0;
			}

			// 補正を実行
			position.x += correctionPos.x;
		}
	}



	// プレイヤーから左下の点
	checkPoint = { position.x - 24 / 2,position.y - 24 / 2 };
	// 左下がヒットしたとき -> 補正する
	if (Map::isHittingBlock(checkPoint)) {
		// 補正分の座標
		Point correctionPos = { 0,0 };

		// 右上に補正する
		while (Map::isHittingBlock(checkPoint)) {
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
			position.y += correctionPos.y;
		}
		// xのほうがyより短い場合 -> xを適応し、yは破棄
		else {
			// 速度がマイナスのときのみ0に
			if (velocity.x < 0) {
				velocity.x = 0;
			}

			// 補正を実行
			position.x += correctionPos.x;
		}
	}
	// もし空中判定された後の場合
	else if (isFlying) {
		// 一個下のマスがヒットしているときは空中ではないということなのでフラグをfalseに
		if (Map::isHittingBlock({ checkPoint.x,checkPoint.y - 1 })) {
			// ヒットしていないときは空中ということなのでフラグをtrueに
			isFlying = false;
		}
	}



	// プレイヤーから右上の点
	checkPoint = { position.x + 24 / 2,position.y + 24 / 2 };
	// 右上がヒットしたとき -> 補正する
	if (Map::isHittingBlock(checkPoint)) {
		// 補正分の座標
		Point correctionPos = { 0,0 };

		// 左下に補正する
		while (Map::isHittingBlock(checkPoint)) {
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
			position.y += correctionPos.y;
		}
		// xのほうがyより短い場合 -> xを適応し、yは破棄
		else {
			// 速度がプラスのときのみ0に
			if (velocity.x > 0) {
				velocity.x = 0;
			}

			// 補正を実行
			position.x += correctionPos.x;
		}
	}



	// プレイヤーから右下の点
	checkPoint = { position.x + 24 / 2,position.y - 24 / 2 };
	// 右下がヒットしたとき -> 補正する
	if (Map::isHittingBlock(checkPoint)) {
		// 補正分の座標
		Point correctionPos = { 0,0 };

		// 左上に補正する
		while (Map::isHittingBlock(checkPoint)) {
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
			position.y += correctionPos.y;
		}
		// xのほうがyより短い場合 -> xを適応し、yは破棄
		else {
			// 速度がプラスのときのみ0に
			if (velocity.x > 0) {
				velocity.x = 0;
			}

			// 補正を実行
			position.x += correctionPos.x;
		}
	}
	// もし空中判定された後の場合
	else if (isFlying) {
		// 一個下のマスがヒットしているときは空中ではないということなのでフラグをfalseに
		if (Map::isHittingBlock({ checkPoint.x,checkPoint.y - 1 })) {
			// ヒットしていないときは空中ということなのでフラグをtrueに
			isFlying = false;
		}
	}
}
*/

ObjectType Player::GetType() {
	return typePlayer;
}
