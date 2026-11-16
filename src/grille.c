#include <stdlib.h>
#include "grille.h"

Grille *creer_grille(int lignes, int colonnes)
{
    /* 1. tailles invalides */
    if (lignes <= 0 || colonnes <= 0)
        return NULL;

    /* 2. étage 1 : la structure */
    Grille *g = malloc(sizeof(Grille));
    if (g == NULL)
        return NULL;

    /* 3. remplir les tailles */
    g->lignes = lignes;
    g->colonnes = colonnes;

    /* 4. étage 2 : un pointeur par ligne */
    g->cases = malloc(lignes * sizeof(Cellule *));
    if (g->cases == NULL) {
        free(g);
        return NULL;
    }

    /* 5. étage 3 : chaque ligne de cellules */
    for (int i = 0; i < g->lignes; i++) {
        g->cases[i] = calloc(g->colonnes, sizeof(Cellule));
        if (g->cases[i] == NULL) {
            /* 6. échec : on libère tout ce qui a déjà été alloué */
            for (int k = 0; k < i; k++)
                free(g->cases[k]);
            free(g->cases);
            free(g);
            return NULL;
        }
    }

    /* 7. tout a marché */
    return g;
}



void detruire_grille(Grille *g)
{
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++)
        free(g->cases[i]);
    free(g->cases);
    free(g);
}


void vider_grille(Grille *g)
{
    /* chaque case : type VIDE, energie 0, age 0 */
}

void copier_grille(const Grille *src, Grille *dst)
{
    /* tailles différentes -> rien ; sinon copier case par case */
}
