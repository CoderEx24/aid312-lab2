#include <raylib.h>

int main()
{
    InitWindow(600, 600, "Sudoku");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawLine(0, 0, 600, 600, PINK);

        EndDrawing();
    }

    CloseWindow();

}

