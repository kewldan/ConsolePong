#pragma once
#include "Game.h"
class Donut :
    public Game
{
public:
	void setup();
	void update(float delta);
	void render();
	void setBuffer(ScreenBuffer* buff);
	Donut();
};

