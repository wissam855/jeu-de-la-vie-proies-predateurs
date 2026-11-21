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

int main(void)
{
    Parametres p;
    parametres_par_defaut(&p);
    assert(p.exporter == 0);                 /* pas d'export par défaut */

    /* Test 1 : choix 11 -> l'export passe à oui */
    simuler_clavier("11\n0\n");
    assert(menu_principal(&p) == 1);
    assert(p.exporter == 1);

    /* Test 2 : choix 11 une deuxième fois -> retour à non */
    simuler_clavier("11\n0\n");
    assert(menu_principal(&p) == 1);
    assert(p.exporter == 0);

    /* Test 3 : 12 n'existe pas -> refusé, le menu redemande, puis 0 */
    simuler_clavier("12\n0\n");
    assert(menu_principal(&p) == 1);
    assert(p.exporter == 0);

    fclose(stdin);                /* sous Windows, un fichier ouvert ne peut pas etre supprime */
    remove("test_saisie.txt");
    printf("\nTous les tests du menu export sont OK\n");
    return 0;
}