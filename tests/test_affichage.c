#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "affichage.h"
#include "regles.h"

int main(void)
{
    char bs[32];
    int nb = 0;
    const Regles *cat = catalogue_regles(&nb);

    /* Test 1 : les 6 règles du catalogue redonnent leur notation */
    const char *attendu[6] = { "B3/S23", "B36/S23", "B2/S",
                               "B3678/S34678", "B3/S12345", "B3/S012345678" };
    assert(nb == 6);
    for (int i = 0; i < 6; i++) {
        notation_bs(&cat[i], bs, (int)sizeof bs);
        assert(strcmp(bs, attendu[i]) == 0);
    }

    /* Test 2 : aller-retour avec regles_depuis_chaine (N6) */
    Regles r;
    assert(regles_depuis_chaine(&r, "Ma regle", "B1357/S02468") == 0);
    notation_bs(&r, bs, (int)sizeof bs);
    assert(strcmp(bs, "B1357/S02468") == 0);

    /* Test 3 : ni naissance ni survie -> "B/S" */
    assert(regles_depuis_chaine(&r, "Vide", "B/S") == 0);
    notation_bs(&r, bs, (int)sizeof bs);
    assert(strcmp(bs, "B/S") == 0);

    /* Test 4 : buffer trop petit -> coupé proprement, sans débordement */
    char petit[4];
    notation_bs(&cat[0], petit, (int)sizeof petit);
    assert(strcmp(petit, "B3/") == 0);

    /* Test 5 : mode proies/prédateurs et règle NULL */
    Regles pp;
    memset(&pp, 0, sizeof pp);
    pp.mode = MODE_PROIES_PREDATEURS;
    notation_bs(&pp, bs, (int)sizeof bs);
    assert(strcmp(bs, "proies/predateurs") == 0);
    notation_bs(NULL, bs, (int)sizeof bs);
    assert(bs[0] == '\0');

    printf("Tous les tests d'affichage sont OK\n");
    return 0;
}
