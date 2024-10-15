#pragma once
#include "Ball.h"
class Bar {
public:
	Bar();
	Ball ball;
	void Update();
	void Draw();
	void Reset(int newStage);
	int positionX, positionY;
	int width, height;
	int speedX1, speedX2;
private:
	
};