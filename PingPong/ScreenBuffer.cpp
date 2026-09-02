#include "ScreenBuffer.h"
#include <algorithm>
#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <cwchar>
#include <iterator>
#include <thread>

ScreenBuffer::ScreenBuffer()
{
	hOriginal = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi{};
	if (GetConsoleScreenBufferInfo(hOriginal, &csbi)) {
		width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
	if (width <= 0 || height <= 0) { // stdout is not a console (redirected) - fall back to a sane size
		width = 80;
		height = 25;
	}
	cells.resize(static_cast<size_t>(width) * height);
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr); // Буфер экрана
	if (hConsole == INVALID_HANDLE_VALUE) {
		hConsole = hOriginal; // draw straight into the existing console instead of crashing
	}
	else {
		SetConsoleScreenBufferSize(hConsole, { width, height }); // no scrollback, so no scrollbar; best effort
		CONSOLE_CURSOR_INFO cursor{ 1, FALSE };
		SetConsoleCursorInfo(hConsole, &cursor); // hide the blinking cursor while the game draws
		SetConsoleActiveScreenBuffer(hConsole); // Настройка консоли
	}
	clear();
}

ScreenBuffer::~ScreenBuffer()
{
	if (hConsole != INVALID_HANDLE_VALUE && hConsole != hOriginal) {
		SetConsoleActiveScreenBuffer(hOriginal); // give the user their original console back
		CloseHandle(hConsole);
	}
}

void ScreenBuffer::clear(wchar_t value, unsigned short color)
{
	CHAR_INFO cell{};
	cell.Char.UnicodeChar = value;
	cell.Attributes = color;
	std::fill(cells.begin(), cells.end(), cell);
}

void ScreenBuffer::set(short x, short y, wchar_t value, unsigned short color)
{
	if (x >= 0 && x < width && y >= 0 && y < height) {
		CHAR_INFO& cell = cells[static_cast<size_t>(y) * width + x];
		cell.Char.UnicodeChar = value;
		cell.Attributes = color;
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

void ScreenBuffer::flush()
{
	// One call writes both characters and attributes for the whole frame (no tearing between the two).
	SMALL_RECT region{ 0, 0, static_cast<short>(width - 1), static_cast<short>(height - 1) };
	WriteConsoleOutputW(hConsole, cells.data(), { width, height }, { 0, 0 }, &region);
	if (vsync) {
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}

short ScreenBuffer::getWidth() const
{
	return width;
}

short ScreenBuffer::getHeight() const
{
	return height;
}

void ScreenBuffer::putText(short x, short y, unsigned short color, const wchar_t* str, int length)
{
	for (int i = 0; i < length; i++) {
		set(static_cast<short>(x + i), y, str[i], color); // set() clips, so text can never run past the row or the buffer
	}
}

void ScreenBuffer::text(short x, short y, unsigned short color, const wchar_t* format, ...)
{
	wchar_t buf[256];
	va_list args;
	va_start(args, format);
	int length = _vsnwprintf_s(buf, _TRUNCATE, format, args);
	va_end(args);
	if (length < 0) length = static_cast<int>(wcsnlen_s(buf, std::size(buf))); // output was truncated to fit

	putText(x, y, color, buf, length);
}

void ScreenBuffer::text(short y, unsigned short color, const wchar_t* format, ...)
{
	wchar_t buf[256];
	va_list args;
	va_start(args, format);
	int length = _vsnwprintf_s(buf, _TRUNCATE, format, args);
	va_end(args);
	if (length < 0) length = static_cast<int>(wcsnlen_s(buf, std::size(buf)));

	const short x = static_cast<short>((width - length) / 2); // centre the formatted text, not the format string
	putText(x, y, color, buf, length);
}

void ScreenBuffer::input(bool* shouldClose)
{
	if (keyPressed('Q')) {
		*shouldClose = true;
	}

	if (keyPressed(VK_F1)) {
		debug = !debug;
	}

	if (keyPressed(VK_F2)) {
		vsync = !vsync;
	}
}

void ScreenBuffer::overlay(Profiler* profiler)
{
	if (debug) {
		text(15, 0, defaultColor, L"F%d D%.2fms", profiler->getFps(), profiler->getDelta());
	}
}
