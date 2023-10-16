#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include <stddef.h>

typedef unsigned short* Grid;

Grid grid_init();
bool grid_attemp_placement(Grid, size_t, size_t, int);
void grid_free(Grid);

#endif

