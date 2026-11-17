#include <stdio.h>
#include <assert.h>
#include "io.h"
#include "grille.h"
#include "simulation.h"

int main(void)
{
    /* Test 1 : le bloc se charge avec la bonne taille et 4 proies */
    Grille *g = charger_motif("motifs/bloc.txt");
    assert(g != NULL);
    assert(g->lignes == 4 && g->colonnes == 4);
    assert(calculer_stats(g, 0).nb_proies == 4);
    assert(g->cases[1][1].type == PROIE && g->cases[0][0].type == VIDE);
    detruire_grille(g);

    /* Test 2 : le planeur a 5 proies */
    g = charger_motif("motifs/planeur.txt");
    assert(g != NULL);
    assert(g->lignes == 10 && g->colonnes == 10);
    assert(calculer_stats(g, 0).nb_proies == 5);
    detruire_grille(g);

    /* Test 3 : un fichier qui n'existe pas renvoie NULL */
    assert(charger_motif("motifs/nexiste_pas.txt") == NULL);

    printf("Tous les tests de io sont OK\n");
    return 0;
}
