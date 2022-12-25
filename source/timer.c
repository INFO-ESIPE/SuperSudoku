#include <stdio.h>
#include <stdlib.h>

#include "./../headers/timer.h"

time_t sartTimeStamp;
int timer_end;
struct TimerData buff_timer_data;

void startTimer()
{
    timer_end = 0;
    sartTimeStamp = time(NULL);
}

struct TimerData endTimer()
{
    buff_timer_data = getTimer();
    timer_end = 1;
    return buff_timer_data;
    
}

struct TimerData getTimer()
{
    time_t timer_s = time(NULL) - sartTimeStamp;
    struct TimerData timer_data;

    if(timer_end == 1) return buff_timer_data;
    
    timer_data.seconds = (int)(timer_s % 60);
    timer_data.minutes = (int)(timer_s / 60);
    return timer_data;
}

void registerScore(struct TimerData timer_data, char* gridName)
{

}

char* readScore()
{

}
