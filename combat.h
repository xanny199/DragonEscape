#ifndef COMBAT_H
#define COMBAT_H

#include "player.h"
#include "dragon.h"
#include "inventory.h"

int fightDragon(Player *player, Dragon *dragon,
                Inventory *inventory);

#endif