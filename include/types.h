#ifndef TYPES_H
#define TYPES_H

/* En mode "jeu de la vie", une cellule vivante = PROIE. */
typedef enum { VIDE = 0, PROIE = 1, PREDATEUR = 2 } TypeCellule;

typedef struct {
    TypeCellule type;
    int energie;        /* utilisee par les predateurs */
    int age;            /* nombre de generations vecues */
} Cellule;

typedef struct {
    int lignes;
    int colonnes;
    Cellule **cases;    /* tableau 2D alloue dynamiquement : cases[i][j] */
} Grille;

typedef struct {
    int nb_proies;      /* parmi les 8 cases voisines */
    int nb_predateurs;
} Voisinage;

typedef struct {
    int generation;
    int nb_proies;
    int nb_predateurs;
} Stats;

#endif
