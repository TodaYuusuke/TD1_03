#include "Class/MiddleBoss/MiddleBoss.h"

/*********************************************
 * 中ボスクラス
 *
 * 中ボス関連の行動すべてを管理するクラス
 *********************************************/

// コンストラクタ
MiddleBoss::MiddleBoss() {
	// 核の当たり判定を初期化
	core = NULL;
}

// 初期化処理
void MiddleBoss::Initialize(ObjectManager* objectManager) {
	// ボスの中心座標をリセット
	this->centerPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth / 2) + 300.0f,(float)(BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight) + 250.0f };
	// ボスの画像サイズ設定
	this->textureSize = { 256.0f, 256.0f };

	// 角度初期化
	this->degree = 0.0f;
	// 1フレーム前の角度を初期化
	this->beforeDegree = 0.0f;

	//シェイクしていない状態に戻す
	this->shakeVariation = { 0.0f, 0.0f };

	// カットシーン用カメラ移動前座標
	this->prevScreenPosition = { 0.0f, 0.0f };
	// カットシーン用カメラ移動後座標
	this->nextScreenPosition = { 0.0f, 0.0f };

	// 画面中央の座標をとる関数
	screenCenterPosition = { 0.0f, 0.0f };

	// バイブレーション初期化
	this->vibInit = false;

	// 振動音再生トリガーをfalseに
	this->isVibPlaySound = false;

	// 戦闘を開始するか
	this->doBattleStart = false;
	// 戦闘開始していない状態にする
	this->isBattleStart = false;

	// 行動終了状態にする
	this->t = 0.0f;
	this->spareT = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->inStun = false;
	this->inDamage = false;
	this->actionWayPoint = 0;

	// ダメージを受けられる状態にする
	this->canTakeDamage = true;

	// 核の当たり判定を初期化
	this->core = objectManager->MakeNewObjectCore(centerPosition, textureSize);

	// 武器のサイズを指定（仮テクスチャのため、今後変える）
	this->weaponSize = { 0.0f, 0.0f };
	this->weaponTextureSize = { 1.0f, 1.0f };

	// 攻撃パターン初期化
	this->prevAttackPattern[0] = NONE;
	this->prevAttackPattern[1] = NONE;
	this->attackPattern = NONE;

	// 待機中
	this->pleaseWait = true;

	// 待機時間を代入
	this->waitTime = 1.0f;

	// HP初期化
	this->HP = MaxHP;

	this->blockSpawnPoint = { 0.0f, 0.0f };

	// 与えるダメージ初期化
	this->bodyDamage = 0.0f;
	this->bladeDamage = 0.0f;

	// 死亡していない状態にする
	this->inDead = false;

	/// オブジェクト関連
	// オブジェクトを生成するかどうか
	this->canGeneratedBlock = false;

	// オブジェクト生成個数
	this->generatedBlockValue = 0;

	// オブジェクト生成間隔
	this->generatedBlockInterval = 0.0f;

	// 色関係初期化
	this->color = 0xFFFFFFFF;

	// 現在演出中か
	isPlayingStartAnim = false;

	// 死亡アニメーション
	isPlayingDeadAnim = false;

	// 死亡アニメーションが終了しているか
	isEndDeadAnim = false;

	// 叫び声
	screamSoundHundle = BaseAudio::kBossScream;
	screamVoiceHundle = -1;

}

