#include "SoundManager.h"
#include "DxLib.h"


SoundManager::SoundManager() {
	
	SESound = LoadSoundMem("Sound\\button01a.mp3");
	failedBgm = LoadSoundMem("Sound\\gameover.mp3");
	TitleBgm = 0;
	BgmSound = 0;
	nowBgm = "";
}

void SoundManager::PlaySoundBgm(int stageNumber) {
	if(stageNumber == 1)
		BgmSound = LoadSoundMem("Sound\\8bit-act04_stage01.mp3");
	else if(stageNumber == 2)
	BgmSound = LoadSoundMem("Sound\\8bit-act06_stage03.mp3");
	else if (stageNumber == 3)
	BgmSound = LoadSoundMem("Sound\\8bit-Dungeon02.mp3");
	else if(stageNumber == 4)
		BgmSound = LoadSoundMem("Sound\\8bit-Epilogue01.mp3");
	ChangeVolumeSoundMem(128, BgmSound);
	PlaySoundMem(BgmSound, DX_PLAYTYPE_LOOP);
}

void SoundManager::StopSoundBgm() {
	StopSoundMem(BgmSound);
}
void SoundManager::PlayFailedSoundBgm() {
	PlaySoundMem(failedBgm, DX_PLAYTYPE_BACK);
}

void SoundManager::StopFailedSoundBgm() {
	StopSoundMem(failedBgm);
}

void SoundManager::PlayTitleSound() {
	TitleBgm = LoadSoundMem("Sound\\8bit-Prologue01.mp3");
	ChangeVolumeSoundMem(128, TitleBgm);
	PlaySoundMem(TitleBgm, DX_PLAYTYPE_BACK);
}

void SoundManager::StopTitleSound() {
	StopSoundMem(TitleBgm);
}

void SoundManager::PlaySoundEffect(int fileNumber) {
	PlaySoundMem(SESound, DX_PLAYTYPE_BACK);
}

void SoundManager::StopSoundEffect() {
	int soundHandle = LoadSoundMem(nowBgm.c_str());
	StopSoundMem(soundHandle);
}

