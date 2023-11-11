#include <stdlib.h>
#include <glib.h>
#include "solver.h"
#include <raylib.h>

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

size_t domains_size(Domains this, size_t xi)
{
    size_t count = 0;

    for (size_t i = 0; i < 9; i ++)
        if (this[xi][i]) count ++;

    return count;
}

void domains_free(Domains this)
{
    for (size_t i = 0; i < 81; i ++)
        free(this[i]);

    free(this);
}

// -xi-|-xj-
// XXXX XXXX
bool ac3(Grid problem, Domains domains)
{
    GQueue queue = G_QUEUE_INIT;

    // initiate the queue
    for (size_t square = 0; square < 81; square ++)
    {
        int xi = square << 4;

        // add variables in the same row

        for (int i = 0; i < 9; i ++)
        {
            // skip current square
            if (square % 9 == i) continue;

            g_queue_push_tail(&queue, GINT_TO_POINTER(xi | ((square / 9 + i) & 0xf)));
        }

        // add variables in the same column

        for (int i = 0; i < 9; i ++)
        {
            // skip current square
            if (square / 9 == i) continue;
            
            g_queue_push_tail(&queue, GINT_TO_POINTER(xi | ((9 * i + square % 9) & 0xf)));
        }

        // add variables in the same block 

        int square_block_x = (square / 9) / 3,
            square_block_y = (square % 9) / 3;
        
        for (int i = 0; i < 3; i ++)
            for (int j = 0; j < 3; j ++)
            {
                int other = (3 * square_block_x + i) + 9 * (3 * square_block_y + j);
                if (other == square)
                    continue;

                g_queue_push_tail(&queue, GINT_TO_POINTER(xi | (other & 0xf)));
            }
    }

    TraceLog(LOG_INFO, "Queue size %i", g_queue_get_length(&queue));
    while (!g_queue_is_empty(&queue))
    {
        int pair = GPOINTER_TO_INT(g_queue_pop_head(&queue));

        int xi = pair >> 4, xj = pair & 0xf;

        TraceLog(LOG_INFO, "Processing %04x (%i, %i): %i & (%i, %i): %i", 
                pair, xi / 9, xi % 9, problem[xi], xj / 9, xj % 9, problem[xj]);

        if (revise(problem, domains, xi, xj))
        {
            if (domains_size(domains, xi) == 0)
                return false;
            
            // row
            for (int i = 0; i < 9; i ++)
            {
                if (xi % 9 == i) continue;

                g_queue_push_tail(&queue, GINT_TO_POINTER(((9 * (xi / 9) + i) << 4) | xi));
            }

            // column
            for (int i = 0; i < 9; i ++)
            {
                if (xi / 9 == i) continue;

                g_queue_push_tail(&queue, GINT_TO_POINTER(((9 * i + (xi % 9)) << 4) | xi));
            }

            // block

            int xi_block_x = (xi / 9) / 3,
                xi_block_y = (xi / 9) % 3;

            for (int i = 0; i < 3; i ++)
                for (int j = 0; j < 3; j ++)
                {
                    int xk = (3 * xi_block_x + i) + 9 * (3 * xi_block_y + j);

                    if (xk == xi) continue;

                    g_queue_push_tail(&queue, GINT_TO_POINTER( (xk << 4) | xi));
                }

        }
    }

    return true;
}

bool revise(Grid problem, Domains domains, size_t xi, size_t xj)
{
    if (!check_constrainted(xi, xj))
        return false;

    bool revised = false;
    for (size_t i = 0; i < 9; i ++)
    {
        bool constraint_can_be_satisfied = false;
        if (!domains[xi][i]) continue;

        for (size_t j = 0; j < 9; j ++)
        {
            if (!domains[xj][j]) continue;

            if (i != j)
            {
                constraint_can_be_satisfied = true;
                break;
            }

        }

        if (!constraint_can_be_satisfied)
        {
            domains[xi][i] = false;
            revised = true;

            TraceLog(LOG_INFO, "Invalidating %i from (%i, %i)", i + 1, xi / 9, xi % 9);
        }

    }

    return revised;
}

bool check_constrainted(size_t xi, size_t xj)
{
    size_t x_xi = xi / 9, y_xi = xi % 9, x_xj = xj / 9, y_xj = xj % 9;
    size_t x_block_i = x_xi / 3, y_block_i = y_xi / 3,
        x_block_j = x_xj / 3, y_block_j = y_xj / 3;

    bool on_same_row = x_xi == x_xj;
    bool on_same_column = y_xi == y_xj;
    bool on_same_block = x_block_i == x_block_j && y_block_i == y_block_j;

    return on_same_row || on_same_column || on_same_block;
}