// 更新処理
void MiddleBoss::Update(Point playerPosition, ObjectManager* objectManager, WireManager* wireManager) {

	// 画面中央の座標を更新
	screenCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth / 2) + 300.0f,
		(float)(BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight / 2) };

	// プレイヤーが一定の距離以上に近づいたらボスとの戦闘を開始する
	if (screenCenterPosition.x - playerPosition.x < 650.0f) {
		doBattleStart = true;
	}

	/******** デバック処理 **********/
	// デバッグ状態の切り替え
	if (BaseInput::GetKeyboardState(DIK_H, Press) && BaseInput::GetKeyboardState(DIK_U, Press)) {
		if (BaseInput::GetKeyboardState(DIK_BACKSPACE, Trigger)) {
			if (inDebug == false) {
				// 戦闘開始状態にする
				isBattleStart = true;
				// 角度初期化
				degree = 0;

				// 行動終了状態に
				endAction = true;
				inAction = false;
				actionWayPoint = WAYPOINT0;

				// デバック状態にする
				inDebug = true;
			}
			else
				inDebug = false;
		}
	}
	// デバッグ関数の実行
	if (inDebug == true) {
		Debug();
	}

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

	if (isBattleStart == true && inDead == false) {

		if (HP == 0) {
			attackPattern = NONE;
			endAction = false;
		}

		// 死亡状態の時の実行処理
		if (HP <= 0) {
			if (isEndDeadAnim == false && isPlayingDeadAnim == false) {

				endAction = true;
				inAction = false;

				inDamage = false;
				inStun = false;
				t = 0.0f;
				actionWayPoint = WAYPOINT0;
				isPlayingDeadAnim = true;
			}
			// HPが0以下になったらボスを死亡状態にする
			HP = 0;
		}

		// 行動の分岐処理
		if (inDead == false && inDebug == false) {
			if (endAction == true) {

				// 行動の間隔を作る
				if (pleaseWait == true) {
					attackPattern = NONE;
				}
				else {
					do {
						// プレイヤーとボスの距離を求めて近いか遠いかで行動を分岐させる
						if (BaseMath::GetLength({ playerPosition.x - centerPosition.x,playerPosition.y - centerPosition.y }) < 500.0f) {

							// 近い
							attackBranch = BaseMath::Random(Pattern1, Pattern4);
							switch (attackBranch)
							{
							case MiddleBoss::Pattern1:
								attackPattern = RUSH;
								break;
							case MiddleBoss::Pattern2:
								attackPattern = SLASH;
								break;
							case MiddleBoss::Pattern3:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[0] == SEPARATION
									|| prevAttackPattern[1] == APPROACH || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = ROTATE;
								}

								break;
							case MiddleBoss::Pattern4:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[1] == APPROACH) {
									continue;
								}
								else {
									attackPattern = SEPARATION;
								}
								break;
							default:
								attackPattern = NONE;
								break;
							}

						}
						else {

							// 遠い
							attackBranch = BaseMath::Random(Pattern1, Pattern4);
							switch (attackBranch)
							{
							case MiddleBoss::Pattern1:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[0] == SEPARATION
									|| prevAttackPattern[1] == APPROACH || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = ROTATE;
								}
								break;
							case MiddleBoss::Pattern2:
								attackPattern = SLASH;
								break;
							case MiddleBoss::Pattern3:
								attackPattern = RUSH;
								break;
							case MiddleBoss::Pattern4:
								if (prevAttackPattern[0] == SEPARATION || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = APPROACH;
								}
								break;
							default:
								attackPattern = NONE;
								break;
							}

						}

					} while (prevAttackPattern[0] == attackPattern || prevAttackPattern[1] == attackPattern);
				}

				if (objectManager->GetIsCreatedBlock() == false) {
					attackPattern = FALL;
				}

				// 行動開始
				inAction = true;
				endAction = false;

			}
		}

		// 行動の実行処理
		if (inAction == true && inStun == false && isPlayingDeadAnim == false) {
			switch (attackPattern)
			{
			case MiddleBoss::NONE:
				None(waitTime);
				break;
			case MiddleBoss::ROTATE:
				Rotate(720, 2.0f, 0.5f, wireManager);
				break;
			case MiddleBoss::RUSH:
				Rush(playerPosition, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case MiddleBoss::SLASH:
				Slash(playerPosition, 0.35f, 0.2f, 1.25f, 1.0f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case MiddleBoss::FALL:
				Fall(0.35f, 1.0f, 0.15f, 0.75f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case MiddleBoss::APPROACH:
				Approach(playerPosition, 1.0f, 0.1f, wireManager);
				break;
			case MiddleBoss::SEPARATION:
				Separation(playerPosition, 1.0f, 0.1f, wireManager);
				break;
			}
		}

		// スタン処理
		if (inStun == true) {
			Stun(1.25f, 1.5f, 3.0f, 0.75f, wireManager);
		}

		// 開いてる時に追従
		core->SetCenterPosition(viewPosition);

		if (canTakeDamage == true) {
			// ここで返り値がtrueのときにダメージ判定を行う
			if (objectManager->isHitCore() == true) {
				// ダメージを与えた際の効果音再生
				Novice::PlayAudio(BaseAudio::kBossDamage, 0, 0.5f);

				// ダメージアニメーション用のtを初期化する
				spareT = 0.0f;
				// ダメージを与えた状態にする
				inDamage = true;

				// HPを低下させる
				HP--;
			}
		}
		
		// ダメージを与えた際のアニメーション再生
		if (inDamage == true) {
			playTakeDamageAnim(0.1f, 50);
		}

		degree %= 360;

		float degreeDifference = degree - beforeDegree;

		for (int i = 0; i < 5; i++) {
			// 武器のヒットボックス
			EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree + (degreeDifference * i), bladeDamage);
		}

		// ボスのヒットボックスを有効にする
		EnemyAttackHitBox::MakeNewHitBox(centerPosition, textureSize.x, textureSize.y, degree, bodyDamage);

		/// オブジェクト関係の更新処理

		// オブジェクト生成する
		if (canGeneratedBlock == true) {

			// 生成間隔が0になると生成
			if (generatedBlockInterval < 0) {
				if (generatedBlockValue > 0) {
					float blockSize = BaseMath::RandomF(20.0f, 60.0f, 0);

					blockSpawnPoint = { BaseMath::RandomF(centerPosition.x - (float)BaseConst::kWindowWidth / 2, centerPosition.x + (float)BaseConst::kWindowWidth / 2, 1),
						(float)BaseConst::kTutorialStageSizeHeight * BaseConst::kMapChipSizeHeight - BaseConst::kMapChipSizeHeight - blockSize };

					// 範囲内だった場合は再抽選
					while (blockSpawnPoint.x + blockSize >= centerPosition.x - textureSize.x / 2.0f && blockSpawnPoint.x - blockSize <= centerPosition.x + textureSize.x / 2.0f)
					{
						blockSpawnPoint = { BaseMath::RandomF(centerPosition.x - (float)BaseConst::kWindowWidth / 2, centerPosition.x + (float)BaseConst::kWindowWidth / 2, 1),
						(float)BaseConst::kTutorialStageSizeHeight* BaseConst::kMapChipSizeHeight - BaseConst::kMapChipSizeHeight - blockSize };
					}
					// ランダムな位置に、ランダムな大きさのブロックを生成
					objectManager->MakeNewObjectBlock(blockSpawnPoint, { blockSize, blockSize });
					generatedBlockValue--;
				}
				else {
					blockSpawnPoint = { 0.0f, 0.0f };
					canGeneratedBlock = false;
				}
				generatedBlockInterval = BaseMath::RandomF(0.1f, 0.2f, 2);
			}
			else {
				generatedBlockInterval -= 1.0f / 60.0f;
			}
		}

		// 最後に1フレーム前の角度を取得
		beforeDegree = degree;

		if (isPlayingDeadAnim == true && isEndDeadAnim == false) {
			PlayDeadAnim(5.0f, 1.0f, 0.75f, 2.5f, wireManager);
		}

	}
	else if (inDead == false && doBattleStart == true) {
		// 開始アニメーション再生
		PlayStartAnim(2.5f, 1.25f, 2.0f, 1.5f);

		if (isPlayingStartAnim == true && PublicFlag::kisStaging == false) {
			// 演出終了
			PublicFlag::kisStaging = false;
			isPlayingStartAnim = false;

			// 初期化
			centerPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kTutorialStageSizeWidth / 2),
				(float)(BaseConst::kMapChipSizeHeight * BaseConst::kTutorialStageSizeHeight / 2) };;

			shakeVariation = { 0.0f, 0.0f };
			isBattleStart = true;
			t = 0.0f;
			actionWayPoint = WAYPOINT0;
		}
	}

}

