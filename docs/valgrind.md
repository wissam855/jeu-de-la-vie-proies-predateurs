# Résultats de valgrind (tâche E9)

Commande utilisée pour chaque cas (les touches du menu sont envoyées avec `printf`) :

    valgrind --leak-check=full --show-leak-kinds=all ./simulation

Environnement : Linux (Ubuntu 24.04), gcc 13.3, valgrind 3.22.0, code de la branche `main` après le merge de la page web.
Ces essais ont été lancés depuis un environnement Linux (Windows n'a pas valgrind). Elamine peut les relancer sous WSL ou sur une machine de la fac pour confirmer.

| Cas | Ce qui est lancé | Allocations / libérations | Résultat |
|---|---|---|---|
| Conway aléatoire | grille 20 x 30, 20 générations | 46 / 46 | 0 fuite, 0 erreur |
| Motif | motifs/planeur.txt | 28 / 28 | 0 fuite, 0 erreur |
| Règle depuis un fichier | regles/highlife.txt | 48 / 48 | 0 fuite, 0 erreur |
| Proies / prédateurs | regles/proies_predateurs.txt, 30 % de proies | 48 / 48 | 0 fuite, 0 erreur |
| Exports activés | choix 11 (stats.csv) et 12 (etats.js) | 56 / 56 | 0 fuite, 0 erreur |
| Erreur : motif introuvable | motifs/nexiste_pas.txt | 3 / 3 | 0 fuite, 0 erreur, message d'erreur |
| Erreur : règles fausses | fichier absent, puis B3/X | 47 / 47 | 0 fuite, 0 erreur, ancienne règle gardée |
| Erreur : saisie invalide | "abc" puis -5 au menu | 2 / 2 | 0 fuite, 0 erreur |

Dans les 8 cas, valgrind affiche : `All heap blocks were freed -- no leaks are possible` et `ERROR SUMMARY: 0 errors`.
