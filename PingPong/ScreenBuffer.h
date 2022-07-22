#pragma once
#include <Windows.h>
#include <string>
#include <chrono>
#include <thread>
#include "Profiler.h"

class ScreenBuffer
{
private:
	int width = -1;
	int height = -1;
	wchar_t* buffer;
	bool debug, vsync;
	HANDLE hConsole;
	DWORD dwBytesWritten = 0;
public:
	ScreenBuffer();
	void clear();
	void clear(wchar_t value);
	void set(int x, int y, wchar_t value);
	void rect(int x, int y, int w, int h);
	void fillRect(int x, int y, int w, int h, wchar_t value);
	wchar_t* getBuffer();
	void flush();
	int getWidth();
	int getHeight();
	void text(int x, int y, std::string text);
	void text(int y, std::string text);
	bool input();
	void overlay(Profiler* profiler);
};

