#include <stdio.h>
#include <assert.h>
#include "regles.h"

int main(void)
{
    int nb;
    const Regles *conway = catalogue_regles(&nb);

    /* Le catalogue contient au moins une règle : Conway */
    assert(nb >= 1);
    assert(conway->mode == MODE_VIE);

    Cellule vide  = { VIDE, 0, 0 };
    Cellule proie = { PROIE, 0, 0 };
    Voisinage v = { 0, 0 };

    for (int n = 0; n <= 8; n++) {
        v.nb_proies = n;

        /* 9 cas : une case vide naît seulement avec 3 voisins */
        Cellule a = appliquer_regle(vide, v, conway);
        if (n == 3)
            assert(a.type == PROIE);
        else
            assert(a.type == VIDE);

        /* 9 cas : une cellule vivante survit seulement avec 2 ou 3 voisins */
        Cellule b = appliquer_regle(proie, v, conway);
        if (n == 2 || n == 3)
            assert(b.type == PROIE);
        else
            assert(b.type == VIDE);
    }

    printf("Les 18 cas de Conway sont OK\n");
    return 0;
}