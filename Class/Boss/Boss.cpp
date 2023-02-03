#include "Class/Boss/Boss.h"

/*********************************************
 * ボスクラス
 *
 * ボス関連の行動すべてを管理するクラス
 *********************************************/

// コンストラクタ
Boss::Boss() {
	// ボスの位置を画面中央に持っていく
	this->centerPosition = { (float)(BaseConst::kWindowWidth / 2),(float)(BaseConst::kWindowHeight / 2) };
	// ボスの画像サイズを設定
	this->textureSize = { 225.0f, 450.0f };
	// ボスのオフセットを初期化
	this->offset = 0.0f;

	// 角度初期化
	this->degree = 0.0f;
	// 1フレーム前の角度を初期化
	this->beforeDegree = 0.0f;

	//シェイクしていない状態に戻す
	this->shakeVariation = { 0.0f, 0.0f };
	this->coreShakeVariation = { 0.0f, 0.0f };

	// バイブレーション初期化
	vibInit = false;

	// 行動終了状態にする
	this->t = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->actionWayPoint = 0;

	// 核の当たり判定を初期化
	core = NULL;

	// 核の位置を設定
	this->coreCenterPosition = centerPosition;
	// 核の画像サイズを設定
	this->coreTextureSize = { 256.0f, 256.0f };

	// 核の画像サイズを設定
	this->hookTextureSize = { 64.0f, 64.0f };

	// 武器のサイズを指定（仮テクスチャのため、今後変える）
	this->weaponSize = { 0.0f, 0.0f };
	this->weaponTextureSize = { 1.0f, 1.0f };

	// フックサイズ初期化
	hookSize = { 96.0f, 96.0f };

	// フックの初期化
	for (int i = 0; i < kmaxWireHang; i++) {
		this->wireHangPosition[i] = { 0.0f, 0.0f };
		hook[i] = NULL;
	}

	// 攻撃パターン初期化
	this->prevAttackPattern[0] = NONE;
	this->prevAttackPattern[1] = NONE;
	this->attackPattern = NONE;

	// 待機中
	pleaseWait = true;

	// 待機時間を代入
	this->waitTime = 2.5f;

	// HP初期化
	this->HP = MaxHP;

	// 与えるダメージ初期化
	this->bodyDamage = 0.0f;
	this->bladeDamage = 0.0f;

	/// 弾の関係初期化
	for (int i = 0; i < kmaxBullet; i++) {
		// 弾の座標
		this->bulletCenterPosition[i] = { 0.0f, 0.0f };

		// 発射していない状態にする
		this->isShot[i] = false;

		// 弾の発射方向をリセットする
		this->bulletDirection[i] = 0.0f;

		// 弾の生存時間をリセットする
		this->bulletAliveTime[i] = 0.0f;

		// 弾のダメージ初期化
		this->bulletDamage[i] = 0.0f;

	}

	// 弾のサイズを指定
	this->bulletSize = { 20.0f, 20.0f };
	// 弾の画像サイズを指定（仮テクスチャのため、今後変える)
	this->bulletTextureSize = { 1.0f, 1.0f };

	// 弾の発射スピードを指定
	this->bulletSpeed = 7.0f;

	/// オブジェクト関連
	// オブジェクトを生成するかどうか
	this->canGeneratedBlock = false;

	// オブジェクト生成個数
	this->generatedBlockValue = 0;

	// オブジェクト生成間隔
	this->generatedBlockInterval = 0.0f;
}

// デストラクタ
Boss::~Boss() {

}

// 初期化処理
void Boss::Initialize(ObjectManager* objectManager) {
	// ボスの位置を画面中央に持っていく
	this->centerPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };
	// ボスの画像サイズを設定
	this->textureSize = { 225.0f, 450.0f };
	// ボスのオフセットを初期化
	this->offset = 0.0f;

	// 角度初期化
	this->degree = 0.0f;
	// 1フレーム前の角度を初期化
	this->beforeDegree = 0.0f;

	//シェイクしていない状態に戻す
	this->shakeVariation = { 0.0f, 0.0f };
	this->coreShakeVariation = { 0.0f, 0.0f };

	// カットシーン用カメラ移動前座標
	this->prevScreenPosition = {0.0f, 0.0f};

	// カットシーン用カメラ移動後座標
	this->nextScreenPosition = {0.0f, 0.0f};

	// バイブレーション初期化
	vibInit = false;

	// 振動音再生トリガーをfalseに
	isVibPlaySound = false;

	// 戦闘開始していない状態にする
	this->isBattleStart = false;

	// 行動終了状態にする
	this->t = 0.0f;
	this->spareT = 0.0f;
	this->endAction = true;
	this->inAction = false;
	this->inStun = false;
	this->canTakeDamage = false;
	this->inDamage = false;
	this->actionWayPoint = 0;

	// 核の位置を設定
	this->coreCenterPosition = centerPosition;
	// 核の画像サイズを設定
	this->coreTextureSize = { 256.0f, 256.0f };

	// 核のサイズ
	this->coreSize = { 256.0f, 256.0f };

	coreSeparated = false;

	// 核の当たり判定を初期化
	core = objectManager->MakeNewObjectCore(coreCenterPosition, coreTextureSize);

	// フックの画像サイズを設定
	this->hookTextureSize = { 48.0f, 48.0f };

	// 武器のサイズを指定（仮テクスチャのため、今後変える）
	this->weaponSize = { 0.0f, 0.0f };
	this->weaponTextureSize = { 1.0f, 1.0f };

	// フックサイズ初期化
	hookSize = { 96.0f, 96.0f };

	for (int i = 0; i < kmaxWireHang; i++) {
		this->wireHangPosition[i] = { 0.0f, 0.0f };
		hook[i] = objectManager->MakeNewObjectHook(wireHangPosition[i], {hookSize.x -20.0f, hookSize.y -20.0f});
	}


	// 攻撃パターン初期化
	this->prevAttackPattern[0] = NONE;
	this->prevAttackPattern[1] = NONE;
	this->attackPattern = NONE;

	// 待機中
	pleaseWait = true;

	// 待機時間を代入
	this->waitTime = 1.0f;

	// HP初期化
	this->HP = MaxHP;

	// 与えるダメージ初期化
	this->bodyDamage = 0.0f;
	this->bladeDamage = 0.0f;

	// 死亡していない状態にする
	this->inDead = false;

	/// 弾の関係初期化
	for (int i = 0; i < kmaxBullet; i++) {
		// 弾の座標
		this->bulletCenterPosition[i] = { 0.0f, 0.0f };

		// 発射していない状態にする
		this->isShot[i] = false;

		// 弾の発射方向をリセットする
		this->bulletDirection[i] = 0.0f;

		// 弾の生存時間をリセットする
		this->bulletAliveTime[i] = 0.0f;

		// 弾のダメージ初期化
		this->bulletDamage[i] = 0.0f;

	}

	// 弾のサイズを指定
	this->bulletSize = { 20.0f, 20.0f };
	// 弾の画像サイズを指定（仮テクスチャのため、今後変える)
	this->bulletTextureSize = { 1.0f, 1.0f };

	// 弾の発射スピードを指定
	this->bulletSpeed = 7.0f;

	/// オブジェクト関連
	// オブジェクトを生成するかどうか
	this->canGeneratedBlock = false;

	// オブジェクト生成個数
	this->generatedBlockValue = 0;

	// オブジェクト生成間隔
	this->generatedBlockInterval = 0.0f;

	// 色関係初期化
	this->color = 0xFFFFFFFF;
	this->coreColor = 0xFFFFFFFF;

	// 演出スキップ用
	LongPressFrame = 0.0f;

	// 現在演出中か
	isPlayingStartAnim = false;

	// 死亡アニメーション
	isPlayingDeadAnim = false;

	// 死亡アニメーションが終了しているか
	isEndDeadAnim = false;

	PullSoundHundle = BaseAudio::kBossPull;
	PullVoiceHundle = -1;

}

