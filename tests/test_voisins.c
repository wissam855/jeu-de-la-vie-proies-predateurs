#include <stdio.h>
#include <assert.h>
#include "grille.h"

int main(void)
{
    Grille *g = creer_grille(5, 5);
    assert(g != NULL);

    /* Test 1 : grille vide -> 0 voisin */
    Voisinage v = compter_voisins(g, 2, 2, 0);
    assert(v.nb_proies == 0 && v.nb_predateurs == 0);

    /* Test 2 : 3 proies et 1 prédateur autour du centre */
    g->cases[1][1].type = PROIE;
    g->cases[1][2].type = PROIE;
    g->cases[3][3].type = PROIE;
    g->cases[2][1].type = PREDATEUR;
    g->cases[2][2].type = PROIE; /* la case elle-même ne compte pas */
    v = compter_voisins(g, 2, 2, 0);
    assert(v.nb_proies == 3);
    assert(v.nb_predateurs == 1);

    /* Test 3 : coin sans tore -> le coin opposé n'est pas voisin */
    vider_grille(g);
    g->cases[4][4].type = PROIE;
    v = compter_voisins(g, 0, 0, 0);
    assert(v.nb_proies == 0);

    /* Test 4 : avec tore, le coin opposé devient voisin */
    v = compter_voisins(g, 0, 0, 1);
    assert(v.nb_proies == 1);

    /* Test 5 : remplissage à 100 % de proies */
    remplir_aleatoire(g, 1.0, 0.0);
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++)
            assert(g->cases[i][j].type == PROIE);

    /* Test 6 : remplissage à 0 % -> tout est vide */
    remplir_aleatoire(g, 0.0, 0.0);
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++)
            assert(g->cases[i][j].type == VIDE);

    detruire_grille(g);
    printf("Tous les tests de voisinage sont OK\n");
    return 0;
}