// 描画処理
void MiddleBoss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };

	if (inDead == false) {
		// ボス武器画像 現在は仮テクスチャ
		BaseDraw::DesignationDrawQuad(
			GetWeaponPosition(viewPosition),
			weaponSize,
			BaseTexture::kDebugTexture,
			weaponTextureSize,
			degree,
			0xFFFFFFFF
		);

		// ボス左側画像
		BaseDraw::DrawQuad(
			viewPosition,
			BaseTexture::kBossCore,
			textureSize,
			1.0f,
			degree,
			color
		);

		if (isBattleStart == true) {
			// ボスHPゲージ（仮）
			Novice::DrawBox(450, 100, 0 + 100 * HP, 30, 0.0f, 0xdc143cFF, kFillModeSolid);
		}

	}

}

// 武器画像の相対座標を求める
Point MiddleBoss::GetWeaponPosition(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { 0, weaponSize.y / 2 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// デバッグ用関数
void MiddleBoss::Debug() {

	Novice::ScreenPrintf(0, 0, "DebugMode :: ON");
	Novice::ScreenPrintf(0, 20, "ActionSwitching :: 1 ~ 7");
	Novice::ScreenPrintf(0, 40, "1:NONE  2:SPIN  3:RUSH  4:SLASH  5:FALL  6:  7:");
	Novice::ScreenPrintf(0, 60, "NowAction = %d", attackPattern);
	Novice::ScreenPrintf(0, 80, "8:STUN  9:DAMAGE");

	if (endAction == true) {

		// 行動を開始させる
		if (BaseInput::GetKeyboardState(DIK_F, Trigger)) {
			inAction = true;
			endAction = false;
		}

		//行動パターン切り替え
		if (BaseInput::GetKeyboardState(DIK_1, Trigger)) {
			attackPattern = NONE;
		}
		else if (BaseInput::GetKeyboardState(DIK_2, Trigger)) {
			attackPattern = ROTATE;
		}
		else if (BaseInput::GetKeyboardState(DIK_3, Trigger)) {
			attackPattern = RUSH;
		}
		else if (BaseInput::GetKeyboardState(DIK_4, Trigger)) {
			attackPattern = SLASH;
		}
		else if (BaseInput::GetKeyboardState(DIK_5, Trigger)) {
			attackPattern = FALL;
		}
		else if (BaseInput::GetKeyboardState(DIK_6, Trigger)) {
			attackPattern = APPROACH;
		}
		else if (BaseInput::GetKeyboardState(DIK_7, Trigger)) {
			attackPattern = SEPARATION;
		}
	}

	// ボスをスタンさせる
	if (BaseInput::GetKeyboardState(DIK_8, Trigger)) {
		actionWayPoint = WAYPOINT0;
		inStun = true;
	}

	if (BaseInput::GetKeyboardState(DIK_UP, Trigger)) {
		actionWayPoint = WAYPOINT0;
		isPlayingDeadAnim = true;
	}

	// ボスを回転させる
	if (BaseInput::GetKeyboardState(DIK_L, Press))
		degree++;

	else if (BaseInput::GetKeyboardState(DIK_J, Press))
		degree--;

	// 武器のサイズを変更
	// x
	if (BaseInput::GetKeyboardState(DIK_O, Press)) {
		weaponSize.x -= 1.0f;
	}
	else if (BaseInput::GetKeyboardState(DIK_P, Press)) {
		weaponSize.x += 1.0f;
	}
	// y
	if (BaseInput::GetKeyboardState(DIK_N, Press)) {
		weaponSize.y -= 1.0f;
	}
	else if (BaseInput::GetKeyboardState(DIK_M, Press)) {
		weaponSize.y += 1.0f;
	}

}

// シェイク関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// ボスをシェイクさせる関数
void MiddleBoss::Shake(int shakeStrength) {
	shakeVariation.x = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
	shakeVariation.y = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
}

// シェイクイーズアウト関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// shakeTime ... シェイクする時間
// ボスをシェイクの強さを少しずつ弱くしながら動かす関数
void MiddleBoss::ShakeEaseOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// シェイクイーズインアウト関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// shakeTime ... シェイクする時間
// ボスのシェイクの強さを少しずつ弱くしながら動かす関数
void MiddleBoss::ShakeEaseInOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_InOut(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// バイブレーション関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// vibTime ... 振動する秒数
// vibRate ... 振動する間隔
// vibValue ... 振動させたい回数
// 一定間隔で、一定秒数振動させる関数
void MiddleBoss::vibration(int shakeStrength, float vibTime, float vibRate, int vibValue) {

	static float _vibTime;
	static float _vibRate;
	static bool vibrating;

	// 初期化
	if (vibInit == false) {
		_vibTime = (vibTime / vibValue) / 2;
		_vibRate = 0;

		isVibPlaySound = false;

		vibInit = true;
	}

	if (_vibRate < 0) {
		vibrating = true;
	}
	else {
		_vibRate -= 1.0f / 60.0f;
	}

	if (vibrating == true) {
		if (_vibTime > 0) {

			if (isVibPlaySound == false) {
				Novice::PlayAudio(BaseAudio::kBossVibration, false, 0.5f);
				isVibPlaySound = true;
			}

			Shake(shakeStrength);
			_vibTime -= 1.0f / 60.0f;
		}
		else {
			isVibPlaySound = false;
			_vibTime = (vibTime / vibValue) / 2;
			_vibRate = (vibTime / vibValue) / 2;
			vibrating = false;
		}
	}

}

/// <summary>
/// ボス戦の開始時のアニメーション関数
/// </summary>
/// <param name="cameraMoveTime">カメラを動かす時間</param>
/// <param name="appearTime">ボスが上から出現する</param>
/// <param name="roarTime">咆哮する</param>
/// <param name="waitTime">待機時間</param>
void MiddleBoss::PlayStartAnim(float cameraMoveTime, float appearTime, float roarTime, float waitTime) {
	switch (actionWayPoint)
	{
		// 初期化
	case MiddleBoss::WAYPOINT0:

		// 演出中の状態に
		PublicFlag::kisStaging = true;
		isPlayingStartAnim = true;

		// スクリーン座標記録
		prevScreenPosition = BaseDraw::GetScreenPosition();
		nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
			screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) };

		prevCenterPosition = centerPosition;
		nextCenterPosition = { screenCenterPosition.x, screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) };

		// t初期化
		t = 0.0f;
		// 次の段階へ
		actionWayPoint++;

		break;
		// カメラをボスのところまで動かす
	case MiddleBoss::WAYPOINT1:
		if (t <= cameraMoveTime) {

			// スクリーンを動かす
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, cameraMoveTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, cameraMoveTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossRush, false, 0.5f);

			// スクリーン座標記録
			prevCenterPosition = centerPosition;
			nextCenterPosition = screenCenterPosition;

			// 初期化
			t = 0.0f;
			actionWayPoint++;
		}

		break;
		// ボスが上から出現する
	case MiddleBoss::WAYPOINT2:
		if (t <= appearTime) {

			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, appearTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, appearTime);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// 初期化
			t = 0.0f;
			actionWayPoint++;
		}
		break;
		// ボスが咆哮する
	case MiddleBoss::WAYPOINT3:
		if (t <= roarTime) {

			if (t > 1.0f) {

				if (Novice::IsPlayingAudio(screamVoiceHundle) == 0 || screamVoiceHundle == -1) {
					// 効果音再生
					screamVoiceHundle = Novice::PlayAudio(screamSoundHundle, false, 0.5f);
				}

				Shake(25);
			}

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// 初期化
			t = 0.0f;
			actionWayPoint++;

		}
		break;
		// 待機してからボス戦開始
	case MiddleBoss::WAYPOINT4:
		if (t <= waitTime) {

			// スクリーンを動かす
			/*Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, nextScreenPosition.x, prevScreenPosition.x - nextScreenPosition.x, waitTime);
			screenPosition.y = BaseDraw::Ease_Out(t, nextScreenPosition.y, prevScreenPosition.y - nextScreenPosition.y, waitTime);

			BaseDraw::SetScreenPosition(screenPosition);*/

			// 元の座標に
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, waitTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, waitTime);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// 演出終了
			PublicFlag::kisStaging = false;
			isPlayingStartAnim = false;

			// 初期化
			isBattleStart = true;
			t = 0.0f;
			actionWayPoint = WAYPOINT0;
		}
		break;
	case MiddleBoss::WAYPOINT5:
		break;
	case MiddleBoss::WAYPOINT6:
		break;
	default:
		break;
	}
}

