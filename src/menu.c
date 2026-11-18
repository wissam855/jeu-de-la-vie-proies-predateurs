#include <stdio.h>
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
        printf("5. Proies au depart          : %d %%\n", (int)(p->p_proie * 100 + 0.5));
        printf("6. Motif de depart           : %s\n",
               p->motif[0] != '\0' ? p->motif : "(grille aleatoire)");
        printf("7. Bords relies (tore)       : %s\n", p->tore ? "oui" : "non");
        printf("8. Couleurs                  : %s\n", p->couleurs ? "oui" : "non");
        printf("0. Quitter\n");

        int choix = lire_entier("Ton choix", 0, 8);
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
        case 5:
            p->p_proie = lire_entier("Pourcentage de proies", 0, 100) / 100.0;
            break;
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
        }
    }
}
