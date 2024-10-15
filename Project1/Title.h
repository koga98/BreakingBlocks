#pragma once
#include "GameManager.h"
#include "UIManager.h"
#include "SoundManager.h"
#include "DataSave.h"
#include "vector"

class Title {
public:
	Title();
	void Run();
	std::vector<int> cursorPositionY;
	bool endGame;
private:
	UIManager titleUI;
	SoundManager sound;
	DataSave titleDataSave;
	bool endTitleScene;
	bool isPicking;
	bool Looking;
	int cursorIndex;
	void ChangeCursorIndex(int index);
	void PickingMenu();
	void ShowOperateWay();
	void ShowBestScore();
};