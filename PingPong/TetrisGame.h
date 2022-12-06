#pragma once
#include <thread>
#include "Game.h"
#include "Field.h"
#include "Shape.h"

class TetrisGame :
    public Game
{
private:
	bool paused;
	Field* field;
	Shape* shapes;
	int currentShape = 1;
	int sX = 0, sY = 0;
	int score, rows;
	std::thread* thread;
public:
	void setup();
	void update(float delta);
	void render();
	void tick();
	void setBuffer(ScreenBuffer* buff);
	TetrisGame();
};

