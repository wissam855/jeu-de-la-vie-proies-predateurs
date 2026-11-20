#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "regles.h"

/* Le catalogue : les 6 règles du jeu de la vie, écrites en notation B/S.
   Ce tableau est la seule chose à modifier pour ajouter une règle. */
static const char *DEFINITIONS[][2] = {
    /*  nom affiché                          notation B/S   */
    { "Conway (B3/S23)",                     "B3/S23"        },
    { "HighLife (B36/S23)",                  "B36/S23"       },
    { "Seeds (B2/S)",                        "B2/S"          },
    { "Day & Night (B3678/S34678)",          "B3678/S34678"  },
    { "Maze (B3/S12345)",                    "B3/S12345"     },
    { "Life without Death (B3/S012345678)",  "B3/S012345678" },
};

#define NB_VIE ((int)(sizeof DEFINITIONS / sizeof DEFINITIONS[0]))  /* 6 */
#define NB_REGLES (NB_VIE + 1)        /* + la règle proies/prédateurs */

static Regles CATALOGUE[NB_REGLES];  /* rempli au premier appel */
static int catalogue_pret = 0;       /* 0 tant qu'il n'est pas rempli */

/* La 7e règle : proies/prédateurs, avec les valeurs de départ du plan
   (validées à la réunion T3.1, à régler en T3.8). */
static void regles_proies_predateurs(Regles *r)
{
    memset(r, 0, sizeof *r);
    strncpy(r->nom, "Proies-Predateurs", sizeof r->nom - 1);
    r->mode = MODE_PROIES_PREDATEURS;
    r->proie_naissance_min = 2;   /* une case vide devient proie avec 2 ou 3 proies voisines */
    r->proie_naissance_max = 3;
    r->proie_survie_min = 1;      /* une proie survit avec 1 à 5 proies voisines */
    r->proie_survie_max = 5;
    r->seuil_predation = 2;       /* 2 prédateurs voisins ou plus : la proie est mangée */
    r->pred_energie_init = 4;     /* énergie d'un nouveau prédateur */
    r->pred_gain = 2;             /* énergie gagnée s'il a au moins une proie voisine */
    r->pred_age_max = 15;         /* au-delà, le prédateur meurt de vieillesse */
}

const Regles *catalogue_regles(int *nb)
{
    if (!catalogue_pret) {
        /* les 6 règles du jeu de la vie : on réutilise regles_depuis_chaine (N6) */
        for (int i = 0; i < NB_VIE; i++)
            regles_depuis_chaine(&CATALOGUE[i], DEFINITIONS[i][0], DEFINITIONS[i][1]);
        /* la 7e : proies/prédateurs */
        regles_proies_predateurs(&CATALOGUE[NB_VIE]);
        catalogue_pret = 1;
    }
    if (nb != NULL)
        *nb = NB_REGLES;
    return CATALOGUE;
}

/* Une case qui devient vide : on remet tout à zéro. */
static Cellule case_vide(void)
{
    Cellule v = { VIDE, 0, 0 };
    return v;
}

/* Mode proies/prédateurs. P = proies voisines, D = prédateurs voisins. */
static Cellule regle_pp(Cellule c, int P, int D, const Regles *r)
{
    Cellule res = c;

    if (c.type == VIDE) {
        /* naissance d'une proie : aucun prédateur autour et assez de proies */
        if (D == 0 && P >= r->proie_naissance_min && P <= r->proie_naissance_max) {
            res.type = PROIE;
            res.energie = 0;
            res.age = 0;
        }
    } else if (c.type == PROIE) {
        /* 1) la prédation passe AVANT la survie */
        if (D >= r->seuil_predation) {
            res.type = PREDATEUR;               /* la proie est mangée */
            res.energie = r->pred_energie_init;
            res.age = 0;
        } else if (P < r->proie_survie_min || P > r->proie_survie_max) {
            res = case_vide();                  /* isolement ou surpopulation */
        } else {
            res.age = c.age + 1;                /* elle survit */
        }
    } else {                                    /* PREDATEUR */
        res.energie = c.energie - 1;            /* il dépense de l'énergie */
        if (P >= 1)
            res.energie += r->pred_gain;        /* il mange */
        if (res.energie <= 0 || c.age + 1 > r->pred_age_max)
            res = case_vide();                  /* faim ou vieillesse */
        else
            res.age = c.age + 1;
    }
    return res;
}

Cellule appliquer_regle(Cellule c, Voisinage v, const Regles *r)
{
    Cellule res = c;
    int n = v.nb_proies;

    if (r == NULL || n < 0 || n > 8 || v.nb_predateurs < 0 || v.nb_predateurs > 8)
        return res;

    if (r->mode == MODE_PROIES_PREDATEURS)
        return regle_pp(c, v.nb_proies, v.nb_predateurs, r);

    /* MODE_VIE */
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

/* Lit un fichier de règles, une information par ligne au format cle=valeur :
       # commentaire (ligne ignorée)
       nom=HighLife
       mode=vie
       bs=B36/S23
   Les lignes vides et celles qui commencent par # sont ignorées.
   Renvoie 0 si ok, -1 si le fichier est introuvable ou incorrect
   (et dans ce cas *r n'est pas modifiée). */
int charger_regles_fichier(Regles *r, const char *chemin)
{
    if (r == NULL || chemin == NULL)
        return -1;

    FILE *f = fopen(chemin, "r");
    if (f == NULL)
        return -1;                          /* fichier introuvable */

    char ligne[256];
    char nom[64] = "";
    char bs[64] = "";
    int erreur = 0;

    while (fgets(ligne, sizeof ligne, f) != NULL) {
        ligne[strcspn(ligne, "\r\n")] = '\0';  /* enlève la fin de ligne */

        if (ligne[0] == '\0' || ligne[0] == '#')
            continue;                       /* ligne vide ou commentaire */

        char *egal = strchr(ligne, '=');
        if (egal == NULL) {                 /* pas de '=' : ligne incorrecte */
            erreur = 1;
            break;
        }
        *egal = '\0';                       /* coupe la ligne en deux */
        const char *cle = ligne;
        const char *valeur = egal + 1;

        if (strcmp(cle, "nom") == 0) {
            strncpy(nom, valeur, sizeof nom - 1);
        } else if (strcmp(cle, "bs") == 0) {
            strncpy(bs, valeur, sizeof bs - 1);
        } else if (strcmp(cle, "mode") == 0) {
            if (strcmp(valeur, "vie") != 0) {   /* proies/prédateurs : phase 3 */
                erreur = 1;
                break;
            }
        } else {                            /* clé inconnue */
            erreur = 1;
            break;
        }
    }
    fclose(f);

    if (erreur || bs[0] == '\0')
        return -1;

    /* la lecture de "B36/S23" est déjà écrite : on la réutilise */
    return regles_depuis_chaine(r, nom, bs);
}