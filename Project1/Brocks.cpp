#include "Brocks.h"
#include "DxLib.h"


Brocks::Brocks(float x,float y){
	positionX = x;
	positionY = y;
	isBumped = false;
}

void Brocks::Destroy() {
	isBumped = true;
}

void Brocks::Draw() {
	if (!isBumped) {
		DrawBox(static_cast<int>(positionX), static_cast<int>(positionY) , static_cast<int>(positionX + 80), static_cast<int>(positionY + 20), GetColor(255, 255, 255), TRUE);
		DrawBox(static_cast<int>(positionX), static_cast<int>(positionY), static_cast<int>(positionX + 80), static_cast<int>(positionY + 20), GetColor(0, 0, 0), FALSE);
	}
}
