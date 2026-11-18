#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "regles.h"

int main(void)
{
    Regles r;

    /* Test 1 : "B3/S23" donne exactement Conway */
    assert(regles_depuis_chaine(&r, "Conway", "B3/S23") == 0);
    assert(r.mode == MODE_VIE);
    assert(strcmp(r.nom, "Conway") == 0);
    for (int n = 0; n <= 8; n++) {
        assert(r.naissance[n] == (n == 3));
        assert(r.survie[n] == (n == 2 || n == 3));
    }

    /* Test 2 : HighLife "B36/S23" : naissance aussi à 6 voisins */
    assert(regles_depuis_chaine(&r, "HighLife", "B36/S23") == 0);
    assert(r.naissance[3] == 1 && r.naissance[6] == 1 && r.naissance[2] == 0);
    Cellule vide = { VIDE, 0, 0 };
    Voisinage v = { 6, 0 };
    assert(appliquer_regle(vide, v, &r).type == PROIE);

    /* Test 3 : minuscules acceptées, nom par défaut = la chaîne */
    assert(regles_depuis_chaine(&r, NULL, "b2/s") == 0);
    assert(strcmp(r.nom, "b2/s") == 0);
    assert(r.naissance[2] == 1);
    for (int n = 0; n <= 8; n++)
        assert(r.survie[n] == 0);

    /* Test 4 : chaînes incorrectes -> -1, et r n'est pas modifiée */
    assert(regles_depuis_chaine(&r, "Conway", "B3/S23") == 0);
    assert(regles_depuis_chaine(&r, "x", "3/23") == -1);     /* pas de B */
    assert(regles_depuis_chaine(&r, "x", "B3S23") == -1);    /* pas de / */
    assert(regles_depuis_chaine(&r, "x", "B9/S23") == -1);   /* 9 voisins impossible */
    assert(regles_depuis_chaine(&r, "x", "B3/S23z") == -1);  /* caractère en trop */
    assert(regles_depuis_chaine(&r, "x", NULL) == -1);
    assert(strcmp(r.nom, "Conway") == 0);                    /* toujours Conway */

    printf("Tous les tests de lecture B/S sont OK\n");
    return 0;
}