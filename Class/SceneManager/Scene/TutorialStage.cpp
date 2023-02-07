#include "Class/SceneManager/Scene/TutorialStage.h"

// �R���X�g���N�^
TutorialStage::TutorialStage() {
	Initialize();
}
// �f�X�g���N�^
TutorialStage::~TutorialStage() {

}



// ������
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
// �X�V
void TutorialStage::Update() {
	if (!objectManager.GetPlayerisAlive()) {
		isGameOver = true;
	}
	// �����蔻��̏�����
	EnemyAttackHitBox::Initialize();

	// �f�o�b�O�p
	if (BaseInput::GetKeyboardState(DIK_RETURN, Trigger)) {
		nextScene = sceneBossStage;
	}
	// �f�o�b�O�p
	if (BaseInput::GetKeyboardState(DIK_E, Trigger)) {
		objectManager.MakeNewObjectEnemy(BaseDraw::ScreentoWorld(BaseInput::GetMousePosition()), { 64,64 });
	}
	// �萔�̃z�b�g�����[�h
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
	// �v���C���[�̐i���`�F�b�N
	CheckPlayerProgress();
}
// �`��
void TutorialStage::Draw() {
	// �f�o�b�O�p
	Novice::ScreenPrintf(0, 0, "Push ENTER to Skip Stage");

	Point screenPosition = BaseDraw::GetScreenPosition();
	Point playerPosition = objectManager.GetPlayerPosition();

	Point screenSubtraction1 = { playerPosition.x / 8.0f ,0.0f };
	Point screenSubtraction2 = { -(float)BaseConst::kWindowWidth / 2 - playerPosition.x / 2.0f ,0.0f };

	// �w�i

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

	if (!isGameOver) {
		objectManager.Draw();
		wireManager.Draw();
	}
	else {
		Player* p = (Player*)objectManager.GetSelectObject(typePlayer);
		p->Draw();
		GameOverDraw();
	}
}


void TutorialStage::CheckPlayerProgress() {
	
	switch (playerProgress)
	{
		case 0:
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

// �Q�[���I�[�o�[���̏���
void TutorialStage::GameOverUpdate() {
	if (gameOverT < 1.0f) {
		gameOverT += BaseConst::kGameOverFlame;
	}
	if(1.0f < gameOverT) {
		gameOverT = 1.0f;
	}
	gameOverColor = gameOverT * 0xCC;
	// ���[���h���W�ɖ߂����v�Z
	Point mp = BaseInput::GetMousePosition();
	// �u�^�C�g���֖߂�v�̒��Ƀ}�E�X������ꍇ
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
// �Q�[���I�[�o�[���̏���
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