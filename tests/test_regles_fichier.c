#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "regles.h"

/* écrit un petit fichier de test */
static void ecrire(const char *chemin, const char *texte)
{
    FILE *f = fopen(chemin, "w");
    assert(f != NULL);
    fputs(texte, f);
    fclose(f);
}

int main(void)
{
    Regles r;

    /* Test 1 : regles/conway.txt */
    assert(charger_regles_fichier(&r, "regles/conway.txt") == 0);
    assert(strcmp(r.nom, "Conway (B3/S23)") == 0);
    assert(r.mode == MODE_VIE);
    assert(r.naissance[3] == 1 && r.survie[2] == 1 && r.survie[3] == 1);

    /* Test 2 : regles/highlife.txt */
    assert(charger_regles_fichier(&r, "regles/highlife.txt") == 0);
    assert(strcmp(r.nom, "HighLife (B36/S23)") == 0);
    assert(r.naissance[6] == 1);

    /* Test 3 : fichier introuvable -> -1, r inchangée */
    assert(charger_regles_fichier(&r, "regles/nexiste_pas.txt") == -1);
    assert(strcmp(r.nom, "HighLife (B36/S23)") == 0);

    /* Test 4 : fichiers incorrects -> -1 */
    ecrire("test_tmp.txt", "nom=X\nbs=B3S23\n");          /* B/S faux */
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);
    ecrire("test_tmp.txt", "nom=X\ncouleur=rouge\nbs=B3/S23\n");  /* clé inconnue */
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);
    ecrire("test_tmp.txt", "nom=X\n");                     /* pas de bs */
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);
    ecrire("test_tmp.txt", "nom X\nbs=B3/S23\n");          /* pas de = */
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);

    /* Test 5 : fin de ligne Windows et lignes vides acceptées */
    ecrire("test_tmp.txt", "# essai\r\n\r\nbs=B2/S\r\n");
    assert(charger_regles_fichier(&r, "test_tmp.txt") == 0);
    assert(strcmp(r.nom, "B2/S") == 0);
    remove("test_tmp.txt");

    printf("Tous les tests de fichiers de regles sont OK\n");
    return 0;
}