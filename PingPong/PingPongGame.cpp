#include "PingPongGame.h"
#include <algorithm>
#include <cmath>

void PingPongGame::setup()
{
	ball = std::make_unique<Ball>(buffer);
	ball->reinit();
}

void PingPongGame::update(float delta)
{
	// ### Input handle ### //
	if (keyDown('W')) {
		playerY--;
	}
	if (keyDown('S')) {
		playerY++;
	}
	playerY = std::clamp(playerY, 2, buffer->getHeight() - 5);

	// ### Ball update ### //
	ball->tick(playerY, player2Y, delta);

	if (ball->isLeftCollide()) {
		player2Score++;
		ball->reinit();
	}
	else if (ball->isRigthCollide()) {
		player1Score++;
		ball->reinit();
	}

	player2Y = static_cast<int>(std::lround(ball->y - 3));
	player2Y = std::clamp(player2Y, 2, buffer->getHeight() - 5);
}

void PingPongGame::render()
{
	// ### Render ### //
	buffer->clear(' ', BACKGROUND_GREEN);

	buffer->fillRect(0, 1, buffer->getWidth(), 1, '_', BACKGROUND_GREEN);
	buffer->fillRect(1, static_cast<short>(playerY), 1, 5, '#', BACKGROUND_GREEN);
	buffer->fillRect(buffer->getWidth() - 2, static_cast<short>(player2Y), 1, 5, '#', BACKGROUND_GREEN);
	ball->draw();

	// ### Draw HUD ### //
	buffer->text(1, 0, BACKGROUND_GREEN, L"Player 1");
	buffer->text(buffer->getWidth() - 9, 0, BACKGROUND_GREEN, L"Player 2");
	buffer->text(0, BACKGROUND_GREEN, L"%d : %d", player1Score, player2Score);
}

PingPongGame::PingPongGame() : Game(L"PingPong")
{
}
