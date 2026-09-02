#pragma once
#include "ScreenBuffer.h"

class Game
{
public:
	const wchar_t* name;
	ScreenBuffer* buffer = nullptr;
	virtual void setup() = 0;
	virtual void update(float delta) = 0;
	virtual void render() = 0;
	void setBuffer(ScreenBuffer* buff);
	explicit Game(const wchar_t* n);
	virtual ~Game() = default; // games are owned and destroyed through Game*, so the destructor must be virtual
};
