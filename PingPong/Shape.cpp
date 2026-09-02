#include "Shape.h"

void Shape::fill(int bitmap)
{
    int j = 0;
    for (int i = 1 << 15; j < 16; i = i / 2) {
        bool v = bitmap & i;
        buffer[j] = v;
        j++;
    }
}

bool Shape::get(int x, int y) const
{
    if (x < 0 || x >= 4 || y < 0 || y >= 4) {
        return false;
    }
    return buffer[static_cast<size_t>(x) + static_cast<size_t>(y) * 4];
}
