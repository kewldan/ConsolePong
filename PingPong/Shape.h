#pragma once
#include <iostream>
class Shape
{
private:
	bool* buffer;
public:
	Shape();
	void fill(int bitmap);
	bool get(int x, int y);
};

