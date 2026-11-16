#include <stdio.h>
#include <assert.h>
#include "grille.h"

int main(void)
{
    /* Test 1 : création d'une grille 5 x 8 */
    Grille *a = creer_grille(5, 8);
    assert(a != NULL);
    assert(a->lignes == 5);
    assert(a->colonnes == 8);

    /* Test 2 : toutes les cases sont VIDE au départ (grâce à calloc) */
    for (int i = 0; i < a->lignes; i++)
        for (int j = 0; j < a->colonnes; j++)
            assert(a->cases[i][j].type == VIDE);

    /* Test 3 : on met une proie en [2][3] et on copie dans une 2e grille */
    a->cases[2][3].type = PROIE;
    Grille *b = creer_grille(5, 8);
    assert(b != NULL);
    copier_grille(a, b);
    assert(b->cases[2][3].type == PROIE);

    /* Test 4 : vider_grille remet tout à VIDE */
    vider_grille(a);
    assert(a->cases[2][3].type == VIDE);

    /* Test 5 : une taille invalide renvoie NULL */
    assert(creer_grille(0, 5) == NULL);

    detruire_grille(a);
    detruire_grille(b);
    printf("Tous les tests de grille sont OK\n");
    return 0;
}
