#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>
#include "grid.h"

typedef bool** Domains;

Domains domains_init();
size_t domains_size(Domains, size_t);
void domains_free(Domains);

bool search_by_backtracking(Grid);
bool ac3(Grid, Domains);
bool revise(Grid, Domains, size_t, size_t);
bool check_constrainted(size_t, size_t);

#endif

