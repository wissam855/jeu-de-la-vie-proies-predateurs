# Jeu de la vie Proies/Prédateurs

Automate cellulaire proies/prédateurs écrit en C (SAE L2 Informatique).

Le programme simule d'abord le jeu de la vie de Conway (règle B3/S23), puis
des règles modifiables (notation B/S, fichiers `.txt`) et enfin un modèle
proies/prédateurs. L'affichage se fait en texte dans le terminal.

## Équipe

| Membre | Rôle | Fichiers responsables | Binôme de secours |
|---|---|---|---|
| Wissam ABASSE | Coordinateur | `main.c`, `menu.c` | John-Lucas |
| John-Lucas BOYER | Distributeur | `affichage.c`, `io.c`, `Makefile`, `motifs/`, `web/` | Wissam |
| Elamine HOUSSENI | Producteur | `grille.c`, `simulation.c`, `tests/` | Nizar |
| Nizar AHMED ATTOUMANI | Éditeur | `regles.c`, `regles/`, `docs/` | Elamine |

## Arborescence

- `include/` : fichiers d'en-tête (`.h`)
- `src/` : code source (`.c`)
- `regles/` : fichiers de règles
- `motifs/` : grilles de départ (planeur, clignotant...)
- `tests/` : tests automatiques
- `export/` : états exportés (générés)
- `web/` : page web (bonus)
- `docs/` : journal de bord, journal IA, expériences, rapport

## Compilation et utilisation

### Prérequis

- `gcc` (C99) et `make` (sous Windows : MinGW, la commande s'appelle `mingw32-make`)
- un terminal qui comprend les couleurs ANSI (Git Bash, terminal Linux ou macOS)
- `valgrind` (facultatif, Linux ou WSL) pour vérifier la mémoire

### Compiler

```bash
make            # compile le programme "simulation"
make clean      # efface les fichiers de compilation (.o, simulation, test_bin)
```

### Lancer

```bash
./simulation                        # grille 20 x 40 remplie au hasard (30 % de cellules vivantes)
./simulation motifs/planeur.txt     # part d'un motif : le planeur traverse la grille
./simulation motifs/clignotant.txt  # trois cellules qui oscillent
./simulation motifs/bloc.txt        # un carré qui ne bouge pas
```

`make run` compile puis lance `./simulation`.

Affichage : `.` = case vide, `o` = proie (vert), `X` = prédateur (rouge).
Sous la grille : numéro de génération, nombre de proies et de prédateurs, nom de la règle.

Valeurs par défaut (`src/menu.c`) : 100 générations, 100 ms entre deux générations,
bords reliés (tore), règle de Conway B3/S23.

### Format d'un motif

Première ligne : nombre de lignes et de colonnes. Ensuite, une ligne de texte par ligne de grille.

```text
5 5
.....
.....
.ooo.
.....
.....
```

### Tests

```bash
make test       # compile et lance chaque fichier tests/test_*.c, s'arrête au premier échec
make valgrind   # lance le programme sous valgrind (Linux ou WSL)
```

| Fichier de test | Ce qu'il vérifie |
|---|---|
| `tests/test_grille.c` | création, copie, vidage et libération d'une grille |
| `tests/test_voisins.c` | comptage des voisins, avec et sans tore ; remplissage aléatoire |
| `tests/test_regles.c` | les 18 cas de Conway (0 à 8 voisins, case vide ou vivante) |
| `tests/test_simulation.c` | bloc stable, clignotant, cellule seule, statistiques |
| `tests/test_io.c` | lecture des motifs, fichier introuvable |

## Avancement

- **v0.1** : jeu de la vie de Conway dans le terminal, grille aléatoire ou motif, tests automatiques.
- À venir : règles modifiables (notation B/S, fichiers de règles), modèle proies/prédateurs, export et page web.
