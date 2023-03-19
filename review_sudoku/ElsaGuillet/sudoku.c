#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

void initialize_empty_board(Board grid)
{
    return;
}

int *create_array(size)
{
    int *new_tab;

    new_tab = (int *)malloc((size + 1) * sizeof(int));
    if (new_tab == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    int i;
    for (i = 0; i < size; i++)
    {
        new_tab[i] = -1;
    }

    new_tab[size] = -1;
    return new_tab;
}

int is_value_correct(Board grid, int ligne, int colonne, int value)
{
	int i,j;
    /* Test ligne et colonne */
    for (i = 0; i <= 9; i++)
    {
        if (grid[ligne][i] == value)
        {
            return 0;
        }
        if (grid[i][colonne] == value)
        {
            return 0;
        }
    }
    /* Test carré */
    int subLigne = ligne / 3;
    int subColonne = colonne / 3;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (grid[i + (subLigne * 3)][j + (subColonne * 3)] == value)
            {
                return 0;
            }
        }
    }
    return 1;
}

int is_grid_correct(Board grid)
{
    int i;
    int j;
    int l = 0;
    int m;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            int valeur = grid[i][j];

            if (valeur == 0)
            {
                return 0;
            }

            /* Test colonne */
            for (l = 0; l < 9; l++)
            {
                if ((grid[l][j] == valeur) && (l != i))
                {
                    return 0;
                }
            }

            /* Test ligne */
            for (l = 0; l < 9; l++)
            {
                if ((grid[i][l] == valeur) && (l != j))
                {
                    return 0;
                }
            }

            /* Test carré */
            int subLigne = i / 3;
            int subColonne = j / 3;

            for (l = 0; l < 3; l++)
            {
                for (m = 0; m < 3; m++)
                {
                    if (grid[l + (subLigne * 3)][m + (subColonne * 3)] == valeur && i != (l + (subLigne * 3)) && j != (m + (subColonne * 3)))
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

void print_board(Board grid)
{
    int i;
    printf("-------------------------------------\n");
    for (i = 0; i < 9; i++)
    {
        printf("| ");
        int j;
        for (j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0)
            {
                printf(" ");
            }
            else
            {
                printf("%d", grid[i][j]);
            }
            printf(" | ");
        }
        printf("\n");
        printf("-------------------------------------\n");
    }
    return;
}
