#include "Class/Include/Object/Object.h"

void Object::Initialize() {
	kGravitationalAcceleration = 9.8f / 60.0f;
	SuccessorInitialize();
 }

void Object::SuccessorInitialize(){

	centerPosition = { -10000,-10000 };

	width = 1;
	height = 1;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = true;


 }

void Object::Update() {

	acceleration = { 0,0 };

	// 加速度や速度を継承先で変更
	SuccessorUpdate();

	if (isFlying) {
		// 加速度に重力を追加
		acceleration.y -= kGravitationalAcceleration;
	}
	// とりあえず速度を弱める
	if (velocity.x < 0) {
		velocity.x *= 0.87f;
	}
	else if (0 < velocity.x) {
		velocity.x *= 0.87f;
	}
	if (0 < velocity.y) {
		velocity.y *= 0.87f;
	}
	if (-0.1f <= velocity.x && velocity.x <= 0.1f) {
		velocity.x = 0;
	}

	// 変更した加速度を追加
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	// 座標に速度分移動させる
	centerPosition.x += velocity.x;
	centerPosition.y += velocity.y;

	CheckFieldHitBox();

}

void Object::SuccessorUpdate() {

}

void Object::Draw() {
	BaseDraw::DrawQuad(centerPosition, BaseTexture::kDebugTexture, { 100,100 }, 1.0f, 0.0f, WHITE);
}

// オブジェクトに速度ベクトルを足す関数
// 返り値：なし
// 引数：足す速度
void Object::AddVelocity(Point _addVelocity) {
	velocity.x += _addVelocity.x;
	velocity.y += _addVelocity.y;
}

bool Object::CheckHitBox(Point hitPosition) {
	// 左右
	if (centerPosition.x - width / 2.0f < hitPosition.x && hitPosition.x < centerPosition.x + width / 2.0f) {
		// 上下
		if (centerPosition.y - height / 2.0f < hitPosition.y && hitPosition.y < centerPosition.y + height / 2.0f) {
			return true;
		}
	}
	return false;
}

bool Object::CheckHitBox(Box hitPosition) {
	if (BaseMath::CheckHitBox({ BaseDraw::WorldtoScreen(centerPosition),width,height }, { BaseDraw::WorldtoScreen(hitPosition.position),hitPosition.width,hitPosition.height })){
		return true;
	}
	else {
		return false;
	}
}

bool Object::CheckFieldHitBox() {
	// フィールド外に出た時の処理
	// 左右
	bool result = false;
	if (centerPosition.x - width / 2.0f < 0) {
		centerPosition.x = width / 2.0f;
		acceleration.x = 0;
		velocity.x = 0;
		result = true;
	}
	else if(BaseConst::kWindowWidth < centerPosition.x + width / 2.0f) {
		centerPosition.x = BaseConst::kWindowWidth - (width / 2.0f);
		acceleration.x = 0;
		velocity.x = 0;
		result = true;
	}
	// 上下
	if (centerPosition.y - height / 2.0f < 0) {
		centerPosition.y = height / 2.0f;
		isFlying = false;
		acceleration.y = 0;
		velocity.y = 0;
		result = true;
	}
	else if (BaseConst::kWindowHeight < centerPosition.y + height / 2.0f) {
		centerPosition.y = BaseConst::kWindowHeight - (height / 2.0f);
		acceleration.y = 0;
		velocity.y = 0;
		result = true;
	}
	return false;
}

ObjectType Object::GetType() {
	return typeObject;
}

Point Object::GetCenterPosition() {
	return centerPosition;
}

Point Object::GetVelocity() {
	return velocity;
}