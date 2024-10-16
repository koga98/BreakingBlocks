#include "SoundManager.h"
#include "DxLib.h"


SoundManager::SoundManager() {
	
	SESound = LoadSoundMem("Sound\\button01a.mp3");
	failedBgm = LoadSoundMem("Sound\\gameover.mp3");
	TitleBgm = 0;
	BgmSound1 = 0;
	BgmSound2 = 0;
	BgmSound3 = 0;
	BgmSound4 = 0;
	nowBgm = "";
}

void SoundManager::PlaySoundBgm(int stageNumber) {
	if (stageNumber == 1) {
		if (BgmSound1 == 0) {
			BgmSound1 = LoadSoundMem("Sound\\8bit-act04_stage01.mp3");
			ChangeVolumeSoundMem(128, BgmSound1);
		}
		PlaySoundMem(BgmSound1, DX_PLAYTYPE_LOOP);
	}	
	else if (stageNumber == 2) {
		if (BgmSound2 == 0) {
			BgmSound2 = LoadSoundMem("Sound\\8bit-act06_stage03.mp3");
			ChangeVolumeSoundMem(128, BgmSound2);
		}
		PlaySoundMem(BgmSound2, DX_PLAYTYPE_LOOP);
	}
	else if (stageNumber == 3 && BgmSound3 == 0) {
		if (BgmSound3 == 0) {
			BgmSound3 = LoadSoundMem("Sound\\8bit-Dungeon02.mp3");
			ChangeVolumeSoundMem(128, BgmSound3);
		}
		PlaySoundMem(BgmSound3, DX_PLAYTYPE_LOOP);
	}
	else if (stageNumber == 4 && BgmSound4 == 0) {
		if (BgmSound4 == 0) {
			BgmSound4 = LoadSoundMem("Sound\\8bit-Epilogue01.mp3");
			ChangeVolumeSoundMem(128, BgmSound4);
		}
		PlaySoundMem(BgmSound4, DX_PLAYTYPE_LOOP);
	}
}

void SoundManager::StopSoundBgm(int stageNumber) {
	if (stageNumber == 1) {
		StopSoundMem(BgmSound1);
	}
	else if (stageNumber == 2) {
		StopSoundMem(BgmSound2);
	}
	else if (stageNumber == 3) {
		StopSoundMem(BgmSound3);
	}
	else if (stageNumber == 4) {
		StopSoundMem(BgmSound4);
	}
	
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

