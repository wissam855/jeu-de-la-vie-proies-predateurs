#include <stdlib.h>
#include "grille.h"

Grille *creer_grille(int lignes, int colonnes)
{
    /* 1. tailles invalides -> NULL
       2. malloc de la structure Grille
       3. remplir lignes et colonnes
       4. malloc du tableau de pointeurs cases
       5. boucle : calloc de chaque ligne
       6. si échec : tout libérer, NULL
       7. return g */
}

void detruire_grille(Grille *g)
{
    /* g NULL -> rien ; sinon libérer lignes, puis cases, puis g */
}

void vider_grille(Grille *g)
{
    /* chaque case : type VIDE, energie 0, age 0 */
}

void copier_grille(const Grille *src, Grille *dst)
{
    /* tailles différentes -> rien ; sinon copier case par case */
}
