# Journal de bord

*Les séances du 10 au 18/11 ont été écrites le 25/11 à partir de l'historique Git (commits, pull requests, tags). Les « présents » sont ceux qui ont poussé du code ou des documents ce jour-là.*

## Séance du 10/11 — présents (d'après Git) : Wissam, Nizar
- Fait : création du dépôt, de l'arborescence et du `.gitignore` ; README avec la description du projet et le tableau de l'équipe (Wissam) ; plan de projet, préparé par Nizar avec l'IA (conversations notées plus tard dans le journal IA, entrées IA-01 à IA-03).
- Décisions prises : les quatre rôles (coordinateur, distributeur, producteur, éditeur) et le responsable de chaque fichier, notés dans le README.
- À faire (qui → quoi) : Nizar → document des tâches de chacun ; Wissam → `types.h` et `main.c` minimal.
- Blocages : aucun noté.

## Séance du 13/11 — présents (d'après Git) : Wissam, Nizar
- Fait : `types.h` et `main.c` minimal (Wissam, PR #1) ; document « Tâches, étapes et ordre de chacun » (Nizar).
- Décisions prises : une tâche = une issue = une branche = une pull request, relue par un autre membre avant la fusion ; `main` protégée (une approbation obligatoire).
- À faire : chacun → les fichiers `.h` de la phase 0 (structures et prototypes de ses fichiers).
- Blocages : aucun noté.

## Séance du 14/11 — présents (d'après Git) : Wissam, Elamine, John-Lucas, Nizar
- Fait : phase 0 terminée avec les fichiers `.h` et le Makefile (PR #2 à #7) : `regles.h` (Nizar), `grille.h` et `simulation.h` (Elamine), `affichage.h` et `io.h` (John-Lucas), `menu.h` (Wissam), Makefile (John-Lucas), modèles des trois journaux (Nizar).
- Décisions prises : on commence la phase 1 (Conway dans le terminal) avec une tâche par personne : W5 `menu.c`, N3 `regles.c`, J4 `affichage.c`, E3 `grille.c`.
- À faire : Nizar → entrées IA-01 à IA-03 dans le dépôt ; John-Lucas → choisir comment lancer le programme sur son PC ; Elamine → vérifier que `make` compile sur son PC.
- Blocages : sur le PC de John-Lucas, Windows bloque le lancement du programme (erreur 4551, Smart App Control) ; chez Elamine, `make` est installé grâce à une clé USB, le serveur MinGW refusant le téléchargement.

## Séance du 16/11 — présents (d'après Git) : Wissam, Elamine, Nizar (John-Lucas sans commit ce jour-là)
- Fait : entrées IA-01 à IA-03 du journal IA (PR #21) ; E3 `grille.c` : `creer_grille`, `detruire_grille`, `vider_grille`, `copier_grille` et leurs tests (PR #22) ; N3 `regles.c` avec Conway B3/S23 et le début du catalogue (PR #23) ; N4 les 18 cas de test de Conway (PR #24) ; E4 `remplir_aleatoire` et `compter_voisins` (PR #25) ; W5 `menu.c` et paramètres par défaut (PR #26) ; E5 `simulation.c` avec `etape_suivante` et `calculer_stats` (PR #27).
- Décisions prises : chaque fonction est livrée avec ses tests dans la même pull request.
- À faire : John-Lucas → J4 `affichage.c` ; Wissam → W6 `main.c` v1.
- Blocages : aucun noté.

## Séance du 17/11 — présents (d'après Git) : Wissam, John-Lucas (Nizar et Elamine sans commit ce jour-là)
- Fait : J4 `affichage.c` (grille, statistiques, couleurs, pause, PR #28) ; W6 `main.c` v1 (PR #29) ; J5 `charger_motif` et les motifs bloc, clignotant et planeur (PR #30) ; J6 cibles `make test` et `make valgrind` (PR #31) ; W7 `main.c` v2 avec la boucle de simulation et un motif en argument (PR #32).
- Décisions prises : le motif de départ peut être donné en argument au programme.
- À faire : Nizar → N5 README ; Wissam → W8 menu des paramètres.
- Blocages : aucun noté.

## Séance du 18/11 — présents (d'après Git) : Wissam, Elamine, John-Lucas, Nizar
- Fait : fin de la phase 1 (README, PR #33), puis phase 2 (règles modifiables) : N6 lecture d'une règle B/S (PR #34), W8 menu des paramètres (PR #35), N7 fichiers de règles (PR #36), N8 catalogue de 6 règles (PR #37), W9 choix de la règle dans le menu (PR #38), E6 test du tore, le planeur revient à sa place après 32 générations (PR #40), J7 notation B/S sous la grille (PR #44) ; essais T2.7 de chacun (Nizar : Maze et Life without Death, Elamine : Day & Night, Wissam : Conway et HighLife, John-Lucas : Seeds, PR #41 à #43 et #45).
- Décisions prises : chaque membre fait ses essais T2.7 deux fois et les note dans `docs/experiences.md`.
- À faire : préparer la release v0.2 ; John-Lucas → J8 et J9 ; Nizar → N9 ; Elamine → E7.
- Blocages : sous Windows, le test du menu ne pouvait pas supprimer `test_saisie.txt` (fichier encore ouvert) ; corrigé en fermant l'entrée standard avant de supprimer le fichier (PR #39).

## Séance du 19/11 — présents : Wissam, Elamine, Nizar (John-Lucas absent)
- Fait depuis la dernière fois : phase 2 terminée (N6, N7, N8, W8, W9, J7, E6, expériences T2.7 de chacun).
- Décisions prises : on prépare la release v0.2 sans attendre John-Lucas ; ses tâches J8 et J9 lui restent.
- À faire (qui → quoi) : Wissam → release v0.2 ; Nizar → N9 ; Elamine → E7.
- Blocages : John-Lucas absent, Nizar relit les PR de Wissam à sa place.

## Séance du 20/11 — présents : Wissam, Elamine, Nizar (John-Lucas absent)
- Fait : release v0.2 (tag sur adb3ba5) ; N9 (règle proies/prédateurs, 7e règle du catalogue, PR #46) ; N10 (paramètres proies/prédateurs dans les fichiers de règles, PR #47) ; E7 (six cas validés à la main) ; E8 (initialiser_predateurs et tests, PR #48).
- Décisions prises : W10 est coupée en deux : W10a (prédateurs et graine dans le menu) tout de suite, W10b (export stats.csv) après J9.
- À faire : John-Lucas → J8 et J9 à son retour ; Wissam → W10a.
- Blocages : J9 (export) attendue pour W10b.

## Séance du 21/11 — présents : Nizar, John-Lucas (Wissam absent l'après-midi, Elamine absent)
- Fait : J8 (test des couleurs, PR #49) et J9 (exporter_stats_csv, PR #50), relues par Nizar ; W10a (PR #51) et W10b (PR #52) faites par Nizar à la place de Wissam, avec son accord, et relues par John-Lucas. Wissam a fusionné depuis son téléphone.
- Décisions prises : sur le PC de John-Lucas, Smart App Control bloque le lancement des programmes compilés (« Permission denied ») ; il compile et pousse, et ses relecteurs lancent les tests. On ne désactive pas Smart App Control (impossible de le réactiver ensuite).
- À faire : John-Lucas → courbe des populations (fin de J9) ; tous → T3.8.
- Blocages : avec les paramètres de départ, les prédateurs disparaissent vers la génération 25.

## Séance du 22/11 — présents : Wissam, Nizar (John-Lucas et Elamine absents)
- Fait : début de T3.8. Méthode : grille 40 × 80, 30 % de proies, 3 % de prédateurs, graine 42, 500 générations, un seul paramètre changé à la fois, sur un fichier d'essai. Nizar → pred_energie_init (4, 6, 8) : aucun effet, les prédateurs disparaissent toujours à la génération 25. Wissam → pred_age_max (15, 25, 40).
- Décisions prises : les essais à comparer se font sur le même PC (avec la même graine, rand() ne donne pas les mêmes nombres sous Windows et sous Linux). John-Lucas testera seuil_predation, Elamine pred_gain ; on choisira les paramètres finaux quand les 4 essais seront faits.
- À faire : John-Lucas → courbe « avant » et son essai ; Elamine → son essai ; Nizar → paramètres finaux dans regles/ ; puis release v0.3.
- Blocages : John-Lucas et Elamine absents aujourd'hui.

## Séance du 23/11 — présents : Wissam, Nizar (John-Lucas et Elamine absents)
- Fait : T3.8 terminée. Essais pred_age_max de Wissam (PR #55) et de Nizar (PR #56 et #57, dont 12 graines différentes). Paramètres finaux : seuil_predation = 1 et pred_energie_init = 1 (PR #58) ; avec la graine 42, 403 proies et 355 prédateurs après 500 générations, et les deux espèces vivantes sur les 12 graines. Courbes avant / après dans docs/ (PR #59). Release v0.3 (tag sur ce75b97). Bonus web : export des états, choix 12 du menu et page web/index.html (PR #60, faite par Nizar à la place de John-Lucas). valgrind sur 8 cas, 0 fuite (PR #61). Commentaires de regles.c (PR #62). README complet (PR #63).
- Décisions prises : on arrête les essais dès qu'un jeu de paramètres marche (l'essai de pred_gain par Elamine et John-Lucas est abandonné) ; les tests test_pp.c et test_regles_pp.c fixent eux-mêmes leurs valeurs pour ne plus dépendre des paramètres du fichier ; la page web lit export/etats.js (et non un .json) parce qu'un navigateur bloque fetch() sur un fichier local ; valgrind n'existe pas sous Windows, les 8 essais ont été lancés sous Linux et Elamine les reconfirmera sous WSL ou à la fac.
- À faire : Wissam → commentaires de main.c et menu.c, relecture du README, puis test final depuis un clone vide et release v1.0 ; Nizar → journal IA, expériences, journal de bord ; Elamine → valgrind sous WSL, commentaires de grille.c et simulation.c ; John-Lucas → commentaires de affichage.c et io.c, démo et vidéo de secours ; tous → entrées du journal IA (2 chacun, dont un échec).
- Blocages : John-Lucas et Elamine toujours absents ; pas de valgrind sous Windows.

## Séance du 24/11 — présents : Wissam, Nizar (John-Lucas et Elamine absents)
- Fait : README complet (PR #63, Nizar). Commentaires de main.c et menu.c (PR #64, Wissam) : la gestion d'erreurs et les free ont été relus (W11), rien à changer, valgrind sur 7 cas : 0 erreur. charger_motif refuse maintenant les motifs invalides (en-tête hors de 1 à 1000, ligne trop courte ou trop longue, caractère inconnu, ligne en trop, fichier incomplet), avec fichier fermé et grille libérée ; tests/test_io.c passe de 3 à 11 cas (PR #69, J11 reprise par Nizar, issue #65 fermée). Commentaires de io.c et affichage.c (PR #70) puis de grille.c et simulation.c (PR #71), faits par Nizar à la place de John-Lucas et d'Elamine : tous les fichiers .c sont maintenant commentés (T5.3 terminée). Dépôt nettoyé (branches fusionnées supprimées), issues #66 (test final), #67 (release v1.0) et #68 (slides et oral) créées dans le tableau Projects.
- Décisions prises : l'oral est supposé le 2 décembre (à confirmer sur le planning) ; le jeu sera rendu par le lien GitHub et par une archive zip du code ; le rapport et le PowerPoint se font à la fin, quand toutes les autres tâches seront terminées.
- À faire : Nizar → journal de bord, nettoyage de docs/experiences.md, assemblage du journal IA ; Wissam → ses entrées du journal IA, puis test final depuis un clone vide (#66) et release v1.0 avec le zip (#67) ; Elamine → valgrind sous WSL ; John-Lucas → démo et vidéo de secours ; tous → 2 entrées du journal IA chacun, dont un échec ; puis slides, rapport et 2 répétitions chronométrées.
- Blocages : John-Lucas et Elamine toujours absents ; valgrind pas encore reconfirmé sous WSL.
