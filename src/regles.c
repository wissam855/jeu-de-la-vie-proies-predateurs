#include <stddef.h>
#include <string.h>
#include "regles.h"

/* Le catalogue : pour l'instant une seule règle, Conway (B3/S23). */
static const Regles CATALOGUE[] = {
    {
        .nom = "Conway (B3/S23)",
        .mode = MODE_VIE,
        /*            voisins : 0  1  2  3  4  5  6  7  8 */
        .naissance =          { 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        .survie =             { 0, 0, 1, 1, 0, 0, 0, 0, 0 },
    },
};

const Regles *catalogue_regles(int *nb)
{
    if (nb != NULL)
        *nb = (int)(sizeof(CATALOGUE) / sizeof(CATALOGUE[0]));
    return CATALOGUE;
}

Cellule appliquer_regle(Cellule c, Voisinage v, const Regles *r)
{
    Cellule res = c;
    int n = v.nb_proies;

    if (r == NULL || n < 0 || n > 8)
        return res;

    if (r->mode == MODE_VIE) {
        if (c.type == PROIE) {
            if (r->survie[n]) {
                res.age = c.age + 1;
            } else {
                res.type = VIDE;
                res.energie = 0;
                res.age = 0;
            }
        } else {
            if (r->naissance[n]) {
                res.type = PROIE;
                res.energie = 0;
                res.age = 0;
            } else {
                res.type = VIDE;
            }
        }
    }
    return res;
}

/* Lit une règle écrite "B36/S23" :
   après B, les nombres de voisins qui font naître une cellule ;
   après S, les nombres de voisins qui la font survivre.
   Renvoie 0 si la chaîne est correcte, -1 sinon (et *r n'est pas modifiée). */
int regles_depuis_chaine(Regles *r, const char *nom, const char *bs)
{
    if (r == NULL || bs == NULL)
        return -1;

    /* on remplit une règle temporaire : en cas d'erreur, *r reste intacte */
    Regles tmp;
    memset(&tmp, 0, sizeof tmp);
    tmp.mode = MODE_VIE;

    const char *p = bs;

    /* 1. la lettre B (majuscule ou minuscule) */
    if (*p != 'B' && *p != 'b')
        return -1;
    p++;

    /* 2. les chiffres de naissance, de 0 à 8 */
    while (*p >= '0' && *p <= '8') {
        tmp.naissance[*p - '0'] = 1;
        p++;
    }

    /* 3. la barre / puis la lettre S */
    if (*p != '/')
        return -1;
    p++;
    if (*p != 'S' && *p != 's')
        return -1;
    p++;

    /* 4. les chiffres de survie, de 0 à 8 */
    while (*p >= '0' && *p <= '8') {
        tmp.survie[*p - '0'] = 1;
        p++;
    }

    /* 5. fin de la chaîne (on tolère un retour à la ligne) */
    while (*p == '\r' || *p == '\n' || *p == ' ')
        p++;
    if (*p != '\0')
        return -1;

    /* 6. le nom : celui donné, sinon la chaîne elle-même */
    if (nom != NULL && nom[0] != '\0')
        strncpy(tmp.nom, nom, sizeof tmp.nom - 1);
    else
        strncpy(tmp.nom, bs, sizeof tmp.nom - 1);
    tmp.nom[sizeof tmp.nom - 1] = '\0';

    *r = tmp;
    return 0;
}