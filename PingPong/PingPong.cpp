#include <chrono>
#include <string>
#include <regex>
#include <thread>

#include "ScreenBuffer.h"
#include "Ball.h"
#include "PingPongGame.h"
#include "TetrisGame.h"
#include "Game.h"

using namespace std;

int selected = 0;
int gameMode = -1;
int gameModesLength = -1;
bool shouldClose;

ScreenBuffer* buffer;
Profiler* profiler;


int main()
{
	buffer = new ScreenBuffer();
	profiler = new Profiler(1);

	Game* gameModes[] = { new PingPongGame(), new TetrisGame() };
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
			char* t = new char[16];
			memset(t, 0, 16);
			t[0] = selected == i ? '>' : ' ';
			strcat(t, gameModes[i]->name.c_str());
			buffer->text(buffer->getWidth() / 2 - 6, buffer->getHeight() / 2 + i,t);
		}
		if (gameModesLength == 0) {
			buffer->text(3, "NO GAMES LOADED");
		}
		buffer->flush();
	}

	while (!shouldClose) // Game loop
	{
		profiler->update();
		buffer->input(&shouldClose);

		gameModes[gameMode]->update(profiler->getDelta());

		gameModes[gameMode]->render();

		buffer->overlay(profiler);
		buffer->flush();
	}
	return 0;
}