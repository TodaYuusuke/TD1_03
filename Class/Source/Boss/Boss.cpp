#include "Class/Include/Boss/Boss.h"

/*********************************
	ボスクラス
*********************************/

//コンストラクタ
Boss::Boss() {
	Boss::Initialize();
}

//デストラクタ
Boss::~Boss() {

}

//初期化処理
void Boss::Initialize() {
	//ボスの位置を画面中央に持っていく
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	//ボスの画像サイズを設定
	this->textureSize = { 225.0f, 450.0f };

	//核の位置を設定
	kernelCenterPosition = centerPosition;
	//核の画像サイズを設定
	kernelTextureSize = { 256.0f, 256.0f };
}

//更新処理
void Boss::Update(Point playerPosition) {

}

//描画処理
void Boss::Draw() {

	//ボス核画像
	BaseDraw::DrawQuad(
		kernelCenterPosition,
		BaseTexture::kBossKernel,
		kernelTextureSize,
		1.0f,
		0.0f,
		0xFFFFFFFF
	);

	//ボス左側画像
	BaseDraw::DrawQuad(
		centerPosition,
		BaseTexture::kBossLCover,
		textureSize,
		1.0f,
		0.0f,
		0xFFFFFFFF
	);

	//ボス右側画像
	BaseDraw::DrawQuad(
		centerPosition,
		BaseTexture::kBossRCover,
		textureSize,
		1.0f,
		0.0f,
		0xFFFFFFFF
	);
}