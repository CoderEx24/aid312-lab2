#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>

typedef bool** Domains;

Domains domains_init();
void domains_free(Domains);

#endif

