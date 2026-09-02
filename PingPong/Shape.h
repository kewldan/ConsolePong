#pragma once
#include <array>
class Shape
{
private:
	std::array<bool, 16> buffer{}; // 4x4 bitmap, row-major
public:
	Shape() = default;
	void fill(int bitmap);
	bool get(int x, int y) const;
};