/// <summary>
/// 死亡時のアニメーションを再生する関数
/// </summary>
///<param name="cameraMoveTime">カメラを動かす時間</param>
/// <param name="roarTime">咆哮する</param>
/// <param name="moveTime">少し下に行く</param>
/// <param name="runAwayTime">そして上へ</param>
/// <param name="cameraBackTime">カメラを戻す</param>
void MiddleBoss::PlayDeadAnim(float cameraMoveTime, float moveTime, float runAwayTime, float cameraBackTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// 初期化
	case MiddleBoss::WAYPOINT0:

		// 演出中の状態に
		PublicFlag::kisStaging = true;
		isPlayingDeadAnim = true;

		wireManager->Initialize();

		// スクリーン座標記録
		prevScreenPosition = BaseDraw::GetScreenPosition();
		nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
			screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) };

		// 武器サイズ初期化
		weaponSize = { 0.0f, 0.0f };

		prevCenterPosition = centerPosition;
		nextCenterPosition = screenCenterPosition;

		if (Novice::IsPlayingAudio(screamVoiceHundle) == 0 || screamVoiceHundle == -1) {
			// 効果音再生
			screamVoiceHundle = Novice::PlayAudio(screamSoundHundle, false, 0.5f);
		}

		// t初期化
		t = 0.0f;
		// 次の段階へ
		actionWayPoint++;

		break;
		// カメラをボスのところまで動かす
	case MiddleBoss::WAYPOINT1:
		if (t <= cameraMoveTime) {

			// スクリーンを動かす
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_In(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, cameraMoveTime);
			screenPosition.y = BaseDraw::Ease_In(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, cameraMoveTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// ボスを動かす
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, cameraMoveTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, cameraMoveTime);

			// ボスを振動させる
			Shake(15);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// スクリーン座標記録
			prevScreenPosition = BaseDraw::GetScreenPosition();
			nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
				screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) - 150.0f };
			 
			// ボスの座標
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, centerPosition.y - 150.0f };

			// チャージ音
			Novice::PlayAudio(BaseAudio::kBossCharge, false, 0.5f);

			// 初期化
			t = 0.0f;
			actionWayPoint++;
		}

		break;
		// ボスが少し下に行く
	case MiddleBoss::WAYPOINT2:
		if (t <= moveTime) {

			ShakeEaseOut(15, moveTime);

			// スクリーンを動かす
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, moveTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, moveTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// ボスを動かす
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, moveTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, moveTime);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// スクリーン座標記録
			prevScreenPosition = BaseDraw::GetScreenPosition();
			nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
				screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) + 250.0f };

			// ボスの座標
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, centerPosition.y + BaseConst::kWindowHeight };

			Novice::PlayAudio(BaseAudio::kBossRush, false, 0.5f);

			// 初期化
			t = 0.0f;
			actionWayPoint++;
		}
		break;
		// ボスが咆哮する
	case MiddleBoss::WAYPOINT3:
		if (t <= runAwayTime) {

			// スクリーンを動かす
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, runAwayTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, runAwayTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// ボスを動かす
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, runAwayTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, runAwayTime);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// スクリーン座標記録
			prevScreenPosition = BaseDraw::GetScreenPosition();
			nextScreenPosition = { screenCenterPosition.x - (float)(BaseConst::kWindowWidth / 2),
				screenCenterPosition.y + (float)(BaseConst::kWindowHeight / 2) };

			// 初期化
			t = 0.0f;
			actionWayPoint++;

		}
		break;
		// 待機してからボス戦開始
	case MiddleBoss::WAYPOINT4:
		if (t <= cameraBackTime) {

			// スクリーンを動かす
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, cameraBackTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, cameraBackTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// 演出終了
			PublicFlag::kisStaging = false;
			isPlayingDeadAnim = false;

			// 初期化
			isEndDeadAnim = true;

			inDead = true;

			t = 0.0f;
			actionWayPoint = WAYPOINT0;

		}
		break;
	case MiddleBoss::WAYPOINT5:
		break;
	case MiddleBoss::WAYPOINT6:
		break;
	default:
		break;
	}
}

