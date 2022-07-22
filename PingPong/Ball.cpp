#include "Ball.h"

Ball::Ball(ScreenBuffer* buff)
{
	buffer = buff;
}

void Ball::tick(int x1, int x2, float d)
{
	x += vx;
	y += vy;
	if (y < 2 || y > buffer->getHeight()) {
		vy = -vy;
	}
	if (round(x) == 2 && vx < 0) {
		if (y > x1 && y < x1 + 5) {
			vx = -vx;
		}
	}
	if (round(x) == buffer->getWidth() - 2 && vx > 0) {
		if (y > x2 && y < x2 + 5) {
			vx = -vx;
		}
	}
}

float random() {
	return ((float) rand() / RAND_MAX);
}

float randomn() {
	return random() * 2.f - 1.f;
}

int round(float v) {
	return (int)(v + 0.5f - (v < 0));
}

void Ball::reinit()
{
	x = (float) buffer->getWidth() / 2;
	y = (float) buffer->getHeight() / 2;
	vx = randomn() * 0.4f + 0.6f;
	vy = randomn() * 0.4f + 0.6f;
}

bool Ball::isLeftCollide()
{
	return x < 0;
}

bool Ball::isRigthCollide()
{
	return x > buffer->getWidth();
}

void Ball::draw()
{
	buffer->fillRect(round(x), round(y), 1, 1, 'o');
}
