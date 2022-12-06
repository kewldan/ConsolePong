#pragma once
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>
#include "Profiler.h"

class ScreenBuffer
{
private:
	short width = -1;
	short height = -1;
	wchar_t* buffer;
	unsigned short* attributes;
	bool debug, vsync;
	void* hConsole;
	unsigned long dwBytesWritten = 0;
public:
	ScreenBuffer();
	void clear(wchar_t value = ' ');
	void set(short x, short y, wchar_t value);
	void rect(short x, short y, short w, short h);
	void fillRect(short x, short y, short w, short h, wchar_t value);
	wchar_t* getBuffer();
	void flush();
	short getWidth();
	short getHeight();
	void text(short x, short y, const char* text);
	void text(short y, const char* text);
	void setColor(short x, short y, int length, int color = 7);
	void input(bool* shouldClose);
	void overlay(Profiler* profiler);
};
