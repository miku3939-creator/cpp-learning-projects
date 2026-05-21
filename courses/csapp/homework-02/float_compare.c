#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Q1答案
#define q1 1

// Q2答案
#define x1 0.0f
#define y1 7e-45f
#define x2 1048576.0f
#define y2 1048576.125f

// Q3: ULP比较函数
bool AlmostEqualULP(float x, float y)
{
    if (x == y)
        return true;

    int32_t nx, ny;
    memcpy(&nx, &x, sizeof(float));
    memcpy(&ny, &y, sizeof(float));

    if (nx < 0)
        nx = 0x80000000 - nx;
    if (ny < 0)
        ny = 0x80000000 - ny;

    int32_t distance = (nx > ny) ? (nx - ny) : (ny - nx);

    if (distance <= 5)
    {
        return true;
    }

    return false;
}
