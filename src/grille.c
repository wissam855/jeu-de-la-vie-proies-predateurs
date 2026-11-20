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
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++) {
            g->cases[i][j].type = VIDE;
            g->cases[i][j].energie = 0;
            g->cases[i][j].age = 0;
        }
}

void copier_grille(const Grille *src, Grille *dst)
{
    if (src == NULL || dst == NULL)
        return;
    if (src->lignes != dst->lignes || src->colonnes != dst->colonnes)
        return;
    for (int i = 0; i < src->lignes; i++)
        for (int j = 0; j < src->colonnes; j++)
            dst->cases[i][j] = src->cases[i][j];
}


void remplir_aleatoire(Grille *g, double p_proie, double p_predateur)
{
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++) {
            double x = rand() / (RAND_MAX + 1.0); /* nombre entre 0 (inclus) et 1 (exclu) */
            Cellule c = { VIDE, 0, 0 };
            if (x < p_proie)
                c.type = PROIE;
            else if (x < p_proie + p_predateur)
                c.type = PREDATEUR;
            g->cases[i][j] = c;
        }
}

Voisinage compter_voisins(const Grille *g, int i, int j, int tore)
{
    Voisinage v = { 0, 0 };
    if (g == NULL)
        return v;
    for (int di = -1; di <= 1; di++)
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0)
                continue; /* on ne compte pas la case elle-même */
            int x = i + di;
            int y = j + dj;
            if (tore) {
                /* les bords se rejoignent */
                x = (x + g->lignes) % g->lignes;
                y = (y + g->colonnes) % g->colonnes;
            } else if (x < 0 || x >= g->lignes || y < 0 || y >= g->colonnes) {
                continue; /* hors de la grille : on ignore */
            }
            if (g->cases[x][y].type == PROIE)
                v.nb_proies++;
            else if (g->cases[x][y].type == PREDATEUR)
                v.nb_predateurs++;
        }
    return v;
}

void initialiser_predateurs(Grille *g, int energie)
{
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++)
            if (g->cases[i][j].type == PREDATEUR) {
                g->cases[i][j].energie = energie;
                g->cases[i][j].age = 0;
            }
}
