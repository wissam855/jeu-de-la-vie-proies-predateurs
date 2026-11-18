#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "types.h"
#include "regles.h"

/* Efface le terminal. */
void effacer_ecran(void);

/* Affiche la grille : . vide, o proie, X predateur. couleurs = 1 : en couleur. */
void afficher_grille(const Grille *g, int couleurs);

/* Ecrit la notation B/S de la regle dans buf, par exemple "B36/S23".
   En mode proies/predateurs, ecrit "proies/predateurs". */
void notation_bs(const Regles *r, char *buf, int taille);

/* Affiche la generation, les compteurs, le nom de la regle
   et sa notation B/S si elle n'est pas deja dans le nom. */
void afficher_stats(Stats s, const Regles *r);

/* Attend ms millisecondes (Linux et Windows). */
void pause_ms(int ms);

#endif
