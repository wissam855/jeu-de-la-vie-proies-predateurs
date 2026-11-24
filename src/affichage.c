#ifdef _WIN32
#include <windows.h>
#else
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#endif

#include <stdio.h>
#include <string.h>
#include "affichage.h"

/* Codes couleur ANSI */
#define VERT  "\033[32m"
#define ROUGE "\033[31m"
#define RESET "\033[0m"

/* Efface le terminal et remet le curseur en haut à gauche (code ANSI).
   Aucun paramètre, pas de valeur renvoyée. */
void effacer_ecran(void)
{
    /* efface l'écran et remet le curseur en haut à gauche */
    printf("\033[2J\033[H");
}

/* Affiche la grille dans le terminal : '.' = case vide, 'o' = proie, 'X' = prédateur.
   Paramètres : g = la grille à afficher (s'il est NULL, rien n'est affiché),
   couleurs = 1 pour les proies en vert et les prédateurs en rouge, 0 pour sans couleur.
   Pas de valeur renvoyée. */
void afficher_grille(const Grille *g, int couleurs)
{
    if (g == NULL)
        return;
    for (int i = 0; i < g->lignes; i++) {
        for (int j = 0; j < g->colonnes; j++) {
            TypeCellule t = g->cases[i][j].type;
            if (t == PROIE) {
                if (couleurs)
                    printf(VERT "o" RESET);
                else
                    printf("o");
            } else if (t == PREDATEUR) {
                if (couleurs)
                    printf(ROUGE "X" RESET);
                else
                    printf("X");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

/* Écrit la notation B/S de la règle dans buf (par exemple "B3/S23"). En mode
   proies/prédateurs, écrit "proies/predateurs". Si r est NULL, buf reste vide ; si buf
   est NULL ou taille <= 0, la fonction ne fait rien.
   Paramètres : r = la règle, buf = le tableau où écrire, taille = sa taille (l'écriture
   ne la dépasse jamais).
   Pas de valeur renvoyée. */
void notation_bs(const Regles *r, char *buf, int taille)
{
    if (buf == NULL || taille <= 0)
        return;
    buf[0] = '\0';
    if (r == NULL)
        return;
    if (r->mode != MODE_VIE) {
        snprintf(buf, (size_t)taille, "proies/predateurs");
        return;
    }

    /* "B" + jusqu'à 9 chiffres + "/S" + jusqu'à 9 chiffres + '\0' = 22 cases max */
    char tmp[32];
    int k = 0;
    tmp[k++] = 'B';
    for (int n = 0; n <= 8; n++)
        if (r->naissance[n])
            tmp[k++] = (char)('0' + n);    /* le chiffre n en caractère */
    tmp[k++] = '/';
    tmp[k++] = 'S';
    for (int n = 0; n <= 8; n++)
        if (r->survie[n])
            tmp[k++] = (char)('0' + n);
    tmp[k] = '\0';

    snprintf(buf, (size_t)taille, "%s", tmp);  /* copie sans dépasser */
}

/* Affiche la ligne de statistiques d'une génération : son numéro, le nombre de proies et
   de prédateurs, le nom de la règle, puis sa notation B/S si le nom ne la contient pas déjà.
   Paramètres : s = les compteurs de la génération, r = la règle (s'il est NULL, le nom
   affiché est « ? »).
   Pas de valeur renvoyée. */
void afficher_stats(Stats s, const Regles *r)
{
    char bs[32];
    notation_bs(r, bs, (int)sizeof bs);

    printf("Generation %d | proies : %d | predateurs : %d | regle : %s",
           s.generation, s.nb_proies, s.nb_predateurs,
           r != NULL ? r->nom : "?");

    /* on ajoute la notation seulement si le nom ne la contient pas déjà */
    if (r != NULL && bs[0] != '\0' && strstr(r->nom, bs) == NULL)
        printf(" [%s]", bs);
    printf("\n");
}

/* Attend ms millisecondes (Sleep sous Windows, nanosleep ailleurs). Ne fait rien si ms <= 0.
   Paramètre : ms = la durée de la pause, en millisecondes.
   Pas de valeur renvoyée. */
void pause_ms(int ms)
{
    if (ms <= 0)
        return;
#ifdef _WIN32
    Sleep(ms);
#else
    struct timespec t;
    t.tv_sec = ms / 1000;
    t.tv_nsec = (ms % 1000) * 1000000L;
    nanosleep(&t, NULL);
#endif
}
