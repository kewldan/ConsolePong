#include "Ball.h"

inline int roundFloat(float v) {
	return (int)(v + 0.5f - (v < 0));
}

inline float random() {
	return ((float)rand() / RAND_MAX);
}

inline float randomn() {
	return random() * 2.f - 1.f;
}

Ball::Ball(ScreenBuffer* buff)
{
	buffer = buff;
	vx = 0;
	vy = 0;
	x = 0;
	y = 0;
}

void Ball::tick(int x1, int x2, float d)
{
	x += vx;
	y += vy;
	if (y < 2 || y > buffer->getHeight()) {
		vy = -vy;
	}
	if (roundFloat(x) == 2 && vx < 0) {
		if (y > x1 && y < x1 + 5) {
			vx = -vx;
		}
	}
	if (roundFloat(x) == buffer->getWidth() - 2 && vx > 0) {
		if (y > x2 && y < x2 + 5) {
			vx = -vx;
		}
	}
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
	buffer->set(roundFloat(x), roundFloat(y), 'o', BACKGROUND_GREEN | FOREGROUND_RED);
}
