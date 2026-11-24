#include <stddef.h>
#include "simulation.h"
#include "grille.h"

/* Calcule la génération suivante : lit uniquement dans actuelle et écrit uniquement dans
   suivante, donc toutes les cellules changent en même temps. Chaque case reçoit la règle
   appliquée à son état et à ses voisins.
   Paramètres : actuelle = la génération en cours, suivante = la grille où écrire (même
   taille), r = la règle à appliquer, tore = 1 si les bords se rejoignent.
   Si un pointeur est NULL ou si les tailles diffèrent, rien n'est fait.
   Pas de valeur renvoyée. */
void etape_suivante(const Grille *actuelle, Grille *suivante, const Regles *r, int tore)
{
    if (actuelle == NULL || suivante == NULL || r == NULL)
        return;
    if (actuelle->lignes != suivante->lignes || actuelle->colonnes != suivante->colonnes)
        return;

    /* on LIT seulement "actuelle" et on ÉCRIT seulement dans "suivante" :
       toutes les cellules changent en même temps */
    for (int i = 0; i < actuelle->lignes; i++)
        for (int j = 0; j < actuelle->colonnes; j++) {
            Voisinage v = compter_voisins(actuelle, i, j, tore);
            suivante->cases[i][j] = appliquer_regle(actuelle->cases[i][j], v, r);
        }
}

/* Compte les proies et les prédateurs de la grille.
   Paramètres : g = la grille (s'il est NULL, les deux compteurs restent à 0),
   generation = le numéro de génération à noter dans le résultat.
   Renvoie : les statistiques (numéro de génération, nombre de proies, nombre de prédateurs). */
Stats calculer_stats(const Grille *g, int generation)
{
    Stats s = { generation, 0, 0 };
    if (g == NULL)
        return s;
    for (int i = 0; i < g->lignes; i++)
        for (int j = 0; j < g->colonnes; j++) {
            if (g->cases[i][j].type == PROIE)
                s.nb_proies++;
            else if (g->cases[i][j].type == PREDATEUR)
                s.nb_predateurs++;
        }
    return s;
}
