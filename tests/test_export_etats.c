#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "grille.h"
#include "io.h"

/* Lit tout un fichier texte dans buf ; renvoie 0 si ok. */
static int lire_fichier(const char *chemin, char *buf, size_t taille)
{
    FILE *f = fopen(chemin, "r");
    if (f == NULL)
        return -1;
    size_t n = fread(buf, 1, taille - 1, f);
    buf[n] = '\0';
    fclose(f);
    return 0;
}

int main(void)
{
    char buf[2048];

    /* une grille 3 x 4 : une proie en (0,1), un predateur en (2,3) */
    Grille *g = creer_grille(3, 4);
    assert(g != NULL);
    g->cases[0][1].type = PROIE;
    g->cases[2][3].type = PREDATEUR;

    /* exporter_etat : "GEN n" puis la grille en texte */
    FILE *f = fopen("test_tmp_etats.txt", "w");
    assert(f != NULL);
    assert(exporter_entete(f, g, "Test") == 0);
    assert(exporter_etat(f, g, 0) == 0);
    g->cases[1][1].type = PROIE;
    assert(exporter_etat(f, g, 1) == 0);
    fclose(f);
    assert(lire_fichier("test_tmp_etats.txt", buf, sizeof buf) == 0);
    assert(strcmp(buf, "LIGNES 3 COLONNES 4 REGLE Test\n"
                       "GEN 0\n.o..\n....\n...X\n"
                       "GEN 1\n.o..\n.o..\n...X\n") == 0);

    /* parametres invalides */
    assert(exporter_etat(NULL, g, 0) == -1);
    assert(exporter_etat(stdout, NULL, 0) == -1);
    assert(exporter_entete(NULL, g, "x") == -1);

    /* convertir_export_js : une chaine par generation */
    assert(convertir_export_js("test_tmp_etats.txt", "test_tmp_etats.js") == 0);
    assert(lire_fichier("test_tmp_etats.js", buf, sizeof buf) == 0);
    assert(strstr(buf, "const SIMULATION = { lignes: 3, colonnes: 4, regle: \"Test\", etats: [") != NULL);
    assert(strstr(buf, "\".o.........X\",") != NULL);       /* generation 0 : .o.. + .... + ...X */
    assert(strstr(buf, "\".o...o.....X\",") != NULL);       /* generation 1 */

    /* fichier source absent : erreur, pas de plantage */
    assert(convertir_export_js("n_existe_pas.txt", "test_tmp_etats.js") == -1);

    /* fichier coupe au milieu d'une generation : erreur ET pas de .js laisse */
    f = fopen("test_tmp_etats.txt", "w");
    assert(f != NULL);
    fputs("LIGNES 3 COLONNES 4 REGLE Test\nGEN 0\n.o..\n", f);
    fclose(f);
    assert(convertir_export_js("test_tmp_etats.txt", "test_tmp_etats.js") == -1);
    assert(fopen("test_tmp_etats.js", "r") == NULL);

    /* en-tete fausse */
    f = fopen("test_tmp_etats.txt", "w");
    assert(f != NULL);
    fputs("n'importe quoi\n", f);
    fclose(f);
    assert(convertir_export_js("test_tmp_etats.txt", "test_tmp_etats.js") == -1);

    detruire_grille(g);
    remove("test_tmp_etats.txt");
    remove("test_tmp_etats.js");
    printf("Tous les tests de l'export des etats sont OK\n");
    return 0;
}
