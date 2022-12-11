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
	void clear(wchar_t value = ' ', unsigned short color = 7Ui16);
	void set(short x, short y, wchar_t value, unsigned short color = 7Ui16);
	void rect(short x, short y, short w, short h, unsigned short color = 7Ui16);
	void fillRect(short x, short y, short w, short h, wchar_t value, unsigned short color = 7Ui16);
	wchar_t* getBuffer();
	void flush();
	short getWidth();
	short getHeight();
	void text(short x, short y, const char* text, unsigned short color = 7Ui16);
	void text(short y, const char* text, unsigned short color = 7Ui16);
	void input(bool* shouldClose);
	void overlay(Profiler* profiler);
};
