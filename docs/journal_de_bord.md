# Journal de bord

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
