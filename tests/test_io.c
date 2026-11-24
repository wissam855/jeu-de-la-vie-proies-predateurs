#include <stdio.h>
#include <assert.h>
#include "io.h"
#include "grille.h"
#include "simulation.h"

/* Écrit contenu dans un fichier temporaire, le charge avec charger_motif,
   puis supprime le fichier. Renvoie la grille (ou NULL si le motif est refusé). */
static Grille *charger_texte(const char *contenu)
{
    FILE *f = fopen("test_tmp_motif.txt", "wb");
    assert(f != NULL);
    fputs(contenu, f);
    fclose(f);

    Grille *g = charger_motif("test_tmp_motif.txt");
    remove("test_tmp_motif.txt");
    return g;
}

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

    /* Test 4 : un motif valide avec une proie et un prédateur */
    g = charger_texte("2 3\n.oX\n...\n");
    assert(g != NULL);
    assert(g->lignes == 2 && g->colonnes == 3);
    assert(g->cases[0][1].type == PROIE && g->cases[0][2].type == PREDATEUR);
    assert(g->cases[1][0].type == VIDE);
    detruire_grille(g);

    /* Test 5 : fins de ligne Windows et lignes vides acceptées */
    g = charger_texte("2 2\r\n.o\r\n\r\no.\r\n");
    assert(g != NULL);
    assert(calculer_stats(g, 0).nb_proies == 2);
    detruire_grille(g);

    /* Test 6 : une ligne trop courte est refusée */
    assert(charger_texte("3 3\n.o.\n..\nooo\n") == NULL);

    /* Test 7 : une ligne trop longue est refusée */
    assert(charger_texte("3 3\n.o.\n....\nooo\n") == NULL);

    /* Test 8 : un caractère inconnu est refusé */
    assert(charger_texte("3 3\n.o.\n.z.\nooo\n") == NULL);

    /* Test 9 : un fichier incomplet (il manque une ligne) est refusé */
    assert(charger_texte("3 3\n.o.\n..o\n") == NULL);
    assert(charger_texte("3 3\n") == NULL);

    /* Test 10 : une ligne en trop est refusée */
    assert(charger_texte("2 2\n..\n..\n..\n") == NULL);

    /* Test 11 : un en-tête illisible, nul ou démesuré est refusé */
    assert(charger_texte("abc\n") == NULL);
    assert(charger_texte("") == NULL);
    assert(charger_texte("0 3\n...\n") == NULL);
    assert(charger_texte("3 -2\n..\n") == NULL);
    assert(charger_texte("5000 5000\n") == NULL);

    printf("Tous les tests de io sont OK\n");
    return 0;
}