// 行動なし関数
// 返り値：なし
// 引数：
// waitTime ... 待機する秒数
// 行動の合間に挟む関数。
void MiddleBoss::None(float waitFrame) {
	if (t <= waitFrame) {
		t += 1.0f / 60.0f;
	}
	else {
		pleaseWait = false;
		t = 0.0f;
		endAction = true;
		inAction = false;
	}
}

// 接近関数
// 返り値：なし
// 引数：
// playerPosition ... プレイヤー中心座標
// moveTIme ... 回転する時間
// afterWaitTime ... 行動後に発生する待機時間
// プレイヤーに向かって接近する関数
void MiddleBoss::Approach(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case MiddleBoss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;

		// プレイヤーの座標を取得
		prePlayerPosition = playerPosition;

		// プレイヤーとの距離を求める
		playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

		// プレイヤーがいる方向を求める
		playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

		// 突進する座標を求める
		nextCenterPosition = {
			centerPosition.x + (cosf(playerDirection) * playerDistance / 4),
			centerPosition.y + (sinf(playerDirection) * playerDistance / 4)
		};

		// t初期化
		t = 0.0f;

		// 次の段階へ
		actionWayPoint++;
		break;
	case MiddleBoss::WAYPOINT1:
		if (t <= moveTime) {

			// ボスを取得したプレイヤーの向きに向かって突進させる
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, (nextCenterPosition.x) - prevCenterPosition.x, moveTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, (nextCenterPosition.y) - prevCenterPosition.y, moveTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			//t が一定以上になったら行動終了
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = APPROACH;
			pleaseWait = true;
			waitTime = afterWaitTime;
			t = 0.0f;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}

		break;
	}
}

// 離反関数
// 返り値：なし
// 引数：
// playerPosition ... プレイヤー中心座標
// moveTIme ... 回転する時間。これは秒数
// afterWaitTime ... 行動後に発生する待機時間
// プレイヤーに向かって離反する関数
void MiddleBoss::Separation(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case MiddleBoss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;

		// プレイヤーの座標を取得
		prePlayerPosition = playerPosition;

		// プレイヤーがいる方向を求める
		playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

		// プレイヤーとの距離を求める
		playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

		// 突進する座標を求める
		nextCenterPosition = {
			centerPosition.x + (cosf(playerDirection) * playerDistance / 4),
			centerPosition.y + (sinf(playerDirection) * playerDistance / 4)
		};

		// t初期化
		t = 0.0f;

		// 次の段階へ
		actionWayPoint++;
		break;
	case MiddleBoss::WAYPOINT1:

		if (t <= moveTime) {

			// ボスを取得したプレイヤーの向きに向かって突進させる
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, -(nextCenterPosition.x - prevCenterPosition.x), moveTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, -(nextCenterPosition.y - prevCenterPosition.y), moveTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			//t が一定以上になったら行動終了
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = SEPARATION;
			pleaseWait = true;
			waitTime = afterWaitTime;
			t = 0.0f;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}

		break;
	}
}

