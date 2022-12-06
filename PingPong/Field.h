#pragma once
#include <iostream>

class Field
{
	bool* buffer;
	int width, height;
public:
	Field(int w, int h);
	void clear();
	void fill();
	void set(int x, int y, bool v);
	bool get(int x, int y);
};

