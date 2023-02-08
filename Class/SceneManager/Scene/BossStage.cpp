#include "Class/SceneManager/Scene/BossStage.h"

// コンストラクタ
BossStage::BossStage() {
	Initialize();
}
// デストラクタ
BossStage::~BossStage() {

}



// 初期化
void BossStage::Initialize() {
	nextScene = sceneNone;

	BaseDraw::SetScreenPosition({ 0,1080 });

	PublicFlag::Initialize();
	ObjectHitBox::Initialize();
	MapManager::BossInitialize();
	objectManager.Initialize();
	wireManager.Initialize();

	objectManager.MakeNewObjectPlayer({ 100,200 }, &wireManager);
	boss.Initialize(&objectManager);

	preScrollPositionX = 1080;
	for (int i = 0; i < 3; i++) {
		backGroundPositionX[i] = 0;
	}

	reticlePosition = { 1000,500 };
	preMousePosition = BaseInput::GetMousePosition();
	isGameOver = false;
	gameOverColor = 0x00000000;
	gameOverT = BaseConst::kGameOverFirstValue;
	isToTitle = false;
	isToRetry = false;
	Novice::StopAudio(BaseAudio::kBGMBoss);
	Novice::StopAudio(BaseAudio::kBGMChance);
}
// 更新
void BossStage::Update() {
	if (!objectManager.GetPlayerisAlive()) {
		isGameOver = true;
	}
	// 当たり判定の初期化
	EnemyAttackHitBox::Initialize();

	MapManager::Update();

	boss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	if (!isGameOver) {
		objectManager.Update();
		wireManager.Update(&objectManager);
	}
	else {
		Player* p = (Player*)objectManager.GetSelectObject(typePlayer);
		if (p != NULL) {
			p->Update();
		}
		GameOverUpdate();
	}


	// 背景スクロール用
	backGroundPositionX[0] -= (BaseDraw::GetScreenPosition().x - preScrollPositionX) * 0.6f;
	backGroundPositionX[1] -= (BaseDraw::GetScreenPosition().x - preScrollPositionX) * 0.5f;
	backGroundPositionX[2] -= (BaseDraw::GetScreenPosition().x - preScrollPositionX) * 0.3f;

	for (int i = 1; i <= 3; i++) {
		while (true) {
			if (backGroundPositionX[i - 1] > 0) {
				backGroundPositionX[i - 1] -= 1920;
				continue;
			}
			else if (backGroundPositionX[i - 1] < -1920) {
				backGroundPositionX[i - 1] += 1920;
				continue;
			}
			break;

		}
	}
	// 前回の座標を更新
	preScrollPositionX = BaseDraw::GetScreenPosition().x;
}
// 描画
void BossStage::Draw() {

	// 背景の描画
	for (int i = 1; i <= 3; i++) {
		BaseDraw::DrawSprite({ backGroundPositionX[i - 1] + (BaseDraw::GetScreenPosition().x / 1920) * 1920,  BaseDraw::GetScreenPosition().y }, BaseTexture::kBackGround[i - 1], { 1,1 }, 0, WHITE);
		BaseDraw::DrawSprite({ backGroundPositionX[i - 1] + 1920 + (BaseDraw::GetScreenPosition().x / 1920) * 1920, BaseDraw::GetScreenPosition().y }, BaseTexture::kBackGround[i - 1], { 1,1 }, 0, WHITE);
		BaseDraw::DrawSprite({ backGroundPositionX[i - 1] - 1920 + (BaseDraw::GetScreenPosition().x / 1920) * 1920, BaseDraw::GetScreenPosition().y }, BaseTexture::kBackGround[i - 1], { 1,1 }, 0, WHITE);
	}

	MapManager::Draw();
	// 演出時に下がスケスケなのが気になるので修正
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < BaseConst::kBossStageSizeWidth; x++) {
			BaseDraw::DrawSprite({ (float)x * BaseConst::kMapChipSizeWidth, (float)y * -BaseConst::kMapChipSizeHeight }, BaseTexture::kTextureMapChip[0], { 1,1 }, 0, WHITE);
		}
	}
	boss.Draw();
	if (!isGameOver) {
		objectManager.Draw();
		wireManager.Draw();
	}
	else {
		Player* p = (Player*)objectManager.GetSelectObject(typePlayer);
		if (p != NULL) {
			p->Draw();
		}
		GameOverDraw();
	}
	/*
	// デバックの操作方法テクスチャ
	int debugMoveTex = Novice::LoadTexture("./Resources/Texture/Debug/Move.png");
	int debugShotTex = Novice::LoadTexture("./Resources/Texture/Debug/Shot.png");
	int debugJumpTex = Novice::LoadTexture("./Resources/Texture/Debug/Jump.png");
	int debugAttractTex = Novice::LoadTexture("./Resources/Texture/Debug/Attract.png");
	int debugBGTex = Novice::LoadTexture("./Resources/Texture/Debug/BG.png");
	int debugHPTex = Novice::LoadTexture("./Resources/Texture/Debug/HP.png");

	Novice::DrawSprite(1280, 10, debugBGTex, 10, 0.5f, 0, WHITE);
	// 動作方法
	Novice::DrawSprite(1280, 10, debugMoveTex, 0.25f, 0.25f, 0.0f, WHITE);
	Novice::DrawSprite(1600, 10, debugJumpTex, 0.25f, 0.25f, 0.0f, WHITE);
	Novice::DrawSprite(1280, 42, debugShotTex, 0.25f, 0.25f, 0.0f, WHITE);
	Novice::DrawSprite(1600, 42, debugAttractTex, 0.25f, 0.25f, 0.0f, WHITE);

	Novice::DrawSprite(620, 10, debugHPTex, 0.5f, 0.5f, 0, WHITE);*/
}

