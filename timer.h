
#ifndef TIMER_H
#define TIMER_H

#include <windows.h>

#define DRAGON_TIME 60

typedef struct {
    ULONGLONG startTime;
} DragonTimer;

void startTimer(DragonTimer *timer);
int getRemainingTime(DragonTimer *timer);

#endif