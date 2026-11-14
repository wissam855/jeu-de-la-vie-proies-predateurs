#ifndef MENU_H
#define MENU_H

#include "regles.h"

typedef struct {
    int lignes, colonnes;
    int nb_generations;
    int delai_ms;           /* pause entre deux generations */
    int tore;               /* 1 = les bords se rejoignent */
    int couleurs;           /* 1 = affichage en couleur */
    double p_proie, p_predateur;   /* proportions de depart, entre 0 et 1 */
    char motif[256];        /* "" = grille aleatoire */
    int exporter;           /* 1 = ecrire dans export/ */
    unsigned int graine;    /* pour srand : meme graine = meme grille de depart */
    Regles regles;
} Parametres;

/* Remplit p avec les valeurs par defaut. */
void parametres_par_defaut(Parametres *p);

/* Affiche le menu et modifie p. Renvoie 0 pour lancer une simulation, 1 pour quitter. */
int menu_principal(Parametres *p);

#endif
