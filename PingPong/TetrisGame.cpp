#include "TetrisGame.h"

void TetrisGame::setup()
{
	field = new Field(10, 20);
	score = 0;
	rows = 0;
	shapes = new Shape[2];
	shapes[0].fill(0b1100110000000000);
	shapes[1].fill(0b1000100010001000);
	thread = new std::thread(&TetrisGame::tick, this);
}


void TetrisGame::update(float delta)
{
	if (GetAsyncKeyState('P') & 1) {
		paused ^= 1;
	}
	if (GetAsyncKeyState(13) & 1) {
		//Restart
	}
	if (GetAsyncKeyState('R') & 1) {
		//Rotate
	}
	if (GetAsyncKeyState('A') & 1) {
		//Right
		sX--;
	}
	if (GetAsyncKeyState('D') & 1) {
		//Left
		sX++;
	}
	if (GetAsyncKeyState(VK_SPACE) & 1) {
		//Drop
	}

	if (!paused) {

	}
}

void TetrisGame::render()
{
	int start_x = buffer->getWidth() / 2 - 8;

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
	buffer->text(3, 18, 7U, L"[%s] Pause: P", paused ? "Y" : " ");


	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 20; y++) {
			if (field->get(x, y)) {
				buffer->set(x + start_x + 1, y + 3, '#');
			}
		}
	}

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (shapes[currentShape].get(x, y)) {
				buffer->set(x + sX + start_x + 4, y + sY + 3, '?');
			}
		}
	}
}

void TetrisGame::tick()
{
	while (1) {
		if (!paused) {
			sY++;
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
	}
}

void TetrisGame::setBuffer(ScreenBuffer* buff)
{
	buffer = buff;
}

TetrisGame::TetrisGame() : Game(L"Tetris")
{

}
