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
	reticlePosition = { -10000,-10000 };

	invincibleFrame = 0;
	// 現在右を向いているかどうか
	isRight = true;
}
// 更新
void Player::SuccessorUpdate() {

	if (invincibleFrame > 0) {
		invincibleFrame--;
	}

	// 回転を常に初期化
	angle = 0;
	angleVelocity = 0;

	reticlePosition = BaseInput::GetMousePosition();

	Move();
	Jump();
	ShotWire();


	Point screenPos = BaseDraw::GetScreenPosition();

	/// x座標の調整 ///

	if (isRight) {
		screenPos.x = centerPosition.x - 300;
	}
	else {
		screenPos.x = centerPosition.x + 300 - BaseConst::kWindowWidth;
	}

	/// y座標の調整 ///

	if (!isFlying) {
		screenPos.y = centerPosition.y + 900;
	}
	else {

	}


	// スクリーン座標が画面外に行かないように調整
	if (screenPos.x < 0) {
		screenPos.x = 0;
	}
	else if (screenPos.x + BaseConst::kWindowWidth > BaseConst::kMapChipSizeWidth * BaseConst::kMapSizeWidth) {
		screenPos.x = BaseConst::kMapChipSizeWidth * BaseConst::kMapSizeWidth - BaseConst::kWindowWidth;
	}
	if (screenPos.y - BaseConst::kWindowHeight < 0 ) {
		screenPos.y = BaseConst::kWindowHeight;
	}
	else if (screenPos.y > BaseConst::kMapChipSizeHeight * BaseConst::kMapSizeHeight) {
		screenPos.y = BaseConst::kMapChipSizeHeight * BaseConst::kMapSizeHeight;
	}


	//////////　　ここで線形補完　　//////////
	// screenPos ... 移動先のカメラ
	// BaseDraw::GetScreenPosition ... このフレームでの現在のカメラ座標

	BaseDraw::SetScreenPosition(screenPos);

	//////////　　　ここまで　　　　//////////
}
// 描画
void Player::Draw() {
	if (isAlive) {

		if (invincibleFrame % 10 == 0) {
			BaseDraw::DrawSprite({ centerPosition.x - width / 2, centerPosition.y + height / 2 }, BaseTexture::kDebugTexture, { width,height }, 0, RED);
		}
	}
}



// どちらもUpdate()で毎フレーム呼び出すこと

// 移動関連
void Player::Move() {

	// 左移動
	if (BaseInput::GetKeyboardState(DIK_A, Press)) {
		if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
			velocity.x -= 0.5f;
			isRight = false;
		}
	}
	else if(velocity.x < 0) {
		velocity.x += 0.1f;
	}
	// 右移動
	if (BaseInput::GetKeyboardState(DIK_D, Press)) {
		if (velocity.x < BaseConst::kPlayerVelocityLimit) {
			velocity.x += 0.5f;
			isRight = true;
		}
	}
	else if (velocity.x > 0) {
		velocity.x -= 0.1f;
	}
}

// ジャンプ
void Player::Jump() {
	// スペースキーが押されたとき
	if (BaseInput::GetKeyboardState(DIK_SPACE, Trigger)) {
		if (!isFlying) {
			// 速度Yがマイナスのとき -> 0にリセットしてから
			if (velocity.y < 0) {
				velocity.y = 0;
			}
			// ジャンプ分の速度を足す
			velocity.y += 9.8f * 1.2f;
		}
	}
}

// ワイヤー関連
void Player::ShotWire() {
	if (BaseInput::GetMouseState(LeftClick, Trigger)) {
		reticlePosition = BaseInput::GetMousePosition();

		// 反動のベクトル
		Point p = { 7,0 };

		switch (wireManager->Shot(centerPosition, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition), this))
		{
			// ワイヤーの射出に成功した場合
			case 1:
				// 射出方向と反対方向のベクトルを足す
				p = BaseMath::TurnPoint(p, BaseMath::GetDegree(BaseDraw::WorldtoScreen(centerPosition), reticlePosition) + 180);

				velocity.x = p.x;
				velocity.y = p.y;
				break;
			// 射出失敗
			case -1:
				break;
			// これ以上射出できない
			case -2:
				break;
		}
	}
	if (BaseInput::GetMouseState(RightClick, Trigger)) {
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


	// 攻撃に対する当たり判定を実装
	if (EnemyAttackHitBox::CheckHitBox(centerPosition) != 0 && invincibleFrame <= 0) {
		// 無敵時間を設定
		invincibleFrame = 60;
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
	}
}


ObjectType Player::GetType() {
	return typePlayer;
}
