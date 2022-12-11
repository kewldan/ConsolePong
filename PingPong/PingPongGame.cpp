#include "PingPongGame.h"

void PingPongGame::setup()
{
	ball = new Ball(buffer);
	ball->reinit();
}

void PingPongGame::update(float delta)
{
	// ### Input handle ### //
	if (GetAsyncKeyState('W') & 0x8000) {
		playerY--;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		playerY++;
	}
	playerY = max(2, min(buffer->getHeight() - 5, playerY));

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

	player2Y = (int) round(ball->y - 3);
	player2Y = max(2, min(buffer->getHeight() - 5, player2Y));
}

void PingPongGame::render()
{
	// ### Render ### //
	buffer->clear(' ', BACKGROUND_GREEN);

	buffer->fillRect(0, 1, buffer->getWidth(), 1, '_', BACKGROUND_GREEN);
	buffer->fillRect(1, playerY, 1, 5, '#', BACKGROUND_GREEN);
	buffer->fillRect(buffer->getWidth() - 2, player2Y, 1, 5, '#', BACKGROUND_GREEN);
	ball->draw();

	// ### Draw HUD ### //
	buffer->text(1, 0, "Player 1", BACKGROUND_GREEN);
	buffer->text(buffer->getWidth() - 9, 0, "Player 2", BACKGROUND_GREEN);
	static char* t = new char[24];
	strcpy(t, "");
	_itoa(player1Score, t, 10);
	strcat(t, " : ");
	_itoa(player2Score, t + strlen(t), 10);
	buffer->text(0, t, BACKGROUND_GREEN);
}

void PingPongGame::setBuffer(ScreenBuffer* buff) {
	buffer = buff;
}

PingPongGame::PingPongGame() : Game("PingPong")
{
	ball = nullptr;
}
