#pragma once
#include <memory>
#include "Game.h"
#include "Ball.h"

class PingPongGame : public Game {
	int playerY = 2;
	int player2Y = 2;
	int player1Score = 0;
	int player2Score = 0;
	std::unique_ptr<Ball> ball;
public:
	void setup() override;
	void update(float delta) override;
	void render() override;
	PingPongGame();
};
