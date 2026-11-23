#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grille.h"
#include "simulation.h"
#include "affichage.h"
#include "menu.h"
#include "io.h"

/* Lance UNE simulation avec les paramètres p.
   Renvoie 0 si tout s'est bien passé, 1 en cas d'erreur. */
static int lancer_simulation(const Parametres *p)
{
    /* même graine = même grille de départ (utile pour comparer des essais) */
    if (p->graine != 0)
        srand(p->graine);

    /* 1. la grille de départ : un motif ou du hasard */
    Grille *actuelle;
    if (p->motif[0] != '\0') {
        actuelle = charger_motif(p->motif);
        if (actuelle == NULL) {
            fprintf(stderr, "Erreur : impossible de lire le motif %s\n", p->motif);
            return 1;
        }
    } else {
        actuelle = creer_grille(p->lignes, p->colonnes);
        if (actuelle == NULL) {
            fprintf(stderr, "Erreur : impossible de creer la grille\n");
            return 1;
        }
        remplir_aleatoire(actuelle, p->p_proie, p->p_predateur);
    }

    /* les prédateurs de départ ont 0 d'énergie : on leur donne celle de la règle
       (E8). En mode vie, il n'y a pas de prédateur : ça ne change rien. */
    initialiser_predateurs(actuelle, p->regles.pred_energie_init);

    /* 2. la deuxième grille, de la même taille */
    Grille *suivante = creer_grille(actuelle->lignes, actuelle->colonnes);
    if (suivante == NULL) {
        fprintf(stderr, "Erreur : impossible de creer la grille\n");
        detruire_grille(actuelle);
        return 1;
    }

    /* 3. l'export des populations (J9) : export/stats.csv, si le choix 11 est à oui.
       Si le fichier ne s'ouvre pas, on prévient et la simulation continue sans export. */
    FILE *csv = NULL;
    if (p->exporter) {
        csv = fopen("export/stats.csv", "w");
        if (csv == NULL)
            fprintf(stderr, "Attention : impossible d'ecrire export/stats.csv\n");
    }

    /* 3 bis. l'export pour la page web (J10) : export/etats.txt, si le choix 12 est à oui.
       La premiere ligne (taille + nom de la regle) est ecrite une seule fois. */
    FILE *etats = NULL;
    if (p->exporter_web) {
        etats = fopen("export/etats.txt", "w");
        if (etats == NULL)
            fprintf(stderr, "Attention : impossible d'ecrire export/etats.txt\n");
        else
            exporter_entete(etats, actuelle, p->regles.nom);
    }

    /* 4. la boucle : afficher, exporter, calculer la suite, échanger, attendre */
    for (int gen = 0; gen < p->nb_generations; gen++) {
        Stats s = calculer_stats(actuelle, gen);

        effacer_ecran();
        afficher_grille(actuelle, p->couleurs);
        afficher_stats(s, &p->regles);
        if (csv != NULL)
            exporter_stats_csv(csv, s);
        if (etats != NULL)
            exporter_etat(etats, actuelle, gen);

        etape_suivante(actuelle, suivante, &p->regles, p->tore);

        Grille *tmp = actuelle;      /* échange des deux pointeurs */
        actuelle = suivante;
        suivante = tmp;

        pause_ms(p->delai_ms);
    }

    /* 5. on ferme le fichier et on libère tout */
    if (csv != NULL) {
        fclose(csv);
        printf("Populations enregistrees dans export/stats.csv\n");
    }
    if (etats != NULL) {
        fclose(etats);
        /* etats.txt -> etats.js : c'est ce fichier que lit la page web */
        if (convertir_export_js("export/etats.txt", "export/etats.js") == 0)
            printf("Page web : ouvrir web/index.html (donnees dans export/etats.js)\n");
        else
            fprintf(stderr, "Attention : conversion en export/etats.js impossible\n");
    }
    detruire_grille(actuelle);
    detruire_grille(suivante);
    return 0;
}

int main(int argc, char *argv[])
{
    Parametres p;
    parametres_par_defaut(&p);

    /* ./simulation motifs/planeur.txt : le motif est déjà choisi dans le menu */
    if (argc > 1) {
        strncpy(p.motif, argv[1], sizeof p.motif - 1);
        p.motif[sizeof p.motif - 1] = '\0';
    }

    /* graine du hasard : 0 = une grille différente à chaque lancement */
    if (p.graine == 0)
        srand((unsigned int)time(NULL));
    else
        srand(p.graine);

    /* le menu revient après chaque simulation, jusqu'à "0. Quitter" */
    while (menu_principal(&p) == 0) {
        if (lancer_simulation(&p) != 0)
            printf("La simulation n'a pas pu demarrer.\n");
    }

    printf("Au revoir !\n");
    return 0;
}