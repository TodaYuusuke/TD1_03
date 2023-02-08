#include "Class/Object/Enemy/Balloon.h"

// コンストラクタ
Balloon::Balloon(Point _centerPosition, Point size,Object* _object) {

	centerPosition = _centerPosition;
	width = 64;
	height = 64;

	object = _object;

	Initialize();
}

Balloon::~Balloon() {

}

void Balloon::SuccessorInitialize() {

	elapsedFrame = 0;
	degree = 0;

	// 速度
	velocity = { 0,0 };
	// 加速度
	acceleration = { 0,0 };

	// 回転角度（Degree）
	angle = 0.0f;
	// 回転速度（Degree）
	angleVelocity = 0;

	//空中にいるかどうか
	isFlying = true;
	isAlive = true;

	direct = -1;
}

void Balloon::Update() {
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
	}
}
void Balloon::SuccessorUpdate() {
	elapsedFrame++;
	degree+=5;
	if (degree > 360) {
		degree = 0;
	}
	// 回転を常に初期化
	angle = 0;
	angleVelocity = 0;

	if (!isFlying) {
		if (object->GetCenterPosition().x < centerPosition.x) {
			direct = -1;
		}
		else if (centerPosition.x < object->GetCenterPosition().x) {
			direct = 1;
		}
		else {
			direct = 0;
		}

		// 左移動
		if (direct < 0) {
			if (velocity.x > -BaseConst::kPlayerVelocityLimit) {
				acceleration.x -= 0.5f;
			}
		}
		else if (0 < direct) {
			// 右移動
			if (velocity.x < BaseConst::kPlayerVelocityLimit) {
				acceleration.x += 0.5f;
			}
		}
		else {

		}
	}

	// 当たり判定 -> ヒット時死亡
	if (isStub) {
		isAlive = false;
		if (direct == -1) {
			BaseEffectManager::MakeNewEffectBalloonDead(centerPosition, false);
		}
		else {
			BaseEffectManager::MakeNewEffectBalloonDead(centerPosition, true);
		}
		Novice::PlayAudio(BaseAudio::kEnemyBallonDead,0,BaseAudio::SEvolume);
	}

	EnemyAttackHitBox::MakeNewHitBox(centerPosition, width, height, 0, 1);	
}

void Balloon::Draw() {
	if (isAlive) {
		Point p = centerPosition;
		p.y += BaseMath::TurnPoint({ 0,5 }, degree).y;

		if (direct == -1) {
			BaseDraw::DrawQuad(p, BaseTexture::kEnemyBalloon[elapsedFrame % 10 / 5], { width,height }, 1.0f, angle, WHITE);
		}
		else {
			BaseDraw::DrawQuad(p, BaseTexture::kEnemyBalloon[elapsedFrame % 10 / 5 + 2], { width,height }, 1.0f, angle, WHITE);
		}
	}
}

ObjectType Balloon::GetType() {
	return typeBalloon;
}
