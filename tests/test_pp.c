#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "grille.h"
#include "simulation.h"
#include "regles.h"

/* place une cellule en (i, j) */
static void poser(Grille *g, int i, int j, TypeCellule t, int energie)
{
    g->cases[i][j].type = t;
    g->cases[i][j].energie = energie;
    g->cases[i][j].age = 0;
}

/* calcule UNE génération et renvoie la case du centre (2, 2) */
static Cellule centre_apres(Grille *a, Grille *b, const Regles *r)
{
    etape_suivante(a, b, r, 0);     /* sans tore : rien ne revient par les bords */
    return b->cases[2][2];
}

int main(void)
{
    int nb;
    const Regles *pp = &catalogue_regles(&nb)[6];
    assert(pp->mode == MODE_PROIES_PREDATEURS);
    /* Les cas ci-dessous sont écrits pour seuil_predation = 2 et une énergie
       de départ de 4 : on fixe ces valeurs ici pour que le test ne dépende
       pas du réglage final du catalogue (T3.8). */
    Regles ref = *pp;
    ref.seuil_predation = 2;
    ref.pred_energie_init = 4;
    pp = &ref;
    Grille *a = creer_grille(5, 5);
    Grille *b = creer_grille(5, 5);
    assert(a != NULL && b != NULL);
    Cellule c;

    /* Les six cas de E7, sur une vraie grille 5 x 5 (case étudiée : le centre) */

    /* 1. case vide, 2 proies voisines, 0 prédateur -> proie */
    vider_grille(a);
    poser(a, 1, 1, PROIE, 0); poser(a, 1, 2, PROIE, 0);
    c = centre_apres(a, b, pp);
    assert(c.type == PROIE);

    /* 2. case vide, 3 proies voisines, 1 prédateur -> reste vide */
    vider_grille(a);
    poser(a, 1, 1, PROIE, 0); poser(a, 1, 2, PROIE, 0); poser(a, 1, 3, PROIE, 0);
    poser(a, 3, 3, PREDATEUR, 4);
    c = centre_apres(a, b, pp);
    assert(c.type == VIDE);

    /* 3. proie avec 2 prédateurs voisins -> prédateur avec 4 d'énergie */
    vider_grille(a);
    poser(a, 2, 2, PROIE, 0);
    poser(a, 1, 1, PREDATEUR, 4); poser(a, 3, 3, PREDATEUR, 4);
    c = centre_apres(a, b, pp);
    assert(c.type == PREDATEUR && c.energie == 4 && c.age == 0);

    /* 4. proie sans aucune voisine -> meurt */
    vider_grille(a);
    poser(a, 2, 2, PROIE, 0);
    c = centre_apres(a, b, pp);
    assert(c.type == VIDE);

    /* 5. prédateur à 1 d'énergie sans proie voisine -> meurt */
    vider_grille(a);
    poser(a, 2, 2, PREDATEUR, 1);
    c = centre_apres(a, b, pp);
    assert(c.type == VIDE);

    /* 6. prédateur à 1 d'énergie avec une proie voisine -> reste, 2 d'énergie */
    vider_grille(a);
    poser(a, 2, 2, PREDATEUR, 1);
    poser(a, 2, 3, PROIE, 0);
    c = centre_apres(a, b, pp);
    assert(c.type == PREDATEUR && c.energie == 2);

    /* Test 7 : initialiser_predateurs donne l'énergie à TOUS les prédateurs,
       remet leur âge à 0, et ne touche pas aux proies */
    vider_grille(a);
    poser(a, 0, 0, PREDATEUR, 0); a->cases[0][0].age = 9;
    poser(a, 4, 4, PREDATEUR, 0);
    poser(a, 2, 2, PROIE, 0);
    initialiser_predateurs(a, 4);
    assert(a->cases[0][0].energie == 4 && a->cases[0][0].age == 0);
    assert(a->cases[4][4].energie == 4);
    assert(a->cases[2][2].type == PROIE && a->cases[2][2].energie == 0);
    initialiser_predateurs(NULL, 4);              /* ne plante pas */

    /* Test 8 : sans initialiser_predateurs, un prédateur à 0 d'énergie meurt
       tout de suite ; avec, il survit (c'est pour ça qu'on l'a ajoutée) */
    vider_grille(a);
    poser(a, 2, 2, PREDATEUR, 0);
    assert(centre_apres(a, b, pp).type == VIDE);
    initialiser_predateurs(a, pp->pred_energie_init);
    assert(centre_apres(a, b, pp).type == PREDATEUR);

    detruire_grille(a);
    detruire_grille(b);

    /* Test 9 : remplir_aleatoire sur 100 x 100 avec 30 % de proies et 3 % de
       prédateurs : environ 3 000 proies et 300 prédateurs */
    srand(42);
    Grille *g = creer_grille(100, 100);
    assert(g != NULL);
    remplir_aleatoire(g, 0.30, 0.03);
    Stats s = calculer_stats(g, 0);
    assert(s.nb_proies >= 2500 && s.nb_proies <= 3500);
    assert(s.nb_predateurs >= 150 && s.nb_predateurs <= 450);
    detruire_grille(g);

    printf("Tous les tests proies/predateurs sur la grille sont OK\n");
    return 0;
}
