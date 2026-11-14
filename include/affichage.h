#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "types.h"
#include "regles.h"

/* Efface le terminal. */
void effacer_ecran(void);

/* Affiche la grille : . vide, o proie, X predateur. couleurs = 1 : en couleur. */
void afficher_grille(const Grille *g, int couleurs);

/* Affiche la generation, les compteurs et le nom de la regle. */
void afficher_stats(Stats s, const Regles *r);

/* Attend ms millisecondes (Linux et Windows). */
void pause_ms(int ms);

#endif
