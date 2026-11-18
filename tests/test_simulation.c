#include <stdio.h>
#include <assert.h>
#include "grille.h"
#include "simulation.h"
#include "regles.h"

/* place une proie en (i, j) */
static void poser(Grille *g, int i, int j)
{
    g->cases[i][j].type = PROIE;
}

/* renvoie 1 si les deux grilles ont le même type dans chaque case */
static int grilles_egales(const Grille *a, const Grille *b)
{
    if (a->lignes != b->lignes || a->colonnes != b->colonnes)
        return 0;
    for (int i = 0; i < a->lignes; i++)
        for (int j = 0; j < a->colonnes; j++)
            if (a->cases[i][j].type != b->cases[i][j].type)
                return 0;
    return 1;
}

/* pose un planeur dont le coin haut-gauche est en (i, j) :
       . o .
       . . o
       o o o        il descend vers la droite */
static void poser_planeur(Grille *g, int i, int j)
{
    poser(g, i, j + 1);
    poser(g, i + 1, j + 2);
    poser(g, i + 2, j); poser(g, i + 2, j + 1); poser(g, i + 2, j + 2);
}

int main(void)
{
    int nb;
    const Regles *conway = catalogue_regles(&nb);
    Grille *a = creer_grille(6, 6);
    Grille *b = creer_grille(6, 6);
    assert(a != NULL && b != NULL);

    /* Test 1 : le bloc 2x2 ne bouge pas */
    poser(a, 1, 1); poser(a, 1, 2); poser(a, 2, 1); poser(a, 2, 2);
    etape_suivante(a, b, conway, 0);
    assert(calculer_stats(b, 1).nb_proies == 4);
    assert(b->cases[1][1].type == PROIE && b->cases[2][2].type == PROIE);

    /* Test 2 : le clignotant passe de horizontal à vertical, puis revient */
    vider_grille(a);
    poser(a, 2, 1); poser(a, 2, 2); poser(a, 2, 3);
    etape_suivante(a, b, conway, 0);
    assert(b->cases[1][2].type == PROIE);
    assert(b->cases[2][2].type == PROIE);
    assert(b->cases[3][2].type == PROIE);
    assert(b->cases[2][1].type == VIDE);
    assert(calculer_stats(b, 1).nb_proies == 3);
    etape_suivante(b, a, conway, 0);
    assert(a->cases[2][1].type == PROIE && a->cases[2][3].type == PROIE);

    /* Test 3 : une cellule seule meurt */
    vider_grille(a);
    poser(a, 3, 3);
    etape_suivante(a, b, conway, 0);
    assert(calculer_stats(b, 1).nb_proies == 0);

    /* Test 4 : calculer_stats garde le numéro de génération */
    Stats s = calculer_stats(b, 42);
    assert(s.generation == 42 && s.nb_predateurs == 0);

    /* Test 5 (E6) : le tore. Sur une grille 8 x 8, un planeur avance
       d'une case en diagonale toutes les 4 générations :
       après 32 générations, il a fait le tour et revient à sa place. */
    Grille *depart = creer_grille(8, 8);
    Grille *g1 = creer_grille(8, 8);
    Grille *g2 = creer_grille(8, 8);
    Grille *decale = creer_grille(8, 8);
    assert(depart != NULL && g1 != NULL && g2 != NULL && decale != NULL);
    poser_planeur(depart, 0, 0);
    poser_planeur(decale, 1, 1);          /* le même planeur, 1 case plus loin */

    copier_grille(depart, g1);
    for (int gen = 1; gen <= 32; gen++) {
        etape_suivante(g1, g2, conway, 1);  /* tore = 1 */
        Grille *tmp = g1; g1 = g2; g2 = tmp;  /* échange des pointeurs */

        if (gen == 4)                       /* après 4 générations : décalé de (1, 1) */
            assert(grilles_egales(g1, decale));
        assert(calculer_stats(g1, gen).nb_proies == 5);  /* toujours 5 cellules */
    }
    assert(grilles_egales(g1, depart));       /* revenu exactement à sa place */

    /* Test 6 (E6) : sans le tore, le planeur se bloque contre le bord
       et ne revient pas à sa place */
    copier_grille(depart, g1);
    for (int gen = 1; gen <= 32; gen++) {
        etape_suivante(g1, g2, conway, 0);  /* tore = 0 */
        Grille *tmp = g1; g1 = g2; g2 = tmp;
    }
    assert(!grilles_egales(g1, depart));

    detruire_grille(depart);
    detruire_grille(g1);
    detruire_grille(g2);
    detruire_grille(decale);

    detruire_grille(a);
    detruire_grille(b);
    printf("Tous les tests de simulation sont OK\n");
    return 0;
}
