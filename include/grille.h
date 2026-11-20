#ifndef GRILLE_H
#define GRILLE_H

#include "types.h"

/* Cree une grille lignes x colonnes, toutes les cases a VIDE. NULL si erreur. */
Grille *creer_grille(int lignes, int colonnes);

/* Libere toute la memoire de la grille. Accepte NULL. */
void detruire_grille(Grille *g);

/* Remet toutes les cases a VIDE. */
void vider_grille(Grille *g);

/* Remplit au hasard : p_proie et p_predateur sont des proportions entre 0 et 1. */
void remplir_aleatoire(Grille *g, double p_proie, double p_predateur);

/* Donne l'energie "energie" a chaque predateur de la grille et remet son age a 0.
   A appeler apres remplir_aleatoire ou un motif : sinon les predateurs
   partent avec 0 d'energie et meurent des la 1re generation. */
void initialiser_predateurs(Grille *g, int energie);

/* Copie src dans dst (les deux grilles doivent avoir la meme taille). */
void copier_grille(const Grille *src, Grille *dst);

/* Compte les proies et les predateurs parmi les 8 voisines de la case (i, j).
   tore = 1 : les bords se rejoignent ; tore = 0 : hors de la grille = vide. */
Voisinage compter_voisins(const Grille *g, int i, int j, int tore);

#endif