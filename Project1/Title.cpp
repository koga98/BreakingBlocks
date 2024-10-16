#include "Title.h"
#include "DxLib.h"

// グローバル変数として前回の入力時間を保持
int previousTime = 0;

Title::Title() {
    isPicking = true;
    Looking = false;
    int startPosition = 238;

    // カーソルのY座標位置を設定
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
        PickingMenu();  // メニュー選択を実行
        if (endGame) {  // ゲームが終了する場合はループを抜ける
            break;
        }
    }
}

void Title::PickingMenu() {
    isPicking = true;

    while (isPicking && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        ClearDrawScreen();
        int currentTime = GetNowCount();

        // カーソル位置を反映してタイトル画面を描画
        titleUI.RenderFirstScene(cursorPositionY[cursorIndex]);

        // Wキーでカーソルを上に移動
        if (CheckHitKey(KEY_INPUT_W)) {
            if (currentTime - previousTime >= 200) {  // 前回から200ミリ秒経過
                ChangeCursorIndex(-1);
                previousTime = currentTime;  // 入力時間をリセット
            }
        }
        // Sキーでカーソルを下に移動
        else if (CheckHitKey(KEY_INPUT_S)) {
            if (currentTime - previousTime >= 200) {  // 前回から200ミリ秒経過
                ChangeCursorIndex(1);
                previousTime = currentTime;  // 入力時間をリセット
            }
        }
        // Enterキーで選択を確定
        else if (CheckHitKey(KEY_INPUT_RETURN)) {
            isPicking = false;
            previousTime = currentTime;  // 入力時間をリセット
        }

        ScreenFlip();  // 描画内容を画面に反映
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

        titleUI.RenderOperateWay();  // 操作方法を描画
        ScreenFlip();

        // スペースキーで操作方法画面を閉じる
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            if (currentTime - previousTime >= 200) {  // 前回から200ミリ秒経過
                isPicking = false;
                previousTime = currentTime;  // 入力時間をリセット
            }
            Looking = false;  // 操作方法画面を閉じる
        }
    }
    isPicking = true;  // メニュー選択に戻る
}

void Title::ShowBestScore() {
    while (Looking) {
        ClearDrawScreen();

        titleUI.RenderBestScore(titleDataSave.LoadScore());  // 操作方法を描画
        ScreenFlip();

        // スペースキーで素材表示を閉じる
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            isPicking = false;
            Looking = false;
        }
    }
    isPicking = true;  // メニュー選択に戻る
}

void Title::ChangeCursorIndex(int index) {
    cursorIndex += index;

    // カーソルインデックスの範囲をループする
    if (cursorIndex < 0) {
        cursorIndex = static_cast<int>(cursorPositionY.size()) - 1;  // 最大値に戻る
    }
    else if (cursorIndex >= static_cast<int>(cursorPositionY.size())) {
        cursorIndex = 0;  // 最小値に戻る
    }
}