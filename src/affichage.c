#ifdef _WIN32
#include <windows.h>
#else
#define _POSIX_C_SOURCE 199309L
#include <time.h>
#endif

#include <stdio.h>
#include "affichage.h"

/* Codes couleur ANSI */
#define VERT  "\033[32m"
#define ROUGE "\033[31m"
#define RESET "\033[0m"

void effacer_ecran(void)
{
    /* efface l'écran et remet le curseur en haut à gauche */
    printf("\033[2J\033[H");
}

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

void afficher_stats(Stats s, const Regles *r)
{
    printf("Generation %d | proies : %d | predateurs : %d | regle : %s\n",
           s.generation, s.nb_proies, s.nb_predateurs,
           r != NULL ? r->nom : "?");
}

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
