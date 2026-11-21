#include <stdio.h>
#include <assert.h>
#include "menu.h"

/* Fait comme si l'utilisateur tapait "saisie" au clavier */
static void simuler_clavier(const char *saisie)
{
    FILE *f = fopen("test_saisie.txt", "w");
    assert(f != NULL);
    fputs(saisie, f);
    fclose(f);
    assert(freopen("test_saisie.txt", "r", stdin) != NULL);
}

/* compare deux réels à 0,001 près */
static int proche(double a, double b)
{
    return a - b < 0.001 && b - a < 0.001;
}

int main(void)
{
    Parametres p;
    parametres_par_defaut(&p);
    assert(proche(p.p_predateur, 0.0) && p.graine == 0);

    /* Test 1 : choix 5 -> 30 % de proies et 3 % de prédateurs, puis quitter */
    simuler_clavier("5\n30\n3\n0\n");
    assert(menu_principal(&p) == 1);
    assert(proche(p.p_proie, 0.30) && proche(p.p_predateur, 0.03));

    /* Test 2 : 90 % de proies -> 20 % de prédateurs est refusé (max 10),
       le menu redemande, puis 10 est accepté */
    simuler_clavier("5\n90\n20\n10\n0\n");
    assert(menu_principal(&p) == 1);
    assert(proche(p.p_proie, 0.90) && proche(p.p_predateur, 0.10));

    /* Test 3 : choix 10 -> graine 42 */
    simuler_clavier("10\n42\n0\n");
    assert(menu_principal(&p) == 1);
    assert(p.graine == 42);

    /* Test 4 : graine 0 = de nouveau aléatoire */
    simuler_clavier("10\n0\n0\n");
    assert(menu_principal(&p) == 1);
    assert(p.graine == 0);

    fclose(stdin);                /* sous Windows, un fichier ouvert ne peut pas etre supprime */
    remove("test_saisie.txt");
    printf("\nTous les tests du menu proies/predateurs sont OK\n");
    return 0;
}