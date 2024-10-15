#include "ScoreManager.h"

ScoreManager::ScoreManager() {
	totalScore = 0;
	bonusScore = 0;
	AfterClearScore = 0;
	StageFailedPenalty = 1; 
}

void ScoreManager::CalculateScore() {
	totalScore += 1 + bonusScore;
	bonusScore++;
}

void ScoreManager::CalculateFailedScore() {
	totalScore = AfterClearScore;
	totalScore -= StageFailedPenalty;
	AfterClearScore = totalScore;
	StageFailedPenalty++;
}

void ScoreManager::ResetScore() {
	bonusScore = 0;
}

void ScoreManager::SaveClearScore() {
	AfterClearScore = totalScore;
}