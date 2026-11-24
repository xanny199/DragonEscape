#include "timer.h"

/**
 * Spustí časovač tým, že uloží aktuálny počet milisekúnd zo systémovej funkcie GetTickCount64()
 * @param timer Ukazovateľ na časovač
 */
void startTimer(DragonTimer *timer) {
    timer->startTime = GetTickCount64();
}

/**
 * Vypočíta počet celých sekúnd zostávajúcich do príchodu draka z rozdielu aktuálneho času a času spustenia
 * @param timer Ukazovateľ na už spustený časovač
 * @return Zostávajúce sekundy v rozsahu od 0 po DRAGON_TIME
 */
int getRemainingTime(DragonTimer *timer) {
    ULONGLONG currentTime = GetTickCount64();

    ULONGLONG elapsed =
        (currentTime - timer->startTime) / 1000;

    if (elapsed >= DRAGON_TIME) {
        return 0;
    }

    return DRAGON_TIME - (int)elapsed;
}