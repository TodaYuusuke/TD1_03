#include "Class/Include/Object/Object.h"

void Object::Initialize() {

	SuccessorInitialize();

	CheckFieldHitBox();
 }

void Object::SuccessorInitialize(){

	// 中心座標
	centerPosition = { -10000,-10000 };
	// 速度
	velocity = { 0,0 };
	// 加速度
	acceleration = { 0,0 };

	// 回転角度（Degree）
	angle = 0;
	// 回転速度（Degree）
	angleVelocity = 0;

	// 当たり判定のサイズ（左上の点からの長さ）
	width = 0;
	height = 0;

	//空中にいるかどうか
	isFlying = true;
 }

void Object::Update() {

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

	// 速度制限にかかっている場合、減速させる
	if (velocity.x > BaseConst::kPlayerVelocityLimit) {
		velocity.x -= 0.02f;
	}
	if (velocity.x < -(BaseConst::kPlayerVelocityLimit)) {
		velocity.x += 0.02f;
	}
	if (velocity.y > BaseConst::kPlayerVelocityLimit) {
		velocity.y -= 0.02f;
	}
	if (velocity.y < -(BaseConst::kPlayerVelocityLimit)) {
		velocity.y += 0.02f;
	}

	// 速度を追加
	centerPosition.x += velocity.x;
	centerPosition.y += velocity.y;


	// 回転速度を追加
	angle += angleVelocity;

	if (angleVelocity > 0) {
		centerPosition.x -= 0.5f * angleVelocity;
	}
	else if (angleVelocity < 0) {
		centerPosition.x -= 0.5f * angleVelocity;
	}

	// 回転速度を減速させていく
	if (angleVelocity > BaseConst::kPlayerVelocityLimit) {
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
	}


	CheckFieldHitBox();
}

void Object::SuccessorUpdate() {

}

void Object::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
}


// メンバ変数に関与する関数

// オブジェクトの中心座標を受け取る関数
// 返り値：中心座標
// 引数：なし
Point Object::GetCenterPosition() {
	return centerPosition;
}

// オブジェクトの速度を受け取る関数
// 返り値：速度のベクトル
// 引数：なし
Point Object::GetVelocity() {
	return velocity;
}


// オブジェクトに速度ベクトルを足す関数
// 返り値：なし
// 引数：足す速度
void Object::AddVelocity(Point _addVelocity) {
	velocity.x += _addVelocity.x;
	velocity.y += _addVelocity.y;
}

// オブジェクトに回転速度を足す関数
// 返り値：なし
// 引数：足す速度
void Object::AddVelocity(float _addVelocity) {
	angleVelocity += _addVelocity;
}


// 当たり判定関連

bool Object::CheckHitBox(Point hitPosition) {
	return BaseMath::CheckHitBox(centerPosition, width, height, angle, hitPosition);
}

bool Object::CheckHitBox(Box hitPosition) {
	if (BaseMath::CheckHitBox({ BaseDraw::WorldtoScreen(centerPosition),width,height }, { BaseDraw::WorldtoScreen(hitPosition.position),hitPosition.width,hitPosition.height })){
		return true;
	}
	else {
		return false;
	}
}


// その他

ObjectType Object::GetType() {
	return typeObject;
}


// 関数

