#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "io.h"

int main(void)
{
    /* Test 1 : f = NULL renvoie -1 */
    Stats s0 = { 0, 10, 2 };
    assert(exporter_stats_csv(NULL, s0) == -1);

    /* Test 2 : on écrit 3 générations dans un fichier */
    FILE *f = fopen("test_tmp.txt", "w");
    assert(f != NULL);
    Stats s1 = { 1, 12, 3 };
    Stats s2 = { 2, 9, 4 };
    assert(exporter_stats_csv(f, s0) == 0);
    assert(exporter_stats_csv(f, s1) == 0);
    assert(exporter_stats_csv(f, s2) == 0);
    fclose(f);

    /* Test 3 : on relit le fichier ligne par ligne */
    f = fopen("test_tmp.txt", "r");
    assert(f != NULL);
    char ligne[64];

    assert(fgets(ligne, sizeof ligne, f) != NULL);
    assert(strcmp(ligne, "generation,proies,predateurs\n") == 0);   /* l'en-tête, une seule fois */
    assert(fgets(ligne, sizeof ligne, f) != NULL);
    assert(strcmp(ligne, "0,10,2\n") == 0);
    assert(fgets(ligne, sizeof ligne, f) != NULL);
    assert(strcmp(ligne, "1,12,3\n") == 0);
    assert(fgets(ligne, sizeof ligne, f) != NULL);
    assert(strcmp(ligne, "2,9,4\n") == 0);
    assert(fgets(ligne, sizeof ligne, f) == NULL);                  /* rien de plus */
    fclose(f);

    remove("test_tmp.txt");
    printf("Tous les tests de l'export stats.csv sont OK\n");
    return 0;
}
