#include <algorithm>
#include <memory>
#include <vector>

#include "ScreenBuffer.h"
#include "Profiler.h"
#include "PingPongGame.h"
#include "TetrisGame.h"
#include "Donut.h"
#include "Game.h"

int main()
{
	ScreenBuffer buffer;   // restores the original console on destruction
	Profiler profiler(1);

	std::vector<std::unique_ptr<Game>> gameModes;
	gameModes.push_back(std::make_unique<PingPongGame>());
	gameModes.push_back(std::make_unique<TetrisGame>());
	gameModes.push_back(std::make_unique<Donut>());
	const int gameModesLength = static_cast<int>(gameModes.size());

	for (auto& game : gameModes) {
		game->setBuffer(&buffer);
		game->setup();
	}

	bool shouldClose = false;
	while (!shouldClose) {
		int selected = 0;
		int gameMode = -1;

		while (gameMode == -1 && !shouldClose) { // Menu
			buffer.input(&shouldClose);
			if (keyPressed('W')) {
				selected--;
			}
			if (keyPressed('S')) {
				selected++;
			}
			selected = std::clamp(selected, 0, gameModesLength - 1);
			if (keyPressed(VK_RETURN)) {
				gameMode = selected;
			}
			buffer.clear();
			buffer.text(buffer.getHeight() / 2 - 5, 7U, L"Select a game");
			buffer.text(buffer.getHeight() / 2 + 10, 7U, L"Press enter to continue");
			buffer.text(buffer.getHeight() - 2, 7U, L"by kewldan");
			buffer.rect(buffer.getWidth() / 2 - 15, buffer.getHeight() / 2 - 1, 30, 2 + gameModesLength);
			for (int i = 0; i < gameModesLength; i++) {
				buffer.text(buffer.getWidth() / 2 - 6, buffer.getHeight() / 2 + i, 7U, L"%s%s", i == selected ? L">" : L" ", gameModes[i]->name);
			}
			buffer.flush();
		}
		if (shouldClose) {
			break;
		}

		profiler.reset(); // otherwise the first frame's delta is the whole time spent in the menu
		while (!shouldClose) // Game loop
		{
			if (keyDown('X')) {
				break; // back to the menu
			}
			profiler.update();
			buffer.input(&shouldClose);

			gameModes[gameMode]->update(profiler.getDelta());

			gameModes[gameMode]->render();

			buffer.overlay(&profiler);
			buffer.flush();
		}
	}
	return 0;
}
