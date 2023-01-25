#include "Class/Object/Object.h"

void Object::Initialize() {

	SuccessorInitialize();

	//CheckFieldHitBox();
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
	isAlive = false;

 }

void Object::Update() {
	if (isAlive) {

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
}

void Object::SuccessorUpdate() {

}

void Object::Draw() {
	if (isAlive) {
		BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
	}
}


// メンバ変数に関与する関数

// オブジェクトの中心座標を受け取る関数
// 返り値：中心座標
// 引数：なし
Point Object::GetCenterPosition() {
	return centerPosition;
}

// オブジェクトの中心座標を設定する関数
	// 返り値：なし
	// 引数：セットする中心座標
void Object::SetCenterPosition(Point _setPosition) {
	centerPosition = _setPosition;
}

// オブジェクトの速度を受け取る関数
// 返り値：速度のベクトル
// 引数：なし
Point Object::GetVelocity() {
	return { velocity.x - 0.5f * angleVelocity, velocity.y };
}

// オブジェクトが空中かどうかを受け取る関数
// 返り値：空中ならばtrue
// 引数：なし
bool Object::GetisFlying() {
	return isFlying;
}

/// <summary>
/// 生きてるかどうかを受け取る関数
/// </summary>
/// <returns>生きてる場合 true</returns>
bool Object::GetisAlive() {
	return isAlive;
}

/// <summary>
/// 引っ張られたかどうかを受け取る関数
/// </summary>
/// <returns>引っ張られた場合 true</returns>
bool Object::GetisPulled() {
	return isPulled;
}

/// <summary>
/// Angle(Degree)を取得する関数
/// </summary>
/// <returns>Angle(Degree)</returns>
float Object::GetAngle() {
	return angle;
}

/// <summary>
/// AngleVelocity(Degree)を取得する関数
/// </summary>
/// <returns>AngleVelocity(Degree)</returns>
float Object::GetAngleVelocity() {
	return angleVelocity;
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

/// <summary>
/// 生きてるかどうかを設定する関数
/// </summary>
/// <param name="_isAlive">生きてるかどうか</param>
void Object::SetisAlive(bool _isAlive) {
	isAlive = _isAlive;
}

/// <summary>
/// 引っ張られたかどうかを設定する関数
/// </summary>
/// <param name="_isPulled">引っ張られたかどうか</param>
void Object::SetisPulled(bool _isPulled) {
	isPulled = _isPulled;
}

/// <summary>
/// Angle(Degree)を設定する関数
/// </summary>
/// <param name="_angle">angle(Degree)</param>
void Object::SetAngle(float _angle) {
	angle = _angle;
}

/// <summary>
/// AngleVelocity(Degree)を設定する関数
/// </summary>
/// <param name="_angleVelocity">angleVelocity(Degree)</param>
void Object::SetAngleVelocity(float _angleVelocity) {
	angleVelocity = _angleVelocity;
}


// 当たり判定関連

bool Object::CheckHitBox(Point hitPosition) {
	if (!isAlive) {
		return false;
	}
	return BaseMath::CheckHitBox(centerPosition, width, height, angle, hitPosition);
}

bool Object::CheckHitBox(Box hitPosition) {
	if (!isAlive) {
		return false;
	}
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


	// 8つ角のヒットボックスチェック
	CheckHitBoxRhombus(checkQuadPoint, checkRhombusPoint);

	// 場外に飛び出した場合の補正を行う

	// 左方向に飛び出したとき
	while (centerPosition.x - width / 2 < BaseConst::kMapChipSizeWidth) {
		// 座標を右に
		centerPosition.x += 1;
		// 再計算
		for (int i = 0; i < 4; i++) {
			checkQuadPoint[i].x += 1;
			checkRhombusPoint[i].x += 1;
		}
	}
	// 右方向に飛び出したとき
	while (centerPosition.x + width / 2 > (BaseConst::kMapSizeWidth - 1) * BaseConst::kMapChipSizeWidth) {
		// 座標を左に
		centerPosition.x -= 1;
		// 再計算
		for (int i = 0; i < 4; i++) {
			checkQuadPoint[i].x -= 1;
			checkRhombusPoint[i].x -= 1;
		}
	}
	// 下方向に飛び出したとき
	while (centerPosition.y - height / 2 < BaseConst::kMapChipSizeHeight) {
		// 座標を上に
		centerPosition.y += 1;
		// 再計算
		for (int i = 0; i < 4; i++) {
			checkQuadPoint[i].y += 1;
			checkRhombusPoint[i].y += 1;
		}
	}
	// 上方向に飛び出したとき
	while (centerPosition.y + height / 2 > (BaseConst::kMapSizeHeight - 1) * BaseConst::kMapChipSizeHeight) {
		// 座標を下に
		centerPosition.y -= 1;
		// 速度を0に
		velocity.y = 0;
		// 再計算
		for (int i = 0; i < 4; i++) {
			checkQuadPoint[i].y -= 1;
			checkRhombusPoint[i].y -= 1;
		}
	}
}

// 上下左右の当たり判定の関数
void Object::CheckHitBoxRhombus(Point checkQuadPoint[], Point checkRhombusPoint[]) {

	// 4つ角の座標を検証しヒットしてる座標を確認
	
	//Novice::ScreenPrintf(BaseDraw::WorldtoScreen(checkQuadPoint[0]).x, BaseDraw::WorldtoScreen(checkQuadPoint[0]).y, "0");
	//Novice::ScreenPrintf(BaseDraw::WorldtoScreen(checkQuadPoint[1]).x, BaseDraw::WorldtoScreen(checkQuadPoint[1]).y, "1");
	//Novice::ScreenPrintf(BaseDraw::WorldtoScreen(checkQuadPoint[2]).x, BaseDraw::WorldtoScreen(checkQuadPoint[2]).y, "2");
	//Novice::ScreenPrintf(BaseDraw::WorldtoScreen(checkQuadPoint[3]).x, BaseDraw::WorldtoScreen(checkQuadPoint[3]).y, "3");
	//Novice::ScreenPrintf(BaseDraw::WorldtoScreen(checkRhombusPoint[0]).x, BaseDraw::WorldtoScreen(checkRhombusPoint[0]).y, "0");
	//Novice::ScreenPrintf(BaseDraw::WorldtoScreen(checkRhombusPoint[1]).x, BaseDraw::WorldtoScreen(checkRhombusPoint[1]).y, "1");
	//Novice::ScreenPrintf(BaseDraw::WorldtoScreen(checkRhombusPoint[2]).x, BaseDraw::WorldtoScreen(checkRhombusPoint[2]).y, "2");
	//Novice::ScreenPrintf(BaseDraw::WorldtoScreen(checkRhombusPoint[3]).x, BaseDraw::WorldtoScreen(checkRhombusPoint[3]).y, "3");

	float kAddAngleVelocity = 0.3f;

	float kAngleVelocityMin = 1.5f;

	// 二点がヒットしている場合
	if (isHit(checkQuadPoint[0]) && isHit(checkQuadPoint[1]) || isHit(checkQuadPoint[0]) && isHit(checkQuadPoint[2])) {
		// 何もしない
		velocity.y = 0;
		// 速度を少しずつ減速させる
		velocity.x *= 0.9f;
		isFlying = false;

		int move = 0;
		// ヒットしなくなるまで上へ補正する
		while (isHit(checkQuadPoint[0])) {
			move += 1;
			// 座標を上に
			centerPosition.y += 1;
			// 再計算
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}

			
			// もしある程度上まで補正しないとダメな場合、補正を修正し右方向に補正
			if (move > BaseConst::kMapChipSizeHeight) {
				// 座標を下に
				centerPosition.y -= move;
				// 再計算
				for (int i = 0; i < 4; i++) {
					checkQuadPoint[i].y -= move;
					checkRhombusPoint[i].y -= move;
				}

				int leftMove = 0;
				int rightMove = 0;
				// 右と左、どちらのほうが近いかを検証
				while (true) {
					// 座標を右に
					leftMove -= 1;
					rightMove += 1;

					if (!isHit({checkQuadPoint[2].x + leftMove,checkQuadPoint[2].y})) {
						velocity.x *= -0.9f;
						centerPosition.x += leftMove;
						// 再計算
						for (int i = 0; i < 4; i++) {
							checkQuadPoint[i].x += leftMove;
							checkRhombusPoint[i].x += leftMove;
						}
						break;
					}
					if (!isHit({ checkQuadPoint[1].x + rightMove,checkQuadPoint[1].y })) {
						velocity.x *= -0.9f;
						centerPosition.x += rightMove;
						// 再計算
						for (int i = 0; i < 4; i++) {
							checkQuadPoint[i].x += rightMove;
							checkRhombusPoint[i].x += rightMove;
						}
						break;
					}
				}

				angleVelocity *= -0.9f;

				break;
			}
			
		}

		if (((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -kAngleVelocityMin && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < kAngleVelocityMin) ||
			((int)checkQuadPoint[0].y - (int)checkQuadPoint[2].y > -kAngleVelocityMin && (int)checkQuadPoint[0].y - (int)checkQuadPoint[2].y < kAngleVelocityMin) ) {
			angle = GetNearestValue(angle);
			angleVelocity = 0;
		}
	}
	// 下の場合
	else if (isHit(checkQuadPoint[0])) {

		// 速度を少しずつ減速させる
		velocity.x *= 0.9f;

		// ヒットしなくなるまで上へ補正する
		while (isHit(checkQuadPoint[0])) {
			// 座標を上に
			centerPosition.y += 1;
			// 再計算
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}
		}

		// 左の点の方がy座標が下の場合 -> 左回転のベクトルを足す
		if (checkQuadPoint[1].y < checkQuadPoint[2].y) {
			if ((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -kAngleVelocityMin && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < kAngleVelocityMin) {
				angle = GetNearestValue(angle);
				angleVelocity = 0;
			}
			else {
				angleVelocity -= kAddAngleVelocity;
			}
		}
		// 右の点の方がy座標が下の場合 -> 右回転のベクトルを足す
		else {
			if ((int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y > -kAngleVelocityMin && (int)checkQuadPoint[0].y - (int)checkQuadPoint[1].y < kAngleVelocityMin) {
				angle = GetNearestValue(angle);
				angleVelocity = 0;
			}
			else {
				angleVelocity += kAddAngleVelocity;
			}
		}

		velocity.y = 0;
		isFlying = false;
	}
	// 一番下の中心が触れている場合
	else if (isHit(checkRhombusPoint[0])) {

		// ヒットしなくなるまで上へ補正する
		while (isHit(checkRhombusPoint[0])) {
			// 座標を上に
			centerPosition.y += 1;
			// 再計算
			for (int i = 0; i < 4; i++) {
				checkQuadPoint[i].y += 1;
				checkRhombusPoint[i].y += 1;
			}
		}

		if (angleVelocity > 0) {
			angleVelocity += kAddAngleVelocity;
		}
		else if (angleVelocity < 0) {
			angleVelocity -= kAddAngleVelocity;
		}
		else {
			if (checkQuadPoint[0].x < checkRhombusPoint[0].x) {
				angleVelocity += kAddAngleVelocity;
			}
			else {
				angleVelocity -= kAddAngleVelocity;
			}
		}

		velocity.y = 0;
		isFlying = false;
	}
	// それ以外
	else {
		isFlying = true;

		// 左の場合
		if (isHit(checkQuadPoint[1])) {
			// 移動量
			int move = 0;
			// ヒットしなくなるまで上へ補正する
			while (isHit(checkQuadPoint[1])) {
				move += 1;
				// 座標を上に
				centerPosition.y += 1;
				// 再計算
				for (int i = 0; i < 4; i++) {
					checkQuadPoint[i].y += 1;
					checkRhombusPoint[i].y += 1;
				}

				// もしある程度上まで補正しないとダメな場合、補正を修正し右方向に補正
				if (move > BaseConst::kMapChipSizeHeight) {
					// 座標を下に
					centerPosition.y -= move;
					// 再計算
					for (int i = 0; i < 4; i++) {
						checkQuadPoint[i].y -= move;
						checkRhombusPoint[i].y -= move;
					}

					while (isHit(checkQuadPoint[1])) {
						// 座標を右に
						centerPosition.x -= 1;
						// 再計算
						for (int i = 0; i < 4; i++) {
							checkQuadPoint[i].x -= 1;
							checkRhombusPoint[i].x -= 1;
						}
					}

					angleVelocity *= -0.9f;

					break;
				}
			}
			angleVelocity += kAddAngleVelocity;
		}
		// 右の場合
		else if (isHit(checkQuadPoint[2])) {
			// 移動量
			int move = 0;
			// ヒットしなくなるまで上へ補正する
			while (isHit(checkQuadPoint[2])) {
				move += 1;
				// 座標を上に
				centerPosition.y += 1;
				// 再計算
				for (int i = 0; i < 4; i++) {
					checkQuadPoint[i].y += 1;
					checkRhombusPoint[i].y += 1;
				}

				// もしある程度上まで補正しないとダメな場合、補正を修正し右方向に補正
				if (move > BaseConst::kMapChipSizeHeight) {
					// 座標を下に
					centerPosition.y -= move;
					// 再計算
					for (int i = 0; i < 4; i++) {
						checkQuadPoint[i].y -= move;
						checkRhombusPoint[i].y -= move;
					}

					while (isHit(checkQuadPoint[2])) {
						// 座標を右に
						centerPosition.x += 1;
						// 再計算
						for (int i = 0; i < 4; i++) {
							checkQuadPoint[i].x += 1;
							checkRhombusPoint[i].x += 1;
						}
					}

					angleVelocity *= -0.9f;

					break;
				}
			}
			angleVelocity -= kAddAngleVelocity;
		}
		// 上の場合
		else if (isHit(checkQuadPoint[3])) {
			// ヒットしなくなるまで下へ補正する
			while (isHit(checkQuadPoint[3])) {
				// 座標を下に
				centerPosition.y -= 1;
				// 再計算
				for (int i = 0; i < 4; i++) {
					checkQuadPoint[i].y -= 1;
					checkRhombusPoint[i].y -= 1;
				}
			}
			angleVelocity -= kAddAngleVelocity;
		}
	}
}

bool Object::isHit(Point hitPosition) {
	// マップにヒットしているかどうか
	if (MapManager::CheckHitBox(hitPosition)) {
		return true;
	}
	// 別のobjectにヒットしているかどうか
	//else if (ObjectHitBox::CheckHitBox(hitPosition, num)) {
	//	return true;
	//}
	

	return false;
}