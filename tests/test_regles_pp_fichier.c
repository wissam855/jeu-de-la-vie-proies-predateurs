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

/* compare toutes les valeurs proies/prédateurs de deux règles */
static int memes_pp(const Regles *a, const Regles *b)
{
    return strcmp(a->nom, b->nom) == 0 && a->mode == b->mode
        && a->proie_naissance_min == b->proie_naissance_min
        && a->proie_naissance_max == b->proie_naissance_max
        && a->proie_survie_min == b->proie_survie_min
        && a->proie_survie_max == b->proie_survie_max
        && a->seuil_predation == b->seuil_predation
        && a->pred_energie_init == b->pred_energie_init
        && a->pred_gain == b->pred_gain
        && a->pred_age_max == b->pred_age_max;
}

/* les lignes communes d'un fichier pp correct */
#define PP_OK "mode=pp\nproie_naissance=2-3\nproie_survie=1-5\n" \
              "seuil_predation=2\npred_energie_init=4\npred_gain=2\n"

int main(void)
{
    int nb;
    const Regles *cat = catalogue_regles(&nb);
    Regles r;

    /* Test 1 : regles/proies_predateurs.txt = la 7e règle du catalogue */
    assert(charger_regles_fichier(&r, "regles/proies_predateurs.txt") == 0);
    assert(r.mode == MODE_PROIES_PREDATEURS);
    assert(memes_pp(&r, &cat[6]));

    /* Test 2 : d'autres valeurs sont bien lues */
    ecrire("test_tmp.txt", "nom=Essai\nmode=pp\nproie_naissance=3-3\nproie_survie=2-4\n"
                           "seuil_predation=3\npred_energie_init=6\npred_gain=1\npred_age_max=20\n");
    assert(charger_regles_fichier(&r, "test_tmp.txt") == 0);
    assert(strcmp(r.nom, "Essai") == 0);
    assert(r.proie_naissance_min == 3 && r.proie_naissance_max == 3);
    assert(r.proie_survie_min == 2 && r.proie_survie_max == 4);
    assert(r.seuil_predation == 3 && r.pred_energie_init == 6);
    assert(r.pred_gain == 1 && r.pred_age_max == 20);

    /* Test 3 : fichiers refusés -> -1, et r n'est pas modifiée */
    ecrire("test_tmp.txt", PP_OK);                                    /* pred_age_max manquant */
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);
    ecrire("test_tmp.txt", "mode=pp\nproie_naissance=3-2\nproie_survie=1-5\n"
                           "seuil_predation=2\npred_energie_init=4\npred_gain=2\npred_age_max=15\n");
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);         /* min > max */
    ecrire("test_tmp.txt", PP_OK "pred_age_max=-1\n");
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);         /* valeur négative */
    ecrire("test_tmp.txt", PP_OK "pred_age_max=15x\n");
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);         /* pas un nombre */
    ecrire("test_tmp.txt", PP_OK "pred_age_max=15\nbs=B3/S23\n");
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);         /* bs en mode pp */
    ecrire("test_tmp.txt", "mode=vie\nbs=B3/S23\nseuil_predation=2\n");
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);         /* clé pp en mode vie */
    ecrire("test_tmp.txt", "mode=zoo\nbs=B3/S23\n");
    assert(charger_regles_fichier(&r, "test_tmp.txt") == -1);         /* mode inconnu */
    assert(strcmp(r.nom, "Essai") == 0);                               /* r inchangée */

    /* Test 4 : le mode vie marche toujours (N7) */
    assert(charger_regles_fichier(&r, "regles/highlife.txt") == 0);
    assert(r.mode == MODE_VIE && r.naissance[6] == 1);

    remove("test_tmp.txt");
    printf("Tous les tests des fichiers proies/predateurs sont OK\n");
    return 0;
}