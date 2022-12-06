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
	attributes = new unsigned short[width * height];
	setColor(0, 0, width * height);
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Буфер экрана
	SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли
}

void ScreenBuffer::clear(wchar_t value)
{
	std::fill_n(buffer, width * height + 1, value);
}

void ScreenBuffer::setColor(short x, short y, int length, int color) {
	std::fill_n(attributes + x + y * width, length, color);
}

void ScreenBuffer::set(short x, short y, wchar_t value)
{
	if (x >= 0 && x < width && y >= 0 && y < height) {
		buffer[y * width + x] = value;
	}
}

void ScreenBuffer::rect(short x, short y, short w, short h)
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

void ScreenBuffer::fillRect(short x, short y, short w, short h, wchar_t value)
{
	for (short ix = x; ix < x + w; ix++) {
		for (short iy = y; iy < y + h; iy++) {
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
	WriteConsoleOutputAttribute(hConsole, attributes, width * height, { 0, 0 }, &dwBytesWritten);
	WriteConsoleOutputCharacter(hConsole, buffer, width * height, { 0,0 }, &dwBytesWritten);
	if (vsync) {
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}

short ScreenBuffer::getWidth()
{
	return width;
}

short ScreenBuffer::getHeight()
{
	return height;
}

void ScreenBuffer::text(short x, short y, const char* text)
{
	for (int ix = x; ix < x + strlen(text); ix++) {
		set(ix, y, text[ix - x]);
	}
}

void ScreenBuffer::text(short y, const char* text)
{
	int x = width / 2 - strlen(text) / 2;
	ScreenBuffer::text(x, y, text);
}

void ScreenBuffer::input(bool* shouldClose)
{
	if (GetAsyncKeyState('Q') & 1) {
		*shouldClose = true;
	}

	if (GetAsyncKeyState(112) & 1) {
		debug ^= 1;
	}

	if (GetAsyncKeyState(113) & 1) {
		vsync ^= 1;
	}
}

void ScreenBuffer::overlay(Profiler* profiler)
{
	if (debug) {
		std::string delta = std::to_string(profiler->getDelta());
		static char* data = new char[128];
		strcpy(data, "F");
		_itoa(profiler->getFps(), data + strlen(data), 10);
		strcat(data, " D");
		strcat(data, delta.c_str());
		strcat(data, "ms");
		text(15, 0, data);
	}
}
