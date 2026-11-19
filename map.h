
#ifndef MAP_H
#define MAP_H

#include "player.h"

#define MAP_ROWS 15
#define MAP_COLS 21

#define SHOP_ROWS 5
#define SHOP_COLS 7

typedef enum {
    LAIR,
    SHOP
} Location;

extern char lairMap[MAP_ROWS][MAP_COLS + 1];
extern char shopMap[SHOP_ROWS][SHOP_COLS + 1];

void printMap(Player player, Location location);
int canMove(Location location, int x, int y);

#endif