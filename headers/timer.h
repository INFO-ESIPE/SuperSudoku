#ifndef _TIMER_
#define _TIMER_

#include <time.h>


struct TimerData {
    int seconds;
    int minutes;
};

void startTimer();
struct TimerData endTimer();
struct TimerData getTimer();
void registerScore(struct TimerData timer_data, char* gridName);

#endif
