/*
	Programmation C - TP7
	Max Ducoudré - INFO1
    Fonctions permettant de gérer le timer durant la partie de sudoku
*/

#ifndef _TIMER_
#define _TIMER_

#include <time.h>

#include "constants.h"
#include <string.h>

struct TimerData {
    int seconds;
    int minutes;
};

struct ScoreData {
    int time;
    char grid[40];
    char date[40];
};


void startTimer();
struct TimerData endTimer(int saveScore);
struct TimerData getTimer();
void registerScore(struct TimerData timer_data, char* gridName);
void readScore(struct ScoreData* scores, int scoresCount);

#endif
