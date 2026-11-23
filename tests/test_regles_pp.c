#include <stdio.h>
#include <assert.h>
#include "regles.h"

/* fabrique une cellule et un voisinage en une ligne */
static Cellule cel(TypeCellule t, int energie, int age)
{
    Cellule c = { t, energie, age };
    return c;
}

static Voisinage vois(int proies, int predateurs)
{
    Voisinage v = { proies, predateurs };
    return v;
}

int main(void)
{
    int nb;
    const Regles *r = &catalogue_regles(&nb)[6];   /* la 7e règle */
    assert(r->mode == MODE_PROIES_PREDATEURS);
    Cellule res;

    /* Les cas ci-dessous sont écrits pour seuil_predation = 2 et une énergie
       de départ de 4 : on fixe ces valeurs ici pour que le test ne dépende
       pas du réglage final du catalogue (T3.8). */
    Regles ref = *r;
    ref.seuil_predation = 2;
    ref.pred_energie_init = 4;
    r = &ref; 

    /* Les six cas de E7 (valeurs du plan : naissance 2-3, survie 1-5,
       seuil 2, énergie 4, gain 2, âge maximal 15) */

    /* 1. case vide, 2 proies, 0 prédateur -> proie */
    res = appliquer_regle(cel(VIDE, 0, 0), vois(2, 0), r);
    assert(res.type == PROIE && res.age == 0);

    /* 2. case vide, 3 proies, 1 prédateur -> reste vide */
    res = appliquer_regle(cel(VIDE, 0, 0), vois(3, 1), r);
    assert(res.type == VIDE);

    /* 3. proie avec 2 prédateurs -> prédateur avec 4 d'énergie, âge 0 */
    res = appliquer_regle(cel(PROIE, 0, 7), vois(3, 2), r);
    assert(res.type == PREDATEUR && res.energie == 4 && res.age == 0);

    /* 4. proie sans aucune voisine -> meurt */
    res = appliquer_regle(cel(PROIE, 0, 3), vois(0, 0), r);
    assert(res.type == VIDE && res.age == 0);

    /* 5. prédateur à 1 d'énergie sans proie -> meurt */
    res = appliquer_regle(cel(PREDATEUR, 1, 2), vois(0, 0), r);
    assert(res.type == VIDE && res.energie == 0);

    /* 6. prédateur à 1 d'énergie avec une proie -> reste, 2 d'énergie */
    res = appliquer_regle(cel(PREDATEUR, 1, 2), vois(1, 0), r);
    assert(res.type == PREDATEUR && res.energie == 2 && res.age == 3);

    /* Cas en plus */

    /* 7. l'ordre : 2 prédateurs ET 0 proie -> mangée (pas morte d'isolement) */
    res = appliquer_regle(cel(PROIE, 0, 0), vois(0, 2), r);
    assert(res.type == PREDATEUR);

    /* 8. proie qui survit : son âge augmente */
    res = appliquer_regle(cel(PROIE, 0, 4), vois(2, 1), r);
    assert(res.type == PROIE && res.age == 5);

    /* 9. proie trop entourée (6 proies) -> meurt */
    res = appliquer_regle(cel(PROIE, 0, 0), vois(6, 0), r);
    assert(res.type == VIDE);

    /* 10. prédateur trop vieux (âge 15 -> 16 > 15) -> meurt, même s'il mange */
    res = appliquer_regle(cel(PREDATEUR, 5, 15), vois(3, 0), r);
    assert(res.type == VIDE);

    /* 11. prédateur d'âge 14 avec de l'énergie -> vit encore (âge 15) */
    res = appliquer_regle(cel(PREDATEUR, 5, 14), vois(0, 0), r);
    assert(res.type == PREDATEUR && res.energie == 4 && res.age == 15);

    /* 12. le mode vie ne change pas : Conway, case vide avec 3 voisines -> proie */
    res = appliquer_regle(cel(VIDE, 0, 0), vois(3, 0), &catalogue_regles(&nb)[0]);
    assert(res.type == PROIE);

    printf("Tous les tests des regles proies/predateurs sont OK\n");
    return 0;
}