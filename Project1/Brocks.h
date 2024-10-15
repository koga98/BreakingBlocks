#pragma once
#include "Ball.h"

class Brocks {
public:
	Brocks(int x, int y);
	void Draw();
	void Destroy();
	void Update();
	int positionX, positionY;
	bool isBumped;
private:
	Ball ball;
};
