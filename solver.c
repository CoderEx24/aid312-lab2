#include <stdlib.h>
#include "solver.h"

Domains domains_init()
{
    Domains domains = (bool**) malloc(81 * sizeof(bool*)); 
    for (size_t i = 0; i < 81; i ++)
    {  
        domains[i] = (bool*) malloc(9 * sizeof(bool));

        for (size_t j = 0; j < 9; j ++)
            domains[i][j] = true;
    }
    return domains;
}

void domains_free(Domains this)
{
    for (size_t i = 0; i < 81; i ++)
        free(this[i]);

    free(this);
}