// ゲームオーバー時の処理
void BossStage::GameOverUpdate() {
	if (gameOverT < 1.0f) {
		gameOverT += BaseConst::kGameOverFlame;
	}
	if (1.0f < gameOverT) {
		gameOverT = 1.0f;
	}
	gameOverColor = gameOverT * 0xCC;
	// ワールド座標に戻さず計算
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

	// 「タイトルへ戻る」の中にマウスがある場合
	if (BaseConst::kGameOverTitleLeftTop.x < reticlePosition.x && reticlePosition.x < BaseConst::kGameOverTitleRightBottom.x &&
		BaseConst::kGameOverTitleLeftTop.y < reticlePosition.y && reticlePosition.y < BaseConst::kGameOverTitleRightBottom.y) {
		isToTitle = true;
		if (BaseInput::GetMouseState(LeftClick, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonL1, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonL2A, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonR2B, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonLeft, Trigger)) {
			nextScene = sceneTitle;
		}
	}
	else {
		isToTitle = false;
	}
	if (BaseConst::kGameOverRetryLeftTop.x < reticlePosition.x && reticlePosition.x < BaseConst::kGameOverRetryRightBottom.x &&
		BaseConst::kGameOverRetryLeftTop.y < reticlePosition.y && reticlePosition.y < BaseConst::kGameOverRetryRightBottom.y) {
		isToRetry = true;
		if (BaseInput::GetMouseState(LeftClick, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonR1, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonL2A, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonR2B, Trigger) ||
			BaseInput::GetControllerState(kControllerButtonRight, Trigger)) {
			Initialize();
		}
	}
	else {
		isToRetry = false;
	}
	if (BaseInput::GetControllerState(kControllerButtonL1, Trigger) ||
		BaseInput::GetControllerState(kControllerButtonLeft, Trigger)) {
		nextScene = sceneTitle;
	}
	if (BaseInput::GetControllerState(kControllerButtonR1, Trigger) ||
		BaseInput::GetControllerState(kControllerButtonRight, Trigger)) {
		Initialize();
	}
	preMousePosition = BaseInput::GetMousePosition();
}
// ゲームオーバー時の処理
void BossStage::GameOverDraw() {
	Novice::DrawBox(0, 0, BaseConst::kWindowWidth, BaseConst::kWindowHeight, 0.0f, gameOverColor, kFillModeSolid);
	Novice::DrawSprite(
		(BaseConst::kWindowWidth / 2.0f) - gameOverT * (BaseConst::kWindowWidth / 2.0f),
		(BaseConst::kWindowHeight / 2.0f) - gameOverT * (BaseConst::kWindowHeight / 2.0f),
		BaseTexture::kUserInterfaceGameOver, gameOverT, gameOverT, 0.0f, WHITE
	);
	Novice::SetBlendMode(kBlendModeAdd);
	if (isToTitle) {
		Novice::DrawBox(
			BaseConst::kGameOverTitleLeftTop.x - BaseConst::kSelectPadding, BaseConst::kGameOverTitleLeftTop.y - BaseConst::kSelectPadding,
			BaseConst::kGameOverTitleRightBottom.x - BaseConst::kGameOverTitleLeftTop.x + BaseConst::kSelectPadding * 2,
			BaseConst::kGameOverTitleRightBottom.y - BaseConst::kGameOverTitleLeftTop.y + BaseConst::kSelectPadding * 2,
			0.0f, 0x00AAAAFF, kFillModeSolid
		);
	}
	if (isToRetry) {
		Novice::DrawBox(
			BaseConst::kGameOverRetryLeftTop.x - BaseConst::kSelectPadding, BaseConst::kGameOverRetryLeftTop.y - BaseConst::kSelectPadding,
			BaseConst::kGameOverRetryRightBottom.x - BaseConst::kGameOverRetryLeftTop.x + BaseConst::kSelectPadding * 2,
			BaseConst::kGameOverRetryRightBottom.y - BaseConst::kGameOverRetryLeftTop.y + BaseConst::kSelectPadding * 2,
			0.0f, 0x00AAAAFF, kFillModeSolid
		);
	}
	Novice::SetBlendMode(kBlendModeNormal);
	if (isToTitle || isToRetry) {
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 10, 10, 0.0f, 0xFF0000FF, kFillModeWireFrame);
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 13, 13, 0.0f, 0xFF0000FF, kFillModeWireFrame);
	}
	else {
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 10, 10, 0.0f, 0x00FF00FF, kFillModeWireFrame);
		Novice::DrawEllipse(reticlePosition.x, reticlePosition.y, 13, 13, 0.0f, 0x00FF00FF, kFillModeWireFrame);
	}
}