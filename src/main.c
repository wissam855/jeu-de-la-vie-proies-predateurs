#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grille.h"
#include "simulation.h"
#include "affichage.h"
#include "menu.h"
#include "io.h"

int main(int argc, char *argv[])
{
    Parametres p;
    parametres_par_defaut(&p);

    /* ./simulation motifs/planeur.txt : on part d'un motif */
    if (argc > 1) {
        strncpy(p.motif, argv[1], sizeof p.motif - 1);
        p.motif[sizeof p.motif - 1] = '\0';
    }

    /* graine du hasard : 0 = une grille différente à chaque lancement */
    if (p.graine == 0)
        srand((unsigned int)time(NULL));
    else
        srand(p.graine);

    /* 1. la grille de départ : un motif ou du hasard */
    Grille *actuelle;
    if (p.motif[0] != '\0') {
        actuelle = charger_motif(p.motif);
        if (actuelle == NULL) {
            fprintf(stderr, "Erreur : impossible de lire le motif %s\n", p.motif);
            return 1;
        }
    } else {
        actuelle = creer_grille(p.lignes, p.colonnes);
        if (actuelle == NULL) {
            fprintf(stderr, "Erreur : impossible de creer la grille\n");
            return 1;
        }
        remplir_aleatoire(actuelle, p.p_proie, p.p_predateur);
    }

    /* 2. la deuxième grille, de la même taille */
    Grille *suivante = creer_grille(actuelle->lignes, actuelle->colonnes);
    if (suivante == NULL) {
        fprintf(stderr, "Erreur : impossible de creer la grille\n");
        detruire_grille(actuelle);
        return 1;
    }

    /* 3. la boucle : afficher, calculer la suite, échanger, attendre */
    for (int gen = 0; gen < p.nb_generations; gen++) {
        effacer_ecran();
        afficher_grille(actuelle, p.couleurs);
        afficher_stats(calculer_stats(actuelle, gen), &p.regles);

        etape_suivante(actuelle, suivante, &p.regles, p.tore);

        Grille *tmp = actuelle;      /* échange des deux pointeurs : */
        actuelle = suivante;         /* la nouvelle génération devient */
        suivante = tmp;              /* l'actuelle, sans rien copier */

        pause_ms(p.delai_ms);
    }

    /* 4. on libère tout */
    detruire_grille(actuelle);
    detruire_grille(suivante);
    return 0;
}
