#include <stdio.h>
#include <string.h>
#include "menu.h"

/* Remplit p avec les valeurs par défaut : grille 20 x 40, 100 générations, pause de 100 ms,
   bords reliés, couleurs, 30 % de proies, règle de Conway.
   Paramètre : p = les paramètres à remplir (s'il est NULL, la fonction ne fait rien).
   Pas de valeur renvoyée. */
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

    /* motif[0] = '\0' (pas de motif), exporter = 0, exporter_web = 0, graine = 0 :
       déjà mis à zéro par memset */

    /* la règle : la première du catalogue (Conway B3/S23) */
    p->regles = catalogue_regles(NULL)[0];
}

/* Lit un entier entre min et max ; redemande tant que la saisie est fausse.
   Si l'entrée est fermée (fin de fichier), renvoie min. */
static int lire_entier(const char *question, int min, int max)
{
    char ligne[64];
    int x;
    for (;;) {
        printf("%s (%d a %d) : ", question, min, max);
        fflush(stdout);
        if (fgets(ligne, sizeof ligne, stdin) == NULL)
            return min;
        if (sscanf(ligne, "%d", &x) == 1 && x >= min && x <= max)
            return x;
        printf("Valeur invalide, recommence.\n");
    }
}

/* Lit une ligne de texte (sans le retour à la ligne) dans dest. */
static void lire_texte(const char *question, char *dest, int taille)
{
    printf("%s : ", question);
    fflush(stdout);
    if (fgets(dest, taille, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    dest[strcspn(dest, "\r\n")] = '\0';
}

/* Sous-menu du choix 9 : change la règle de p.
   Si la nouvelle règle est invalide, l'ancienne est gardée. */
static void choisir_regle(Parametres *p)
{
    printf("\n--- Choix de la regle ---\n");
    printf("1. Une regle du catalogue\n");
    printf("2. Un fichier de regles (ex. regles/highlife.txt)\n");
    printf("3. Taper une regle B/S (ex. B36/S23)\n");
    printf("0. Retour\n");

    int choix = lire_entier("Ton choix", 0, 3);
    Regles nouvelle;
    char texte[256];
    int ok = -1;

    switch (choix) {
    case 0:
        return;                             /* on ne change rien */
    case 1: {
        int nb = 0;
        const Regles *cat = catalogue_regles(&nb);
        for (int i = 0; i < nb; i++)
            printf("%d. %s\n", i + 1, cat[i].nom);
        int n = lire_entier("Numero de la regle", 1, nb);
        nouvelle = cat[n - 1];              /* copie de la structure */
        ok = 0;
        break;
    }
    case 2:
        lire_texte("Chemin du fichier", texte, (int)sizeof texte);
        ok = charger_regles_fichier(&nouvelle, texte);
        break;
    case 3:
        lire_texte("Regle (ex. B36/S23)", texte, (int)sizeof texte);
        ok = regles_depuis_chaine(&nouvelle, texte, texte);
        break;
    }

    if (ok == 0) {
        p->regles = nouvelle;
        printf("Nouvelle regle : %s\n", p->regles.nom);
    } else {
        printf("Regle invalide, on garde : %s\n", p->regles.nom);
    }
}

/* Affiche le menu en boucle et modifie p selon les choix de l'utilisateur (taille, pause,
   proportions, motif, tore, couleurs, règle, graine, exports).
   Paramètre : p = les paramètres à modifier.
   Renvoie : 0 pour lancer une simulation (choix 1), 1 pour quitter (choix 0, ou p NULL). */
int menu_principal(Parametres *p)
{
    if (p == NULL)
        return 1;

    for (;;) {
        printf("\n========== Jeu de la vie ==========\n");
        printf("Regle : %s\n\n", p->regles.nom);
        printf("1. Lancer la simulation\n");
        printf("2. Taille de la grille       : %d x %d\n", p->lignes, p->colonnes);
        printf("3. Nombre de generations     : %d\n", p->nb_generations);
        printf("4. Pause entre generations   : %d ms\n", p->delai_ms);
        printf("5. Proies / predateurs       : %d %% / %d %%\n",
               (int)(p->p_proie * 100 + 0.5), (int)(p->p_predateur * 100 + 0.5));
        printf("6. Motif de depart           : %s\n",
               p->motif[0] != '\0' ? p->motif : "(grille aleatoire)");
        printf("7. Bords relies (tore)       : %s\n", p->tore ? "oui" : "non");
        printf("8. Couleurs                  : %s\n", p->couleurs ? "oui" : "non");
        printf("9. Changer de regle\n");
        if (p->graine == 0)
            printf("10. Graine du hasard         : aleatoire\n");
        else
            printf("10. Graine du hasard         : %u\n", p->graine);
        printf("11. Export export/stats.csv  : %s\n", p->exporter ? "oui" : "non");
        printf("12. Export page web (etats.js) : %s\n", p->exporter_web ? "oui" : "non");
        printf("0. Quitter\n");

        int choix = lire_entier("Ton choix", 0, 12);
        switch (choix) {
        case 0:
            return 1;                       /* quitter */
        case 1:
            return 0;                       /* lancer */
        case 2:
            p->lignes = lire_entier("Nombre de lignes", 5, 100);
            p->colonnes = lire_entier("Nombre de colonnes", 5, 200);
            break;
        case 3:
            p->nb_generations = lire_entier("Nombre de generations", 1, 10000);
            break;
        case 4:
            p->delai_ms = lire_entier("Pause en millisecondes", 0, 2000);
            break;
        case 5: {
            /* proies + prédateurs ne doivent pas dépasser 100 % */
            int proies = lire_entier("Pourcentage de proies", 0, 100);
            int preds = lire_entier("Pourcentage de predateurs", 0, 100 - proies);
            p->p_proie = proies / 100.0;
            p->p_predateur = preds / 100.0;
            break;
        }
        case 6:
            lire_texte("Fichier motif (ex. motifs/planeur.txt, vide = aleatoire)",
                       p->motif, (int)sizeof p->motif);
            break;
        case 7:
            p->tore = !p->tore;             /* oui <-> non */
            break;
        case 8:
            p->couleurs = !p->couleurs;
            break;
        case 9:
            choisir_regle(p);
            break;
        case 10:
            /* 0 = une grille différente à chaque fois ; un autre nombre (ex. 42)
               = la même grille de départ à chaque lancement */
            p->graine = (unsigned int)lire_entier("Graine (0 = aleatoire)", 0, 1000000);
            break;
        case 11:
            p->exporter = !p->exporter;     /* oui <-> non */
            break;
        case 12:
            p->exporter_web = !p->exporter_web;
            break;
        }
    }
}