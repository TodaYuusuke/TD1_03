#include "Class/Include/Map/MapManager.h"

// コンストラクタ
MapManager::MapManager() {

}
// デストラクタ
MapManager::~MapManager() {

}


// 初期化
void MapManager::Initialize() {
	for (int y = 0; y < BaseConst::kMapSizeHeight; y++) {
		for (int x = 0; x < BaseConst::kMapSizeWidth; x++) {
            map[y][x].Initialize((MapChipType)BaseConst::kMapData[y][x]);
		}
	}
}
// 更新
void MapManager::Update() {
	for (int y = 0; y < BaseConst::kMapSizeHeight; y++) {
		for (int x = 0; x < BaseConst::kMapSizeWidth; x++) {
			map[y][x].Update();
		}
	}
}
// 描画
void MapManager::Draw() {
	for (int y = 0; y < BaseConst::kMapSizeHeight; y++) {
		for (int x = 0; x < BaseConst::kMapSizeWidth; x++) {
            // もし画面外の場合は描画しない
            Point drawPosition = { (float)x * BaseConst::kMapChipSizeWidth, (float)(BaseConst::kMapSizeHeight - y) * BaseConst::kMapChipSizeHeight};
            drawPosition = BaseDraw::WorldtoScreen(drawPosition);

            if (drawPosition.y > 0 - BaseConst::kMapChipSizeHeight) {
                if (drawPosition.y < BaseConst::kWindowHeight + BaseConst::kMapChipSizeHeight) {
                    if (drawPosition.x > 0 - BaseConst::kMapChipSizeWidth) {
                        if (drawPosition.x < BaseConst::kWindowWidth + BaseConst::kMapChipSizeWidth) {
                            map[y][x].Draw(BaseDraw::ScreentoWorld(drawPosition), GetMapChipType(y, x));
                        }
                    }
                }
            }
		}
	}
}

/// <summary>
/// 指定した座標がマップにヒットしているかどうか
/// </summary>
/// <param name="hitPosition 当たり判定を確認するワールド座標"></param>
/// <returns>ヒットしていた場合 ... true、ヒットしていなかった場合 ... false</returns>
bool MapManager::CheckHitBox(Point hitPosition) {

    int y = BaseConst::kMapSizeHeight - (hitPosition.y / BaseConst::kMapChipSizeHeight);
    int x = hitPosition.x / BaseConst::kMapChipSizeWidth;

    return map[y][x].CheckHitBox(hitPosition);
}



// マップチップの形を決定する関数
int MapManager::GetMapChipType(int y, int x) {

    // 上下左右が同じチップかを記録する変数
    bool up, down, left, right;

    // 場外じゃないかチェック
    if (y - 1 < 0) {
        // 場外ならば上はあると仮定する
        up = true;
    }
    // 上が同じチップかを確認
    else {
        if (map[y][x].type == map[y - 1][x].type) {
            up = true;
        }
        else {
            up = false;
        }
    }

    // 場外じゃないかチェック
    if (y + 1 >= BaseConst::kMapSizeHeight) {
        // 場外ならば下はあると仮定する
        down = true;
    }
    // 下が同じチップかを確認
    else {
        if (map[y][x].type == map[y + 1][x].type) {
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
        if (map[y][x].type == map[y][x - 1].type) {
            left = true;
        }
        else {
            left = false;
        }
    }

    // 場外じゃないかチェック
    if (x + 1 >= BaseConst::kMapSizeWidth) {
        // 場外ならば右はあると仮定する
        right = true;
    }
    // 右が同じチップかを確認
    else {
        if (map[y][x].type == map[y][x + 1].type) {
            right = true;
        }
        else {
            right = false;
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




// マップの配列
Map MapManager::map[BaseConst::kMapSizeHeight][BaseConst::kMapSizeWidth];