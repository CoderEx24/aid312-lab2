#include "grid.h"
#include <stdlib.h>

Grid grid_init()
{
    Grid grid = (Grid) malloc(81 * sizeof(unsigned short));
    for (size_t i = 0; i < 81; i ++)
        grid[i] = 0;

    return grid;
}

bool grid_attempt_placement(Grid grid, size_t x, size_t y, int number)
{
    // check row
    for (size_t i = 0; i < 9; i ++)
        if (grid[i + y * 9] == number)
            return false;

    // check column
    for (size_t j = 0; j < 9; j ++)
        if (grid[x + j * 9] == number)
            return false;

    // check block
    for (size_t i = 0; i < 3; i ++)
        for (size_t j = 0; j < 3; j ++)
            if (grid[(x / 3 + i) + (y / 3 + j) * 9] == number)
                return false;

    grid[x + y * 9] = number;
    return true;
}

void grid_free(Grid grid)
{
    free(grid);
}

