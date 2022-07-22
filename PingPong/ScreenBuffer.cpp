#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer()
{
	debug = false;
	vsync = true;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
	buffer = new wchar_t[width * height + 1];
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Буфер экрана
	SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли
}

void ScreenBuffer::clear()
{
	clear(' ');
}

void ScreenBuffer::clear(wchar_t value)
{
	std::fill_n(buffer, width * height + 1, value);
}

void ScreenBuffer::set(int x, int y, wchar_t value)
{
	if (x >= 0 && x < width && y >= 0 && y < height) {
		buffer[y * width + x] = value;
	}
}

void ScreenBuffer::rect(int x, int y, int w, int h)
{
	fillRect(x + 1, y, w - 2, 1, '-'); //Top
	fillRect(x + 1, y + h - 1, w - 2, 1, '-'); //Bottom

	fillRect(x + w - 1, y + 1, 1, h - 2, '|'); //Right
	fillRect(x, y + 1, 1, h - 2, '|'); //Left

	set(x, y, '+');
	set(x + w - 1, y, '+');
	set(x, y + h - 1, '+');
	set(x + w - 1, y + h - 1, '+');
}

void ScreenBuffer::fillRect(int x, int y, int w, int h, wchar_t value)
{
	for (int ix = x; ix < x + w; ix++) {
		for (int iy = y; iy < y + h; iy++) {
			set(ix, iy, value);
		}
	}
}

wchar_t* ScreenBuffer::getBuffer()
{
	return buffer;
}

void ScreenBuffer::flush()
{
	WriteConsoleOutputCharacter(hConsole, buffer, width * height, { 0,0 }, &dwBytesWritten);
	if (vsync) {
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}

int ScreenBuffer::getWidth()
{
	return width;
}

int ScreenBuffer::getHeight()
{
	return height;
}

void ScreenBuffer::text(int x, int y, std::string text)
{
	for (int ix = x; ix < x + text.length(); ix++) {
		set(ix, y, text[ix - x]);
	}
}

void ScreenBuffer::text(int y, std::string text)
{
	int x = width / 2 - (int) text.length() / 2;
	for (int ix = x; ix < x + text.length(); ix++) {
		set(ix, y, text[ix - x]);
	}
}

bool ScreenBuffer::input()
{
	if (GetAsyncKeyState('Q') & 1) {
		return 1;
	}

	if (GetAsyncKeyState(112) & 1) {
		debug ^= 1;
	}

	if (GetAsyncKeyState(113) & 1) {
		vsync ^= 1;
	}
	return false;
}

void ScreenBuffer::overlay(Profiler* profiler)
{
	if (debug) {
		std::string delta = std::to_string(profiler->getDelta());
		text(15, 0, "F" + std::to_string(profiler->getFps()) + " D" + delta.substr(0, delta.find(".") + 2) + "ms");
	}
}
