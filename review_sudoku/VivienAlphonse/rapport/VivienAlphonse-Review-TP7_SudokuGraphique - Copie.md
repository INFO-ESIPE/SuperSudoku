# Rapport de relecture de code

Production soumise à la relecture : **TP7 - Sudoku Graphique**
Projet/code produit par **Vivien Alphonse**
Relecture opérée par **Max Ducoudré** le 13 janvier 2023

## Concision et propreté des rendus

Les contenus transmis sont à la fois concis et complets. Un maximum d'éléments sont générés 
automatiquement rendant la production minimale en taille lors de sa diffusion.

## Installation et compilation des sources transmises

Un makefile propre, lisible et complet permet la compilation de toutes les sources sans aucun warning 
et avec les drapeaux -Wall et -ansi (voire -pedantic). Le makefile gère correctement les dépendances 
et intègre une règle pour le nettoyage des produits de compilation.

Le makefile n'a pas de règle de dépendance entre les fichiers.

## Fonctionnalités implantées dans les rendus

Les programmes contiennent quelques preuves de leurs bons fonctionnements.

Le programme réalise presque l'intégralité du cahier des charges. 

-il est impossible d'annuler un coup (si l'utilisateur veut se raviser sur son coup, il ne pourra pas).
-Si l'utilisateur fait une erreur, le programme se termine. Ce n'est pas précisé dans le cahier des charges, mais je pense qu'il serait mieux de simplement annuler le coup en cas d'erreur.

## Utilisations et sécurité des programmes produits

Tous les cas d'utilisations normales sont traités correctement par les programmes.

Tous les cas d'utilisation normaux sont pris en compte. 
Par contre, si l'utilisateur spécifie en argument de l'exécutable un chemin de fichier invalide, la grille se génère avec des nombres incohérents.

## Nommage des éléments dans les productions rendues

Les identifiants apportent de l'information facilitant la compréhension par autrui.

Les fonctions, variables et constantes ont des noms explicites.
De plus, les constantes modifiables sont précisés dans le fichier readme.txt.


## Efficacité et performance des productions rendues

Les programmes sont basés sur des algorithmes attendues.

Le programme est efficace et utilise correctement la structure de donnée utilisé dans le TP6. (le tableau 2D de integers)

## Commentaires dans les sources des productions rendues

Les programmes sont correctement commentés.

Le programme est correctement commenté, notamment des parties du codes sources des fonctions.
Même si les noms des fonctions & des arguments sont explicites, je rajouterais avant chaque fonctions dans les fichier .h ce qu'elles font et le rôle de chaque arguments.

## derniers commentaires :

A part les quelques bugs relevés précédemment, rien à dire de plus sur le programme.
Si je devais reprendre ce projet, le maintenir ou faire des modifications dessus, je ne pense pas rencontrer de difficultés.