// オブジェクト自体の当たり判定をチェックする関数
void Object::CheckFieldHitBox() {

	// 0 ... 上
	// 1 ... 下
	// 2 ... 左
	// 3 ... 右
	// の4点を用意
	checkRhombusPoint[0] = BaseMath::TurnPoint({ 0, +height / 2 }, angle);
	checkRhombusPoint[1] = BaseMath::TurnPoint({ 0, -height / 2 }, angle);
	checkRhombusPoint[2] = BaseMath::TurnPoint({ -width / 2, 0 }, angle);
	checkRhombusPoint[3] = BaseMath::TurnPoint({ +width / 2, 0 }, angle);

	// 0 ... 左上
	// 1 ... 右上
	// 2 ... 左下
	// 3 ... 右下
	// の4点を用意
	checkQuadPoint[0] = BaseMath::TurnPoint({ -width / 2, +height / 2 }, angle);
	checkQuadPoint[1] = BaseMath::TurnPoint({ +width / 2, +height / 2 }, angle);
	checkQuadPoint[2] = BaseMath::TurnPoint({ -width / 2, -height / 2 }, angle);
	checkQuadPoint[3] = BaseMath::TurnPoint({ +width / 2, -height / 2 }, angle);


	// centerPositionを追加
	for (int i = 0; i < 4; i++) {
		checkRhombusPoint[i].x += centerPosition.x;
		checkRhombusPoint[i].y += centerPosition.y;
		checkQuadPoint[i].x += centerPosition.x;
		checkQuadPoint[i].y += centerPosition.y;
	}


	// N-1回操作
	for (int i = 0; i < 4 - 1; i++) {
		// 右からソート（左からやると変数が1つ増える）
		for (int j = 4 - 1; i < j; j--) {
			if (checkRhombusPoint[j].y < checkRhombusPoint[j - 1].y) { // 左の数値が小さければ交換
				// スワップ
				Point p = checkRhombusPoint[j];
				checkRhombusPoint[j] = checkRhombusPoint[j - 1];
				checkRhombusPoint[j - 1] = p;
			}
			if (checkQuadPoint[j].y < checkQuadPoint[j - 1].y) { // 左の数値が小さければ交換
				// スワップ
				Point p = checkQuadPoint[j];
				checkQuadPoint[j] = checkQuadPoint[j - 1];
				checkQuadPoint[j - 1] = p;
			}
		}
	}

	// X座標が左側の方を[1]に、右側の方を[2]に代入
	if (checkRhombusPoint[1].x < checkRhombusPoint[2].x) { // 左の数値が小さければ交換
		// スワップ
		Point p = checkRhombusPoint[1];
		checkRhombusPoint[1] = checkRhombusPoint[2];
		checkRhombusPoint[2] = p;
	}
	if (checkQuadPoint[1].x < checkQuadPoint[2].x) { // 左の数値が小さければ交換
		// スワップ
		Point p = checkQuadPoint[1];
		checkQuadPoint[1] = checkQuadPoint[2];
		checkQuadPoint[2] = p;
	}


	// 上下左右のヒットボックスチェック
	CheckHitBoxRhombus(checkQuadPoint, checkRhombusPoint);
	// 左上、左下、右上、右下のヒットボックスチェック
	//CheckHitBoxQuad(checkQuadPoint);

}

