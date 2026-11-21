#include <stdlib.h>
#include "io.h"
#include "grille.h"

Grille *charger_motif(const char *chemin)
{
    if (chemin == NULL)
        return NULL;

    FILE *f = fopen(chemin, "r");
    if (f == NULL)
        return NULL;                      /* fichier introuvable */

    /* 1re ligne : le nombre de lignes et de colonnes */
    int lignes, colonnes;
    if (fscanf(f, "%d %d", &lignes, &colonnes) != 2) {
        fclose(f);
        return NULL;                      /* en-tête illisible */
    }

    Grille *g = creer_grille(lignes, colonnes);
    if (g == NULL) {
        fclose(f);
        return NULL;
    }

    /* ensuite : une ligne de texte par ligne de grille
       '.' = vide, 'o' = proie, 'X' = prédateur */
    int i = 0, j = 0, c;
    while (i < lignes && (c = fgetc(f)) != EOF) {
        if (c == '\r')
            continue;                     /* fin de ligne Windows */
        if (c == '\n') {
            if (j > 0) {                  /* une ligne de grille vient de finir */
                i++;
                j = 0;
            }
            continue;
        }
        if (j < colonnes) {
            if (c == 'o')
                g->cases[i][j].type = PROIE;
            else if (c == 'X')
                g->cases[i][j].type = PREDATEUR;
        }
        j++;
    }

    fclose(f);
    return g;
}

int exporter_stats_csv(FILE *f, Stats s)
{
    if (f == NULL)
        return -1;                        /* pas de fichier ouvert */

    /* à la génération 0, on écrit d'abord le nom des colonnes */
    if (s.generation == 0)
        fprintf(f, "generation,proies,predateurs\n");

    /* une ligne par génération : 3 nombres séparés par des virgules */
    fprintf(f, "%d,%d,%d\n", s.generation, s.nb_proies, s.nb_predateurs);
    return 0;
}
