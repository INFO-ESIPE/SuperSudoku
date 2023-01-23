## TP 7 - Sudoku Graphique (Patch note)
#### Max Ducoudré
#

### Patch 1 : Tableau high scores
- Correction de l'affichage des chaînes de caractère
- Amélioration de la lecture du fichier contenant les high scores
- Ajout de la grille lié au score & de la date
© Elsa Guillet
#

### Patch 2 : Makefile 
- Ajout de règles "run" pour tester le programme :
    `make run` : lance le sudoku avec grid3.txt
    `make run_random` : lance le sudoku avec une grille aléatoire
- Ajout de commentaires dans le fichier makefile devant chaque règles
© Vivien Alphonse
#

### Patch 3 : Variables globales
- Suppression des variables globales dans le fichier main.c
- Suppression des variables globales dans le fichier grid_frame.c
#

### Patch 4 : Commentaires
- Suppression des commentaires qui contiennet du code dans  : grid_frame.c & mouse_listener.c
Crédits : Vivien Alphonse
- Suppression des commentaires en double dans les fonctions
© Mourad Amghari
#

### Patch 5 : Grille aléatoire
- Correction du fait que certaines grilles aléatoires ne soient pas résolvables
© Mourad Amghari
#   