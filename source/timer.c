/*
	Programmation C - TP7
	Max Ducoudré - INFO1
    Fonctions permettant de gérer le timer durant la partie de sudoku
*/

#include <stdio.h>
#include <stdlib.h>

#include "./../headers/timer.h"

time_t sartTimeStamp;
int timer_end;
struct TimerData buff_timer_data;


/*Lance le début du timer*/
void startTimer()
{
    timer_end = 0;
    sartTimeStamp = time(NULL);
}

/* Met fin au timer*/
struct TimerData endTimer(int saveScore)
{
    buff_timer_data = getTimer();
    timer_end = 1;
    if(saveScore) registerScore(buff_timer_data, "grid1");
    return buff_timer_data;
    
}

/*Permet de récupérer les données du timer en cours*/
struct TimerData getTimer()
{
    time_t timer_s = time(NULL) - sartTimeStamp;
    struct TimerData timer_data;

    if(timer_end == 1) return buff_timer_data;
    
    timer_data.seconds = (int)(timer_s % 60);
    timer_data.minutes = (int)(timer_s / 60);
    return timer_data;
}

/*Permet d'enregistrer le score dans un fichier*/
void registerScore(struct TimerData timer_data, char* gridName)
{
    
    FILE *file;
    char buffer[255];

    /* Récupération de la date*/
    char buffer_date[50];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer_date,"%d/%02d/%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);


    file = fopen(SCORE_FILE, "a");

    sprintf(buffer, "grid=\"%s\"|time=\"%d\"|date=\"%s\"\n", gridName, (timer_data.minutes*60+timer_data.seconds), buffer_date);
    fprintf(file, "%s", buffer);
    fclose(file);

}


void swap(struct ScoreData* xp, struct ScoreData* yp)
{
    struct ScoreData  temp = *xp;
    *xp = *yp;
    *yp = temp;
}
/* Fonction permettant de trier les scores du meilleur au pire*/
void selectionSort(struct ScoreData arr[], int n)
{
    int i, j, min_idx;
     for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j].time < arr[min_idx].time)
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

/* Permet de lire les scores dans le fichiers des scores*/
void readScore(struct ScoreData* scores, int scoresCount)
{
    int index = 0;
    int i,j,k;
    int lineCount = 0;
    int flag = 0;
    char line[256];
    char gridNameBuffer[30];
    char dateBuffer[30];
    char timeBuffer[30];
    FILE *file;

    file = fopen(SCORE_FILE, "r");
    if ( file == NULL ) {
        printf("Can't open score file !\n");
        strcpy(scores[0].grid, "Can't open score file");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        lineCount++;

        /*Get gridname in line*/
        j = 0;
        for(i = 0; line[i] != '\n'; i++) {
            if(line[i] == '\"' && line[i+1] == '|') flag = 0;
            if(flag == 1)  {
                gridNameBuffer[j] = line[i];
                j++;
            }
            if(line[i] == '\"' && line[i-1] == '=' && line[i-2] == 'd' && line[i-3] == 'i' && line[i-4] == 'r' && line[i-5] == 'g') flag = 1;
        }
        gridNameBuffer[j] = '\0';
        flag = 0;


        strcpy(scores[index].grid, gridNameBuffer);
        for(k = 0; k < j; k++) gridNameBuffer[k] = '\0';
        j=0;



        /*Get timer in line*/
        for(i = 0; line[i] != '\n'; i++) {
            if(line[i] == '\"' && line[i+1] == '|') flag = 0;
            if(flag == 1)  {
                timeBuffer[j] = line[i];
                j++;
            }
            if(line[i] == '\"' && line[i-1] == '=' && line[i-2] == 'e' && line[i-3] == 'm' && line[i-4] == 'i' && line[i-5] == 't') flag = 1;
        }
        timeBuffer[j] = '\0';
        j=0;
        flag = 0;
        scores[index].time = atoi(timeBuffer);
        for(k = 0; k < j; k++) timeBuffer[k] = '\0';


        /*Get date in line*/
        for(i = 0; line[i] != '\n'; i++) {
            if(line[i] == '\"' && line[i+1] == '|') flag = 0;
            if(flag == 1)  {
                dateBuffer[j] = line[i];
                j++;
            }
            if(line[i] == '\"' && line[i-1] == '=' && line[i-2] == 'e' && line[i-3] == 't' && line[i-4] == 'a' && line[i-5] == 'd') flag = 1;
        }
        dateBuffer[j-1] = '\0';
        flag = 0;

        strcpy(scores[index].date, dateBuffer);

        for(k = 0; k < j; k++) dateBuffer[k] = '\0';
        j=0;

        index++;

        if(index > SCORE_TO_DISPLAY) break;
    }
    scores[index].time = -1;

    fclose(file);

    selectionSort(scores, lineCount);
}
