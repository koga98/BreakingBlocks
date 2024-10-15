#pragma once
#include <string>
#include "vector"
class UIManager {
public:
	UIManager();
	void RenderGameOverUI();
	void RenderGameClearUI();
	void RenderElapsedTime(int currentTime);
	void RenderStageNumber(const std::string& stage);
	void RenderUpdate(int totalScore, int nowStage, const std::string& timeText);
	void RenderFirstScene(int cursorPositionY);
	void RenderOperateWay();
	void RenderUseMaterials();
	void RenderBestScore(std::vector<int> scores);
	int fontHandle;
	int fontTitle;
	int fontHeadword;
};