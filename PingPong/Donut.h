#pragma once
#include "Game.h"
class Donut :
    public Game
{
	float time = 0.f;                              // animation clock, ms
	float camX = -2.f, camY = 0.f, camZ = 0.f;     // camera position (was a function-static inside the shader)
public:
	void setup() override;
	void update(float delta) override;
	void render() override;
	Donut();
};
