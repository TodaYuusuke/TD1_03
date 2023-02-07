#include "Class/Map/MapManager.h"

// コンストラクタ
MapManager::MapManager() {

}
// デストラクタ
MapManager::~MapManager() {

}


// 初期化
void MapManager::TutorialInitialize() {
	for (int y = 0; y < BaseConst::kTutorialStageSizeHeight; y++) {
		for (int x = 0; x < BaseConst::kTutorialStageSizeWidth; x++) {
            tutorialMap[y][x].Initialize((MapChipType)BaseConst::kTutorialStageData[y][x]);
		}
	}

    isBoss = false;
}
void MapManager::BossInitialize() {
    for (int y = 0; y < BaseConst::kBossStageSizeHeight; y++) {
        for (int x = 0; x < BaseConst::kBossStageSizeWidth; x++) {
            bossMap[y][x].Initialize((MapChipType)BaseConst::kBossStageData[y][x]);
        }
    }

    isBoss = true;
}
// 更新
void MapManager::Update() {
    /*if (isBoss) {
        for (int y = 0; y < BaseConst::kBossStageSizeHeight; y++) {
            for (int x = 0; x < BaseConst::kBossStageSizeWidth; x++) {
                bossMap[y][x].Update();
            }
        }
    }
    else {
        for (int y = 0; y < BaseConst::kTutorialStageSizeHeight; y++) {
            for (int x = 0; x < BaseConst::kTutorialStageSizeWidth; x++) {
                tutorialMap[y][x].Update();
            }
        }
    }*/
}
// 描画
void MapManager::Draw() {
    if (isBoss) {
        for (int y = 0; y < BaseConst::kBossStageSizeHeight; y++) {
            for (int x = 0; x < BaseConst::kBossStageSizeWidth; x++) {
                if (bossMap[y][x].type == kTypeAir) {
                    continue;
                }

                // もし画面外の場合は描画しない
                Point drawPosition = { (float)x * BaseConst::kMapChipSizeWidth, (float)(BaseConst::kBossStageSizeHeight - y) * BaseConst::kMapChipSizeHeight };
                drawPosition = BaseDraw::WorldtoScreen(drawPosition);

                if (drawPosition.y > 0 - BaseConst::kMapChipSizeHeight) {
                    if (drawPosition.y < BaseConst::kWindowHeight + BaseConst::kMapChipSizeHeight) {
                        if (drawPosition.x > 0 - BaseConst::kMapChipSizeWidth) {
                            if (drawPosition.x < BaseConst::kWindowWidth + BaseConst::kMapChipSizeWidth) {
                                bossMap[y][x].Draw(BaseDraw::ScreentoWorld(drawPosition), GetMapChipType(y, x));
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        for (int y = 0; y < BaseConst::kTutorialStageSizeHeight; y++) {
            for (int x = 0; x < BaseConst::kTutorialStageSizeWidth; x++) {
                if (tutorialMap[y][x].type == kTypeAir) {
                    continue;
                }

                // もし画面外の場合は描画しない
                Point drawPosition = { (float)x * BaseConst::kMapChipSizeWidth, (float)(BaseConst::kTutorialStageSizeHeight - y) * BaseConst::kMapChipSizeHeight };
                drawPosition = BaseDraw::WorldtoScreen(drawPosition);

                if (drawPosition.y > 0 - BaseConst::kMapChipSizeHeight) {
                    if (drawPosition.y < BaseConst::kWindowHeight + BaseConst::kMapChipSizeHeight) {
                        if (drawPosition.x > 0 - BaseConst::kMapChipSizeWidth) {
                            if (drawPosition.x < BaseConst::kWindowWidth + BaseConst::kMapChipSizeWidth) {
                                //if (tutorialMap[y][x].type == kTypeSummonEnemy) {
                                //    tutorialMap[y][x].type = kTypeAir;
                                //}
                                //else {
                                tutorialMap[y][x].Draw(BaseDraw::ScreentoWorld(drawPosition), GetMapChipType(y, x));
                                //}
                            }
                        }
                    }
                }
            }
        }
        //int startY = BaseConst::kTutorialStageSizeHeight - (BaseDraw::GetScreenPosition().y / BaseConst::kMapChipSizeHeight);
        //int startX = BaseDraw::GetScreenPosition().x / BaseConst::kMapChipSizeWidth;

        //for (int y = startY; y < BaseConst::kTutorialStageSizeHeight && y < startY + (BaseConst::kWindowHeight / BaseConst::kMapChipSizeHeight) + 3; y++) {
        //    for (int x = startX; x < BaseConst::kTutorialStageSizeWidth && x < startX + BaseConst::kWindowWidth / BaseConst::kMapChipSizeWidth; x++) {
        //        // もし画面外の場合は描画しない
        //        Point drawPosition = { (float)x * BaseConst::kMapChipSizeWidth, (float)(BaseConst::kTutorialStageSizeHeight - y) * BaseConst::kMapChipSizeHeight };
        //        drawPosition = BaseDraw::WorldtoScreen(drawPosition);

        //        if (drawPosition.y > 0 - BaseConst::kMapChipSizeHeight) {
        //            if (drawPosition.y < BaseConst::kWindowHeight + BaseConst::kMapChipSizeHeight) {
        //                if (drawPosition.x > 0 - BaseConst::kMapChipSizeWidth) {
        //                    if (drawPosition.x < BaseConst::kWindowWidth + BaseConst::kMapChipSizeWidth) {
        //                        tutorialMap[y][x].Draw(BaseDraw::ScreentoWorld(drawPosition), GetMapChipType(y, x));
        //                    }
        //                }
        //            }
        //        }
        //    }
        //}
    }
}


/// <summary>
/// 指定した座標がマップにヒットしているかどうか
/// </summary>
/// <param name="hitPosition 当たり判定を確認するワールド座標"></param>
/// <param name="isBlock ヒットするのがBlockかどうか"></param>
/// <returns>ヒットしていた場合 ... true、ヒットしていなかった場合 ... false</returns>
bool MapManager::CheckHitBox(Point hitPosition, bool isBlock) {
    if (isBoss) {
        int y = BaseConst::kBossStageSizeHeight - (hitPosition.y / BaseConst::kMapChipSizeHeight);
        int x = hitPosition.x / BaseConst::kMapChipSizeWidth;

        if (y < 0 || y >= BaseConst::kBossStageSizeHeight) {
            return false;
        }
        if (x < 0 || x >= BaseConst::kBossStageSizeWidth) {
            return false;
        }

        hitPosition.x -= x * BaseConst::kMapChipSizeWidth;
        hitPosition.y -= (BaseConst::kBossStageSizeHeight - y - 1) * BaseConst::kMapChipSizeHeight;

        return bossMap[y][x].CheckHitBox(hitPosition, isBlock);
    }
    else {
        int y = BaseConst::kTutorialStageSizeHeight - (hitPosition.y / BaseConst::kMapChipSizeHeight);
        int x = hitPosition.x / BaseConst::kMapChipSizeWidth;

        if (y < 0 || y >= BaseConst::kTutorialStageSizeHeight) {
            return false;
        }
        if (x < 0 || x >= BaseConst::kTutorialStageSizeWidth) {
            return false;
        }

        hitPosition.x -= x * BaseConst::kMapChipSizeWidth;
        hitPosition.y -= (BaseConst::kTutorialStageSizeHeight - y - 1) * BaseConst::kMapChipSizeHeight;

        return tutorialMap[y][x].CheckHitBox(hitPosition, isBlock);
    }
}


// マップチップの形を決定する関数
 int MapManager::GetMapChipType(int y, int x) {

    // 上下左右が同じチップかを記録する変数
    bool up, down, left, right;

    if (isBoss) {
        // 場外じゃないかチェック
        if (y - 1 < 0) {
            // 場外ならば上はあると仮定する
            up = true;
        }
        // 上が同じチップかを確認
        else {
            if (bossMap[y][x].type == bossMap[y - 1][x].type) {
                up = true;
            }
            else {
                up = false;
            }
        }

        // 場外じゃないかチェック
        if (y + 1 >= BaseConst::kBossStageSizeHeight) {
            // 場外ならば下はあると仮定する
            down = true;
        }
        // 下が同じチップかを確認
        else {
            if (bossMap[y][x].type == bossMap[y + 1][x].type ||
                (bossMap[y][x].type == kTypeNormal && bossMap[y + 1][x].type == kTypeWall) ||
                (bossMap[y][x].type == kTypeWall && bossMap[y + 1][x].type == kTypeNormal)) {
                down = true;
            }
            else {
                down = false;
            }
        }

        // 場外じゃないかチェック
        if (x - 1 < 0) {
            // 場外ならば左はあると仮定する
            left = true;
        }
        // 左が同じチップかを確認
        else {
            if (bossMap[y][x].type == bossMap[y][x - 1].type ||
                (bossMap[y][x].type == kTypeNormal && bossMap[y][x - 1].type == kTypeWall) ||
                (bossMap[y][x].type == kTypeWall && bossMap[y][x - 1].type == kTypeNormal)) {
                left = true;
            }
            else {
                left = false;
            }
        }

        // 場外じゃないかチェック
        if (x + 1 >= BaseConst::kBossStageSizeWidth) {
            // 場外ならば右はあると仮定する
            right = true;
        }
        // 右が同じチップかを確認
        else {
            if (bossMap[y][x].type == bossMap[y][x + 1].type ||
                (bossMap[y][x].type == kTypeNormal && bossMap[y][x + 1].type == kTypeWall) ||
                (bossMap[y][x].type == kTypeWall && bossMap[y][x + 1].type == kTypeNormal)) {
                right = true;
            }
            else {
                right = false;
            }
        }
    }
    // ここより下はチュートリアル
    else {
        // 場外じゃないかチェック
        if (y - 1 < 0) {
            // 場外ならば上はあると仮定する
            up = true;
        }
        // 上が同じチップかを確認
        else {
            if (tutorialMap[y][x].type == tutorialMap[y - 1][x].type) {
                up = true;
            }
            else if ((tutorialMap[y][x].type == kTypeNormal || tutorialMap[y][x].type == kTypeWall || tutorialMap[y][x].type == kTypeWeak) &&
                     (tutorialMap[y - 1][x].type == kTypeNormal || tutorialMap[y - 1][x].type == kTypeWall || tutorialMap[y - 1][x].type == kTypeWeak)) {
                up = true;
            }
            else {
                up = false;
            }
        }

        // 場外じゃないかチェック
        if (y + 1 >= BaseConst::kTutorialStageSizeHeight) {
            // 場外ならば下はあると仮定する
            down = true;
        }
        // 下が同じチップかを確認
        else {
            if (tutorialMap[y][x].type == tutorialMap[y + 1][x].type) {
                down = true;
            }
            else if ((tutorialMap[y][x].type == kTypeNormal || tutorialMap[y][x].type == kTypeWall || tutorialMap[y][x].type == kTypeWeak) &&
                     (tutorialMap[y + 1][x].type == kTypeNormal || tutorialMap[y + 1][x].type == kTypeWall || tutorialMap[y + 1][x].type == kTypeWeak)) {
                down = true;
            }
            else {
                down = false;
            }
        }

        // 場外じゃないかチェック
        if (x - 1 < 0) {
            // 場外ならば左はあると仮定する
            left = true;
        }
        // 左が同じチップかを確認
        else {
            if (tutorialMap[y][x].type == tutorialMap[y][x - 1].type) {
                left = true;
            }
            else if ((tutorialMap[y][x].type == kTypeNormal || tutorialMap[y][x].type == kTypeWall || tutorialMap[y][x].type == kTypeWeak) &&
                     (tutorialMap[y][x - 1].type == kTypeNormal || tutorialMap[y][x - 1].type == kTypeWall || tutorialMap[y][x - 1].type == kTypeWeak)) {
                left = true;
            }
            else {
                left = false;
            }
        }

        // 場外じゃないかチェック
        if (x + 1 >= BaseConst::kTutorialStageSizeWidth) {
            // 場外ならば右はあると仮定する
            right = true;
        }
        // 右が同じチップかを確認
        else {
            if (tutorialMap[y][x].type == tutorialMap[y][x + 1].type) {
                right = true;
            }
            else if ((tutorialMap[y][x].type == kTypeNormal || tutorialMap[y][x].type == kTypeWall || tutorialMap[y][x].type == kTypeWeak) &&
                     (tutorialMap[y][x + 1].type == kTypeNormal || tutorialMap[y][x + 1].type == kTypeWall || tutorialMap[y][x + 1].type == kTypeWeak)) {
                right = true;
            }
            else {
                right = false;
            }
        }
    }


    // 各種方向のパターン検証

    // 全方向ある
    if (up && down && left && right) {
        return 0;
    }

    // 上のみ無い
    else if (!up && down && left && right) {
        return 1;
    }
    // 右のみ無い
    else if (up && down && left && !right) {
        return 2;
    }
    // 下のみ無い
    else if (up && !down && left && right) {
        return 3;
    }
    // 左のみ無い
    else if (up && down && !left && right) {
        return 4;
    }

    // 上と右のみ無い
    else if (!up && down && left && !right) {
        return 5;
    }
    // 右と下のみ無い
    else if (up && !down && left && !right) {
        return 6;
    }
    // 下と左のみ無い
    else if (up && !down && !left && right) {
        return 7;
    }
    // 左と上のみ無い
    else if (!up && down && !left && right) {
        return 8;
    }

    // 下のみ有る
    else if (!up && down && !left && right) {
        return 9;
    }
    // 左のみ有る
    else if (!up && !down && left && !right) {
        return 10;
    }
    // 上のみ有る
    else if (up && !down && !left && !right) {
        return 11;
    }
    // 右のみ有る
    else if (!up && !down && !left && right) {
        return 12;
    }

    // 全方向ない
    else {
        return 13;
    }
}


// 現在ボスマップの処理を行っているのかフラグ
bool MapManager::isBoss;

// チュートリアルマップの配列
Map MapManager::tutorialMap[BaseConst::kTutorialStageSizeHeight][BaseConst::kTutorialStageSizeWidth];
// マップの配列
Map MapManager::bossMap[BaseConst::kBossStageSizeHeight][BaseConst::kBossStageSizeWidth];