#include "Class/Include/Object/Object.h"

void Object::Initialize() {
	kGravitationalAcceleration = 9.8f;
	SuccessorInitialize();
 }

void Object::SuccessorInitialize(){

	centerPosition = { 100,100 };

	width = 100;
	height = 100;

	velocity = { 0,0 };
	acceleration = { 0,0 };

	isFlying = false;

	texture = Novice::LoadTexture("white1x1.png");

 }

void Object::Update() {

	// 加速度に重力を追加
	acceleration.y += kGravitationalAcceleration;

	// 加速度や速度を継承先で変更
	SuccessorUpdate();

	// 変更した加速度を追加
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;


}

void Object::SuccessorUpdate() {

}

void Object::Draw() {
	BaseDraw::DrawQuad(centerPosition, texture, { 100,100 }, 1.0f, 0.0f, WHITE);
}

bool Object::CheckHitBox(Point hitPosition) {
	return false;
}

bool Object::CheckHitBox(Box hitPosition) {
	return false;

}