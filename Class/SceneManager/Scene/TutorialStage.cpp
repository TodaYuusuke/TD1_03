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

	playerProgress = 0;
	isGameOver = false;
	gameOverColor = 0x00000000;
	gameOverT = BaseConst::kGameOverFirstValue;
}
// 更新
void TutorialStage::Update() {
	if (!objectManager.GetPlayerisAlive()) {
		isGameOver = true;
	}
	// 当たり判定の初期化
	EnemyAttackHitBox::Initialize();

	//// デバッグ用
	//if (BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
	//	nextScene = sceneBossStage;
	//}
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
	// プレイヤーの進捗チェック
	CheckPlayerProgress();
}
// 描画
void TutorialStage::Draw() {
	// デバッグ用
	Novice::ScreenPrintf(0, 0, "Push ENTER to Skip Stage");

	Point screenPosition = BaseDraw::GetScreenPosition();
	Point playerPosition = objectManager.GetPlayerPosition();

	Point screenSubtraction1 = { playerPosition.x / 8.0f ,0.0f };
	Point screenSubtraction2 = { -(float)BaseConst::kWindowWidth / 2 - playerPosition.x / 2.0f ,0.0f };

	// 背景

	for (int i = 0; i < 7; i++) {
		BaseDraw::DrawQuad({ 
			(float)BaseConst::kWindowWidth / 2 + ((float)BaseConst::kWindowWidth * 1.25f * i) + screenSubtraction1.x, 
			screenPosition.y - (float)BaseConst::kWindowHeight / 2 },
			BaseTexture::kBackGroundCity, { 1920, 1080 }, 1.25f, 0.0f, 0xFFFFFFFF);
	}

	for (int i = 0; i < 10; i++) {
		BaseDraw::DrawQuad({ (float)BaseConst::kWindowWidth / 2 + ((float)BaseConst::kWindowWidth * 1.25f * i) + screenSubtraction2.x,
			screenPosition.y - (float)BaseConst::kWindowHeight / 2 },
			BaseTexture::kBackGroundForest, { 1920, 1080 }, 1.25f, 0.0f, 0xFFFFFFFF);
	}

	BaseDraw::DrawQuad({ screenPosition.x + BaseConst::kWindowWidth / 2, screenPosition.y - BaseConst::kWindowHeight / 2 },
		BaseTexture::kBackGroundFrame, { 1920, 1080 }, 1.35f, 0.0f, 0xFFFFFFFF);

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
	if(1.0f < gameOverT) {
		gameOverT = 1.0f;
	}
	gameOverColor = gameOverT * 0xCC;
	// ワールド座標に戻さず計算
	Point mp = BaseInput::GetMousePosition();
	// 「タイトルへ戻る」の中にマウスがある場合
	if (BaseConst::kGameOverTitleLeftTop.x < mp.x && mp.x < BaseConst::kGameOverTitleRightBottom.x &&
		BaseConst::kGameOverTitleLeftTop.y < mp.y && mp.y < BaseConst::kGameOverTitleRightBottom.y) {
		if (BaseInput::GetMouseState(LeftClick, Trigger)) {
			nextScene = sceneTitle;
		}
	}
	else if (BaseConst::kGameOverRetryLeftTop.x < mp.x && mp.x < BaseConst::kGameOverRetryRightBottom.x &&
		BaseConst::kGameOverRetryLeftTop.y < mp.y && mp.y < BaseConst::kGameOverRetryRightBottom.y) {
		if (BaseInput::GetMouseState(LeftClick, Trigger)) {
			Initialize();
		}
	}

}
// ゲームオーバー時の処理
void TutorialStage::GameOverDraw() {
	Novice::DrawBox(0, 0, BaseConst::kWindowWidth, BaseConst::kWindowHeight, 0.0f, gameOverColor, kFillModeSolid);
	Novice::DrawSprite(
		(BaseConst::kWindowWidth / 2.0f) - gameOverT * (BaseConst::kWindowWidth / 2.0f),
		(BaseConst::kWindowHeight / 2.0f) - gameOverT * (BaseConst::kWindowHeight / 2.0f),
		BaseTexture::kUserInterfaceGameOver, gameOverT, gameOverT, 0.0f, WHITE
	);
	Point mp = BaseInput::GetMousePosition();
	Novice::DrawEllipse(mp.x, mp.y, 10, 10, 0.0f, 0x00FF00FF, kFillModeWireFrame);
	Novice::DrawEllipse(mp.x, mp.y, 13, 13, 0.0f, 0x00FF00FF, kFillModeWireFrame);
}