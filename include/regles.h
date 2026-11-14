#ifndef REGLES_H
#define REGLES_H

#include "types.h"

typedef enum { MODE_VIE, MODE_PROIES_PREDATEURS } ModeRegles;

typedef struct {
    char nom[64];
    ModeRegles mode;

    /* Mode vie (notation B/S) */
    int naissance[9];   /* naissance[n] = 1 : une case vide avec n voisines vivantes nait */
    int survie[9];      /* survie[n] = 1 : une cellule vivante avec n voisines survit */

    /* Mode proies/predateurs */
    int proie_naissance_min, proie_naissance_max;
    int proie_survie_min, proie_survie_max;
    int seuil_predation;      /* nombre de predateurs voisins pour manger une proie */
    int pred_energie_init;
    int pred_gain;            /* energie gagnee quand une proie est voisine */
    int pred_age_max;
} Regles;

/* Lit une regle comme "B3/S23". Renvoie 0 si ok, -1 si erreur. */
int regles_depuis_chaine(Regles *r, const char *nom, const char *bs);

/* Lit un fichier de regles (cle=valeur). Renvoie 0 si ok, -1 si erreur. */
int charger_regles_fichier(Regles *r, const char *chemin);

/* Renvoie le tableau des regles predefinies et met leur nombre dans *nb. */
const Regles *catalogue_regles(int *nb);

/* Donne l'etat suivant d'UNE case a partir de son etat et de ses voisines. */
Cellule appliquer_regle(Cellule c, Voisinage v, const Regles *r);

#endif
