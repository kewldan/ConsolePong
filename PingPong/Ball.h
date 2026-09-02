#pragma once
#include "ScreenBuffer.h"
class Ball
{
private:
	ScreenBuffer* buffer;
	float vx, vy;
public:
	float x, y;
	explicit Ball(ScreenBuffer* buff);
	void tick(int x1, int x2, float d);
	bool isLeftCollide() const;
	bool isRigthCollide() const;
	void draw();
	void reinit();
};
