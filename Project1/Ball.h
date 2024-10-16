#pragma once
#include "ProjConf.h"
#include "SoundManager.h"

class Ball {
public:
	Ball();
	void Draw();
	void Update();
	bool CheckCollision(float barX, float barY, float width, float height);
	bool CollisionToEdge();
	bool CheckCollisionBrocks(float X, float Y, int width, int height);
	void Reset(int number);
private:
	SoundManager soundManager;
	int lastCollisionTime;
	int lastTime;
	float deltaTime;
	float x, y;
	float radius;
	float speedX, speedY;
	float changedSpeedXAbs;
	float constSpeedX, constSpeedY;
	float lastX, lastY;
	
};