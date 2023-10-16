#include <raylib.h>
#include "grid.h"

#define WIDTH  900
#define HEIGHT 900

int main()
{
    InitWindow(WIDTH, HEIGHT, "Sudoku");
    int x = 0, y = 0;
    Grid grid = grid_init();

    grid[3] = 2;
    grid[7] = 8;
    grid[12] = 1;

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);

        BeginDrawing();

        // draw grid
        for (int i = 0; i < 9; i ++)
        {
            DrawLine(WIDTH * i /  9, 0, WIDTH * i / 9, HEIGHT, BLACK);
            DrawLine(0, HEIGHT * i / 9, WIDTH, HEIGHT * i / 9, BLACK);
        }
        // draw selected square
        
        DrawRectangle(10 + WIDTH * x / 9, 
                      10 + HEIGHT * y / 9,
                      -20 + WIDTH * (x + 1) / 9, 
                      -20 + HEIGHT * (y + 1) / 9, YELLOW);

        // draw numbers

        const char *numbers_strings[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9" };

        for (size_t xx = 0; xx < 9; xx++)
            for (size_t yy = 0; yy < 9; yy++)
                if (grid[xx + yy * 9] != 0)
                    DrawText(numbers_strings[grid[xx + yy * 9] - 1], 
                             10 + WIDTH * xx / 9,
                             10 + HEIGHT * yy / 9,
                             100, BLACK);

        EndDrawing();
    }

    CloseWindow();

}

