#include "Class/SceneManager/Scene/TutorialStage.h"

// コンストラクタ
TutorialStage::TutorialStage() {
	Initialize();
}
// デストラクタ
TutorialStage::~TutorialStage() {

}



// 初期化
void TutorialStage::Initialize() {
	nextScene = sceneNone;

	PublicFlag::Initialize();

	ObjectHitBox::Initialize();
	MapManager::TutorialInitialize();
	objectManager.Initialize();
	wireManager.Initialize();

	objectManager.MakeNewObjectPlayer({ 100,700 }, &wireManager);

	middleBoss.Initialize(&objectManager);

	BaseDraw::SetScreenPosition({ 0,1080 });

	preScrollPositionX = 1080;
	for (int i = 0; i < 3; i++) {
		backGroundPositionX[i] = 0;
	}


	playerProgress = 0;
	
	reticlePosition = { 1000,500 };
	preMousePosition = BaseInput::GetMousePosition();
	isGameOver = false;
	gameOverColor = 0x00000000;
	gameOverT = BaseConst::kGameOverFirstValue;
	isToTitle = false;
	isToRetry = false;
}
// 更新
void TutorialStage::Update() {
	if (!objectManager.GetPlayerisAlive()) {
		isGameOver = true;
	}
	// 当たり判定の初期化
	EnemyAttackHitBox::Initialize();

	//// デバッグ用
	if (BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
		nextScene = sceneBossStage;
	}
	// デバッグ用
	if (BaseInput::GetKeyboardState(DIK_R, Trigger)) {
		Initialize();
	}

	// デバッグ用
	if (BaseInput::GetKeyboardState(DIK_E, Trigger)) {
		objectManager.MakeNewObjectBalloon(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()));
	}
	// デバッグ用
	if (BaseInput::GetKeyboardState(DIK_I, Trigger)) {
		objectManager.MakeNewObjectIronBalloon(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()));
	}
	// デバッグ用
	if (BaseInput::GetKeyboardState(DIK_B, Trigger)) {
		objectManager.MakeNewObjectBlock(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 64,64 });
	}
	// デバッグ用
	if (BaseInput::GetKeyboardState(DIK_F, Trigger)) {
		objectManager.MakeNewObjectFallBlock(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), false);
	}

	// 定数のホットリロード
	if (BaseInput::GetKeyboardState(DIK_F1, Trigger)) {
		PublicFlag::Initialize();

		ObjectHitBox::Initialize();
		MapManager::TutorialInitialize();
	}

	MapManager::Update();
	//middleBoss.Update(objectManager.GetPlayerPosition(), &objectManager, &wireManager);
	if (!isGameOver) {
		objectManager.Update();
		wireManager.Update(&objectManager);
	}
	else {
		Player* p = (Player*)objectManager.GetSelectObject(typePlayer);
		p->Update();
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


	// プレイヤーの進捗チェック
	CheckPlayerProgress();
}
// 描画
void TutorialStage::Draw() {
	// 背景の描画
	for (int i = 1; i <= 3; i++) {
		BaseDraw::DrawSprite({ backGroundPositionX[i - 1] + (BaseDraw::GetScreenPosition().x / 1920) * 1920,  BaseDraw::GetScreenPosition().y}, BaseTexture::kBackGround[i - 1], { 1,1 }, 0, WHITE);
		BaseDraw::DrawSprite({ backGroundPositionX[i - 1] + 1920 + (BaseDraw::GetScreenPosition().x / 1920) * 1920, BaseDraw::GetScreenPosition().y }, BaseTexture::kBackGround[i - 1], { 1,1 }, 0, WHITE);
		BaseDraw::DrawSprite({ backGroundPositionX[i - 1] - 1920 + (BaseDraw::GetScreenPosition().x / 1920) * 1920, BaseDraw::GetScreenPosition().y }, BaseTexture::kBackGround[i - 1], { 1,1 }, 0, WHITE);
	}


	MapManager::Draw();
	middleBoss.Draw();

	objectManager.Draw();
	if (!isGameOver) {
		wireManager.Draw();
	}
	else {
		GameOverDraw();
	}


	Novice::ScreenPrintf(0, 20, "x = %6.0f, y = %6.0f", BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()).x, BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()).y);
}


void TutorialStage::CheckPlayerProgress() {

	switch (playerProgress)
	{
	case 0:
		if (objectManager.GetPlayerPosition().x > 6500) {
			playerProgress = 1;

			// 敵を召喚
			objectManager.MakeNewObjectBalloon({ 7714,283 });
			objectManager.MakeNewObjectBalloon({ 8037,283 });
			objectManager.MakeNewObjectBalloon({ 8358,283 });
			objectManager.MakeNewObjectBalloon({ 7872,509 });
			objectManager.MakeNewObjectBalloon({ 8197,509 });
		}
		break;
	case 1:
		if (objectManager.GetPlayerPosition().x > 9100) {
			playerProgress = 2;

			// 落ちてくる箱を召喚
			objectManager.MakeNewObjectFallBlock({ 9570,1200 }, false);
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	}

}

// ゲームオーバー時の処理
void TutorialStage::GameOverUpdate() {
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
void TutorialStage::GameOverDraw() {
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