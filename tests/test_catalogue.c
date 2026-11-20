#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "regles.h"

/* vérifie que deux règles sont identiques (nom, mode, naissance, survie) */
static int memes_regles(const Regles *a, const Regles *b)
{
    if (strcmp(a->nom, b->nom) != 0 || a->mode != b->mode)
        return 0;
    for (int n = 0; n <= 8; n++)
        if (a->naissance[n] != b->naissance[n] || a->survie[n] != b->survie[n])
            return 0;
    return 1;
}

int main(void)
{
    int nb = 0;
    const Regles *cat = catalogue_regles(&nb);

    /* Test 1 : 7 règles : les 6 premières en mode vie, la 7e proies/prédateurs */
    assert(nb == 7);
    for (int i = 0; i < 6; i++)
        assert(cat[i].mode == MODE_VIE);
    assert(cat[6].mode == MODE_PROIES_PREDATEURS);
    assert(strcmp(cat[6].nom, "Proies-Predateurs") == 0);
    assert(cat[6].seuil_predation == 2 && cat[6].pred_energie_init == 4);

    /* Test 2 : Conway reste la première (B3/S23) */
    assert(strcmp(cat[0].nom, "Conway (B3/S23)") == 0);
    assert(cat[0].naissance[3] == 1 && cat[0].naissance[6] == 0);
    assert(cat[0].survie[2] == 1 && cat[0].survie[3] == 1 && cat[0].survie[4] == 0);

    /* Test 3 : HighLife fait naître avec 6 voisins */
    assert(strcmp(cat[1].nom, "HighLife (B36/S23)") == 0);
    assert(cat[1].naissance[6] == 1);

    /* Test 4 : Seeds, aucune survie */
    for (int n = 0; n <= 8; n++)
        assert(cat[2].survie[n] == 0);

    /* Test 5 : Life without Death, survie avec 0 à 8 voisins */
    for (int n = 0; n <= 8; n++)
        assert(cat[5].survie[n] == 1);

    /* Test 6 : un 2e appel renvoie le même catalogue */
    int nb2 = 0;
    assert(catalogue_regles(&nb2) == cat && nb2 == 7);
    assert(catalogue_regles(NULL) == cat);

    /* Test 7 : chaque fichier de regles/ donne la même règle que le catalogue */
    const char *fichiers[6] = {
        "regles/conway.txt", "regles/highlife.txt", "regles/seeds.txt",
        "regles/day_night.txt", "regles/maze.txt", "regles/life_without_death.txt"
    };
    for (int i = 0; i < 6; i++) {
        Regles r;
        assert(charger_regles_fichier(&r, fichiers[i]) == 0);
        assert(memes_regles(&r, &cat[i]));
    }

    printf("Tous les tests du catalogue sont OK\n");
    return 0;
}