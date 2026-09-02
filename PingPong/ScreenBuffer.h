#pragma once
#include "Input.h"
#include <vector>
#include "Profiler.h"

class ScreenBuffer
{
private:
	short width = -1;
	short height = -1;
	std::vector<CHAR_INFO> cells; // character + attribute per cell, sent to the console in one call
	bool debug = false, vsync = true;
	HANDLE hConsole = INVALID_HANDLE_VALUE;
	HANDLE hOriginal = INVALID_HANDLE_VALUE;
	void putText(short x, short y, unsigned short color, const wchar_t* str, int length);
public:
	static constexpr unsigned short defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // 7 = light grey on black
	ScreenBuffer();
	~ScreenBuffer();
	ScreenBuffer(const ScreenBuffer&) = delete;
	ScreenBuffer& operator=(const ScreenBuffer&) = delete;
	void clear(wchar_t value = L' ', unsigned short color = defaultColor);
	void set(short x, short y, wchar_t value, unsigned short color = defaultColor);
	void rect(short x, short y, short w, short h, unsigned short color = defaultColor);
	void fillRect(short x, short y, short w, short h, wchar_t value, unsigned short color = defaultColor);
	void flush();
	short getWidth() const;
	short getHeight() const;
	void text(short x, short y, unsigned short color, const wchar_t* format, ...);
	void text(short y, unsigned short color, const wchar_t* format, ...);
	void input(bool* shouldClose);
	void overlay(Profiler* profiler);
};
