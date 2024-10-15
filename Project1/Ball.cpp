#include "Ball.h"
#include "DxLib.h"

Ball::Ball() {
	Reset(0);
}

void Ball::Reset(int number) {
	if (number == 0) {
		x = lastX = 640;
		y = lastY = 360;
		speedX = 2.0f;
		speedY = -3.0f;
	}
	else if (number == 1) {
		x = lastX = 600;
		y = lastY = 330;
		speedX = 1.0f;
		speedY = 2.0f;
	}
	radius = 10.0f;
	lastCollisionTime = 0;
}

void Ball::Update() {
	lastX = x;
	lastY = y;
	x += speedX;
	y += speedY;
}

void Ball::Draw() {
	DrawCircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(radius), GetColor(255, 0, 0), TRUE);
}

bool Ball::CollisionToEdge() {
	if (x + radius >= WIN_MAX_X || x - radius <= 0) {
		speedX *= -1;
	}
	if (y + radius <= 0 || y >= WIN_MAX_Y) {
		speedY *= -1;
		return y >= WIN_MAX_Y;
	}
	return false;
}

bool Ball::CheckCollision(int barX, int barY, int width, int height) {
	if (GetNowCount() - lastCollisionTime < 100) return false;

	bool CollisionX = barX <= x + radius && x - radius <= barX + width;
	bool CollisionY = barY <= y + radius && y - radius <= barY + height;

	if (CollisionX && CollisionY) {
		float hitPosition = (x - barX) / static_cast<float>(width);
		speedX = 2.0f * (hitPosition - 0.5f);
		speedY *= -1;
		lastCollisionTime = GetNowCount();
		return true;
	}
	return false;
}

bool Ball::CheckCollisionBrocks(int X, int Y, int width, int height) {
	if (GetNowCount() - lastCollisionTime < 1) return false;

	bool CollisionX = X <= x + radius && x - radius <= X + width;
	bool CollisionY = Y <= y + radius && y - radius <= Y + height;

	if (CollisionX && CollisionY) {
		soundManager.PlaySoundEffect(0);

		if (lastX + radius <= X || lastX - radius >= X + width) {
			speedX *= -1;
		}
		if (lastY + radius <= Y || lastY - radius >= Y + height) {
			speedY *= -1;
		}

		lastCollisionTime = GetNowCount();
		return true;
	}
	return false;
}