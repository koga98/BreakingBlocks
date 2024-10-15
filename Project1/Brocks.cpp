#include "Brocks.h"
#include "DxLib.h"


Brocks::Brocks(int x,int y){
	positionX = x;
	positionY = y;
	isBumped = false;
}

void Brocks::Update() {
	if (ball.CheckCollision(positionX, positionY, 80, 20)) {
		Destroy();
	}
}

void Brocks::Destroy() {
	isBumped = true;
}

void Brocks::Draw() {
	if (!isBumped) {
		DrawBox(positionX, positionY, positionX + 80, positionY + 20, GetColor(255, 255, 255), TRUE);
		DrawBox(positionX, positionY, positionX + 80, positionY + 20, GetColor(0, 0, 0), FALSE);
	}
}
