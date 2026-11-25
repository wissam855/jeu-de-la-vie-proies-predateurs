# Journal d'utilisation de l'IA

Outil utilisé : Claude (assistant IA d'Anthropic), dans une conversation suivie depuis le 10/11.

Tout le code et toutes les instructions générés par l'IA sont passés par la conversation de Nizar, qui les a transmis aux autres membres. Chaque entrée dit qui a posé la question, qui a appliqué la réponse et ce qui n'a pas marché.

Règles de l'équipe : on copie le prompt exact, on note aussi ce qui n'a pas marché, et on n'intègre pas de code qu'on ne sait pas expliquer.

Les entrées IA-01 à IA-03 ont été préparées avec l'aide de l'IA à partir de la conversation, puis relues et complétées par l'équipe.

### IA-01 — 10/11 et 13/11 — Nizar — Claude
- **Objectif :** obtenir un plan de projet complet à partir du sujet et des deux échanges avec le prof.
- **Prompt 1 (10/11) :** le message exact est recopié dans le bloc ci-dessous.

```text
Résumé IA voici le résumé de la nous ce qu'on va faire c'est une simulation d'un autonome cellulaire Predator et proie comme je l'explique en haut ça sera à code en c , avec l'utilisation de git hub etc...  transcription entre le prof et moi. 
Objet : Changement des règles du jeu
Contenu : Lors d'une discussion sur un projet inspiré du jeu de la vie de , les intervenants évoquent la possibilité de modifier les règles de base du jeu pour créer des versions plus complexes. L'orateur 1 souligne l'importance de gérer et de représenter le monde tout en faisant évoluer le jeu. Il propose de commencer par utiliser les règles normales pour faire fonctionner le jeu avant d'introduire un module permettant de changer les règles. Cela offrirait la possibilité de créer des ensembles de règles et d'observer leurs effets sur l'évolution du jeu. L'orateur 2 s'interroge sur les choix de règles, tandis que l'orateur 3 illustre l'idée par un exemple. L'accent est mis sur la flexibilité et l'expérimentation dans la conception du projet.
Le contenu ci-dessus est généré par l'IA et est fourni à titre de référence uniquement.
Orateur 1 00:00:00
Et ça, c'est les règles de base.
Mais on peut changer les règles et on peut imaginer d'autres règles plus compliquées.
Par exemple, si on peut-on change nous-même les règles.
Voilà donc ce qui ce qui pourrait être intéressant à faire, c'est de faire une version du jeu de la vie où vous, dans votre projet, vous proposez de pouvoir changer les règles et de voir comment ça évolue en fait de donner, voilà.
Orateur 2 00:00:28
Et eux, ils vont utiliser Conway, c'est ça?
Orateur 1 00:00:30
Oui, ils vont faire celui de base.
Orateur 2 00:00:34
Celui le plus simple?
Orateur 1 00:00:38
Alors pas forcément.
De toute façon, il y a toujours à gérer le monde, le représenter et le faire évoluer.
Ça va être la même chose.
Mais eux, ils vont avoir qu'une manière de le faire évoluer.
Alors que vous pouvez avoir un module qui définit les règles pour le faire évoluer, par exemple, ça serait une.
Orateur 2 00:01:04
On doit utiliser quoi?
Orateur 1 00:01:09
Vous pouvez d'abord déjà faire avec les règles normales.
Voilà, comme ça, avoir le truc qui tourne.
Et vous allez voir que il y a pas grand-chose à faire.
En fait, vous mettez un un petit module qui change les règles.
Donc comme ça, vous pouvez faire des stocks de règles et puis vous allez les choisir et voir comment ça évolue.
Orateur 3 00:01:27
Par exemple.


Deuxième retranscription avec le prof Résumé IA
Objet : Gestion de projet en équipe
Contenu : L'orateur 1 encourage les participants à utiliser leurs connaissances en programmation, notamment en C et Python, tout en soulignant l'importance de la gestion de projet en équipe. Il insiste sur la nécessité de définir clairement les rôles de chacun pour faciliter l'évaluation à la fin du projet. L'utilisation de Git est suggérée pour le travail collaboratif, permettant de garder une trace des contributions de chacun. L'orateur 1 attend également des participants qu'ils montrent comment ils ont utilisé l'intelligence artificielle, en partageant les prompts et les résultats obtenus. Il souligne l'importance de la démarche expérimentale, même si les résultats ne sont pas satisfaisants, afin d'apprendre et d'améliorer le processus. L'orateur 2 acquiesce et mentionne que chacun peut faire un résumé des contributions.
Le contenu ci-dessus est généré par l'IA et est fourni à titre de référence uniquement.
Orateur 1 00:00:00
Essayez de vous faire utiliser ce que vous avez vu en L1 ou en L2 et de faire le lien avec.
Donc si vous voulez travailler sur le C, c'est pas mal.
Et comme c'est un petit peu plus, ça serait peut-être un peu plus compliqué à mettre en œuvre que le Python à ce moment-là, vous ne faites pas toute la partie web, c'est pas la peine de le faire.
Après, si une fois que ça sera terminé, vous avez envie de le faire, vous pouvez le faire pour faire évoluer ce que vous avez fait.
Est-ce que ça vous va?
Orateur 2 00:00:30
On sait juste l'interface en test, c'est ça, les.
Orateur 1 00:00:33
Affichages, on affiche le tableau dans le truc.
Orateur 2 00:00:37
Voilà, on n'est pas obligé de le lancer sur un autre programme, on n'est pas obligé de le lancer sur un autre programme.
Non, voilà, c'est ça.
Orateur 1 00:00:45
Déjà, c'est bien, c'est gérer les structures de, et cetera.
Orateur 2 00:00:50
En tout cas, vous l'avez dit, Monsieur, quoi que j'ai dit.
On les fait l'affichage en texte, pas oui, oui, OK, ça.
Orateur 1 00:01:19
Sinon, ce qui est important dans le projet, comme vous êtes plusieurs, c'est de savoir qui fait quoi.
Parce que quand à la fin, dans le dernier jour, vous allez passer un oral, qu'est-ce que vous avez fait?
?
Donc il faut bien savoir ce que chacun a fait, qu'on puisse identifier, donc comment vous répartissez les tâches, comment vous gérez le projet, si vous avez envie.
C'est possible d'utiliser Git puisque vous l'avez fait.
Orateur 2 00:01:45
Bien sûr, vous avez fait.
Orateur 1 00:01:46
Un travail collaboratif, donc c'est l'occasion de le mettre en œuvre et de vous expliquer comment vous avez fait.
Et moi, j'aurai les traces des comics, et cetera.
Donc on voit qui a fait quoi.
Donc votre organisation, c'est bien.
Voilà, moi, ce que j'attends, c'est que vous me dites comment vous êtes organisés, quand vous avez réparti les tâches ensuite.
Vous avez la possibilité d'utiliser l'IA, bien sûr, c'est l'occasion de tester.
À ce moment-là, il faudra me dire comment vous le faites?
Orateur 2 00:02:17
Chacun fait un résumé.
Orateur 1 00:02:18
Vous montrez les prompts que vous avez faits, ce que vous avez obtenu.
Éventuellement, si même si vous faites un essai, que ça ne vous convient pas, vous refaites le prompt pour faire mieux.
Ben vous le voilà, il faut avoir la démarche aussi parce que c'est l'occasion de tester et de voir que ce n'est pas forcément ce qu'on attend exactement.
Donc c'est vraiment ça que moi j'attends en fait, pour voir un peu comment vous menez un un projet, un travail en équipe.
Orateur 2 00:03:04
Oui.    Donc tu vas faire une liste de tous les tâches et de tous les étapes fait un truc simple , chaque nom et chacun a un rôle comme tu avais en haut mais on peut travailler directement ensemble   prends ton temps et prépare tout ça bien dans les détails.  On est 4 comme, mais vraiment tout les détails comme et pour et le fait...etc.....
```
- **Résultat :** un document « Plan de projet » : rôles, organisation, Git, architecture du code C (structures et prototypes), règles du jeu, phases, tests, journal IA, oral.
- **Problème :** les rôles Distributeur, Producteur et Éditeur ont été définis par l'IA et pas par le prof ; le plan n'a pas de dates ; il ne disait pas assez précisément qui commence et dans quel ordre.
- **Prompt 2 (13/11) :** « maintaint tu vas faire les les tache et les etapes et lordre de chacun , sur un autre document bien detailler »
- **Résultat :** un deuxième document « Tâches, étapes et ordre de chacun » : des tâches numérotées par personne (W, J, E, N), ce que chacune attend, et deux schémas de l'ordre.
- **Ce qu'on a gardé :** la répartition des fichiers par personne, les prototypes des fichiers .h, le cycle branche, pull request, relecture, fusion.
- **Ce qu'on a changé :** la tâche W4 (journal IA) est passée de Wissam à Nizar, car c'est lui qui avait les prompts ; make a été installé par clé USB depuis le PC de John-Lucas, car le serveur MinGW refusait le téléchargement ; les rôles proposés par l'IA ont été gardés.
- **Ce que j'ai appris :** un prompt vague donne un résultat général ; en demandant précisément « l'ordre de chacun », on a obtenu un plan qu'on pouvait vraiment suivre. Il faut relire ce que l'IA propose, car elle a inventé des définitions de rôles.

### IA-02 — 10/11 — Nizar — Claude
- **Objectif :** vérifier le dépôt GitHub créé par Wissam.
- **Prompt :** « https://github.com/wissam855/jeu-de-la-vie-proies-predateurs REGARDE SI C'est bon pour luiii wissam cest premier etape »
- **Résultat :** le dépôt, les dossiers et le .gitignore étaient corrects, mais le README s'affichait mal : chaque ligne commençait par un dièse et les symboles étaient échappés, donc tout apparaissait en gros titres et le tableau de l'équipe ne s'affichait pas.
- **Cause :** le texte avait été collé depuis un éditeur de texte riche.
- **Correction :** l'IA a fourni le fichier corrigé ; Wissam l'a collé dans l'éditeur de GitHub (commit « readme: correction de la mise en forme »).
- **Problème :** la dernière ligne n'a pas été collée, et le premier message de commit commençait par des espaces ; Wissam a refait un commit.
- **Ce que j'ai appris :** il ne faut pas coller du texte depuis Word ou Google Docs dans un fichier .md, et il faut vérifier l'onglet Preview avant de valider un commit.

### IA-03 — 10/11 — Nizar — Claude
- **Objectif :** protéger la branche main pour obliger à passer par des pull requests.
- **Prompt :** une capture de la page Settings du dépôt, avec la phrase du plan « Protéger main pour n'accepter que des pull requests (Settings, Branches) ».
- **Résultat :** les étapes à suivre : Settings, Branches, Add classic branch protection rule, main, Require a pull request before merging, Require approvals : 1.
- **Problème :** au premier essai, on était sur la mauvaise page (Planning, Agent suggestions for issues). On a envoyé une deuxième capture et l'IA a indiqué la bonne page.
- **Ce qu'on a gardé :** la règle est active : chaque changement passe par une branche, une pull request et l'approbation d'un autre membre.
- **Ce que j'ai appris :** envoyer une capture d'écran aide l'IA à guider précisément ; il faut vérifier qu'on est sur la bonne page avant de modifier les réglages du dépôt.

### IA-04 — 18/11 — Wissam (prompt de Nizar) — Claude
- **Objectif :** faire passer le test de saisie du menu (tâche W9, `test_saisie.txt`) sous Windows.
- **Prompt 1 (résumé) :** Nizar a demandé un test qui lance le programme avec un fichier de saisie pour vérifier le choix de la règle dans le menu (tâche W9).
- **Résultat :** l'IA a fourni le test, qui lance le programme avec un fichier de saisie, et le code du choix de la règle dans le menu.
- **Problème :** sous Windows, à la fin du test, le fichier `test_saisie.txt` ne pouvait pas être supprimé, parce qu'il était encore ouvert par le programme. Sous Linux, ça passait sans problème.
- **Prompt 2 (amélioré, résumé) :** Nizar a donné à l'IA le message d'erreur exact de Windows sur la suppression de `test_saisie.txt`, au lieu de décrire le problème en général.
- **Ce qu'on a gardé :** le test ferme l'entrée standard avant de supprimer le fichier, et `test_saisie.txt` est ajouté au `.gitignore` (PR n° 39).
- **Ce que j'ai appris :** sous Windows, on ne peut pas supprimer un fichier tant qu'il est encore ouvert, alors qu'il faut le fermer d'abord.

### IA-05 — 24/11 — Wissam (prompt de Nizar) — Claude
- **Objectif :** commenter toutes les fonctions de `main.c` et `menu.c` (tâche T5.3).
- **Prompt 1 (résumé) :** Nizar a demandé des commentaires pour toutes les fonctions de `main.c` et `menu.c`, avec la convention du projet (tâche T5.3).
- **Résultat :** l'IA a donné la règle à suivre (un commentaire juste au-dessus de chaque fonction : ce qu'elle fait, ses paramètres, ce qu'elle renvoie) et les commentaires à recopier.
- **Problème :** au premier essai, j'avais laissé une ligne vide entre le commentaire et la fonction, et il manquait une ligne vide avant le commentaire.
- **Prompt 2 (amélioré, résumé) :** Nizar a envoyé une photo de `main.c` pour que l'IA voie exactement où étaient les lignes vides.
- **Ce qu'on a gardé :** les commentaires de `main()`, `parametres_par_defaut()` et `menu_principal()`, collés directement au-dessus de la fonction, sans ligne vide entre `*/` et la signature (PR n° 64).
- **Ce que j'ai appris :** quand je ne comprends pas ce qui est faux, envoyer une photo de mon fichier permet de voir tout de suite l'erreur.

### IA-06 — 21/11 — John-Lucas (prompt de Nizar) — Claude
- **Objectif :** lancer les programmes compilés sur le PC de John-Lucas pour faire les tests des tâches J8 et J9.
- **Prompt 1 (résumé) :** Nizar a décrit l'erreur « Permission denied » au lancement des programmes sur le PC de John-Lucas et a demandé comment la corriger.
- **Résultat :** l'IA a expliqué que Windows (Smart App Control) bloquait le lancement des programmes compilés, avec l'erreur « Permission denied ».
- **Problème :** la solution évidente était de désactiver Smart App Control, mais on ne peut pas le réactiver ensuite.
- **Prompt 2 (amélioré, résumé) :** Nizar a demandé les solutions possibles et leurs conséquences, avant de choisir de ne pas désactiver Smart App Control.
- **Ce qu'on a gardé :** on ne désactive pas Smart App Control. John-Lucas compile et pousse son code, et ses relecteurs lancent les tests à sa place (J8 et J9, PR n° 49 et n° 50).
- **Ce que j'ai appris :** un blocage de Windows (Smart App Control) ne se contourne pas toujours : on a gardé la sécurité activée et on a fait lancer les tests par les relecteurs.

### IA-07 — 17/11 et 24/11 — John-Lucas (prompt de Nizar) — Claude
- **Objectif :** lire un motif depuis un fichier avec `charger_motif` (tâche J5), puis le rendre solide face aux fichiers invalides (tâche J11).
- **Prompt 1 (résumé) :** Nizar a demandé une fonction `charger_motif` qui lit un motif depuis un fichier et les motifs bloc, clignotant et planeur (tâche J5).
- **Résultat :** l'IA a fourni `charger_motif` et les motifs bloc, clignotant et planeur (PR n° 30).
- **Problème :** la première version ne refusait pas tous les motifs invalides (ligne trop courte ou trop longue, caractère inconnu, ligne en trop, fichier incomplet). C'est apparu en relisant la gestion des erreurs.
- **Prompt 2 (amélioré, résumé) :** Nizar a demandé que `charger_motif` refuse chaque motif invalide, en listant les cas à tester.
- **Ce qu'on a gardé :** `charger_motif` refuse les motifs invalides, ferme le fichier et libère la grille. `tests/test_io.c` passe de 3 à 11 cas (PR n° 69, tâche J11 reprise par Nizar).
- **Ce que j'ai appris :** il faut tester aussi les cas où le fichier est faux, pas seulement le cas où tout se passe bien.

### IA-08 — 20/11 — Elamine (prompt de Nizar) — Claude
- **Objectif :** donner de l'énergie aux prédateurs au départ avec `initialiser_predateurs` (tâche E8), et tester les proies et les prédateurs sur la grille.
- **Prompt 1 (résumé) :** Nizar a demandé les tests des proies et des prédateurs (tâche E8) et ce qu'il fallait faire de l'énergie des prédateurs.
- **Résultat :** l'IA a fourni `initialiser_predateurs` et les tests de `tests/test_pp.c` (PR n° 48).
- **Problème :** après `remplir_aleatoire`, les prédateurs ont une énergie de 0 : sans cette fonction, ils meurent dès la première génération.
- **Prompt 2 (amélioré, résumé) :** Nizar a demandé une fonction qui donne l'énergie de départ aux prédateurs après le remplissage aléatoire.
- **Ce qu'on a gardé :** `initialiser_predateurs(g, energie)` donne l'énergie à chaque prédateur et remet son âge à 0. `main.c` l'appelle après le remplissage aléatoire ou le chargement d'un motif (tâche W10a, PR n° 51).
- **Ce que j'ai appris :** une cellule créée au hasard a toutes ses valeurs à 0, donc l'énergie des prédateurs doit être donnée à part.

### IA-09 — 16/11 — Elamine (prompt de Nizar) — Claude
- **Objectif :** écrire `creer_grille`, `detruire_grille`, `vider_grille` et `copier_grille` en allocation dynamique (tâche E3).
- **Prompt 1 (résumé) :** Nizar a demandé les fonctions `creer_grille`, `detruire_grille`, `vider_grille` et `copier_grille` en allocation dynamique (tâche E3).
- **Résultat :** l'IA a fourni ces 4 fonctions avec une allocation en trois étages : la structure, un pointeur par ligne, puis les cellules (PR n° 22).
- **Problème :** aucun problème signalé. Le travail a été livré par étapes le 16/11 (`creer_grille` et `detruire_grille`, puis `vider_grille` et `copier_grille`, puis les tests de `grille.c`).
- **Prompt 2 (amélioré, résumé) :** pas de deuxième message noté : le travail a été fait par étapes (voir « Problème »).
- **Ce qu'on a gardé :** `creer_grille` libère tout ce qui est déjà alloué si une allocation échoue ; `detruire_grille` accepte NULL.
- **Ce que j'ai appris :** avancer fonction par fonction et tester juste après évite de chercher une erreur dans beaucoup de code à la fois.

### IA-10 — 22/11 et 23/11 — Nizar — Claude
- **Objectif :** trouver des paramètres proies/prédateurs pour que les deux espèces survivent (tâche T3.8) : au départ, les prédateurs disparaissaient vers la génération 25.
- **Prompt 1 (résumé) :** Nizar a décrit les prédateurs qui disparaissent vers la génération 25 et a demandé comment trouver de bons paramètres (tâche T3.8).
- **Résultat :** l'IA a proposé de changer `pred_energie_init` (4, 6, 8) dans un fichier de règles d'essai.
- **Problème :** aucun effet : les prédateurs disparaissaient toujours à la génération 25 (PR n° 53).
- **Prompt 2 (amélioré, résumé) :** une méthode précise : un seul paramètre changé à la fois, sur une grille de 40 × 80 avec 30 % de proies, 3 % de prédateurs, la graine 42 et 500 générations.
- **Ce qu'on a gardé :** `seuil_predation = 1` et `pred_energie_init = 1` : avec la graine 42, 403 proies et 355 prédateurs après 500 générations, et les deux espèces vivantes sur 12 graines différentes (PR n° 56, 57 et 58).
- **Ce que j'ai appris :** pour trouver la cause d'un problème, il faut changer un seul paramètre à la fois et garder les mêmes conditions d'essai.

### IA-11 — 23/11 — Nizar — Claude
- **Objectif :** afficher les états de la simulation dans une page web (bonus, tâche J10 reprise par Nizar).
- **Prompt 1 (résumé) :** Nizar a demandé comment afficher les états de la simulation dans une page web (tâche J10).
- **Résultat :** l'IA a proposé d'exporter les états dans un fichier que la page lit avec `fetch()`.
- **Problème :** un navigateur bloque `fetch()` sur un fichier local ouvert directement depuis le disque.
- **Prompt 2 (amélioré, résumé) :** Nizar a expliqué que le navigateur bloque `fetch()` sur un fichier local et a demandé une autre solution.
- **Ce qu'on a gardé :** l'export écrit `export/etats.js` (et non un fichier `.json`) et la page le charge comme un script (PR n° 60).
- **Ce que j'ai appris :** une page web ouverte depuis le disque n'a pas le droit de lire un autre fichier avec `fetch()` ; on passe par un fichier `.js` chargé avec une balise `script`.

### IA-12 — 23/11 — Nizar — Claude
- **Objectif :** vérifier qu'il n'y a pas de fuite mémoire avec `valgrind` (tâche E9, reprise par Nizar).
- **Prompt 1 (résumé) :** Nizar a demandé comment vérifier les fuites mémoire avec `valgrind` (tâche E9).
- **Résultat :** l'IA a expliqué que `valgrind` n'existe pas sous Windows.
- **Problème :** il a fallu lancer les essais sous Linux, et Elamine doit les reconfirmer sous WSL.
- **Prompt 2 (amélioré, résumé) :** Nizar a demandé comment lancer les essais sous Linux et quels cas tester (8 essais).
- **Ce qu'on a gardé :** 8 essais (Conway, motif, fichier de règles, proies/prédateurs, exports, motif introuvable, règles fausses, saisie invalide) : 0 fuite et 0 erreur, résultats dans `docs/valgrind.md` (PR n° 61), avec la mention « à reconfirmer sous WSL ».
- **Ce que j'ai appris :** les outils de contrôle mémoire dépendent du système : sous Windows, on utilise WSL ou Linux.

## Modèle d'entrée

### IA-XX — JJ/MM — Qui — Outil utilisé
- **Objectif :** ...
- **Prompt 1 :** (copier le prompt exact)
- **Résultat :** ...
- **Problème :** ...
- **Prompt 2 (amélioré) :** ...
- **Ce qu'on a gardé :** ...
- **Ce que j'ai appris :** ...
