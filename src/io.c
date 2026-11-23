#include <stdlib.h>
#include <string.h>
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

int exporter_entete(FILE *f, const Grille *g, const char *regle)
{
    if (f == NULL || g == NULL)
        return -1;
    fprintf(f, "LIGNES %d COLONNES %d REGLE %s\n", g->lignes, g->colonnes,
            regle != NULL ? regle : "inconnue");
    return 0;
}

int exporter_etat(FILE *f, const Grille *g, int generation)
{
    if (f == NULL || g == NULL)
        return -1;

    fprintf(f, "GEN %d\n", generation);
    /* une ligne de texte par ligne de la grille : les memes symboles que l'affichage */
    for (int i = 0; i < g->lignes; i++) {
        for (int j = 0; j < g->colonnes; j++) {
            TypeCellule t = g->cases[i][j].type;
            fputc(t == PROIE ? 'o' : (t == PREDATEUR ? 'X' : '.'), f);
        }
        fputc('\n', f);
    }
    return 0;
}

/* Enleve le \n (et le \r sous Windows) a la fin d'une ligne lue par fgets. */
static void enlever_fin_de_ligne(char *ligne)
{
    size_t n = strlen(ligne);
    while (n > 0 && (ligne[n - 1] == '\n' || ligne[n - 1] == '\r'))
        ligne[--n] = '\0';
}

int convertir_export_js(const char *chemin_txt, const char *chemin_js)
{
    if (chemin_txt == NULL || chemin_js == NULL)
        return -1;

    FILE *in = fopen(chemin_txt, "r");
    if (in == NULL)
        return -1;                        /* export/etats.txt introuvable */

    char ligne[1100];                     /* assez pour 1000 colonnes */
    int lignes = 0, colonnes = 0;
    char regle[128] = "";

    /* 1. l'en-tete : LIGNES l COLONNES c REGLE nom */
    if (fgets(ligne, sizeof ligne, in) == NULL
        || sscanf(ligne, "LIGNES %d COLONNES %d REGLE %127[^\r\n]", &lignes, &colonnes, regle) < 2
        || lignes < 1 || lignes > 1000 || colonnes < 1 || colonnes > 1000) {
        fclose(in);
        return -1;
    }
    /* le nom va entre guillemets dans le .js : on retire ceux qui le casseraient */
    for (char *c = regle; *c != '\0'; c++)
        if (*c == '"' || *c == '\\')
            *c = ' ';

    FILE *out = fopen(chemin_js, "w");
    if (out == NULL) {
        fclose(in);
        return -1;
    }
    fprintf(out, "const SIMULATION = { lignes: %d, colonnes: %d, regle: \"%s\", etats: [\n",
            lignes, colonnes, regle);

    /* 2. chaque generation : "GEN n", puis `lignes` lignes de `colonnes` symboles.
       Elles sont collees bout a bout pour faire UNE chaine par generation. */
    int nb_generations = 0;
    int erreur = 0;
    while (!erreur && fgets(ligne, sizeof ligne, in) != NULL) {
        enlever_fin_de_ligne(ligne);
        if (ligne[0] == '\0')
            continue;                     /* ligne vide : on l'ignore */
        if (strncmp(ligne, "GEN ", 4) != 0) {
            erreur = 1;
            break;
        }
        fputs("  \"", out);
        for (int i = 0; i < lignes && !erreur; i++) {
            if (fgets(ligne, sizeof ligne, in) == NULL) {
                erreur = 1;               /* fichier coupe au milieu d'une generation */
                break;
            }
            enlever_fin_de_ligne(ligne);
            if ((int)strlen(ligne) != colonnes || strspn(ligne, ".oX") != (size_t)colonnes)
                erreur = 1;
            else
                fputs(ligne, out);
        }
        fputs("\",\n", out);
        nb_generations++;
    }

    fputs("] };\n", out);
    fclose(in);
    int ecriture_ok = (fclose(out) == 0);

    if (erreur || nb_generations == 0 || !ecriture_ok) {
        remove(chemin_js);                /* on ne laisse pas un fichier a moitie faux */
        return -1;
    }
    return 0;
}
