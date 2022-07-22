#pragma once
#include "ScreenBuffer.h"
#include <string>

class Game
{
public:
	std::string name;
	ScreenBuffer* buffer;
	virtual void setup() = 0;
	virtual void update(float delta) = 0;
	virtual void render() = 0;
	virtual void setBuffer(ScreenBuffer* buff) = 0;
	Game(std::string n);
	Game();
};

