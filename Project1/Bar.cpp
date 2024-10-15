#include "Bar.h"
#include "DxLib.h"

Bar::Bar() {
	Reset(1);  // デフォルトのステージで初期化
}

void Bar::Reset(int newStage) {
	positionX = 640;
	positionY = 540;

	switch (newStage) {
	case 1:
		width = 150; height = 30; speedX1 = 3; speedX2 = -3;
		break;
	case 2:
		width = 100; height = 20; speedX1 = 4; speedX2 = -2;
		break;
	case 3:
		width = 180; height = 20; speedX1 = 5; speedX2 = -5;
		break;
	default:
		break;
	}
}

void Bar::Update() {
	if (CheckHitKey(KEY_INPUT_A) && positionX > 0) {
		positionX += speedX2;
	}
	if (CheckHitKey(KEY_INPUT_D) && positionX + width < 1280) {
		positionX += speedX1;
	}

	ball.CheckCollision(positionX, positionY, width, height);
}

void Bar::Draw() {
	DrawBox(positionX, positionY, positionX + width, positionY + height, GetColor(255, 255, 255), TRUE);
}