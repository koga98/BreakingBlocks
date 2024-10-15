#pragma once
#include "Ball.h"

class Brocks {
public:
	Brocks(float x, float y);
	void Draw();
	void Destroy();
	float positionX, positionY;
	bool isBumped;
};