// 更新処理
void Boss::Update(Point playerPosition, ObjectManager* objectManager, WireManager* wireManager) {

	/******** デバック処理 **********/
	// デバッグ状態の切り替え
	if (BaseInput::GetKeyboardState(DIK_H, Press) && BaseInput::GetKeyboardState(DIK_U, Press)) {
		if (BaseInput::GetKeyboardState(DIK_BACKSPACE, Trigger)) {
			if (inDebug == false) {
				// 戦闘開始状態にする
				isBattleStart = true;
				// オフセット初期化
				offset = 0;
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

	// 核が分離していない状態では核をボスに追従させる
	if (coreSeparated == false) {
		coreCenterPosition = centerPosition;
		coreShakeVariation = shakeVariation;
		coreDegree = degree;
	}

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
							case Boss::Pattern1:
								attackPattern = FALL;
								break;
							case Boss::Pattern2:
								attackPattern = SLASH;
								break;
							case Boss::Pattern3:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[0] == SEPARATION
									|| prevAttackPattern[1] == APPROACH || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = ROTATE;
								}

								break;
							case Boss::Pattern4:
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
							attackBranch = BaseMath::Random(Pattern1, Pattern5);
							switch (attackBranch)
							{
							case Boss::Pattern1:
								if (prevAttackPattern[0] == APPROACH || prevAttackPattern[0] == SEPARATION
									|| prevAttackPattern[1] == APPROACH || prevAttackPattern[1] == SEPARATION) {
									continue;
								}
								else {
									attackPattern = ROTATE;
								}
								break;
							case Boss::Pattern2:
								attackPattern = SHOT;
								break;
							case Boss::Pattern3:
								attackPattern = SLASH;
								break;
							case Boss::Pattern4:
								attackPattern = RUSH;
								break;
							case Boss::Pattern5:
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

				// 行動開始
				inAction = true;
				endAction = false;

			}
		}

		// 行動の実行処理
		if (inAction == true && inStun == false && canTakeDamage == false && isPlayingDeadAnim ==false) {
			switch (attackPattern)
			{
			case Boss::NONE:
				None(waitTime);
				break;
			case Boss::ROTATE:
				Rotate(720, 2.0f, 0.5f, wireManager);
				break;
			case Boss::RUSH:
				Rush(playerPosition, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case Boss::SLASH:
				Slash(playerPosition, 0.35f, 0.2f, 1.25f, 1.0f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case Boss::SHOT:
				Shot(playerPosition, 0.35f, 0.75f, 1.0f, 5.0f, 1.0f, 1.0f, 0.2f, 1.0f, wireManager);
				break;
			case Boss::FALL:
				Fall(0.35f, 1.0f, 0.15f, 0.75f, 1.0f, 1.0f, 1.0f, wireManager);
				break;
			case Boss::APPROACH:
				Approach(playerPosition, 1.0f, 0.1f, wireManager);
				break;
			case Boss::SEPARATION:
				Separation(playerPosition, 1.0f, 0.1f, wireManager);
				break;
			}
		}

		// スタン処理
		if (inStun == true && canTakeDamage == false) {
			Stun(1.25f, 1.5f, 3.0f, 0.75f, wireManager);
		}

		// ダメージを受けられる状態にする処理
		if (canTakeDamage == true && isPlayingDeadAnim == false) {
			MakeDamagePossible(0.15f, 1.5f, 0.1f, 10.0f, 0.75f, 0.25f, wireManager, objectManager);
		}
		else {
			if (hook[0]->GetisPulled() == true && hook[1]->GetisPulled() == true) {
				actionWayPoint = WAYPOINT0;
				canTakeDamage = true;
			}
		}

		// ダメージを与えた際のアニメーション再生
		if (inDamage == true) {
			playTakeDamageAnim(0.1f, 50);
		}

		degree %= 360;

		//　コアの当たり判定の中心座標をセットし続ける
		// ボスが開いている時はボス自体のヒットボックスを無効にする
		if (offset > 150) {
			// 開いてる時に追従
			core->SetCenterPosition(viewPosition);

			if (isPlayingDeadAnim == false) {
				color = 0x333333FF;
			}

			// ボスのヒットボックスを有効にする
			EnemyAttackHitBox::MakeNewHitBoxRight({ 10000.0f, 10000.0f }, textureSize.y / 2.0f, degree, bodyDamage);
			EnemyAttackHitBox::MakeNewHitBoxLeft({ 10000.0f, 10000.0f }, textureSize.y / 2.0f, degree, bodyDamage);

		}
		else {
			// 開いていないときはありえないほどとおくに
			core->SetCenterPosition({ 10000.0f, 10000.0f });

			if (isPlayingDeadAnim == false) {
				color = 0xFFFFFFFF;
			}

			// ボスのヒットボックスを有効にする
			EnemyAttackHitBox::MakeNewHitBoxRight(GetRCoverCollision(centerPosition), textureSize.y / 2.0f, degree, bodyDamage);
			EnemyAttackHitBox::MakeNewHitBoxLeft(GetLCoverCollision(centerPosition), textureSize.y / 2.0f, degree, bodyDamage);

		}

		// フックの座標を更新し続ける
		wireHangPosition[0] = GetLHookPosition(viewPosition);
		wireHangPosition[1] = GetRHookPosition(viewPosition);

		// フックの中心座標をセットする
		hook[0]->SetCenterPosition(wireHangPosition[0]);
		hook[1]->SetCenterPosition(wireHangPosition[1]);

		float degreeDifference = degree - beforeDegree;

		for (int i = 0; i < 5; i++) {
			// 武器のヒットボックス
			EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree + (degreeDifference * i), bladeDamage);
		}

		// 武器のヒットボックス
		EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree, bladeDamage);
		EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree - 30.0f, bladeDamage);
		EnemyAttackHitBox::MakeNewHitBox(GetWeaponPosition(viewPosition), weaponSize.x, weaponSize.y, (float)degree + 30.0f, bladeDamage);

		/// 弾関係の更新処理
		// 発射地点の更新
		shotPoint = GetShotPosition(centerPosition);

		// 弾が発射されている時の処理
		for (int i = 0; i < kmaxBullet; i++) {

			// 弾のヒットボックス
			EnemyAttackHitBox::MakeNewHitBox(bulletCenterPosition[i], bulletSize.x, bulletSize.y, 0.0f, bulletDamage[i]);

			if (isShot[i] == true && bulletAliveTime[i] > 0.0f) {

				// 弾の移動
				bulletCenterPosition[i].x += -cosf(bulletDirection[i]) * bulletSpeed;
				bulletCenterPosition[i].y += -sinf(bulletDirection[i]) * bulletSpeed;

				// 弾の生存時間をマイナス
				bulletAliveTime[i] -= 1.0f / 60.0f;
			}
			else {
				// 消滅する時ダメージを０に
				bulletDamage[i] = 0.0f;
				isShot[i] = false;
			}
		}

		/// オブジェクト関係の更新処理

		// オブジェクト生成する
		if (canGeneratedBlock == true) {

			// 生成間隔が0になると生成
			if (generatedBlockInterval < 0) {
				if (generatedBlockValue > 0) {
					float blockSize = BaseMath::RandomF(20.0f, 60.0f, 0);

					Point spawnPoint = { BaseMath::RandomF(BaseConst::kMapChipSizeWidth + blockSize, BaseConst::kBossStageSizeWidth * BaseConst::kMapChipSizeWidth - blockSize, 1),
						(float)BaseConst::kBossStageSizeHeight * BaseConst::kMapChipSizeHeight - BaseConst::kMapChipSizeHeight - blockSize };

					// 範囲内だった場合は再抽選
					while (spawnPoint.x + blockSize >= centerPosition.x - textureSize.x / 2.0f && spawnPoint.x - blockSize <= centerPosition.x + textureSize.x / 2.0f)
					{
						spawnPoint = { BaseMath::RandomF(BaseConst::kMapChipSizeWidth + blockSize, BaseConst::kBossStageSizeWidth * BaseConst::kMapChipSizeWidth - blockSize, 1),
						(float)BaseConst::kBossStageSizeHeight * BaseConst::kMapChipSizeHeight - BaseConst::kMapChipSizeHeight - blockSize };
					}
					// ランダムな位置に、ランダムな大きさのブロックを生成
					objectManager->MakeNewObjectBlock(spawnPoint, { blockSize, blockSize });
					generatedBlockValue--;
				}
				else {
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
			PlayDeadAnim(2.5f, 3.0f, 5.0f, 0.45f, 2.0f, wireManager);
		}

	}
	else if (inDead == false) {
		// 開始アニメーション再生
		PlayStartAnim(2.5f, 5.0f, 0.25f, 2.5f, 1.0f);

		if (isPlayingStartAnim == true && PublicFlag::kisStaging == false) {
			// 演出終了
			PublicFlag::kisStaging = false;
			isPlayingStartAnim = false;

			// 初期化
			offset = 0;
			shakeVariation = { 0.0f, 0.0f };
			isBattleStart = true;
			LongPressFrame = 0.0f;
			t = 0.0f;
			actionWayPoint = WAYPOINT0;
		}
	}
}

// 描画処理
void Boss::Draw() {

	Point viewPosition = { centerPosition.x + shakeVariation.x,centerPosition.y + shakeVariation.y };
	Point coreViewPosition = { coreCenterPosition.x + coreShakeVariation.x, coreCenterPosition.y + coreShakeVariation.y };

	if (inDead == false) {
		// ボス武器画像 現在は仮テクスチャ
		BaseDraw::DesignationDrawQuad(
			Boss::GetWeaponPosition(viewPosition),
			weaponSize,
			BaseTexture::kDebugTexture,
			weaponTextureSize,
			degree,
			0xFFFFFFFF
		);

		for (int i = 0; i < kmaxBullet; i++) {
			if (isShot[i] == true) {
				// 弾画像 現在は仮テクスチャ
				BaseDraw::DesignationDrawQuad(
					bulletCenterPosition[i],
					bulletSize,
					BaseTexture::kDebugTexture,
					bulletTextureSize,
					0.0f,
					0x000000FF
				);
			}
		}

		// ボスのコア
		BaseDraw::DesignationDrawQuad(
			coreViewPosition,
			coreSize,
			BaseTexture::kBossCore,
			coreTextureSize,
			coreDegree,
			coreColor
		);

		// ボス左側フック画像
		BaseDraw::DesignationDrawQuad(
			Boss::GetLHookPosition(viewPosition),
			hookSize,
			BaseTexture::kBossLHook,
			hookTextureSize,
			degree,
			color
		);

		// ボス右側フック画像
		BaseDraw::DesignationDrawQuad(
			Boss::GetRHookPosition(viewPosition),
			hookSize,
			BaseTexture::kBossRHook,
			hookTextureSize,
			degree,
			color
		);

		// ボス左側画像
		BaseDraw::DrawQuad(
			Boss::GetLCoverPosition(viewPosition),
			BaseTexture::kBossLCover,
			textureSize,
			1.0f,
			degree,
			color
		);

		// ボス右側画像
		BaseDraw::DrawQuad(
			Boss::GetRCoverPosition(viewPosition),
			BaseTexture::kBossRCover,
			textureSize,
			1.0f,
			degree,
			color
		);
	}

	if (isBattleStart == true) {
		// ボスHPゲージ（仮）
		Novice::DrawBox(450, 100, 0 + 100 * HP, 30, 0.0f, 0xdc143cFF, kFillModeSolid);
	}

}

// ボス自体の当たり判定を返す関数
// 返り値：当たっている ... true 当たっていない ... false
// 引数：
// hitPosition ... 当たった座標
// 引数で指定したPointがボスの外殻に命中しているかどうかを返す関数
bool Boss::GetBossCollision(Point hitPosition) {
	
	// 距離を求める
	float x = centerPosition.x - hitPosition.x;
	float y = centerPosition.y - hitPosition.y;
	float d = sqrt(pow(x, 2) + pow(y, 2));

	// ボスが開いている時は当たらない
	if (offset > 0) {
		return false;
	}
	else {
		// 円に命中した場合trueを返す
		if (d <= textureSize.y / 2) {
			return true;
		}
		else {
			return false;
		}
	}
}

// ボス左画像の相対座標を求める
Point Boss::GetLCoverPosition(Point centerPosition) { 
	// 回転中心からの差異ベクトル作成
	Point p = { -textureSize.x / 2 - offset, 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}
// ボス右画像の相対座標を求める
Point Boss::GetRCoverPosition(Point centerPosition) { 
	// 回転中心からの差異ベクトル作成
	Point p = { textureSize.x / 2 + offset, 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// ボス左画像の当たり判定を求める
Point Boss::GetLCoverCollision(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { -textureSize.x / 2 - offset, 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}
// ボス右画像の当たり判定を求める
Point Boss::GetRCoverCollision(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { textureSize.x / 2 + offset, 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// 武器画像の相対座標を求める
Point Boss::GetWeaponPosition(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { 0, weaponSize.y / 2 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// 発射地点の相対座標を求める
Point Boss::GetShotPosition(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { 0, weaponSize.y };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// 左側フックの相対座標を求める
Point Boss::GetLHookPosition(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { -textureSize.x - offset , 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// 右側フックの相対座標を求める
Point Boss::GetRHookPosition(Point centerPosition) {
	// 回転中心からの差異ベクトル作成
	Point p = { textureSize.x + offset , 0 };
	// ベクトル計算
	p = BaseMath::TurnPoint(p, degree);
	// 計算した値を返す
	return { (centerPosition.x + p.x) ,(centerPosition.y + p.y) };
}

// デバッグ用関数
void Boss::Debug() {

	Novice::ScreenPrintf(0, 0, "DebugMode :: ON");
	Novice::ScreenPrintf(0, 20, "ActionSwitching :: 1 ~ 6");
	Novice::ScreenPrintf(0, 40, "1:NONE  2:SPIN  3:RUSH  4:SLASH  5:SHOT  6:FALL");
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
			attackPattern = SHOT;
		}
		else if (BaseInput::GetKeyboardState(DIK_6, Trigger)) {
			attackPattern = FALL;
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

	// ボスをスタンさせる
	if (BaseInput::GetKeyboardState(DIK_9, Trigger)) {
		actionWayPoint = WAYPOINT0;
		canTakeDamage = true;
	}

	if (BaseInput::GetKeyboardState(DIK_UP, Trigger)) {
		actionWayPoint = WAYPOINT0;
		isPlayingDeadAnim = true;
	}

	// ボスを左右に開かせる
	if (BaseInput::GetKeyboardState(DIK_I, Press))
		offset += 1.0f;

	else if (BaseInput::GetKeyboardState(DIK_K, Press))
		offset -= 1.0f;

	// オフセットが指定の値以下になると0にする
	if (offset < 0) {
		offset = 0;
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
	else if(BaseInput::GetKeyboardState(DIK_P, Press)) {
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
void Boss::Shake(int shakeStrength) {
	shakeVariation.x = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
	shakeVariation.y = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
}

// シェイク関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// ボスをシェイクさせる関数
void Boss::CoreShake(int shakeStrength) {
	coreShakeVariation.x = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
	coreShakeVariation.y = BaseMath::RandomF(-shakeStrength, shakeStrength, 1);
}

// シェイクイーズアウト関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// shakeTime ... シェイクする時間
// ボスをシェイクの強さを少しずつ弱くしながら動かす関数
void Boss::ShakeEaseOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	shakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	shakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// シェイクイーズアウト関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// shakeTime ... シェイクする時間
// ボスをシェイクの強さを少しずつ弱くしながら動かす関数
void Boss::CoreShakeEaseOut(int shakeStrength, float shakeTime) {
	shakeRange = BaseDraw::Ease_Out(t, shakeStrength, -shakeStrength, shakeTime);

	coreShakeVariation.x = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
	coreShakeVariation.y = BaseMath::RandomF(-shakeRange / 2, shakeRange / 2, 0);
}

// シェイクイーズインアウト関数
// 返り値：なし
// 引数：
// shakeStrength ... シェイクする際の強さ
// shakeTime ... シェイクする時間
// ボスのシェイクの強さを少しずつ弱くしながら動かす関数
void Boss::ShakeEaseInOut(int shakeStrength, float shakeTime) {
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
void Boss::vibration(int shakeStrength, float vibTime, float vibRate, int vibValue) {

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
/// 戦闘開始時のアニメーションを再生する関数
/// </summary>
/// <param name="cameraMoveTime">振動する時間</param>
/// <param name="vibTime">振動する時間</param>
/// <param name="closeTime1">ボスが途中まで閉じるのにかかる時間</param>
/// <param name="roarTime">咆哮する時間</param>
/// <param name="closeTime2">ボスを完全に閉じる時間</param>
void Boss::PlayStartAnim(float cameraMoveTime, float vibTime, float closeTime1, float roarTime, float closeTime2) {
	switch (actionWayPoint)
	{
		// 初期化
	case Boss::WAYPOINT0:

		// 演出中の状態に
		PublicFlag::kisStaging = true;
		isPlayingStartAnim = true;

		// スクリーン座標記録
		prevScreenPosition = BaseDraw::GetScreenPosition();
		nextScreenPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2) - (float)(BaseConst::kWindowWidth / 2),
			(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) + (float)(BaseConst::kWindowHeight / 2) };

		// オフセットを初期化
		offset = 100;

		// t初期化
		t = 0.0f;
		// 次の段階へ
		actionWayPoint++;

		break;
		// 振動する
	case Boss::WAYPOINT1:
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

			// オフセットの開始値と終端値をリセット
			prevOffset = offset;
			nextOffset = 110;

			// 初期化
			t = 0.0f;
			actionWayPoint++;
		}

		break;
		// 途中まで閉じる
	case Boss::WAYPOINT2:
		if (t <= vibTime) {

			// 定期的に振動させる
			vibration(t * 2, vibTime, vibTime, 3);

			// オフセットを少しだけ大きくする
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, vibTime);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// オフセットの開始値と終端値をリセット
			prevOffset = offset;
			nextOffset = 20;

			// 初期化
			t = 0.0f;
			actionWayPoint++;
		}
		break;

		// 咆哮 (振動)
	case Boss::WAYPOINT3:
		if (t <= closeTime1) {

			// 閉じるときに振動させる
			ShakeEaseOut(40, closeTime1);

			// オフセットを縮める
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, closeTime1);

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {
			// 初期化
			t = 0.0f;
			actionWayPoint++;
		}
		
		break;
		// 完全に閉じる
	case Boss::WAYPOINT4:
		if (t <= roarTime) {

			if (t > 1.0f) {
				Shake(25);
			}

			// tを加算する
			t += 1.0f / 60.0f;
		}
		else {

			// オフセットの開始値と終端値をリセット
			prevOffset = offset;
			nextOffset = 0;

			// 初期化
			t = 0.0f;
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT5:
		if (t <= closeTime2) {

			// オフセットを縮める
			offset = BaseDraw::Ease_InOut(t, prevOffset, -prevOffset, closeTime2);

			// スクリーンを動かす
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_Out(t, nextScreenPosition.x, prevScreenPosition.x - nextScreenPosition.x, closeTime2);
			screenPosition.y = BaseDraw::Ease_Out(t, nextScreenPosition.y, prevScreenPosition.y - nextScreenPosition.y, closeTime2);

			BaseDraw::SetScreenPosition(screenPosition);

			// 中心座標に戻す
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, closeTime2);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, closeTime2);
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
	case Boss::WAYPOINT6:
		break;
	default:
		break;
	}
}

/// <summary>
/// 死亡時のアニメーションを再生する関数
/// </summary>
/// <param name="cameraMoveTime">カメラとボスを中心に持っていく時間</param>
/// <param name="separationTime">核と殻が分離するのにかかる時間</param>
/// <param name="vibTime">振動しながら縮む時間</param>
/// <param name="explosiveTime">サイズを大きくして爆発する</param>
/// <param name="cameraBackTime">カメラが元の位置に帰るまでの時間</param>
void Boss::PlayDeadAnim(float cameraMoveTime, float separationTime, float vibTime, float explosiveTime, float cameraBackTime, WireManager* wireManager){
	switch (actionWayPoint)
	{
		// 初期化
	case Boss::WAYPOINT0:

		// 演出中の状態に
		PublicFlag::kisStaging = true;
		isPlayingDeadAnim = true;

		wireManager->Initialize();

		// スクリーン座標記録
		prevScreenPosition = BaseDraw::GetScreenPosition();
		nextScreenPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2) - (float)(BaseConst::kWindowWidth / 2),
			(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) + (float)(BaseConst::kWindowHeight / 2) - 250.0f };

		// 中心座標取得
		prevCenterPosition = centerPosition;
		nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) - 250.0f };

		prevOffset = offset;
		nextOffset = 175;

		// 角度取得
		prevDegree = degree;

		// 初期化
		t = 0.0f;
		actionWayPoint++;

		break;
		// カメラとボスを中心に持っていく
	case Boss::WAYPOINT1:
		if (t <= cameraMoveTime) {

			// スクリーンを動かす
			Point screenPosition;

			screenPosition.x = BaseDraw::Ease_InOut(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, cameraMoveTime);
			screenPosition.y = BaseDraw::Ease_InOut(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, cameraMoveTime);

			Shake(15);

			BaseDraw::SetScreenPosition(screenPosition);

			// 画面中央へ戻す
			centerPosition.x = BaseDraw::Ease_Out(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, cameraMoveTime);
			centerPosition.y = BaseDraw::Ease_Out(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, cameraMoveTime);

			// 角度を0に
			degree = BaseDraw::Ease_Out(t, prevDegree, -prevDegree, cameraMoveTime);

			// オフセット開く
			offset = BaseDraw::Ease_Out(t, prevOffset, nextOffset - prevOffset, cameraMoveTime);

			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, cameraMoveTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, cameraMoveTime);

			// tを少しづつプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// スクリーン座標記録
			prevScreenPosition = BaseDraw::GetScreenPosition();
			nextScreenPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2) - (float)(BaseConst::kWindowWidth / 2),
				(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) + (float)(BaseConst::kWindowHeight / 2) };

			// コアとボスを分離させる
			coreSeparated = true;

			// コアの座標を設定
			prevCoreCenterPosition = coreCenterPosition;
			nextCoreCenterPosition = { coreCenterPosition.x, (float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };

			// 色を取得
			color = 0x333333FF;
			prevColor = color;
			nextColor = 0x33333300;

			// 中心座標取得
			prevCenterPosition = centerPosition;
			nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) - 1000.0f };

			// オフセットを設定
			prevOffset = offset;
			nextOffset = 250;

			// 角度を設定
			prevDegree = degree;
			nextDegree = 190;

			// 次の行動へ
			t = 0.0f;
			actionWayPoint++;

		}
		break;
		// 核と殻が分離する
	case Boss::WAYPOINT2:
		if (t <= separationTime) {

			// スクリーンを動かす
			Point screenPosition;

			// カメラ移動
			screenPosition.x = BaseDraw::Ease_Out(t, prevScreenPosition.x, nextScreenPosition.x - prevScreenPosition.x, separationTime);
			screenPosition.y = BaseDraw::Ease_Out(t, prevScreenPosition.y, nextScreenPosition.y - prevScreenPosition.y, separationTime);

			BaseDraw::SetScreenPosition(screenPosition);

			// 振動
			ShakeEaseOut(20, separationTime);
			CoreShakeEaseOut(20, separationTime);

			// 画面中央へ戻す
			coreCenterPosition.x = BaseDraw::Ease_InOut(t, prevCoreCenterPosition.x, nextCoreCenterPosition.x - prevCoreCenterPosition.x, separationTime);
			coreCenterPosition.y = BaseDraw::Ease_InOut(t, prevCoreCenterPosition.y, nextCoreCenterPosition.y - prevCoreCenterPosition.y, separationTime);

			color = ColorEasing(t, prevColor, nextColor, separationTime);

			// 画面中央へ戻す
			centerPosition.x = BaseDraw::Ease_In(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, separationTime);
			centerPosition.y = BaseDraw::Ease_In(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, separationTime);

			// 角度を0に
			degree = BaseDraw::Ease_In(t, prevDegree, nextDegree - prevDegree, separationTime);

			// オフセット開く
			offset = BaseDraw::Ease_In(t, prevOffset, nextOffset - prevOffset, separationTime);

			// tを少しづつプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// コアのサイズを設定
			prevCoreSize = coreSize;
			nextCoreSize = { 64, 64 };

			// 次の行動へ
			t = 0.0f;
			actionWayPoint++;

		}

		break;
		// 振動しながら縮む
	case Boss::WAYPOINT3:
		if (t <= vibTime) {

			CoreShake(15);

			coreSize.x = BaseDraw::Ease_InOut(t, prevCoreSize.x, nextCoreSize.x - prevCoreSize.x, vibTime);
			coreSize.y = BaseDraw::Ease_InOut(t, prevCoreSize.y, nextCoreSize.y - prevCoreSize.y, vibTime);

			// tを少しづつプラスする
			t += 1.0f / 60.0f;
		}
		else {

			prevCoreSize = coreSize;
			nextCoreSize = { 512, 512 };

			prevColor = coreColor;
			nextColor = 0xFFFFFF00;

			// 次の行動へ
			t = 0.0f;
			actionWayPoint++;

		}

		break;
		// サイズを大きくして爆発
	case Boss::WAYPOINT4:
		if (t <= explosiveTime) {

			CoreShake(20);

			coreSize.x = BaseDraw::Ease_InOut(t, prevCoreSize.x, nextCoreSize.x - prevCoreSize.x, explosiveTime);
			coreSize.y = BaseDraw::Ease_InOut(t, prevCoreSize.y, nextCoreSize.y - prevCoreSize.y, explosiveTime);

			coreColor = ColorEasing(t - explosiveTime / 2, prevColor, nextColor, explosiveTime - explosiveTime / 2);

			// tを少しづつプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// 次の行動へ
			t = 0.0f;
			actionWayPoint++;

		}
		break;
		// カメラを元の位置に戻す
	case Boss::WAYPOINT5:
		if (t <= cameraBackTime) {
			// tを少しづつプラスする
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
	case Boss::WAYPOINT6:

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
void Boss::None(float waitFrame) {
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
void Boss::Approach(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case Boss::WAYPOINT0:
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
	case Boss::WAYPOINT1:
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
void Boss::Separation(Point playerPosition, float moveTime, float afterWaitTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case Boss::WAYPOINT0:
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
	case Boss::WAYPOINT1:

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
void  Boss::Rotate(float endDegree, float RotateTime, float afterWaitTime, WireManager* wireManager) {

	static int startDegree;
	// 初期化処理
	if (init == false) {
		startDegree = degree;
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
void Boss::Rush(Point playerPosition, float readyTime, float chargeTime, float rushTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {

	switch (actionWayPoint)
	{
		// 初期化
	case Boss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;

		// t初期化
		t = 0.0f;

		// 次の段階へ
		actionWayPoint++;
		break;
		// 事前動作(震える)
	case Boss::WAYPOINT1:
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
	case Boss::WAYPOINT2:
		
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
	case Boss::WAYPOINT3:
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
	case Boss::WAYPOINT4:
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
	case Boss::WAYPOINT5:
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
void Boss::Slash(Point playerPosition, float readyTime, float deployTime, float preparationTime, float slashTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	// 初期化
	case Boss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;

		// ボスがどれだけ開くかを決める
		prevOffset = offset;
		nextOffset = 20;

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
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// 指定された秒数振動する
			ShakeEaseOut(60, readyTime);

			// ボスが少しづつ開く
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, readyTime);

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
	case Boss::WAYPOINT2:
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
			actionBranch = BaseMath::Random(0, 2);
			switch (actionBranch)
			{
				// 右回転
			case Boss::Pattern1:
				// 左向きに動かす
				nextDegree = prevDegree - 30;
				break;
				// 左回転
			case Boss::Pattern2:
				// 右向きに動かす
				nextDegree = prevDegree + 30;
				break;
				// 回転切り
			case Boss::Pattern3:
				nextDegree = prevDegree;
				break;
			default:
				break;
			}

			// 次の段階
			actionWayPoint++;
		}

		break;
		// 斬撃準備
	case Boss::WAYPOINT3:
		if (t <= preparationTime) {
			//ボスを回転させる
			degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);

			// 分岐：回転斬りの場合は振動させる
			if (actionBranch == Pattern3)
				ShakeEaseInOut(30, preparationTime);

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
			Novice::PlayAudio(BaseAudio::kBossRush, 0, 0.4f);

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
			case Boss::Pattern1:
				nextDegree = prevDegree + 360;
				break;
				// 左回転
			case Boss::Pattern2:
				nextDegree = prevDegree - 360;
				break;
				// 回転切り
			case Boss::Pattern3:
				nextDegree = prevDegree + 720;
				break;
			default:
				break;
			}

			// 次へ
			actionWayPoint++;
		}
		break;
		// 斬撃
	case Boss::WAYPOINT4:
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
			if (actionBranch == 2) {
				t += 0.75f / 60.0f;
			}
			else {
				t += 1.0f / 60.0f;
			}
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
	case Boss::WAYPOINT5:
		if (t <= backTime) {
			// 位置や角度、武器のサイズを元に戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			degree = BaseDraw::Ease_InOut(t, nextDegree, -nextDegree, backTime);
			weaponSize.y = BaseDraw::Ease_InOut(t, nextWeaponSize.y, -nextWeaponSize.y, backTime);
			offset = BaseDraw::Ease_InOut(t, nextOffset, -nextOffset, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			// ボス座標を初期化（一応）
			centerPosition = prevCenterPosition;

			// ダメージを与えられないように
			bladeDamage = 0.0f;

			// オフセット初期化
			offset = 0;

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

// 射撃関数
// 返り値：なし
// 引数：
// playerPosition ... プレイヤーの座標
// readyTime ... ボスが開くまでにかかる秒数
// deployTime ... 銃の展開にかかる秒数
// preparationTime　... 攻撃までの待機時間
// shotTime ... 射撃秒数
// backTime ... 戻る時にかかる秒数
// afterWaitTime ... 行動後に発生する待機時間
// fireRate ... 何秒おきに射撃するか
// damage ... 行動によって発生するダメージ
// ボスが射撃を行う関数
void Boss::Shot(Point playerPosition, float readyTime, float deployTime, float preparationTime, float shotTime, float backTime, float afterWaitTime, float fireRate, float damage, WireManager* wireManager) {

	// ボスがプレイヤーに追従して回転する時に用いるカウント変数
	static int count;

	// ボスの発射レートを管理する変数
	static float fireRateCount;

	switch (actionWayPoint)
	{
		// 初期化
	case Boss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;
		nextCenterPosition = centerPosition;

		// ボスがどれだけ開くかを決める
		prevOffset = offset;
		nextOffset = 20;

		// 武器をどれだけ大きくするかを決める
		weaponSize = { 40, 0 };
		prevWeaponSize = weaponSize;
		nextWeaponSize = { weaponSize.x, 250.0f };

		// t初期化
		t = 0.0f;

		// カウンター系初期化
		count = 0;
		fireRateCount = 0;

		// 効果音再生
		Novice::PlayAudio(BaseAudio::kBossOpen, 0, 0.35f);

		//次の段階へ
		actionWayPoint++;
		break;
		// 事前動作(震えてボスが開く)
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// 指定された秒数振動する
			ShakeEaseOut(60, readyTime);

			// ボスが少しづつ開く
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tをリセット
			t = 0.0f;

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossPickGun, 0, 0.45f);

			//次へ
			actionWayPoint++;
		}
		break;
		// 銃展開
	case Boss::WAYPOINT2:
		if (t <= deployTime) {

			// 銃が伸びる
			weaponSize.y = BaseDraw::Ease_InOut(t, prevWeaponSize.y, nextWeaponSize.y - prevWeaponSize.y, deployTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化
			t = 0.0f;

			// 初期角度を設定
			prevDegree = degree;

			//次の行動をランダムに設定して分岐
			actionBranch = BaseMath::Random(0, 2);
			switch (actionBranch)
			{
				// 右回転
			case Boss::Pattern1:
				// 左向きに動かす
				nextDegree = prevDegree - 30;
				break;
				// 左回転
			case Boss::Pattern2:
				// 右向きに動かす
				nextDegree = prevDegree + 30;
				break;
				// 追従射撃
			case Boss::Pattern3:
				break;
			default:
				break;
			}

			// 次の段階
			actionWayPoint++;
		}

		break;
		// 射撃準備
	case Boss::WAYPOINT3:
		if (t <= preparationTime) {

			if (actionBranch == Pattern3) {

				// プレイヤー座標取得
				prePlayerPosition = playerPosition;

				// プレイヤーがいる方向を求める
				playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

				// プレイヤーのいる角度を取得
				nextDegree = BaseMath::RadiantoDegree(playerDirection) - 90;

				float absDegree = nextDegree - degree;

				degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);
			}
			else {
				// ボスを回転させる
				degree = BaseDraw::Ease_InOut(t, prevDegree, nextDegree - prevDegree, preparationTime);
			}

			// 分岐：回転斬りの場合は振動させる
			if (actionBranch == Pattern3)
				ShakeEaseInOut(30, preparationTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tを初期化
			t = 0.0f;

			// 初期角度を設定
			prevDegree = degree;

			// 行動分岐に基づいて回転角の設定
			switch (actionBranch)
			{
				// 右回転
			case Boss::Pattern1:
				nextDegree = prevDegree + 720;
				break;
				// 左回転
			case Boss::Pattern2:
				nextDegree = prevDegree - 720;
				break;
				// 追従射撃
			case Boss::Pattern3:
				
				break;
			default:
				break;
			}

			// プレイヤー座標取得
			prePlayerPosition = playerPosition;

			// プレイヤーがいる方向を求める
			playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

			// 次へ
			actionWayPoint++;
		}
		break;
		// 射撃
	case Boss::WAYPOINT4:
		if (t <= shotTime) {

			if (actionBranch == Pattern3) {

				// プレイヤー座標取得
				prePlayerPosition = playerPosition;

				// プレイヤーがいる方向を求める
				playerDirection = atan2(prePlayerPosition.y - centerPosition.y, prePlayerPosition.x - centerPosition.x);

				// 初期角度を設定
				/*prevDegree = degree;*/

				// プレイヤーのいる角度を取得
				nextDegree = BaseMath::RadiantoDegree(playerDirection) - 90;

				float absDegree = nextDegree - degree;

				if (count == 0) {
					// ボスを回転させる
					if (absDegree < 0) {
						degree -= 1;
					}
					else if (absDegree > 0) {
						degree += 1;
					}
					count = 0;
				}
				else {
					count++;
				}
			}
			else {
				// ボスを回転させる
				degree = BaseDraw::Linear(t, prevDegree, nextDegree - prevDegree, shotTime);
			}

			// 射撃時に振動させる
			Shake(10);

			if (fireRateCount <= fireRate) {
				fireRateCount += 1.0 / 60.0f;
			}
			else {
				for (int i = 0; i < kmaxBullet; i++) {
					if (isShot[i] == false) {

						Novice::PlayAudio(BaseAudio::kBossShot, 0, 0.55f);

						// ダメージを既定値に
						bulletDamage[i] = damage;

						// 座標を発射地点まで移す
						bulletCenterPosition[i] = shotPoint;
						// 弾の発射向きを変更する
						bulletDirection[i] = BaseMath::DegreetoRadian(degree - 90);

						// 弾の生存時間を決める
						bulletAliveTime[i] = 5.0f;

						// 弾を発射した状態にする
						isShot[i] = true;

						// カウンター初期化
						fireRateCount = 0.0f;
						// 処理を抜ける
						break;
					}
				}
			}

			// tをプラスする
			t += 1.0f / 60.0f;

		}
		else {

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossClose, 0, 0.35f);

			// 現在の座標を記録する
			nextCenterPosition = centerPosition;

			// 現在の角度を決める
			nextDegree = degree;

			// tを初期化
			t = 0.0f;
			// 次へ
			actionWayPoint++;
		}
		break;
		// 元の場所に戻る
	case Boss::WAYPOINT5:
		if (t <= backTime) {
			// 位置や角度、武器のサイズを元に戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, nextCenterPosition.x, prevCenterPosition.x - nextCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, nextCenterPosition.y, prevCenterPosition.y - nextCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);
			degree = BaseDraw::Ease_InOut(t, nextDegree, -nextDegree, backTime);
			weaponSize.y = BaseDraw::Ease_InOut(t, nextWeaponSize.y, -nextWeaponSize.y, backTime);
			offset = BaseDraw::Ease_InOut(t, nextOffset, -nextOffset, backTime);
			t += 1.0f / 60.0f;
		}
		else {
			// ボス座標を初期化（一応）
			centerPosition = prevCenterPosition;

			// オフセット初期化
			offset = 0;

			// 角度初期化
			degree = 0;
			prevDegree = 0;
			nextDegree = 0;

			// t初期化
			t = 0.0f;

			// 行動終了
			prevAttackPattern[1] = prevAttackPattern[0];
			prevAttackPattern[0] = SHOT;
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
void Boss::Fall(float readyTime, float deployTime, float rushTime, float standByTime, float backTime, float afterWaitTime, float damage, WireManager* wireManager) {
	switch (actionWayPoint)
	{
		// 初期化
	case Boss::WAYPOINT0:
		// 中心座標取得
		prevCenterPosition = centerPosition;
		nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };

		// t初期化
		t = 0.0f;

		//次の段階へ
		actionWayPoint++;
		break;
		// ボスを中心座標に戻す
	case Boss::WAYPOINT1:
		if (t <= readyTime) {

			// 画面中央へ戻す
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, readyTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {
			// tをリセット
			t = 0.0f;

			// 座標設定
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, centerPosition.y - 200 };

			//次へ
			actionWayPoint++;
		}
		break;
		// 溜め
	case Boss::WAYPOINT2:
		if (t <= deployTime) {

			// 若干下に下がる
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, deployTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, deployTime);

			ShakeEaseOut(50, deployTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化
			t = 0.0f;

			// 座標設定
			prevCenterPosition = centerPosition;
			nextCenterPosition = { centerPosition.x, ((float)BaseConst::kBossStageSizeHeight * (float)BaseConst::kMapChipSizeHeight - (float)BaseConst::kMapChipSizeHeight) - (textureSize.y / 2) };

			// 次の段階
			actionWayPoint++;
		}

		break;
		// 天井に突進
	case Boss::WAYPOINT3:
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

			canGeneratedBlock = true;
			generatedBlockValue = BaseMath::Random(3, 5);

			// 次へ
			actionWayPoint++;
		}
		break;
		// 待機
	case Boss::WAYPOINT4:
		if (t <= standByTime) {

			// 激突時シェイク
			ShakeEaseOut(50, standByTime);

			// tをプラスする
			t += 1.0f / 60.0f;

		}
		else {

			// 現在の座標を記録する
			prevCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };
			nextCenterPosition = centerPosition;

			// tを初期化
			t = 0.0f;
			// 次へ
			actionWayPoint++;
		}
		break;
		// 元の場所に戻る
	case Boss::WAYPOINT5:
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

			// オフセット初期化
			offset = 0;

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
void Boss::Stun(float readyTime, float deployTime, float stanTime, float backTime, WireManager* wireManager) {
	switch (actionWayPoint)
	{
	case Boss::WAYPOINT0:

		// 念のため一度初期化
		// 座標取得
		prevCenterPosition = {0.0f, 0.0f};
		nextCenterPosition = { 0.0f, 0.0f };

		// 角度取得
		prevDegree = 0;
		nextDegree = 0;

		prevOffset = 0;
		nextOffset = 0;

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

		prevOffset = offset;
		nextOffset = 0;

		// 次の行動へ
		actionWayPoint++;
		break;
		// 
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// 座標関連をイージング
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, readyTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, readyTime);

			// 角度関連をイージング
			degree = BaseDraw::Ease_Out(t, prevDegree, nextDegree - prevDegree, readyTime);

			// オフセットを0に
			offset = BaseDraw::Ease_InOut(t, prevOffset, -prevOffset, readyTime);

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
	case Boss::WAYPOINT2:
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
	case Boss::WAYPOINT3:
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
	case Boss::WAYPOINT4:
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
	case Boss::WAYPOINT5:
		break;
	default:
		break;
	}
}

/******** ダメージ **********/
// ダメージ関数
// 返り値：なし
// 引数：
// readyTime ... スタンし始めモーション秒数
// deployTime ... スタンし始めモーション秒数
// openTime ... 開くまでにかかる時間
// stanTime　... スタン秒数
// backTime ... 戻る時にかかる秒数
// closeTime ... 閉じるまでにかかる時間
// ボスに対してダメージが与えられる状態にする関数
void Boss::MakeDamagePossible(float readyTime, float deployTime, float openTime, float stanTime, float backTime, float closeTime, WireManager* wireManager, ObjectManager* objectManager) {

	switch (actionWayPoint)
	{
	case Boss::WAYPOINT0:

		// 念のため一度初期化
		// 座標取得
		prevCenterPosition = { 0.0f, 0.0f };
		nextCenterPosition = { 0.0f, 0.0f };

		// 角度取得
		prevDegree = 0;
		nextDegree = 0;

		prevOffset = 0;
		nextOffset = 0;

		t = 0.0f;
		endAction = true;
		inAction = false;
		inStun = false;

		// 武器サイズ初期化
		weaponSize = { 0.0f, 0.0f };

		// 座標取得
		prevCenterPosition = centerPosition;
		nextCenterPosition = centerPosition;

		prevOffset = offset;
		nextOffset = 5;

		// 次の行動へ
		actionWayPoint++;
		break;
		// 
	case Boss::WAYPOINT1:
		if (t <= readyTime) {
			// オフセットを0に
			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, readyTime);

			ShakeEaseOut(30, readyTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			if (Novice::IsPlayingAudio(PullVoiceHundle) == 0 || PullVoiceHundle == -1) {
				// 効果音再生
				PullVoiceHundle = Novice::PlayAudio(PullSoundHundle, true, 0.5f);
			}

			// tを初期化する
			t = 0.0f;
			// 次の行動へ
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT2:
		if (t <= deployTime) {
			// 座標関連をイージング
			Shake(10);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			Novice::StopAudio(PullVoiceHundle);

			prevOffset = offset;
			nextOffset = 175;

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossHardOpen, false, 0.5f);

			// tを初期化する
			t = 0.0f;
			// 次の行動へ
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT3:
		if (t <= openTime) {

			offset = BaseDraw::Ease_InOut(t, prevOffset, nextOffset - prevOffset, openTime);

			ShakeEaseInOut(20, openTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			canGeneratedBlock = true;
			generatedBlockValue = 5;

			// tを初期化する
			t = 0.0f;
			// 次の行動へ
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT4:
		if (t <= stanTime) {

			vibration(15, stanTime, stanTime, 4);

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

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			vibInit = false;

			prevCenterPosition = centerPosition;
			nextCenterPosition = { (float)(BaseConst::kMapChipSizeWidth * BaseConst::kBossStageSizeWidth / 2),(float)(BaseConst::kMapChipSizeHeight * BaseConst::kBossStageSizeHeight / 2) };

			prevDegree = degree;

			if (degree < 0) {
				nextDegree = 360;
			}
			else {
				nextDegree = -360;
			}

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossReboot, false, 0.5f);

			// tを初期化する
			t = 0.0f;
			// 次の行動へ
			actionWayPoint++;
		}
		break;
	case Boss::WAYPOINT5:
		if (t <= backTime) {

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

			// 座標関連をイージング
			centerPosition.x = BaseDraw::Ease_InOut(t, prevCenterPosition.x, nextCenterPosition.x - prevCenterPosition.x, backTime);
			centerPosition.y = BaseDraw::Ease_InOut(t, prevCenterPosition.y, nextCenterPosition.y - prevCenterPosition.y, backTime);
			shakeVariation.x = BaseDraw::Ease_InOut(t, shakeVariation.x, -shakeVariation.x, backTime);
			shakeVariation.y = BaseDraw::Ease_InOut(t, shakeVariation.y, -shakeVariation.y, backTime);

			if (t >= (backTime / 2)) {
				wireManager->Initialize();
			}

			// 角度関連をイージング
			degree = BaseDraw::Ease_InOut(t, prevDegree, -prevDegree + nextDegree, backTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// 効果音再生
			Novice::PlayAudio(BaseAudio::kBossOpen, false, 0.35f);

			prevOffset = offset;

			degree = 0;

			// tを初期化する
			t = 0.0f;
			// 次の行動へ
			actionWayPoint++;
		}
		break;
	case WAYPOINT6:

		if (t <= closeTime) {

			offset = BaseDraw::Ease_InOut(t, prevOffset, -prevOffset, closeTime);
			ShakeEaseOut(30, closeTime);

			// tをプラスする
			t += 1.0f / 60.0f;
		}
		else {

			// tを初期化する
			waitTime = 1.0f;
			t = 0.0f;
			// 行動終了
			canTakeDamage = false;
			pleaseWait = false;
			actionWayPoint = WAYPOINT0;
		}

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
void Boss::playTakeDamageAnim(float animTime, float shakeStrength) {
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