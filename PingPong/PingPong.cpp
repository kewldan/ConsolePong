#include <chrono>
#include <string>
#include <regex>
#include <thread>

#include "ScreenBuffer.h"
#include "Ball.h"
#include "PingPongGame.h"
#include "TetrisGame.h"
#include "Donut.h"
#include "Game.h"

using namespace std;

int selected;
int gameMode;
int gameModesLength = -1;
bool shouldClose;

ScreenBuffer* buffer;
Profiler* profiler;


int main()
{
	buffer = new ScreenBuffer();
	profiler = new Profiler(1);

	Game* gameModes[] = { new PingPongGame(), new TetrisGame(), new Donut() };
	gameModesLength = sizeof(gameModes) / sizeof(*gameModes);

	for (int i = 0; i < gameModesLength; i++) {
		gameModes[i]->setBuffer(buffer);
		gameModes[i]->setup();
	}

EnterPoint:
	selected = 0;
	gameMode = -1;

	while (gameMode == -1) {
		if (GetAsyncKeyState('W') & 1) {
			selected--;
		}
		if (GetAsyncKeyState('S') & 1) {
			selected++;
		}
		selected = clamp(selected, 0, gameModesLength - 1);
		if (GetAsyncKeyState(13) & 1) {
			gameMode = selected;
		}
		buffer->clear();
		buffer->text(buffer->getHeight() / 2 - 5, 7U, L"Select a game");
		buffer->text(buffer->getHeight() / 2 + 10, 7U, L"Press enter to continue");
		buffer->text(buffer->getHeight() - 2, 7U, L"by kewldan");
		buffer->rect(buffer->getWidth() / 2 - 15, buffer->getHeight() / 2 - 1, 30, 2 + gameModesLength);
		for (int i = 0; i < gameModesLength; i++) {
			buffer->text(buffer->getWidth() / 2 - 6, buffer->getHeight() / 2 + i, 7U, L"%s%s", i == selected ? L">" : L" ", gameModes[i]->name);
		}
		if (gameModesLength == 0) {
			buffer->text(3, 7U, L"NO GAMES LOADED");
		}
		buffer->flush();
	}

	while (!shouldClose) // Game loop
	{
		if (GetAsyncKeyState('X') & 0x8000) {
			goto EnterPoint;
		}
		profiler->update();
		buffer->input(&shouldClose);

		gameModes[gameMode]->update(profiler->getDelta());

		gameModes[gameMode]->render();

		buffer->overlay(profiler);
		buffer->flush();
	}
	return 0;
}