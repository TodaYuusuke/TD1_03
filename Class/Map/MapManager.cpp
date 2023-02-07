#include "Class/Map/MapManager.h"

// �R���X�g���N�^
MapManager::MapManager() {

}
// �f�X�g���N�^
MapManager::~MapManager() {

}


// ������
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
// �X�V
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
// �`��
void MapManager::Draw() {
    if (isBoss) {
        for (int y = 0; y < BaseConst::kBossStageSizeHeight; y++) {
            for (int x = 0; x < BaseConst::kBossStageSizeWidth; x++) {
                if (bossMap[y][x].type == kTypeAir) {
                    continue;
                }

                // ������ʊO�̏ꍇ�͕`�悵�Ȃ�
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

                // ������ʊO�̏ꍇ�͕`�悵�Ȃ�
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
        //        // ������ʊO�̏ꍇ�͕`�悵�Ȃ�
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
/// �w�肵�����W���}�b�v�Ƀq�b�g���Ă��邩�ǂ���
/// </summary>
/// <param name="hitPosition �����蔻����m�F���郏�[���h���W"></param>
/// <param name="isBlock �q�b�g����̂�Block���ǂ���"></param>
/// <returns>�q�b�g���Ă����ꍇ ... true�A�q�b�g���Ă��Ȃ������ꍇ ... false</returns>
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


// �}�b�v�`�b�v�̌`�����肷��֐�
 int MapManager::GetMapChipType(int y, int x) {

    // �㉺���E�������`�b�v�����L�^����ϐ�
    bool up, down, left, right;

    if (isBoss) {
        // ��O����Ȃ����`�F�b�N
        if (y - 1 < 0) {
            // ��O�Ȃ�Ώ�͂���Ɖ��肷��
            up = true;
        }
        // �オ�����`�b�v�����m�F
        else {
            if (bossMap[y][x].type == bossMap[y - 1][x].type) {
                up = true;
            }
            else {
                up = false;
            }
        }

        // ��O����Ȃ����`�F�b�N
        if (y + 1 >= BaseConst::kBossStageSizeHeight) {
            // ��O�Ȃ�Ή��͂���Ɖ��肷��
            down = true;
        }
        // ���������`�b�v�����m�F
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

        // ��O����Ȃ����`�F�b�N
        if (x - 1 < 0) {
            // ��O�Ȃ�΍��͂���Ɖ��肷��
            left = true;
        }
        // ���������`�b�v�����m�F
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

        // ��O����Ȃ����`�F�b�N
        if (x + 1 >= BaseConst::kBossStageSizeWidth) {
            // ��O�Ȃ�ΉE�͂���Ɖ��肷��
            right = true;
        }
        // �E�������`�b�v�����m�F
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
    // ������艺�̓`���[�g���A��
    else {
        // ��O����Ȃ����`�F�b�N
        if (y - 1 < 0) {
            // ��O�Ȃ�Ώ�͂���Ɖ��肷��
            up = true;
        }
        // �オ�����`�b�v�����m�F
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

        // ��O����Ȃ����`�F�b�N
        if (y + 1 >= BaseConst::kTutorialStageSizeHeight) {
            // ��O�Ȃ�Ή��͂���Ɖ��肷��
            down = true;
        }
        // ���������`�b�v�����m�F
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

        // ��O����Ȃ����`�F�b�N
        if (x - 1 < 0) {
            // ��O�Ȃ�΍��͂���Ɖ��肷��
            left = true;
        }
        // ���������`�b�v�����m�F
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

        // ��O����Ȃ����`�F�b�N
        if (x + 1 >= BaseConst::kTutorialStageSizeWidth) {
            // ��O�Ȃ�ΉE�͂���Ɖ��肷��
            right = true;
        }
        // �E�������`�b�v�����m�F
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


    // �e������̃p�^�[������

    // �S��������
    if (up && down && left && right) {
        return 0;
    }

    // ��̂ݖ���
    else if (!up && down && left && right) {
        return 1;
    }
    // �E�̂ݖ���
    else if (up && down && left && !right) {
        return 2;
    }
    // ���̂ݖ���
    else if (up && !down && left && right) {
        return 3;
    }
    // ���̂ݖ���
    else if (up && down && !left && right) {
        return 4;
    }

    // ��ƉE�̂ݖ���
    else if (!up && down && left && !right) {
        return 5;
    }
    // �E�Ɖ��̂ݖ���
    else if (up && !down && left && !right) {
        return 6;
    }
    // ���ƍ��̂ݖ���
    else if (up && !down && !left && right) {
        return 7;
    }
    // ���Ə�̂ݖ���
    else if (!up && down && !left && right) {
        return 8;
    }

    // ���̂ݗL��
    else if (!up && down && !left && right) {
        return 9;
    }
    // ���̂ݗL��
    else if (!up && !down && left && !right) {
        return 10;
    }
    // ��̂ݗL��
    else if (up && !down && !left && !right) {
        return 11;
    }
    // �E�̂ݗL��
    else if (!up && !down && !left && right) {
        return 12;
    }

    // �S�����Ȃ�
    else {
        return 13;
    }
}


// ���݃{�X�}�b�v�̏������s���Ă���̂��t���O
bool MapManager::isBoss;

// �`���[�g���A���}�b�v�̔z��
Map MapManager::tutorialMap[BaseConst::kTutorialStageSizeHeight][BaseConst::kTutorialStageSizeWidth];
// �}�b�v�̔z��
Map MapManager::bossMap[BaseConst::kBossStageSizeHeight][BaseConst::kBossStageSizeWidth];