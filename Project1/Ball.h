#pragma once
#include "ProjConf.h"
#include "SoundManager.h"

class Ball {
public:
	Ball();
	void Draw();
	void Update();
	bool CheckCollision(int barX, int barY, int width, int height);
	bool CollisionToEdge();
	bool CheckCollisionBrocks(int X, int Y, int width, int height);
	void Reset(int number);
private:
	SoundManager soundManager;
	int lastCollisionTime;
	float x, y;
	float radius;
	float speedX, speedY;
	float lastX, lastY;
	
};