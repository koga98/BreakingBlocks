#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class SoundManager {
public:
	std::vector<std::string> bgmFileNames;
	std::vector<std::string> seFileNames;
	std::string nowBgm;
	std::unordered_map<int, int> bgmHandles;
	SoundManager();
	int SESound;
	int BgmSound1;
	int BgmSound2;
	int BgmSound3;
	int BgmSound4;
	int failedBgm;
	int TitleBgm;
	void PlaySoundBgm(int stageNumber);
	void StopSoundBgm(int stageNumber);
	void PlayFailedSoundBgm();
	void PlayTitleSound();
	void StopTitleSound();
	void StopFailedSoundBgm();
	void PlaySoundEffect(int fileNumber);
	void StopSoundEffect();
};