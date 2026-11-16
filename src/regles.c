#include <stddef.h>
#include "regles.h"

/* Le catalogue : pour l'instant une seule règle, Conway (B3/S23). */
static const Regles CATALOGUE[] = {
    {
        .nom = "Conway (B3/S23)",
        .mode = MODE_VIE,
        /*            voisins : 0  1  2  3  4  5  6  7  8 */
        .naissance =          { 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        .survie =             { 0, 0, 1, 1, 0, 0, 0, 0, 0 },
    },
};

const Regles *catalogue_regles(int *nb)
{
    if (nb != NULL)
        *nb = (int)(sizeof(CATALOGUE) / sizeof(CATALOGUE[0]));
    return CATALOGUE;
}

Cellule appliquer_regle(Cellule c, Voisinage v, const Regles *r)
{
    Cellule res = c;
    int n = v.nb_proies;

    if (r == NULL || n < 0 || n > 8)
        return res;

    if (r->mode == MODE_VIE) {
        if (c.type == PROIE) {
            if (r->survie[n]) {
                res.age = c.age + 1;
            } else {
                res.type = VIDE;
                res.energie = 0;
                res.age = 0;
            }
        } else {
            if (r->naissance[n]) {
                res.type = PROIE;
                res.energie = 0;
                res.age = 0;
            } else {
                res.type = VIDE;
            }
        }
    }
    return res;
}