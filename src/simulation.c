#include <stddef.h>
#include "simulation.h"
#include "grille.h"

void etape_suivante(const Grille *actuelle, Grille *suivante, const Regles *r, int tore)
{
    if (actuelle == NULL || suivante == NULL || r == NULL)
        return;
    if (actuelle->lignes != suivante->lignes || actuelle->colonnes != suivante->colonnes)
        return;

    /* on LIT seulement "actuelle" et on ÉCRIT seulement dans "suivante" :
       toutes les cellules changent en même temps */
    for (int i = 0; i < actuelle->lignes; i++)
        for (int j = 0; j < actuelle->colonnes; j++) {
            Voisinage v = compter_voisins(actuelle, i, j, tore);
            suivante->cases[i][j] = appliquer_regle(actuelle->cases[i][j], v, r);
        }
}

Stats calculer_stats(const Grille *g, int generation)
{
    Stats s = { generation, 0, 0 };
    if (g == NULL)
        return s;
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++) {
            if (g->cases[i][j].type == PROIE)
                s.nb_proies++;
            else if (g->cases[i][j].type == PREDATEUR)
                s.nb_predateurs++;
        }
    return s;
}
