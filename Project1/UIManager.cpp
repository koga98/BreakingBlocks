#include "DxLib.h"
#include "UIManager.h"
#include "ProjConf.h"

// カーソル位置とボタンのサイズ
int cursorX = 1080;
int cursorY = 640;
int width = 150;
int height = 50;

int X = 900;
int Y = 640;

// フォントの初期化
UIManager::UIManager() {
	fontHandle = CreateFontToHandle(NULL, 50, -1, DX_FONTTYPE_ANTIALIASING);
	fontHeadword = CreateFontToHandle(NULL, 65, -1, DX_FONTTYPE_ANTIALIASING);
	fontTitle = CreateFontToHandle(NULL, 30, -1, DX_FONTTYPE_ANTIALIASING);
}

// ゲームオーバー画面の描画
void UIManager::RenderGameOverUI() {
	DrawStringToHandle(300, 250, "GAME OVER", GetColor(255, 0, 0), fontHandle);
	DrawStringToHandle(300, 300, "SPACEで今のステージをリトライ", GetColor(255, 255, 0), fontHandle);
}

// ゲームクリア画面の描画
void UIManager::RenderGameClearUI() {
	DrawStringToHandle(300, 250, "GAME Clear", GetColor(255, 0, 0), fontHandle);
	DrawStringToHandle(300, 300, "SPACEで次のステージへ", GetColor(255, 255, 0), fontHandle);
}

// 経過時間の描画
void UIManager::RenderElapsedTime(int currentTime) {
	int font = CreateFontToHandle(NULL, 15, -1, DX_FONTTYPE_ANTIALIASING);
	std::string timeText = "Play Time: " + std::to_string(currentTime / 1000) + "s";
	DrawStringToHandle(1100, 700, timeText.c_str(), GetColor(255, 255, 255), font);
}

// ステージ番号の描画
void UIManager::RenderStageNumber(const std::string& stage) {
	DrawStringToHandle(600, 300, stage.c_str(), GetColor(255, 255, 255), fontHandle);
}

// スコア、ステージ、時間の更新表示
void UIManager::RenderUpdate(int totalScore, int nowStage, const std::string& timeText) {
	DrawFormatString(600, 700, GetColor(255, 255, 255), "合計スコア: %d", totalScore);
	DrawFormatString(900, 700, GetColor(255, 255, 255), "Stage: %d", nowStage);
	DrawFormatString(1100, 700, GetColor(255, 255, 255), timeText.c_str());
}

// 最初のシーン描画
void UIManager::RenderFirstScene(int cursorPositionY) {
	DrawStringToHandle(450, 100, GAME_TITLE, GetColor(255, 255, 255), fontHeadword);
	DrawStringToHandle(550, 230,"ゲームスタート", GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 330, GAME_OPERATE_WAY, GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 430, "ベストスコア", GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 530, "閉じる", GetColor(255, 255, 255), fontTitle);

	// カーソルとボタン描画
	DrawBox(cursorX, cursorY, cursorX + width, cursorY + height, GetColor(255, 255, 255), FALSE);
	DrawString(cursorX + 20, cursorY + 15, "Enterで選択", GetColor(255, 255, 255));
	DrawBox(500, cursorPositionY, 515, cursorPositionY + 15, GetColor(255, 255, 255), TRUE);
}

// 使用素材の表示
void UIManager::RenderUseMaterials() {
	DrawString(700, 500, "使用素材", GetColor(255, 255, 255));
	DrawString(700, 520, "ユーフルカ様: https://youfulca.com/music_assets/", GetColor(255, 255, 255));
	DrawString(700, 540, "ポケットサウンド様: https://pocket-se.info/", GetColor(255, 255, 255));

	DrawBox(X, Y, X + width, Y + height, GetColor(255, 255, 255), FALSE);
	DrawString(X + 20, Y + 15, "Enterで終了", GetColor(255, 255, 255));

	DrawBox(cursorX, cursorY, cursorX + width, cursorY + height, GetColor(255, 255, 255), FALSE);
	DrawString(cursorX + 20, cursorY + 15, "SpaceでTitleへ", GetColor(255, 255, 255));
}

// 操作方法の表示
void UIManager::RenderOperateWay() {
	SetDrawBright(255, 255, 255);
	DrawString(540, 50, "操作方法", GetColor(255, 255, 255));
	DrawString(400, 100, "A, Dキーでバーを左右に移動", GetColor(255, 255, 255));
	DrawString(400, 150, "ボールがバー中央で反射すると直進", GetColor(255, 255, 255));
	DrawString(400, 200, "右側で反射すると右に、左側なら左に", GetColor(255, 255, 255));
	DrawString(400, 300, "ゲームを中断する場合はエスケープボタンを押下", GetColor(255, 255, 255));

	DrawString(540, 400, "ルール", GetColor(255, 255, 255));
	DrawString(400, 450, "ブロックを壊すごとにスコア +1", GetColor(255, 255, 255));
	DrawString(400, 500, "バーに当たらなければスコア加算量も増加", GetColor(255, 255, 255));
	DrawString(400, 550, "ボールが画面下に触れるとゲームオーバー", GetColor(255, 255, 255));
	DrawString(400, 600, "スペースでリトライ/次のステージへ", GetColor(255, 255, 255));
	DrawString(400, 650, "全3ステージ", GetColor(255, 255, 255));

	// カーソルとボタン描画
	DrawBox(cursorX, cursorY, cursorX + width, cursorY + height, GetColor(255, 255, 255), FALSE);
	DrawString(cursorX + 20, cursorY + 15, "Spaceで閉じる", GetColor(255, 255, 255));
} 

void UIManager::RenderBestScore(std::vector<int> scores) {
	DrawStringToHandle(450, 100, "ベストスコア", GetColor(255, 255, 255), fontHeadword);
	DrawStringToHandle(550, 230, ("1." + std::to_string(scores.size() > 0 ? scores[0] : 0)).c_str(), GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 330, ("2." + (scores.size() > 1 ? std::to_string(scores[1]) : "")).c_str(), GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 430, ("3." + (scores.size() > 2 ? std::to_string(scores[2]) : "")).c_str(), GetColor(255, 255, 255), fontTitle);

	// カーソルとボタン描画
	DrawBox(cursorX, cursorY, cursorX + width, cursorY + height, GetColor(255, 255, 255), FALSE);
	DrawString(cursorX + 20, cursorY + 15, "Spaceで閉じる", GetColor(255, 255, 255));
}