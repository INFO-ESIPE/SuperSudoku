
# Rapport de relecture de code

Production soumise à la relecture : **TP7 - Sudoku Graphique**
Projet/code produit par **Djebloun Yacine**
Relecture opérée par **Ducoudré Max** le 17 janvier 2023

## Concision et propreté des rendus

Les productions transmises sont particulièrement bien structurées et la précision du nommage 
ne laisse aucun doute sur le contenu des répertoires et fichiers.

Les noms des fichiers expliquent bien leur contenu, attention toutefois à ne pas livrer les fichiers compilés (.o et exécutable) et de rajouter un readme pour expliquer comment compiler.  

## Installation et compilation des sources transmises

Un makefile propre, lisible et complet permet la compilation de toutes les sources sans aucun warning 
et avec les drapeaux -Wall et -ansi (voire -pedantic). Le makefile gère correctement les dépendances 
et intègre une règle pour le nettoyage des produits de compilation.

## Fonctionnalités implantées dans les rendus

Une des fonctionnalité n'est pas implantée correctement.

Il est possible d'effectuer une partie de sudoku avec ce programme, mais non pas sans difficultés :
-Il n'est pas possible d'annuler un coup/de jouer par dessus
-Il est possible de jouer à des endroits où les règles ne le permettent pas.

## Utilisations et sécurité des programmes produits

Tous les cas d'utilisations normales sont traités correctement par les programmes.

Les cas d'utilisation normale sont gérés (c'est à dire avec une grille en argument).
Quand aucun argument n'est donné, il est expliqué qu'il faut une grille en argument.
Par contre, si l'argument n'est pas un chemin de fichier, le programme se lance et lève une erreur segfault.

## Nommage des éléments dans les productions rendues

Les identifiants apportent de l'information facilitant la compréhension par autrui.

## Efficacité et performance des productions rendues

Les programmes sont basés sur des algorithmes attendues.

## Commentaires dans les sources des productions rendues

Un passage trop rusé ou surprenant manque de commentaires ou encore un commentaire est présent mais non-éclairant .

Même si les identifiants de fonctions & de variables sont explicites, le programme ne comporte quasiment aucun commentaires.
Il serait peut être opportun d'en mettre dans les fichiers .h devant chaque fonctions.


## derniers commentaires :

En terme d'optimisation, je recommanderais d'éviter l'utilisation de variable globale (notamment dans le fichier main.c qui pourrait facilement être évité en les mettant directement dans la fonction main().

