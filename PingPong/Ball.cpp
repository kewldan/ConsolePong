#include "Ball.h"
#include <algorithm>
#include <random>

static int roundFloat(float v) {
	return static_cast<int>(v + 0.5f - (v < 0));
}

// [0, 1); seeded once per run so the ball does not start the same way every launch
static float random() {
	static std::mt19937 engine{ std::random_device{}() };
	static std::uniform_real_distribution<float> dist(0.f, 1.f);
	return dist(engine);
}

// [-1, 1)
static float randomn() {
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
	// Velocity is in cells per ~16 ms frame; scale by the real frame time so speed does not
	// depend on FPS (vsync off). Cap the step so a stall (window drag, breakpoint) cannot teleport the ball.
	const float step = std::min(d, 50.f) / 16.f;
	x += vx * step;
	y += vy * step;

	const float top = 2.f;                                     // row 1 is the HUD underline
	const float bottom = static_cast<float>(buffer->getHeight() - 1); // last visible row
	if (y < top && vy < 0) {
		y = top;
		vy = -vy;
	}
	if (y > bottom && vy > 0) {
		y = bottom;
		vy = -vy;
	}

	// Paddles are 5 cells tall at columns 1 and width-2; the ball bounces on the cell next to them.
	// Range checks instead of "== column" so a fast ball cannot tunnel through a paddle.
	const int ry = roundFloat(y);
	const float left = 2.f;
	if (x <= left && vx < 0 && ry >= x1 && ry < x1 + 5) {
		x = left;
		vx = -vx;
	}
	const float right = static_cast<float>(buffer->getWidth() - 3);
	if (x >= right && vx > 0 && ry >= x2 && ry < x2 + 5) {
		x = right;
		vx = -vx;
	}
}


void Ball::reinit()
{
	x = static_cast<float>(buffer->getWidth()) / 2;
	y = static_cast<float>(buffer->getHeight()) / 2;
	vx = randomn() * 0.4f + 0.6f;
	vy = randomn() * 0.4f + 0.6f;
}

bool Ball::isLeftCollide() const
{
	return x < 0;
}

bool Ball::isRigthCollide() const
{
	return x > buffer->getWidth();
}

void Ball::draw()
{
	buffer->set(static_cast<short>(roundFloat(x)), static_cast<short>(roundFloat(y)), 'o', BACKGROUND_GREEN | FOREGROUND_RED);
}
