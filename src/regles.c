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
    r->seuil_predation = 1;       /* 1 prédateur voisin ou plus : la proie est mangée */
    r->pred_energie_init = 1;     /* énergie d'un nouveau prédateur */
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

/* Lit "2-3" dans *min et *max. Renvoie 0 si ok, -1 sinon. */
static int lire_intervalle(const char *valeur, int *min, int *max)
{
    char reste;
    /* %c doit ne rien trouver après le 2e nombre : "2-3x" est refusé */
    if (sscanf(valeur, "%d-%d%c", min, max, &reste) != 2)
        return -1;
    if (*min < 0 || *max > 8 || *min > *max)
        return -1;
    return 0;
}

/* Lit un entier positif ou nul dans *x. Renvoie 0 si ok, -1 sinon. */
static int lire_nombre(const char *valeur, int *x)
{
    char reste;
    if (sscanf(valeur, "%d%c", x, &reste) != 1 || *x < 0)
        return -1;
    return 0;
}

/* Lit un fichier de règles, une information par ligne au format cle=valeur.
   Mode vie (le mode par défaut) :
       nom=HighLife
       mode=vie
       bs=B36/S23
   Mode proies/prédateurs :
       nom=Proies-Predateurs
       mode=pp
       proie_naissance=2-3
       proie_survie=1-5
       seuil_predation=2
       pred_energie_init=4
       pred_gain=2
       pred_age_max=15
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
    int mode_pp = 0;                        /* 0 : vie, 1 : proies/prédateurs */
    Regles pp;                              /* les valeurs lues en mode pp */
    memset(&pp, 0, sizeof pp);
    int vus = 0;                            /* nombre de clés pp lues (il en faut 6) */
    int erreur = 0;

    while (fgets(ligne, sizeof ligne, f) != NULL && !erreur) {
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
            if (strcmp(valeur, "vie") == 0)
                mode_pp = 0;
            else if (strcmp(valeur, "pp") == 0)
                mode_pp = 1;
            else
                erreur = 1;                 /* mode inconnu */
        } else if (strcmp(cle, "proie_naissance") == 0) {
            erreur = lire_intervalle(valeur, &pp.proie_naissance_min, &pp.proie_naissance_max) != 0;
            vus++;
        } else if (strcmp(cle, "proie_survie") == 0) {
            erreur = lire_intervalle(valeur, &pp.proie_survie_min, &pp.proie_survie_max) != 0;
            vus++;
        } else if (strcmp(cle, "seuil_predation") == 0) {
            erreur = lire_nombre(valeur, &pp.seuil_predation) != 0;
            vus++;
        } else if (strcmp(cle, "pred_energie_init") == 0) {
            erreur = lire_nombre(valeur, &pp.pred_energie_init) != 0;
            vus++;
        } else if (strcmp(cle, "pred_gain") == 0) {
            erreur = lire_nombre(valeur, &pp.pred_gain) != 0;
            vus++;
        } else if (strcmp(cle, "pred_age_max") == 0) {
            erreur = lire_nombre(valeur, &pp.pred_age_max) != 0;
            vus++;
        } else {                            /* clé inconnue */
            erreur = 1;
        }
    }
    fclose(f);

    if (erreur)
        return -1;

    if (!mode_pp) {
        /* mode vie : il faut une notation B/S et aucune clé pp */
        if (bs[0] == '\0' || vus != 0)
            return -1;
        /* la lecture de "B36/S23" est déjà écrite : on la réutilise */
        return regles_depuis_chaine(r, nom, bs);
    }

    /* mode pp : les 6 clés, pas de notation B/S, et des valeurs sensées */
    if (vus != 6 || bs[0] != '\0')
        return -1;
    if (pp.seuil_predation < 1 || pp.seuil_predation > 8 ||
        pp.pred_energie_init < 1 || pp.pred_age_max < 1)
        return -1;

    pp.mode = MODE_PROIES_PREDATEURS;
    strncpy(pp.nom, nom[0] != '\0' ? nom : "Proies-Predateurs", sizeof pp.nom - 1);
    *r = pp;
    return 0;
}