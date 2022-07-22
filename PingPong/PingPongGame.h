#pragma once
#include "Game.h"
#include "Ball.h"

class PingPongGame : public Game {
	int playerY = 2;
	int player2Y = 2;
	int player1Score = 0;
	int player2Score = 0;
	Ball* ball;
public:
	void setup();
	void update(float delta);
	void render();
	void setBuffer(ScreenBuffer* buff);
	PingPongGame();
};