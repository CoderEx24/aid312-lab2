#include <raylib.h>
#include "grid.h"
#include "solver.h"

#define WIDTH  900
#define HEIGHT 900

int main()
{
    InitWindow(WIDTH, HEIGHT, "Sudoku");
    int x = 2, y = 0;
    Grid grid = grid_init();
    Domains domains = domains_init();
    
    bool result = ac3(grid, domains);

    TraceLog(LOG_INFO, "result is %i", result);

/*    for (int i = 0; i < 9; i ++)
    {
        for (int j = 0; j < 9; j ++)
        {
            TraceLog(LOG_INFO, "Domain of (%i, %i):-\n", i, j);

            for (int k = 0; k < 9; k ++)
                if (domains[j + i * 9][k])
                    TraceLog(LOG_INFO, "\b\t%i", k + 1);
        }
    }
*/
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
                      -20 + WIDTH / 9, 
                      -20 + HEIGHT / 9, YELLOW);

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

        if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_H))
            x = (x + 8) % 9;
        else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_K))
            y = (y + 8) % 9;
        else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_L))
            x = (x + 1) % 9;
        else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_J))
            y = (y + 1) % 9;

        const int numbers[] = { KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_FIVE, KEY_SIX, KEY_SEVEN, KEY_EIGHT, KEY_NINE, };

        for (size_t i = 0; i < 9; i ++)
            if (IsKeyPressed(numbers[i]))
                grid_attempt_placement(grid, x, y, i + 1);
    }

    CloseWindow();

}