// 回転関数
// 返り値：なし
// 引数：
// endDegree ... 終了時の角度
// rotateTime ... 回転する時間。これは秒数
// afterWaitTime ... 行動後に発生する待機時間
// ボスを回転させる関数
void MiddleBoss::Rotate(float endDegree, float RotateTime, float afterWaitTime, WireManager* wireManager) {

	static int startDegree;
	// 初期化処理
	if (init == false) {
		startDegree = degree;

		// 効果音再生
		Novice::PlayAudio(BaseAudio::kBossClose, false, 0.5f);

		init = true;
	}

	// t の値が一定以上になるまで足す
	if (t <= RotateTime) {
		inAction = true;
		// イージングを用いて回転
		degree = BaseDraw::Ease_InOut(t, startDegree, endDegree, RotateTime);

		if (t >= (RotateTime / 2)) {
			// ワイヤーちぎる
			PublicFlag::kBossisTurningAndCutWire = true;
		}

		t += 1.0f / 60.0f;
	}
	else {

		// ワイヤーをちぎれなくする
		PublicFlag::kBossisTurningAndCutWire = false;

		//t が一定以上になったら行動終了
		prevAttackPattern[1] = prevAttackPattern[0];
		prevAttackPattern[0] = ROTATE;
		pleaseWait = true;
		waitTime = afterWaitTime;
		t = 0.0f;
		degree = 0;
		init = false;
		endAction = true;
		inAction = false;
	}
}

// 突進関数
// 返り値：なし
// 引数：
// playerPosition ... プレイヤーの座標
// readyTime ... 突進の準備にかかる秒数
// chargeTime ... 突進の溜めにかかる秒数
// rushTime ... 突進にかかる秒数
// backTime ... 戻る時にかかる秒数
// afterWaitTime ... 行動後に発生する待機時間
// damage ... 行動によって発生するダメージ
// ボスをプレイヤーの向きに突進させる関数
void MiddleBoss::Rush(Point playerPosition, float readyTime, float chargeTime, float rushTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {

	switch (actionWayPoint)
	{
		// 初期化
	case MiddleBoss::WAYPOINT0:

		// 効果音再生
		Novice::PlayAudio(BaseAudio::kBossCharge, false, 0.5f);

		// 中心座標取得
		prevCenterPosition = centerPosition;

		// t初期化
		t = 0.0f;

		// 次の段階へ
		actionWayPoint++;
		break;
		// 事前動作(震える)
	case MiddleBoss::WAYPOINT1:
		if (t <= readyTime) {
			// 指定された秒数振動する
			ShakeEaseOut(60, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// t初期化
			t = 0.0f;

			// プレイヤーの座標を取得
			prePlayerPosition = playerPosition;

			// プレイヤーがいる方向を求める
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// プレイヤーとの距離を求める
			playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

			if (playerDistance < 500.0f) {
				playerDistance = 500.0f;
			}

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossVibration, false, 0.5f);

			// 突進する座標を求める
			nextCenterPosition = {
				centerPosition.x + (cosf(playerDirection) * -300.0f),
				centerPosition.y + (sinf(playerDirection) * -300.0f)
			};

			// 次へ
			actionWayPoint++;
		}
		break;
		// 溜め
	case MiddleBoss::WAYPOINT2:

		if (t <= chargeTime) {

			// ボスを取得したプレイヤーの向きに向かって突進させる
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// t初期化
			t = 0.0f;

			// プレイヤーの座標を取得
			prePlayerPosition = playerPosition;

			// プレイヤーがいる方向を求める
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// プレイヤーとの距離を求める
			playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

			if (playerDistance < 500.0f) {
				playerDistance = 500.0f;
			}

			prevCenterPosition = centerPosition;

			// 突進する座標を求める
			nextCenterPosition = {
				centerPosition.x + (cosf(playerDirection) * playerDistance),
				centerPosition.y + (sinf(playerDirection) * playerDistance)
			};

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossRush, false, 0.7f);

			// 次へ
			actionWayPoint++;
		}

		break;
		// 突進
	case MiddleBoss::WAYPOINT3:
		if (t <= rushTime) {

			// ボスを取得したプレイヤーの向きに向かって突進させる
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);

			// ダメージを与えられるようにする
			bodyDamage = damage;

			t += 1.0f / 60.0f;
		}
		else {

			// ダメージを与えられなくする
			bodyDamage = 0.0f;

			// 突進する座標を求める
			prevCenterPosition = {
				prevCenterPosition.x + (cosf(playerDirection) * 300.0f),
				prevCenterPosition.y + (sinf(playerDirection) * 300.0f)
			};

			// tを初期化
			t = 0.0f;

			// 次の行動へ
			actionWayPoint++;
		}
		break;
		// 戻る
	case MiddleBoss::WAYPOINT4:
		if (t <= backTime) {
			// ボスを元の座標に戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {

			// ボスの座標を元の位置に戻す（一応）
			centerPosition = prevCenterPosition;

			// t初期化
			t = 0.0f;

			// 行動終了
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = RUSH;
			pleaseWait = true;
			waitTime = afterWaitTime;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	case MiddleBoss::WAYPOINT5:
		break;
	default:
		break;
	}
}

