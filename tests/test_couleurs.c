#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "affichage.h"
#include "grille.h"

/* Affiche g dans test_tmp.txt au lieu de l'écran, puis relit tout dans buf.
   (freopen : les printf de afficher_grille vont dans le fichier) */
static void capturer(const Grille *g, int couleurs, char *buf, int taille)
{
    assert(freopen("test_tmp.txt", "w", stdout) != NULL);
    afficher_grille(g, couleurs);
    fflush(stdout);

    FILE *f = fopen("test_tmp.txt", "r");
    assert(f != NULL);
    size_t n = fread(buf, 1, (size_t)taille - 1, f);
    buf[n] = '\0';
    fclose(f);
}

int main(void)
{
    /* une grille 1 x 3 : proie, prédateur, vide */
    Grille *g = creer_grille(1, 3);
    assert(g != NULL);
    g->cases[0][0].type = PROIE;
    g->cases[0][1].type = PREDATEUR;

    char buf[256];

    /* Test 1 : sans couleurs, aucun code ANSI */
    capturer(g, 0, buf, (int)sizeof buf);
    assert(strcmp(buf, "oX.\n") == 0);
    assert(strchr(buf, '\033') == NULL);

    /* Test 2 : avec couleurs, proie en vert, prédateur en rouge, puis retour normal */
    capturer(g, 1, buf, (int)sizeof buf);
    assert(strcmp(buf, "\033[32mo\033[0m\033[31mX\033[0m.\n") == 0);

    detruire_grille(g);
    fclose(stdout);               /* sous Windows, un fichier ouvert ne peut pas etre supprime */
    remove("test_tmp.txt");
    /* stdout est fermé : le message passe par stderr */
    fprintf(stderr, "Tous les tests des couleurs sont OK\n");
    return 0;
}
