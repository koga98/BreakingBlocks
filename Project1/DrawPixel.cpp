#include "DxLib.h"
#include <windows.h>
#include "ProjConf.h"
#include "GameManager.h"
#include "Title.h"


void GameRun(Title title, GameManager gamemanager);

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	/*** Window Init ***/
	SetWindowText("�u���b�N����");					// �E�B���h�E�̃^�C�g��
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);	// �E�B���h�E�̈ʒu
	SetGraphMode(WIN_MAX_X, WIN_MAX_Y, 32);			// �E�B���h�E�̃T�C�Y
	SetBackgroundColor(0, 0, 0);				// �E�B���h�E�̔w�i�F
	SetDrawScreen(DX_SCREEN_BACK);					// �`����ʂ𗠉�ʂɂ���
	SetAlwaysRunFlag(TRUE);							// �E�C���h�E��A�N�e�B�u��Ԃł������𑱍s����
	Title title;
	GameManager gamemanager;
	GameRun(title, gamemanager);
	
	
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

void GameRun(Title title, GameManager gamemanager) {
	title.Run();
	if (!title.endGame) {
		gamemanager.Run();
	}

	if (gamemanager.backTitle) {
		title = Title(); // �V�����C���X�^���X���쐬���ď�����
		gamemanager = GameManager(); // ���l�ɏ�����
		GameRun(title, gamemanager);
	}
	else if (gamemanager.gameEnd)
		return;
}



