#include "Game.h"

Game::Game(const wchar_t* n)
{
	name = n;
}

void Game::setBuffer(ScreenBuffer* buff)
{
	buffer = buff;
}