// 斬撃関数
// 返り値：なし
// 引数：
// playerPosition ... プレイヤーの座標
// readyTime ... ボスが開くまでにかかる秒数
// deployTime ... ブレードの展開にかかる秒数
// preparationTime　... 攻撃までの待機時間
// rushTime ... 突進にかかる秒数
// backTime ... 戻る時にかかる秒数
// afterWaitTime ... 行動後に発生する待機時間
// damage ... 行動によって発生するダメージ
// ボスが斬撃を行う関数
void MiddleBoss::Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// 初期化
	case MiddleBoss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;

		// 武器をどれだけ大きくするかを決める
		weaponSize = { 40, 0 };
		prevWeaponSize = weaponSize;
		nextWeaponSize = { weaponSize.x, 400.0f };

		// t初期化
		t = 0.0f;

		// 効果音再生
		Novice::PlayAudio(BaseAudio::kBossOpen, 0, 0.35f);

		//次の段階へ
		actionWayPoint++;
		break;
		// 事前動作(震えてボスが開く)
	case MiddleBoss::WAYPOINT1:
		if (t <= readyTime) {
			// 指定された秒数振動する
			ShakeEaseOut(60, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tをリセット
			t = 0.0f;

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossDeployBlade, 0, 0.5f);

			//次へ
			actionWayPoint++;
		}
		break;
		// ブレード展開
	case MiddleBoss::WAYPOINT2:
		if (t <= deployTime) {

			// ブレードが伸びる
			weaponSize.y = BaseDraw::Ease_InOut(t, prevWeaponSize.y, nextWeaponSize.y - prevWeaponSize.y, deployTime);

			bladeDamage = 1.0f;

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化
			t = 0.0f;

			// 初期角度を設定
			prevDegree = degree;

			//次の行動をランダムに設定して分岐
			actionBranch = BaseMath::Random(Pattern1, Pattern2);
			switch (actionBranch)
			{
				// 右回転
			case MiddleBoss::Pattern1:
				// 左向きに動かす
				nextDegree = prevDegree - 30;
				break;
				// 左回転
			case MiddleBoss::Pattern2:
				// 右向きに動かす
				nextDegree = prevDegree + 30;
				break;
				// 回転切り
				break;
			default:
				break;
			}

			// 次の段階
			actionWayPoint++;
		}

		break;
		// 斬撃準備
	case MiddleBoss::WAYPOINT3:
		if (t <= preparationTime) {
			//ボスを回転させる
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);
			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tを初期化
			t = 0.0f;

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossSlash, 0, 0.25f);

			//プレイヤー座標取得
			prePlayerPosition = playerPosition;

			// プレイヤーがいる方向を求める
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// プレイヤーとの距離を求める
			float playerDistance = BaseMath::GetLength({ prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x });

			// プレイヤーとの距離が一定以下ならその場で斬撃を行う
			if (playerDistance < 200.0f) {
				playerDistance = 0.0f;
			}
			else {
			}

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossRush, 0, 0.6f);

			// 突進する座標を求める
			nextCenterPosition = {
				centerPosition.x + (cosf(playerDirection) * playerDistance / 1.25f),
				centerPosition.y + (sinf(playerDirection) * playerDistance / 1.25f)
			};

			// 初期角度を設定
			prevDegree = degree;

			// 行動分岐に基づいて回転角の設定
			switch (actionBranch)
			{
				// 右回転
			case MiddleBoss::Pattern1:
				nextDegree = prevDegree + 360;
				break;
				// 左回転
			case MiddleBoss::Pattern2:
				nextDegree = prevDegree - 360;
				break;
			default:
				break;
			}

			// 次へ
			actionWayPoint++;
		}
		break;
		// 斬撃
	case MiddleBoss::WAYPOINT4:
		if (t <= slashTime) {

			// ボスを回転させる
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, slashTime);

			// ボスを取得した角度を元に突進させる
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, slashTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, slashTime);

			if (t >= (slashTime / 2)) {
				// ワイヤーちぎる
				PublicFlag::kBossisTurningAndCutWire = true;
			}

			// 分岐：回転斬り以外の場合はtにプラスする値を少しだけ多くする
			t += 1.0f / 60.0f;
		}
		else {

			// ワイヤーちぎる
			PublicFlag::kBossisTurningAndCutWire = false;

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossClose, 0, 0.35f);

			// tを初期化
			t = 0.0f;
			// 次へ
			actionWayPoint++;
		}
		break;
		// 元の場所に戻る
	case MiddleBoss::WAYPOINT5:
		if (t <= backTime) {

			// 位置や角度、武器のサイズを元に戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			degree = BaseDraw::Ease_InOut(t, nextDegree, -nextDegree, backTime);
			weaponSize.y = BaseDraw::Ease_InOut(t, nextWeaponSize.y, -nextWeaponSize.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {

			// ボス座標を初期化（一応）
			centerPosition = prevCenterPosition;

			// ダメージを与えられないように
			bladeDamage = 0.0f;

			// 角度初期化
			degree = 0;
			prevDegree = 0;
			nextDegree = 0;

			// t初期化
			t = 0.0f;

			// 行動終了
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = SLASH;
			waitTime = afterWaitTime;
			pleaseWait = true;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	default:
		break;
	}
}

// オブジェクト落下関数
// 返り値：なし
// 引数：
// readyTime ... ボスの座標を中心に戻す秒数
// deployTime ... 攻撃準備にかかる秒数
// rushTime　... 天井に突進するまでにかかる秒数
// standByTime ... 待機秒数
// backTime ... 戻る時にかかる秒数
// damage ... 行動によって発生するダメージ
// ボスが天井にぶつかり、破片を落下させて攻撃を行う関数
void MiddleBoss::Fall(float readyTime, float deployTime, float rushTime, float standByTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// 初期化
	case MiddleBoss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;
		nextCenterPosition = screenCenterPosition;

		// t初期化
		t = 0.0f;

		//次の段階へ
		actionWayPoint++;
		break;
		// ボスを中心座標に戻す
	case MiddleBoss::WAYPOINT1:
		if (t <= readyTime) {

			// 画面中央へ戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, readyTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossCharge, false, 0.5f);

			// tをリセット
			t = 0.0f;

			// 座標設定
			prevCenterPosition = centerPosition;
			nextCenterPosition = { screenCenterPosition.x, screenCenterPosition.y - 200 };

			//次へ
			actionWayPoint++;
		}
		break;
		// 溜め
	case MiddleBoss::WAYPOINT2:
		if (t <= deployTime) {

			// 若干下に下がる
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, deployTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, deployTime);

			ShakeEaseOut(50, deployTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossRush, false, 0.5f);

			// tを初期化
			t = 0.0f;

			// 座標設定
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, screenCenterPosition.y + ((float)BaseConst::kTutorialStageSizeHeight * ((float)BaseConst::kMapChipSizeHeight) / 2) - (textureSize.y / 2)};

			// 次の段階
			actionWayPoint++;
		}

		break;
		// 天井に突進
	case MiddleBoss::WAYPOINT3:
		if (t <= rushTime) {

			// 突進
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, rushTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, rushTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tを初期化
			t = 0.0f;

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossVibration, false, 0.5f);
			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossStrike, false, 0.5f);


			canGeneratedBlock = true;
			generatedBlockValue = BaseMath::Random(3, 5);

			// 次へ
			actionWayPoint++;
		}
		break;
		// 待機
	case MiddleBoss::WAYPOINT4:
		if (t <= standByTime) {

			// 激突時シェイク
			ShakeEaseOut(50, standByTime);

			// tをプラスする
			t += 1.0f / 60.0f;

		}
		else {

			// 現在の座標を記録する
			prevCenterPosition = screenCenterPosition;
			nextCenterPosition = centerPosition;

			// tを初期化
			t = 0.0f;
			// 次へ
			actionWayPoint++;
		}
		break;
		// 元の場所に戻る
	case MiddleBoss::WAYPOINT5:
		if (t <= backTime) {
			// 位置や角度、武器のサイズを元に戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			// ボス座標を初期化（一応）
			centerPosition = prevCenterPosition;

			// 角度初期化
			degree = 0;
			prevDegree = 0;
			nextDegree = 0;

			// t初期化
			t = 0.0f;

			// 行動終了
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = FALL;
			waitTime = 0.25f;
			pleaseWait = true;
			init = false;
			endAction = true;
			inAction = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	default:
		break;
	}
}

