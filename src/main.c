#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grille.h"
#include "simulation.h"
#include "affichage.h"
#include "menu.h"

int main(void)
{
    Parametres p;
    parametres_par_defaut(&p);

    /* graine du hasard : 0 = une grille différente à chaque lancement */
    if (p.graine == 0)
        srand((unsigned int)time(NULL));
    else
        srand(p.graine);

    Grille *g = creer_grille(p.lignes, p.colonnes);
    if (g == NULL) {
        fprintf(stderr, "Erreur : impossible de creer la grille\n");
        return 1;
    }

    remplir_aleatoire(g, p.p_proie, p.p_predateur);

    effacer_ecran();
    afficher_grille(g, p.couleurs);
    afficher_stats(calculer_stats(g, 0), &p.regles);

    detruire_grille(g);
    return 0;
}
