#include "Field.h"

Field::Field(int w, int h) : width(w), height(h)
{
    buffer = new bool[w * h];
    clear();
}

void Field::clear()
{
    memset(buffer, false, width * height);
}

void Field::fill()
{
    memset(buffer, true, width * height);
}

void Field::set(int x, int y, bool v)
{
    buffer[x + y * width] = v;
}

bool Field::get(int x, int y)
{
    return buffer[x + y * width];
}
