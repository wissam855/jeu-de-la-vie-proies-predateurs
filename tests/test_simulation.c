#include <stdio.h>
#include <assert.h>
#include "grille.h"
#include "simulation.h"
#include "regles.h"

/* place une proie en (i, j) */
static void poser(Grille *g, int i, int j)
{
    g->cases[i][j].type = PROIE;
}

int main(void)
{
    int nb;
    const Regles *conway = catalogue_regles(&nb);
    Grille *a = creer_grille(6, 6);
    Grille *b = creer_grille(6, 6);
    assert(a != NULL && b != NULL);

    /* Test 1 : le bloc 2x2 ne bouge pas */
    poser(a, 1, 1); poser(a, 1, 2); poser(a, 2, 1); poser(a, 2, 2);
    etape_suivante(a, b, conway, 0);
    assert(calculer_stats(b, 1).nb_proies == 4);
    assert(b->cases[1][1].type == PROIE && b->cases[2][2].type == PROIE);

    /* Test 2 : le clignotant passe de horizontal à vertical, puis revient */
    vider_grille(a);
    poser(a, 2, 1); poser(a, 2, 2); poser(a, 2, 3);
    etape_suivante(a, b, conway, 0);
    assert(b->cases[1][2].type == PROIE);
    assert(b->cases[2][2].type == PROIE);
    assert(b->cases[3][2].type == PROIE);
    assert(b->cases[2][1].type == VIDE);
    assert(calculer_stats(b, 1).nb_proies == 3);
    etape_suivante(b, a, conway, 0);
    assert(a->cases[2][1].type == PROIE && a->cases[2][3].type == PROIE);

    /* Test 3 : une cellule seule meurt */
    vider_grille(a);
    poser(a, 3, 3);
    etape_suivante(a, b, conway, 0);
    assert(calculer_stats(b, 1).nb_proies == 0);

    /* Test 4 : calculer_stats garde le numéro de génération */
    Stats s = calculer_stats(b, 42);
    assert(s.generation == 42 && s.nb_predateurs == 0);

    detruire_grille(a);
    detruire_grille(b);
    printf("Tous les tests de simulation sont OK\n");
    return 0;
}
