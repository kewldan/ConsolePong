#pragma once
#include "ScreenBuffer.h"
#include <string>

class Game
{
public:
	const wchar_t* name;
	ScreenBuffer* buffer;
	virtual void setup() = 0;
	virtual void update(float delta) = 0;
	virtual void render() = 0;
	virtual void setBuffer(ScreenBuffer* buff) = 0;
	Game(const wchar_t* n);
	Game();
};

