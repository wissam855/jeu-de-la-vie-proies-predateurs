#include <string.h>
#include "menu.h"

void parametres_par_defaut(Parametres *p)
{
    if (p == NULL)
        return;

    /* tout à zéro d'abord : aucun champ n'est oublié */
    memset(p, 0, sizeof *p);

    /* la grille */
    p->lignes = 20;
    p->colonnes = 40;

    /* la simulation */
    p->nb_generations = 100;
    p->delai_ms = 100;
    p->tore = 1;
    p->couleurs = 1;

    /* le remplissage au départ */
    p->p_proie = 0.3;
    p->p_predateur = 0.0;

    /* motif[0] = '\0' (pas de motif), exporter = 0, graine = 0 :
       déjà mis à zéro par memset */

    /* la règle : Conway B3/S23, écrite à la main pour l'instant */
    strcpy(p->regles.nom, "Conway (B3/S23)");
    p->regles.mode = MODE_VIE;
    p->regles.naissance[3] = 1;
    p->regles.survie[2] = 1;
    p->regles.survie[3] = 1;
}
