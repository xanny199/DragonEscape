#ifndef SHOP_H
#define SHOP_H

#include "player.h"
#include "inventory.h"

int isNearMerchant(Player player);
void openShop(Player *player, Inventory *inventory);

#endif