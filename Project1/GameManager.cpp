#include "GameManager.h"
#include "DxLib.h"
#include <iostream>

GameManager::GameManager() {
    gameState = Playing;
    startTime = GetNowCount();
    nowStage = 1;
    currentTime = 0;
    gameEnd = false;
    backTitle = false;
    Stage = "Stage" + std::to_string(nowStage);
    
}

void GameManager::InitializeGame(int stageNumber) {
    gameState = Playing;
    nowStage = stageNumber;
    startTime = GetNowCount();
    scoreManager.bonusScore = 0;
    StageCreate(nowStage);

    // ステージ1の時はボールをリセット
    if (stageNumber == 1) {
        balls.clear();
        balls.push_back(Ball());
    }
    // ステージ3でボールが1つだけの時、追加
    else if (stageNumber == 3 && balls.size() == 1) {
        balls.push_back(Ball());
    }

    // 各ボールをリセット
    for (int i = 0; i < balls.size(); i++) {
        balls[i].Reset(i);
    }

    // バーをリセット
    bar.Reset(nowStage);
}

void GameManager::Run() {
    nowStage = 1;
    backTitle = false;
    gameEnd = false;
    
    auto start = GetNowCount();  // 計測開始
    InitializeGame(nowStage);
    auto end = GetNowCount();
    soundManager.PlaySoundBgm(nowStage);
    RenderStage(Stage);
    
    // メインループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !gameEnd && !backTitle) {
        if (gameState == Playing) {
            Update();
            CheckCollisions();
            Render();
        }
        else if (gameState == GameOver) {
            HandleGameOver();
        }
        else if (gameState == GameClear) {
            HandleGameClear();
        }
    }
}

void GameManager::Update() {
    currentTime = GetNowCount() - startTime;
        bar.Update();
        for (int i = 0; i < balls.size(); i++) {
            if (balls[i].CollisionToEdge()) {
                gameState = GameOver;
                soundManager.PlayFailedSoundBgm();
            }
            balls[i].Update();
        }
}

void GameManager::Render() {
    ClearDrawScreen();

    bar.Draw();

    for (Brocks& brock : brocks) {
        brock.Draw();
    }

    for (int i = 0; i < balls.size(); i++) {
        balls[i].Draw();
    }

    std::string timeText = "Play Time: " + std::to_string(currentTime / 1000) + "s";
    uIManager.RenderUpdate(scoreManager.totalScore, nowStage, timeText);

    ScreenFlip();
}

void GameManager::RenderStage(const std::string& stageName) {
    ClearDrawScreen();
    int nowTime = GetNowCount();
    int elapsedTime = 0;

    uIManager.RenderStageNumber(stageName);
    ScreenFlip();

    int waitTime = (stageName == "Congratulation!") ? 15 : 2;

    // ステージ表示の待機処理
    while (elapsedTime / 1000 < waitTime) {
        Sleep(1);
        elapsedTime = GetNowCount() - nowTime;

        if (elapsedTime / 1000 >= 5 && stageName == "Congratulation!") {
            if (RenderFinalScore())
                break;
        }
        
    }

    if (stageName == "Congratulation!") {
        HandleCongratulation();
    }
    ClearDrawScreen();
}

bool GameManager::RenderFinalScore(){
    ClearDrawScreen();
    std::string score = "あなたのスコアは: " + std::to_string(scoreManager.totalScore);
    uIManager.RenderStageNumber(score);
    uIManager.RenderUseMaterials();
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        backTitle = true;
        return true;
    }
    else if (CheckHitKey(KEY_INPUT_RETURN)) {
        gameEnd = true;
        return true;
    }
    ScreenFlip();
    return false;
}

void GameManager::StageCreate(int stageNumber) {
    brocks.clear();
    brocks.shrink_to_fit();  // メモリの解放を促す
    switch (stageNumber) {
    case 1:
        CreateStageLayout();
        break;
    case 2:
        CreateMShapedStage();
        break;
    case 3:
        CreateInvertedMShapedStage();
        break;
    default:
        break;
    }
}

void GameManager::CreateStageLayout() {
    for (float i = 0; i < 8; i++) {
        for (float j = 0; j < 4; j++) {
            brocks.push_back(Brocks(320 + 80 * i, 100 + 20 * j));
        }
    }
}

void GameManager::HandleCongratulation() {
    dataSave.SaveScore(scoreManager.totalScore);
    soundManager.StopSoundBgm(nowStage);
    if (!backTitle && !gameEnd)
        backTitle = true;
}

void GameManager::CheckCollisions() {
    for (int i = 0; i < balls.size(); i++) {
        if (balls[i].CheckCollision(bar.positionX, bar.positionY, bar.width, bar.height)) {
            scoreManager.ResetScore();
        }
    }

    for (Brocks& brock : brocks) {
        for (int i = 0; i < balls.size(); i++) {
            if (balls[i].CheckCollisionBrocks(brock.positionX, brock.positionY, 80, 20)) {
                brock.Destroy();
                scoreManager.CalculateScore();
            }
        }
    }

    // 衝突したブロックを削除
    brocks.erase(std::remove_if(brocks.begin(), brocks.end(), [](Brocks& brock) { return brock.isBumped; }), brocks.end());

    // 全てのブロックがなくなったらステージクリア
    if (brocks.empty()) {
        gameState = GameClear;
    }
}

void GameManager::HandleGameOver() {
    soundManager.StopSoundBgm(nowStage);
    uIManager.RenderGameOverUI();
    ScreenFlip();

    if (CheckHitKey(KEY_INPUT_SPACE)) {
        soundManager.StopFailedSoundBgm();
        soundManager.PlaySoundBgm(nowStage);
        Stage = "Stage" + std::to_string(nowStage);
        RenderStage(Stage);
        scoreManager.CalculateFailedScore();
        InitializeGame(nowStage);
    }
}

void GameManager::HandleGameClear() {
    if (nowStage + 1 < 4) {
        uIManager.RenderGameClearUI();
        ScreenFlip();
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            RenderCongratulation();
        }
        return;
    }
    
    RenderCongratulation();
}

void GameManager::RenderCongratulation() {
    Stage = "Stage" + std::to_string(nowStage + 1);
    scoreManager.SaveClearScore();
    soundManager.StopSoundBgm(nowStage);
    soundManager.PlaySoundBgm(nowStage + 1);

    if (Stage == "Stage4") {
        Stage = "Congratulation!";
    }
    RenderStage(Stage);
    InitializeGame(nowStage + 1);
}

void GameManager::CreateMShapedStage() {
    for (float i = 0; i < 8; i++) {
        for (float j = 0; j < 4; j++) {
            float x = 320 + 80 * i;
            float y = 100 + 40 * j;

            if (i == 0 || i == 7) {
                y += 80;
            }
            else if (i == 1 || i == 6) {
                y += 40;
            }
            brocks.push_back(Brocks(x, y));
        }
    }
}

void GameManager::CreateInvertedMShapedStage() {
    for (float i = 0; i < 8; i++) {
        for (float j = 0; j < 4; j++) {
            float x = 320 + 80 * i;
            float y = 100 + 40 * j;

            if (i == 3 || i == 4) {
                y += 80;
            }
            else if (i == 2 || i == 5) {
                y += 40;
            }
            brocks.push_back(Brocks(x, y));
        }
    }
}