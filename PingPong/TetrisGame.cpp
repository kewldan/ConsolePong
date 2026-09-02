#include "TetrisGame.h"
#include <algorithm>

void TetrisGame::setup()
{
	field = std::make_unique<Field>(10, 20);
	score = 0;
	rows = 0;
	shapes[0].fill(0b1100110000000000);
	shapes[1].fill(0b1000100010001000);
}


void TetrisGame::update(float delta)
{
	if (keyPressed('P')) {
		paused = !paused;
	}
	if (keyPressed(VK_RETURN)) {
		//Restart
	}
	if (keyPressed('R')) {
		//Rotate
	}
	if (keyPressed('A')) {
		//Left
		sX--;
	}
	if (keyPressed('D')) {
		//Right
		sX++;
	}
	if (keyPressed(VK_SPACE)) {
		//Drop
	}
	sX = std::clamp(sX, -3, 3); // keep the 4x4 piece box inside the 10-wide field

	if (!paused) {
		// The piece falls on the game loop's clock instead of a background thread that
		// used to start at program launch (and spun at 100% CPU while paused).
		fallTimer += delta;
		while (fallTimer >= 1000.f) {
			fallTimer -= 1000.f;
			tick();
		}
	}
}

void TetrisGame::render()
{
	const short start_x = buffer->getWidth() / 2 - 8;

	buffer->clear();
	buffer->rect(start_x, 2, 12, 22);

	buffer->text(2, 1, 7U, L"Statistics");
	buffer->text(2, 2, 7U, L"==========");
	buffer->text(3, 3, 7U, L"Score: %d", score);
	buffer->text(3, 4, 7U, L"Rows: %d", rows);

	buffer->text(2, 7, 7U, L"Hotkeys");
	buffer->text(2, 8, 7U, L"=======");
	buffer->text(3, 9, 7U, L"Quit: Q");
	buffer->text(3, 10, 7U, L"Restart: ENTER");
	buffer->text(3, 11, 7U, L"Rotate: R");
	buffer->text(3, 12, 7U, L"Move: A/D");
	buffer->text(3, 13, 7U, L"Drop: SPACE");

	buffer->text(2, 16, 7U, L"Toggles");
	buffer->text(2, 17, 7U, L"=======");
	buffer->text(3, 18, 7U, L"[%s] Pause: P", paused ? L"Y" : L" "); // %s in a wide format string takes a wide string


	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 20; y++) {
			if (field->get(x, y)) {
				buffer->set(static_cast<short>(x + start_x + 1), static_cast<short>(y + 3), '#');
			}
		}
	}

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (shapes[currentShape].get(x, y)) {
				buffer->set(static_cast<short>(x + sX + start_x + 4), static_cast<short>(y + sY + 3), '?');
			}
		}
	}
}

// Move the current piece one row down (it stops at the bottom of the 20-row field).
void TetrisGame::tick()
{
	if (sY < 16) {
		sY++;
	}
}

TetrisGame::TetrisGame() : Game(L"Tetris")
{

}
