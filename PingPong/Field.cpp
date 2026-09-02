#include "Field.h"

Field::Field(int w, int h) : buffer(static_cast<size_t>(w) * h, false), width(w), height(h)
{
}

void Field::clear()
{
    buffer.assign(buffer.size(), false);
}

void Field::fill()
{
    buffer.assign(buffer.size(), true);
}

void Field::set(int x, int y, bool v)
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
        buffer[static_cast<size_t>(x) + static_cast<size_t>(y) * width] = v;
    }
}

bool Field::get(int x, int y) const
{
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return false; // outside the field counts as empty instead of reading out of bounds
    }
    return buffer[static_cast<size_t>(x) + static_cast<size_t>(y) * width];
}
