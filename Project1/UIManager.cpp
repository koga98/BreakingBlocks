#include "DxLib.h"
#include "UIManager.h"
#include "ProjConf.h"

// �J�[�\���ʒu�ƃ{�^���̃T�C�Y
int cursorX = 1080;
int cursorY = 640;
int width = 150;
int height = 50;

int X = 900;
int Y = 640;

// �t�H���g�̏�����
UIManager::UIManager() {
	fontHandle = CreateFontToHandle(NULL, 50, -1, DX_FONTTYPE_ANTIALIASING);
	fontHeadword = CreateFontToHandle(NULL, 65, -1, DX_FONTTYPE_ANTIALIASING);
	fontTitle = CreateFontToHandle(NULL, 30, -1, DX_FONTTYPE_ANTIALIASING);
}

// �Q�[���I�[�o�[��ʂ̕`��
void UIManager::RenderGameOverUI() {
	DrawStringToHandle(300, 250, "GAME OVER", GetColor(255, 0, 0), fontHandle);
	DrawStringToHandle(300, 300, "SPACE�ō��̃X�e�[�W�����g���C", GetColor(255, 255, 0), fontHandle);
}

// �Q�[���N���A��ʂ̕`��
void UIManager::RenderGameClearUI() {
	DrawStringToHandle(300, 250, "GAME Clear", GetColor(255, 0, 0), fontHandle);
	DrawStringToHandle(300, 300, "SPACE�Ŏ��̃X�e�[�W��", GetColor(255, 255, 0), fontHandle);
}

// �o�ߎ��Ԃ̕`��
void UIManager::RenderElapsedTime(int currentTime) {
	int font = CreateFontToHandle(NULL, 15, -1, DX_FONTTYPE_ANTIALIASING);
	std::string timeText = "Play Time: " + std::to_string(currentTime / 1000) + "s";
	DrawStringToHandle(1100, 700, timeText.c_str(), GetColor(255, 255, 255), font);
}

// �X�e�[�W�ԍ��̕`��
void UIManager::RenderStageNumber(const std::string& stage) {
	DrawStringToHandle(600, 300, stage.c_str(), GetColor(255, 255, 255), fontHandle);
}

// �X�R�A�A�X�e�[�W�A���Ԃ̍X�V�\��
void UIManager::RenderUpdate(int totalScore, int nowStage, const std::string& timeText) {
	DrawFormatString(600, 700, GetColor(255, 255, 255), "���v�X�R�A: %d", totalScore);
	DrawFormatString(900, 700, GetColor(255, 255, 255), "Stage: %d", nowStage);
	DrawFormatString(1100, 700, GetColor(255, 255, 255), timeText.c_str());
}

// �ŏ��̃V�[���`��
void UIManager::RenderFirstScene(int cursorPositionY) {
	DrawStringToHandle(450, 100, GAME_TITLE, GetColor(255, 255, 255), fontHeadword);
	DrawStringToHandle(550, 230,"�Q�[���X�^�[�g", GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 330, GAME_OPERATE_WAY, GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 430, "�x�X�g�X�R�A", GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 530, "����", GetColor(255, 255, 255), fontTitle);

	// �J�[�\���ƃ{�^���`��
	DrawBox(cursorX, cursorY, cursorX + width, cursorY + height, GetColor(255, 255, 255), FALSE);
	DrawString(cursorX + 20, cursorY + 15, "Enter�őI��", GetColor(255, 255, 255));
	DrawBox(500, cursorPositionY, 515, cursorPositionY + 15, GetColor(255, 255, 255), TRUE);
}

// �g�p�f�ނ̕\��
void UIManager::RenderUseMaterials() {
	DrawString(700, 500, "�g�p�f��", GetColor(255, 255, 255));
	DrawString(700, 520, "���[�t���J�l: https://youfulca.com/music_assets/", GetColor(255, 255, 255));
	DrawString(700, 540, "�|�P�b�g�T�E���h�l: https://pocket-se.info/", GetColor(255, 255, 255));

	DrawBox(X, Y, X + width, Y + height, GetColor(255, 255, 255), FALSE);
	DrawString(X + 20, Y + 15, "Enter�ŏI��", GetColor(255, 255, 255));

	DrawBox(cursorX, cursorY, cursorX + width, cursorY + height, GetColor(255, 255, 255), FALSE);
	DrawString(cursorX + 20, cursorY + 15, "Space��Title��", GetColor(255, 255, 255));
}

// ������@�̕\��
void UIManager::RenderOperateWay() {
	SetDrawBright(255, 255, 255);
	DrawString(540, 50, "������@", GetColor(255, 255, 255));
	DrawString(400, 100, "A, D�L�[�Ńo�[�����E�Ɉړ�", GetColor(255, 255, 255));
	DrawString(400, 150, "�{�[�����o�[�����Ŕ��˂���ƒ��i", GetColor(255, 255, 255));
	DrawString(400, 200, "�E���Ŕ��˂���ƉE�ɁA�����Ȃ獶��", GetColor(255, 255, 255));
	DrawString(400, 300, "�Q�[���𒆒f����ꍇ�̓G�X�P�[�v�{�^��������", GetColor(255, 255, 255));

	DrawString(540, 400, "���[��", GetColor(255, 255, 255));
	DrawString(400, 450, "�u���b�N���󂷂��ƂɃX�R�A +1", GetColor(255, 255, 255));
	DrawString(400, 500, "�o�[�ɓ�����Ȃ���΃X�R�A���Z�ʂ�����", GetColor(255, 255, 255));
	DrawString(400, 550, "�{�[������ʉ��ɐG���ƃQ�[���I�[�o�[", GetColor(255, 255, 255));
	DrawString(400, 600, "�X�y�[�X�Ń��g���C/���̃X�e�[�W��", GetColor(255, 255, 255));
	DrawString(400, 650, "�S3�X�e�[�W", GetColor(255, 255, 255));

	// �J�[�\���ƃ{�^���`��
	DrawBox(cursorX, cursorY, cursorX + width, cursorY + height, GetColor(255, 255, 255), FALSE);
	DrawString(cursorX + 20, cursorY + 15, "Space�ŕ���", GetColor(255, 255, 255));
} 

void UIManager::RenderBestScore(std::vector<int> scores) {
	DrawStringToHandle(450, 100, "�x�X�g�X�R�A", GetColor(255, 255, 255), fontHeadword);
	DrawStringToHandle(550, 230, ("1." + std::to_string(scores.size() > 0 ? scores[0] : 0)).c_str(), GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 330, ("2." + (scores.size() > 1 ? std::to_string(scores[1]) : "")).c_str(), GetColor(255, 255, 255), fontTitle);
	DrawStringToHandle(550, 430, ("3." + (scores.size() > 2 ? std::to_string(scores[2]) : "")).c_str(), GetColor(255, 255, 255), fontTitle);

	// �J�[�\���ƃ{�^���`��
	DrawBox(cursorX, cursorY, cursorX + width, cursorY + height, GetColor(255, 255, 255), FALSE);
	DrawString(cursorX + 20, cursorY + 15, "Space�ŕ���", GetColor(255, 255, 255));
}