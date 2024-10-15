#include "DxLib.h"
#include <windows.h>
#include "ProjConf.h"
#include "GameManager.h"
#include "Title.h"


void GameRun(Title title, GameManager gamemanager);

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	/*** Window Init ***/
	SetWindowText("ブロック崩し");					// ウィンドウのタイトル
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);	// ウィンドウの位置
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);			// ウィンドウのサイズ
	SetBackgroundColor(0, 0, 0);				// ウィンドウの背景色
	SetDrawScreen(DX_SCREEN_BACK);					// 描画先画面を裏画面にする
	SetAlwaysRunFlag(TRUE);							// ウインドウ非アクティブ状態でも処理を続行する
	Title title;
	GameManager gamemanager;
	GameRun(title, gamemanager);
	
	
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

void GameRun(Title title, GameManager gamemanager) {
	title.Run();
	if (!title.endGame) {
		gamemanager.Run();
	}

	if (gamemanager.backTitle) {
		title = Title(); // 新しいインスタンスを作成して初期化
		gamemanager = GameManager(); // 同様に初期化
		GameRun(title, gamemanager);
	}
	else if (gamemanager.gameEnd)
		return;
}