// 上下左右の当たり判定の関数
void Object::CheckHitBoxRhombus(Point checkQuadPoint[], Point checkRhombusPoint[]) {

	// 4つ角の座標を検証しヒットしてる座標を確認

	// 二点がヒットしている場合
	if (MapManager::CheckHitBox(checkQuadPoint[0]) && MapManager::CheckHitBox(checkQuadPoint[1]) || MapManager::CheckHitBox(checkQuadPoint[0]) && MapManager::CheckHitBox(checkQuadPoint[2])) {
		// 何もしない
		velocity.y = 0;
		isFlying = false;

		// ヒットしなくなるまで上へ補正する
		while (MapManager::CheckHitBox(checkQuadPoint[0])) {
			// 座標を上に
			centerPosition.y += 1;
			// 再計算
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}
		}

		if (((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -1 && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < 1) ||
			((int)checkQuadPoint[0].y - (int)checkQuadPoint[2].y > -1 && (int)checkQuadPoint[0].y - (int)checkQuadPoint[2].y < 1) ) {
			angle = GetNearestValue(angle);
			angleVelocity = 0;
		}
	}
	// 下の場合
	else if (MapManager::CheckHitBox(checkQuadPoint[0])) {

		// ヒットしなくなるまで上へ補正する
		while (MapManager::CheckHitBox(checkQuadPoint[0])) {
			// 座標を上に
			centerPosition.y += 1;
			// 再計算
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}
		}

		velocity.y = 0;
		isFlying = false;


		// 左の点の方がy座標が下の場合 -> 左回転のベクトルを足す
		if (checkQuadPoint[1].y < checkQuadPoint[2].y) {
			if ((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -1 && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < 1) {
				angle = GetNearestValue(angle);
				angleVelocity = 0;
			}
			else {
				angleVelocity -= 0.3f;
			}
		}
		// 右の点の方がy座標が下の場合 -> 右回転のベクトルを足す
		else {
			if ((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -1 && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < 1) {
				angle = GetNearestValue(angle);
				angleVelocity = 0;
			}
			else {
				angleVelocity += 0.3f;
			}
		}
	}
	// 一番下の中心が触れている場合
	else if (MapManager::CheckHitBox(checkRhombusPoint[0])) {

		// ヒットしなくなるまで上へ補正する
		while (MapManager::CheckHitBox(checkRhombusPoint[0])) {
			// 座標を上に
			centerPosition.y += 1;
			// 再計算
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}
		}

		if (angleVelocity > 0) {
			angleVelocity += 0.3f;
		}
		else if (angleVelocity < 0) {
			angleVelocity -= 0.3f;
		}
		else {
			if (checkQuadPoint[0].x < checkRhombusPoint[0].x) {
				angleVelocity += 0.3f;
			}
			else {
				angleVelocity -= 0.3f;
			}
		}

		velocity.y = 0;
		isFlying = false;
	}
	else {
		isFlying = true;

		// 左の場合
		if (MapManager::CheckHitBox(checkQuadPoint[1])) {
			
			// ヒットしなくなるまで上へ補正する
			while (MapManager::CheckHitBox(checkQuadPoint[1])) {
				// 座標を上に
				centerPosition.y += 1;
				// 再計算
				for (int i = 0; i < 4; i++) {
					checkQuadPoint[i].y += 1;
					checkRhombusPoint[i].y += 1;
				}
			}
			angleVelocity += 0.3f;
		}
		// 右の場合
		else if (MapManager::CheckHitBox(checkQuadPoint[2])) {
			
			// ヒットしなくなるまで上へ補正する
			while (MapManager::CheckHitBox(checkQuadPoint[2])) {
				// 座標を上に
				centerPosition.y += 1;
				// 再計算
				for (int i = 0; i < 4; i++) {
					checkQuadPoint[i].y += 1;
					checkRhombusPoint[i].y += 1;
				}
			}
			angleVelocity -= 0.3f;
		}
		// 上の場合
		else if (MapManager::CheckHitBox(checkQuadPoint[3])) {

		}
	}




	/*

	// 当たり判定をチェックする座標
	Point checkPoint;

	// 下の点（一番下の点）
	checkPoint = checkPosition[0];
	// 下がヒットしたとき
	if (MapManager::CheckHitBox(checkPoint)) {
		// 速度は0に
		velocity.y = 0;
		// 飛んでいないのでフラグを戻す
		isFlying = false;

		// ヒットしなくなるまで上へ補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			// 座標を上に
			//centerPosition.y += 1;
			// 再計算
			checkPoint.y += 1;
		}
	}
	// 一個下のマスがヒットしていないときは空中ということなのでフラグをtrueに
	else if (!MapManager::CheckHitBox({ checkPoint.x ,checkPoint.y - 1 })) {
		isFlying = true;
	}

	// 左がヒットしたとき
	if (MapManager::CheckHitBox(checkPosition[1])) {
		// 速度は0に
		velocity.x = 0;

		// ヒットしなくなるまで右へ補正する
		while (MapManager::CheckHitBox(checkPosition[1])) {
			// 座標を右に
			//centerPosition.x += 1;
			// 再計算
			checkPosition[1].x += 1;
		}
	}

	// 右の点
	checkPoint = checkPosition[2];
	// 右がヒットしたとき
	if (MapManager::CheckHitBox(checkPoint)) {
		// 速度は0に
		velocity.x = 0;

		// ヒットしなくなるまで左へ補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			// 座標を左に
			//centerPosition.x -= 1;
			// 再計算
			checkPoint.x -= 1;
		}
	}

	// 上の点（一番上の点）
	checkPoint = checkPosition[3];
	// 上がヒットしたとき
	if (MapManager::CheckHitBox(checkPoint)) {
		// 速度は0に
		velocity.y = 0;

		// ヒットしなくなるまで下へ補正する
		while (MapManager::CheckHitBox(checkPoint)) {
			// 座標を下に
			//centerPosition.y -= 1;
			// 再計算
			checkPoint.y -= 1;
		}
	}



	*/

}

// 左上、左下、右上、右下の当たり判定の関数
void Object::CheckHitBoxQuad(Point checkPosition[]) {

	// 当たり判定をチェックする座標
	Point checkPoint;


	// 上の点（一番上の点）
	checkPoint = checkPosition[3];
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



	// 上の点（一番下の点）
	checkPoint = checkPosition[0];
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
}

Quad Object::GetQuad() {
	Point halfsize = { width / 2.0f,height / 2.0f };
	Quad result;
	result.q1 = { centerPosition.x - halfsize.x,centerPosition.y + halfsize.y };
	result.q2 = { centerPosition.x + halfsize.x,centerPosition.y + halfsize.y };
	result.q3 = { centerPosition.x - halfsize.x,centerPosition.y - halfsize.y };
	result.q4 = { centerPosition.x + halfsize.x,centerPosition.y - halfsize.y };
	return BaseMath::TurnBox(result, angle);
}