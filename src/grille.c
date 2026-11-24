#include <stdlib.h>
#include "grille.h"

/* Crée une grille de lignes x colonnes cases, toutes vides, en 3 étages : la structure, le
   tableau de pointeurs (un par ligne), puis chaque ligne de cellules. Si une allocation
   échoue, tout ce qui a déjà été alloué est libéré.
   Paramètres : lignes, colonnes = la taille (elles doivent être positives).
   Renvoie : la nouvelle grille (à libérer avec detruire_grille), ou NULL si la taille est
   invalide ou si la mémoire manque. */
Grille *creer_grille(int lignes, int colonnes)
{
    /* 1. tailles invalides */
    if (lignes <= 0 || colonnes <= 0)
        return NULL;

    /* 2. étage 1 : la structure */
    Grille *g = malloc(sizeof(Grille));
    if (g == NULL)
        return NULL;

    /* 3. remplir les tailles */
    g->lignes = lignes;
    g->colonnes = colonnes;

    /* 4. étage 2 : un pointeur par ligne */
    g->cases = malloc(lignes * sizeof(Cellule *));
    if (g->cases == NULL) {
        free(g);
        return NULL;
    }

    /* 5. étage 3 : chaque ligne de cellules */
    for (int i = 0; i < g->lignes; i++) {
        g->cases[i] = calloc(g->colonnes, sizeof(Cellule));
        if (g->cases[i] == NULL) {
            /* 6. échec : on libère tout ce qui a déjà été alloué */
            for (int k = 0; k < i; k++)
                free(g->cases[k]);
            free(g->cases);
            free(g);
            return NULL;
        }
    }

    /* 7. tout a marché */
    return g;
}



/* Libère toute la mémoire d'une grille : chaque ligne, puis le tableau de pointeurs, puis
   la structure (dans cet ordre).
   Paramètre : g = la grille à détruire (s'il est NULL, la fonction ne fait rien).
   Pas de valeur renvoyée. */
void detruire_grille(Grille *g)
{
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++)
        free(g->cases[i]);
    free(g->cases);
    free(g);
}


/* Remet toutes les cases de la grille à VIDE, avec une énergie et un âge de 0.
   Paramètre : g = la grille à vider (s'il est NULL, la fonction ne fait rien).
   Pas de valeur renvoyée. */
void vider_grille(Grille *g)
{
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++) {
            g->cases[i][j].type = VIDE;
            g->cases[i][j].energie = 0;
            g->cases[i][j].age = 0;
        }
}

/* Copie toutes les cases de src dans dst.
   Paramètres : src = la grille à copier, dst = la grille qui reçoit la copie. Elles doivent
   avoir la même taille ; sinon, ou si l'une est NULL, rien n'est copié.
   Pas de valeur renvoyée. */
void copier_grille(const Grille *src, Grille *dst)
{
    if (src == NULL || dst == NULL)
        return;
    if (src->lignes != dst->lignes || src->colonnes != dst->colonnes)
        return;
    for (int i = 0; i < src->lignes; i++)
        for (int j = 0; j < src->colonnes; j++)
            dst->cases[i][j] = src->cases[i][j];
}


/* Remplit la grille au hasard : chaque case devient une proie avec la probabilité p_proie,
   un prédateur avec la probabilité p_predateur, sinon elle reste vide. Les prédateurs
   gardent une énergie de 0 : voir initialiser_predateurs.
   Paramètres : g = la grille à remplir (s'il est NULL, rien n'est fait), p_proie et
   p_predateur = des proportions entre 0 et 1 dont la somme ne dépasse pas 1.
   Pas de valeur renvoyée. */
void remplir_aleatoire(Grille *g, double p_proie, double p_predateur)
{
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++) {
            double x = rand() / (RAND_MAX + 1.0); /* nombre entre 0 (inclus) et 1 (exclu) */
            Cellule c = { VIDE, 0, 0 };
            if (x < p_proie)
                c.type = PROIE;
            else if (x < p_proie + p_predateur)
                c.type = PREDATEUR;
            g->cases[i][j] = c;
        }
}

/* Compte les proies et les prédateurs parmi les 8 cases voisines de la case (i, j).
   Paramètres : g = la grille, i et j = la ligne et la colonne de la case, tore = 1 pour
   que les bords se rejoignent, 0 pour que ce qui est hors de la grille compte pour vide.
   Renvoie : le nombre de proies et de prédateurs voisins (0 et 0 si g est NULL). */
Voisinage compter_voisins(const Grille *g, int i, int j, int tore)
{
    Voisinage v = { 0, 0 };
    if (g == NULL)
        return v;
    for (int di = -1; di <= 1; di++)
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0)
                continue; /* on ne compte pas la case elle-même */
            int x = i + di;
            int y = j + dj;
            if (tore) {
                /* les bords se rejoignent */
                x = (x + g->lignes) % g->lignes;
                y = (y + g->colonnes) % g->colonnes;
            } else if (x < 0 || x >= g->lignes || y < 0 || y >= g->colonnes) {
                continue; /* hors de la grille : on ignore */
            }
            if (g->cases[x][y].type == PROIE)
                v.nb_proies++;
            else if (g->cases[x][y].type == PREDATEUR)
                v.nb_predateurs++;
        }
    return v;
}

/* Donne l'énergie energie à chaque prédateur de la grille et remet son âge à 0. À appeler
   après remplir_aleatoire ou le chargement d'un motif, sinon les prédateurs partent avec 0
   d'énergie et meurent dès la première génération.
   Paramètres : g = la grille (s'il est NULL, rien n'est fait), energie = l'énergie de départ.
   Pas de valeur renvoyée. */
void initialiser_predateurs(Grille *g, int energie)
{
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++)
            if (g->cases[i][j].type == PREDATEUR) {
                g->cases[i][j].energie = energie;
                g->cases[i][j].age = 0;
            }
}
