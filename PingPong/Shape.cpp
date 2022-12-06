#include "Shape.h"

Shape::Shape()
{
    buffer = new bool[16];
    std::fill_n(buffer, 17, false);
}

void Shape::fill(int bitmap)
{
    int j = 0;
    for (int i = 1 << 15; j < 16; i = i / 2) {
        bool v = bitmap & i;
        buffer[j] = v;
        j++;
    }
}

bool Shape::get(int x, int y)
{
    return buffer[x + y * 4];
}
