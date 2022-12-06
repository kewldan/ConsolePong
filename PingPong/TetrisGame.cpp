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

	buffer->text(2, 1, "Statistics");
	buffer->text(2, 2, "==========");
	char* t = new char[32];
	strcpy(t, "Score: ");
	_itoa(score, t + strlen(t), 10);
	buffer->text(3, 3, t);
	strcpy(t, "Rows: ");
	_itoa(rows, t + strlen(t), 10);
	buffer->text(3, 4, t);

	buffer->text(2, 7, "Hotkeys");
	buffer->text(2, 8, "=======");
	buffer->text(3, 9, "Quit: Q");
	buffer->text(3, 10, "Restart: ENTER");
	buffer->text(3, 11, "Rotate: R");
	buffer->text(3, 12, "Move: A/D");
	buffer->text(3, 13, "Drop: SPACE");

	buffer->text(2, 16, "Toggles");
	buffer->text(2, 17, "=======");
	strcpy(t, "[");
	t[strlen(t)] = paused ? 'Y' : ' ';
	strcat(t, "] Pause: P");
	buffer->text(3, 18, t);


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

TetrisGame::TetrisGame() : Game("Tetris")
{

}