// スタン関数
// 返り値：なし
// 引数：
// readyTime ... スタンし始めモーション秒数
// deployTime ... スタンし始めモーション秒数
// stanTime　... スタン秒数
// backTime ... 戻る時にかかる秒数
// 指定された秒数ボスがスタンする関数
void MiddleBoss::Stun(float readyTime, float deployTime, float stanTime, float backTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case MiddleBoss::WAYPOINT0:

		// 念のため一度初期化
		// 座標取得
		prevCenterPosition = { 0.0f, 0.0f };
		nextCenterPosition = { 0.0f, 0.0f };

		// 角度取得
		prevDegree = 0;
		nextDegree = 0;

		t = 0.0f;
		endAction = true;
		inAction = false;

		// 武器サイズ初期化
		weaponSize = { 0.0f, 0.0f };

		// 座標取得
		prevCenterPosition = centerPosition;
		nextCenterPosition = { centerPosition.x, centerPosition.y + 100.0f };

		// 角度取得
		prevDegree = degree;
		nextDegree = degree + 20;

		// 次の行動へ
		actionWayPoint++;
		break;
		// 
	case MiddleBoss::WAYPOINT1:
		if (t <= readyTime) {
			// 座標関連をイージング
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, readyTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, readyTime);

			// 角度関連をイージング
			degree = BaseDraw::Ease_Out(t, prevDegree, nextDegree - prevDegree, readyTime);

			ShakeEaseOut(30, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// 座標取得
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, centerPosition.y - 150.0f };

			// 角度取得
			prevDegree = degree;
			nextDegree = degree - 40;

			// tを初期化する
			t = 0.0f;
			// 次の行動へ
			actionWayPoint++;
		}
		break;
	case MiddleBoss::WAYPOINT2:
		if (t <= deployTime) {
			// 座標関連をイージング
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, deployTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, deployTime);

			// 角度関連をイージング
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, deployTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化する
			t = 0.0f;
			// 次の行動へ
			actionWayPoint++;
		}
		break;
	case MiddleBoss::WAYPOINT3:
		if (t <= stanTime) {

			// 一定秒数振動
			vibration(10, stanTime, stanTime, 3);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			prevCenterPosition = centerPosition;
			nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };

			prevDegree = degree;

			vibInit = false;

			// tを初期化する
			t = 0.0f;
			// 次の行動へ
			actionWayPoint++;
		}
		break;
	case MiddleBoss::WAYPOINT4:
		if (t <= backTime) {

			// 座標関連をイージング
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);

			// 角度関連をイージング
			degree = BaseDraw::Ease_InOut(t, prevDegree, -prevDegree, backTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化する
			t = 0.0f;
			// 行動終了
			inStun = false;
			actionWayPoint = WAYPOINT0;
		}
		break;
	case MiddleBoss::WAYPOINT5:
		break;
	default:
		break;
	}
}

/******** ダメージアニメーション **********/
// ダメージアニメーション関数
// 返り値：なし
// 引数：
// readyTime ... 振動する時間
// shakeStrength ... 振動する強さ
// ダメージが与えられた時のアニメーションを再生する関数
void MiddleBoss::playTakeDamageAnim(float animTime, float shakeStrength) {
	if (spareT <= animTime) {
		shakeRange = BaseDraw::Ease_Out(spareT, shakeStrength, -shakeStrength, animTime);

		shakeVariation.x = BaseMath::RandomF(-shakeStrength / 2, shakeStrength / 2, 0);
		shakeVariation.y = BaseMath::RandomF(-shakeStrength / 2, shakeStrength / 2, 0);

		// tをプラスする
		spareT += 1.0f / 60.0f;
	}
	else {

		//tを初期化
		spareT = 0.0f;
		inDamage = false;
	}
}