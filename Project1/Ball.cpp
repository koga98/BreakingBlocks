#include "Ball.h"
#include "DxLib.h"

Ball::Ball() {
	lastTime = 0;
	Reset(0);
}

void Ball::Reset(int number) {
	lastTime = 0;
	if (number == 0) {
		x = lastX = 640;
		y = lastY = 360;
		speedX = 300.0f;
		speedY = 400.0f;
		constSpeedX = 300.0f;
		constSpeedY = 400.0f;
		changedSpeedXAbs = 300.0f;
	}
	else if (number == 1) {
		x = lastX = 600;
		y = lastY = 330;
		speedX = 150.0f;
		speedY = 200.0f;
		constSpeedX = 150.0f;
		constSpeedY = 200.0f;
		changedSpeedXAbs = 150.0f;
	}
	radius = 10.0f;
	lastCollisionTime = 0;
}

void Ball::Update() {
	if (lastTime == 0)
		lastTime = GetNowCount();
	int currentTime = GetNowCount();  // 現在の時間を取得
	float deltaTime = (currentTime - lastTime) / 1000.0f;  // 前のフレームとの時間差を秒単位で計算
	lastTime = currentTime;
	lastX = x;
	lastY = y;
	x += speedX * deltaTime;
	y += speedY * deltaTime;
}

void Ball::Draw() {
	DrawCircle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(radius), GetColor(255, 0, 0), TRUE);
}

bool Ball::CollisionToEdge() {
	if (x + radius >= WIN_MAX_X ) {
		speedX = -1 * changedSpeedXAbs;
	}
	else if (x - radius <= 0) {
		speedX = changedSpeedXAbs;
	}
	
	if (y >= WIN_MAX_Y) {
		speedY = -1 * constSpeedY;
		return y >= WIN_MAX_Y;
	}
	else if (y - radius <= 0) {
		speedY = constSpeedY;
	}
	return false;
}

bool Ball::CheckCollision(float barX, float barY, float width, float height) {
	if (GetNowCount() - lastCollisionTime < 100) return false;

	bool CollisionX = barX <= x + radius && x - radius <= barX + width;
	bool CollisionY = barY <= y + radius && y - radius <= barY + height;

	if (CollisionX && CollisionY) {
		float hitPosition = (x - barX) / static_cast<float>(width);
		speedX = constSpeedX * (2.0f * (hitPosition - 0.5f));
		changedSpeedXAbs = std::abs(speedX);
		speedY = -1 * constSpeedY;
		lastCollisionTime = GetNowCount();
		return true;
	}
	return false;
}

bool Ball::CheckCollisionBrocks(float X, float Y, int width, int height) {
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