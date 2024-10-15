#pragma once

class ScoreManager {
public:
	ScoreManager();
	int totalScore;
	int bonusScore;
	int StageFailedPenalty;
	int AfterClearScore;
	void CalculateScore();
	void ResetScore();
	void CalculateFailedScore();
	void SaveClearScore();
};