#include "Title.h"
#include "DxLib.h"

// �O���[�o���ϐ��Ƃ��đO��̓��͎��Ԃ�ێ�
int previousTime = 0;

Title::Title() {
    isPicking = true;
    Looking = false;
    int startPosition = 238;

    // �J�[�\����Y���W�ʒu��ݒ�
    cursorPositionY.push_back(startPosition);
    cursorPositionY.push_back(startPosition + 100);
    cursorPositionY.push_back(startPosition + 200);
    cursorPositionY.push_back(startPosition + 300);

    cursorIndex = 0;
    endGame = false;
    endTitleScene = false;
}

void Title::Run() {
    endTitleScene = false;
    sound.PlayTitleSound();  
    while (!endTitleScene ) {
        PickingMenu();  // ���j���[�I�������s
        if (endGame) {  // �Q�[�����I������ꍇ�̓��[�v�𔲂���
            break;
        }
    }
}

void Title::PickingMenu() {
    isPicking = true;

    while (isPicking && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ClearDrawScreen();
        int currentTime = GetNowCount();

        // �J�[�\���ʒu�𔽉f���ă^�C�g����ʂ�`��
        titleUI.RenderFirstScene(cursorPositionY[cursorIndex]);

        // W�L�[�ŃJ�[�\������Ɉړ�
        if (CheckHitKey(KEY_INPUT_W)) {
            if (currentTime - previousTime >= 200) {  // �O�񂩂�200�~���b�o��
                ChangeCursorIndex(-1);
                previousTime = currentTime;  // ���͎��Ԃ����Z�b�g
            }
        }
        // S�L�[�ŃJ�[�\�������Ɉړ�
        else if (CheckHitKey(KEY_INPUT_S)) {
            if (currentTime - previousTime >= 200) {  // �O�񂩂�200�~���b�o��
                ChangeCursorIndex(1);
                previousTime = currentTime;  // ���͎��Ԃ����Z�b�g
            }
        }
        // Enter�L�[�őI�����m��
        else if (CheckHitKey(KEY_INPUT_RETURN)) {
            isPicking = false;
            previousTime = currentTime;  // ���͎��Ԃ����Z�b�g
        }

        ScreenFlip();  // �`����e����ʂɔ��f
    }

    if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
        endGame = true;
        endTitleScene = true;
        return;
    }

    if (cursorIndex == 0) {
        sound.StopTitleSound();  
        endTitleScene = true;  
        return;
    }
    else if (cursorIndex == 1) {
        Looking = true;
        ShowOperateWay();  
    }
    else if (cursorIndex == 2) {
        Looking = true;
        ShowBestScore();
    }
    else if (cursorIndex == 3) {
        endGame = true;
        endTitleScene = true;
        return;
    }
}

void Title::ShowOperateWay() {
    while (Looking) {
        int currentTime = GetNowCount();
        ClearDrawScreen();

        titleUI.RenderOperateWay();  // ������@��`��
        ScreenFlip();

        // �X�y�[�X�L�[�ő�����@��ʂ����
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            if (currentTime - previousTime >= 200) {  // �O�񂩂�200�~���b�o��
                isPicking = false;
                previousTime = currentTime;  // ���͎��Ԃ����Z�b�g
            }
            Looking = false;  // ������@��ʂ����
        }
    }
    isPicking = true;  // ���j���[�I���ɖ߂�
}

void Title::ShowBestScore() {
    while (Looking) {
        ClearDrawScreen();

        titleUI.RenderBestScore(titleDataSave.LoadScore());  // ������@��`��
        ScreenFlip();

        // �X�y�[�X�L�[�őf�ޕ\�������
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            isPicking = false;
            Looking = false;
        }
    }
    isPicking = true;  // ���j���[�I���ɖ߂�
}

void Title::ChangeCursorIndex(int index) {
    cursorIndex += index;

    // �J�[�\���C���f�b�N�X�͈̔͂����[�v����
    if (cursorIndex < 0) {
        cursorIndex = static_cast<int>(cursorPositionY.size()) - 1;  // �ő�l�ɖ߂�
    }
    else if (cursorIndex >= static_cast<int>(cursorPositionY.size())) {
        cursorIndex = 0;  // �ŏ��l�ɖ߂�
    }
}