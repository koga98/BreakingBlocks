#pragma once
#include "Ball.h"
class Bar {
public:
	Bar();
	Ball ball;
	void Update();
	void Draw();
	void Reset(int newStage);
	float positionX, positionY;
	int lastTime;
	float width, height;
	float speedX1, speedX2;
private:
	
};