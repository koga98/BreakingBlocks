#pragma once
#include "Bar.h"
#include "Brocks.h"
#include "vector"
#include "Ball.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "ScoreManager.h"
#include "DataSave.h"
#include <string>

enum GameState {
	Playing,
	GameOver,
	GameClear
};

class GameManager {
public:
	GameManager();
	void Run();
	void InitializeGame(int stageIndex);
	bool backTitle;
	bool gameEnd;
private:
	// �����o�ϐ�
	Bar bar;
	int currentTime;
	int startTime;
	int nowStage;
	std::string Stage;

	std::vector<Ball> balls;
	std::vector<Brocks> brocks;

	UIManager uIManager;
	SoundManager soundManager;
	ScoreManager scoreManager;
	DataSave dataSave;
	GameState gameState;

	// �����o�֐�
	void StageCreate(int stageIndex);
	void RenderStage(const std::string& stageName);
	void HandleGameOver();
	void HandleGameClear();
	void CreateStageLayout();
	void CreateInvertedMShapedStage();
	void CreateMShapedStage();
	void HandleCongratulation();
	void RenderCongratulation();
	void Update();
	void Render();
	void CheckCollisions();
	bool RenderFinalScore();
};