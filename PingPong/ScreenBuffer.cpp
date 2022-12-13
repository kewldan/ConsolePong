#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer()
{
	debug = false;
	vsync = true;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
	buffer = new wchar_t[width * height];
	attributes = new unsigned short[width * height];
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL); // Буфер экрана
	SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли
}

void ScreenBuffer::clear(wchar_t value, unsigned short color)
{
	std::fill_n(buffer, width * height, value);
	std::fill_n(attributes, width * height, color);
}

void ScreenBuffer::set(short x, short y, wchar_t value, unsigned short color)
{
	if (x >= 0 && x < width && y >= 0 && y < height) {
		buffer[y * width + x] = value;
		attributes[y * width + x] = color;
	}
}

void ScreenBuffer::rect(short x, short y, short w, short h, unsigned short color)
{
	fillRect(x + 1, y, w - 2, 1, '-', color); //Top
	fillRect(x + 1, y + h - 1, w - 2, 1, '-', color); //Bottom

	fillRect(x + w - 1, y + 1, 1, h - 2, '|', color); //Right
	fillRect(x, y + 1, 1, h - 2, '|', color); //Left

	set(x, y, '+', color);
	set(x + w - 1, y, '+', color);
	set(x, y + h - 1, '+', color);
	set(x + w - 1, y + h - 1, '+', color);
}

void ScreenBuffer::fillRect(short x, short y, short w, short h, wchar_t value, unsigned short color)
{
	for (short ix = x; ix < x + w; ix++) {
		for (short iy = y; iy < y + h; iy++) {
			set(ix, iy, value, color);
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
	WriteConsoleOutputCharacterW(hConsole, buffer, width * height, { 0,0 }, &dwBytesWritten);
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

void ScreenBuffer::text(short x, short y, unsigned short color, const wchar_t* format, ...)
{
	static wchar_t* buf = new wchar_t[256];
	va_list args;
	va_start(args, format);
	int i = _vsnwprintf(buf, 256, format, args);
	va_end(args);

	memcpy(buffer + x + y * width, buf, i * sizeof(wchar_t));
}

void ScreenBuffer::text(short y, unsigned short color, const wchar_t* format, ...)
{
	static wchar_t* buf = new wchar_t[256];
	int x = width / 2 - wcslen(format) / 2;

	va_list args;
	va_start(args, format);
	int i = _vsnwprintf(buf, 256, format, args);
	va_end(args);

	memcpy(buffer + x + y * width, buf, i * sizeof(wchar_t));
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
		ScreenBuffer::text(15Ui16, 0Ui16, 7Ui16, L"F%d D%.2fms", profiler->getFps(), profiler->getDelta());
	}
}
