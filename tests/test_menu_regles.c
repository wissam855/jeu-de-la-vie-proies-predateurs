#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "menu.h"

/* Fait comme si l'utilisateur tapait "saisie" au clavier :
   on écrit le texte dans un fichier, puis stdin lit ce fichier. */
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

    /* Test 1 : la règle par défaut est Conway, la 1re du catalogue */
    parametres_par_defaut(&p);
    assert(strcmp(p.regles.nom, "Conway (B3/S23)") == 0);
    assert(p.regles.naissance[3] == 1 && p.regles.survie[2] == 1);

    /* Test 2 : 9 -> catalogue -> règle n° 2 (HighLife), puis 0 = quitter */
    simuler_clavier("9\n1\n2\n0\n");
    assert(menu_principal(&p) == 1);
    assert(strcmp(p.regles.nom, "HighLife (B36/S23)") == 0);
    assert(p.regles.naissance[6] == 1);

    /* Test 3 : 9 -> fichier regles/seeds.txt, puis 0 */
    simuler_clavier("9\n2\nregles/seeds.txt\n0\n");
    assert(menu_principal(&p) == 1);
    assert(strcmp(p.regles.nom, "Seeds (B2/S)") == 0);

    /* Test 4 : 9 -> règle tapée B36/S23, puis 1 = lancer */
    simuler_clavier("9\n3\nB36/S23\n1\n");
    assert(menu_principal(&p) == 0);
    assert(strcmp(p.regles.nom, "B36/S23") == 0);
    assert(p.regles.naissance[6] == 1);

    /* Test 5 : règle invalide -> l'ancienne est gardée */
    simuler_clavier("9\n3\nZ12\n9\n2\nregles/nexiste_pas.txt\n0\n");
    assert(menu_principal(&p) == 1);
    assert(strcmp(p.regles.nom, "B36/S23") == 0);

    /* Test 6 : 9 puis 0 = retour, rien ne change */
    simuler_clavier("9\n0\n0\n");
    assert(menu_principal(&p) == 1);
    assert(strcmp(p.regles.nom, "B36/S23") == 0);

    
    fclose(stdin);
    remove("test_saisie.txt");
    printf("\nTous les tests du menu des regles sont OK\n");
    return 0;
}
