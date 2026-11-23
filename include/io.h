#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "types.h"

/* Charge un motif (ex. motifs/planeur.txt). NULL si erreur. */
Grille *charger_motif(const char *chemin);

/* Ecrit la premiere ligne de export/etats.txt : LIGNES l COLONNES c REGLE nom.
   A appeler une seule fois, avant la generation 0. 0 si ok, -1 si erreur. */
int exporter_entete(FILE *f, const Grille *g, const char *regle);

/* Ecrit une generation dans le fichier d'export : la ligne "GEN n", puis la grille
   (. vide, o proie, X predateur). 0 si ok, -1 si erreur. */
int exporter_etat(FILE *f, const Grille *g, int generation);

/* Ecrit une ligne generation,proies,predateurs. 0 si ok, -1 si erreur. */
int exporter_stats_csv(FILE *f, Stats s);

/* Bonus web : convertit export/etats.txt en export/etats.js. 0 si ok, -1 si erreur. */
int convertir_export_js(const char *chemin_txt, const char *chemin_js);

#endif
