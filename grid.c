#include "grid.h"
#include <stdlib.h>
#include <time.h>

Grid grid_init()
{
    srand(time(0));

    int n_blocks = rand() % 81;

    Grid grid = (Grid) malloc(81 * sizeof(unsigned short));
    for (size_t i = 0; i < 81; i ++)
        grid[i] = 0;

    for (size_t i = 0; i < n_blocks; i ++)
    {
        int random_x = rand() % 9;
        int random_y = rand() % 9;
        int random_number = rand() % 9 + 1;

        grid_attempt_placement(grid, random_x, random_y, random_number);
    }

    return grid;
}

bool grid_attempt_placement(Grid grid, size_t x, size_t y, int number)
{
    // check row
    for (size_t i = 0; i < 9; i ++)
        if (grid[i + y * 9] == number && i != x)
            return false;

    // check column
    for (size_t j = 0; j < 9; j ++)
        if (grid[x + j * 9] == number && j != y)
            return false;

    // check block
    for (size_t i = 0; i < 3; i ++)
        for (size_t j = 0; j < 3; j ++)
            if (grid[(3 * (x / 3) + i) + (3 * (y / 3) + j) * 9] == number && (x / 3 + i) + (y / 3 + j) * 9 != x + y * 9)
                return false;

    grid[x + y * 9] = number;
    return true;
}

void grid_free(Grid grid)
{
    free(grid);
}

