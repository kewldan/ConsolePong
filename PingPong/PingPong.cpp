#include <chrono>
#include <string>
#include <regex>
#include <thread>

#include "ScreenBuffer.h"
#include "Ball.h"
#include "PingPongGame.h"
#include "Game.h"

using namespace std;

int selected = 0;
int gameMode = -1;
int gameModesLength = -1;

ScreenBuffer* buffer;
Profiler* profiler;


int main()
{
	buffer = new ScreenBuffer();
	profiler = new Profiler(1);

	Game* gameModes[] = { new PingPongGame() };
	gameModesLength = *(&gameModes + 1) - gameModes;

	for (int i = 0; i < gameModesLength; i++) {
		gameModes[i]->setBuffer(buffer);
		gameModes[i]->setup();
	}

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
		buffer->text(buffer->getHeight() / 2 - 5, "Select a game");
		buffer->text(buffer->getHeight() / 2 + 10, "Press enter to continue");
		buffer->text(buffer->getHeight() - 2, "by kewldan");
		buffer->rect(buffer->getWidth() / 2 - 15, buffer->getHeight() / 2 - 1, 30, 2 + gameModesLength);
		for (int i = 0; i < gameModesLength; i++) {
			buffer->text(buffer->getWidth() / 2 - 6, buffer->getHeight() / 2 + i, (selected == i ? ">" : " ") + gameModes[i]->name);
		}
		if (gameModesLength == 0) {
			buffer->text(3, "NO GAMES LOADED");
		}
		buffer->flush();
	}

	while (1) // Game loop
	{
		profiler->update();
		if (buffer->input()) break;

		gameModes[gameMode]->update(profiler->getDelta());

		gameModes[gameMode]->render();

		buffer->overlay(profiler);
		buffer->flush();
	}
	return 0;
}