#pragma once
#include <array>
#include <memory>
#include "Game.h"
#include "Field.h"
#include "Shape.h"

class TetrisGame :
    public Game
{
private:
	bool paused = false;
	std::unique_ptr<Field> field;
	std::array<Shape, 2> shapes;
	int currentShape = 1;
	int sX = 0, sY = 0;
	int score = 0, rows = 0;
	float fallTimer = 0.f; // ms since the piece last moved down
public:
	void setup() override;
	void update(float delta) override;
	void render() override;
	void tick();
	TetrisGame();
};
