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
	int BgmSound;
	int failedBgm;
	int TitleBgm;
	void PlaySoundBgm(int stageNumber);
	void StopSoundBgm();
	void PlayFailedSoundBgm();
	void PlayTitleSound();
	void StopTitleSound();
	void StopFailedSoundBgm();
	void PlaySoundEffect(int fileNumber);
	void StopSoundEffect();
};