#include "dragon.h"
#include "map.h"

/**
 * Nastaví počiatočnú pozíciu, životy, útok a obranu draka
 * @param dragon Ukazovateľ na štruktúru draka
 */
void initDragon(Dragon *dragon) {
    dragon->x = 10;
    dragon->y = 12;

    dragon->hp = 200;
    dragon->maxHp = 200;

    dragon->attack = 25;
    dragon->defense = 8;

    dragon->isAwake = 0;
}

/**
 * Prebudí draka a umiestni znak D na jeho súradnice v globálnej mape brlohu
 * @param dragon Ukazovateľ na draka
 */
void spawnDragon(Dragon *dragon) {
    dragon->isAwake = 1;

    lairMap[dragon->y][dragon->x] = 'D';
}
