
#include "timer.h"

void startTimer(DragonTimer *timer) {
    timer->startTime = GetTickCount64();
}

int getRemainingTime(DragonTimer *timer) {
    ULONGLONG currentTime = GetTickCount64();

    ULONGLONG elapsed =
        (currentTime - timer->startTime) / 1000;

    if (elapsed >= DRAGON_TIME) {
        return 0;
    }

    return DRAGON_TIME - (int)elapsed;
}