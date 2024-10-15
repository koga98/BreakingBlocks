#include "Bar.h"
#include "DxLib.h"

Bar::Bar() {
	Reset(1);  // �f�t�H���g�̃X�e�[�W�ŏ�����
	
}

void Bar::Reset(int newStage) {
	positionX = 640;
	positionY = 540;
	lastTime = 0;
	switch (newStage) {
	case 1:
		width = 150; height = 30; speedX1 = 330; speedX2 = -330;
		break;
	case 2:
		width = 100; height = 20; speedX1 = 400; speedX2 = -210;
		break;
	case 3:
		width = 180; height = 20; speedX1 = 530; speedX2 = -530;
		break;
	default:
		break;
	}
}

void Bar::Update() {
	if (lastTime == 0)
		lastTime = GetNowCount();
	int currentTime = GetNowCount();  // ���݂̎��Ԃ��擾
	float deltaTime = (currentTime - lastTime) / 1000.0f;  // �O�̃t���[���Ƃ̎��ԍ���b�P�ʂŌv�Z
	lastTime = currentTime;

	if (CheckHitKey(KEY_INPUT_A) && positionX > 0) {
		
		positionX += speedX2 * deltaTime;
	}
	if (CheckHitKey(KEY_INPUT_D) && positionX + width < 1280) {
		positionX += speedX1 * deltaTime;
	}

	ball.CheckCollision(positionX, positionY, width, height);
}

void Bar::Draw() {
	
	DrawBox(static_cast<int>(positionX), static_cast<int>(positionY), static_cast<int>(positionX + width), static_cast<int>(positionY + height), GetColor(255, 255, 255), TRUE);
}