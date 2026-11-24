
#include <stdio.h>
#include "map.h"
#include "player.h"

char lairMap[MAP_ROWS][MAP_COLS + 1] = {
    "##########E##########",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#...................#",
    "#####################"
};


char shopMap[SHOP_ROWS][SHOP_COLS + 1] = {
    "#######",
    "#.....#",
    "#..S..#",
    "#.....#",
    "###E###"
};


/**
 * Vypíše obchod alebo dračí brloh do konzoly podľa aktuálnej lokácie
 * @param player Kópia hráča s aktuálnymi súradnicami
 * @param location Lokácia SHOP alebo LAIR, ktorá určuje mapu a jej rozmery
 */
void printMap(Player player, Location location) {
    int rows;
    int cols;

    if (location == LAIR) {
        rows = MAP_ROWS;
        cols = MAP_COLS;
    } else {
        rows = SHOP_ROWS;
        cols = SHOP_COLS;
    }

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (x == player.x && y == player.y) {
                printf("P");
            } else if (location == LAIR) {
                printf("%c", lairMap[y][x]);
            } else {
                printf("%c", shopMap[y][x]);
            }
        }
        printf("\n");
    }
}


/**
 * Overí, či cieľové súradnice ležia v hraniciach zvolenej mapy a či cieľové políčko neobsahuje zakázanú prekážku
 * @param location Lokácia
 * @param x Cieľový stĺpec
 * @param y Cieľový riadok
 * @return 1, ak je pohyb podľa aktuálnej implementácie povolený, inak 0.
 */
int canMove(Location location, int x, int y) {
    int rows = location == LAIR ? MAP_ROWS : SHOP_ROWS;
    int cols = location == LAIR ? MAP_COLS : SHOP_COLS;

    if (x < 0 || x >= cols ||
        y < 0 || y >= rows) {
        return 0;
    }
    
    if (location == LAIR) {
        return lairMap[y][x] != '#' && lairMap[y][x] != 'D';
    }

    return shopMap[y][x] != 'S' && shopMap[y][x] != '#';
}