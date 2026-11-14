#ifndef SIMULATION_H
#define SIMULATION_H

#include "types.h"
#include "regles.h"

/* Calcule la generation suivante : lit dans actuelle, ecrit dans suivante. */
void etape_suivante(const Grille *actuelle, Grille *suivante, const Regles *r, int tore);

/* Compte les proies et les predateurs de la grille. */
Stats calculer_stats(const Grille *g, int generation);

#endif
