#ifndef INVENTORY_H
#define INVENTORY_H

#include "resource.h"
#include "player.h"

#define RESOURCE_COUNT 5

typedef enum {
    WOODEN_SWORD,
    IRON_SWORD,
    STEEL_SWORD,
    CRYSTAL_SWORD,
    DRAGON_SWORD,

    CLOTH_ARMOR,
    LEATHER_ARMOR,
    IRON_ARMOR,
    STEEL_ARMOR,
    DRAGON_ARMOR,

    SMALL_POTION,
    MEDIUM_POTION,
    LARGE_POTION,
    STRENGTH_POTION,
    DEFENSE_POTION,

    ITEM_COUNT
} ItemType;

typedef enum {
    WEAPON,
    ARMOR,
    POTION
} ItemCategory;

typedef struct {
    ItemType type;
    ItemCategory category;
    const char *name;
    int price;
    int value;
} Item;

typedef struct {
    int quantities[RESOURCE_COUNT];
    int items[ITEM_COUNT];
} Inventory;

void initInventory(Inventory *inventory);
void addResource(Inventory *inventory, ResourceType type);
void addItem(Inventory *inventory, ItemType type);
void printInventory(Inventory inventory);

Item getItem(ItemType type);

const char *getItemName(ItemType type);

int equipItem(Player *player, Inventory *inventory,
             ItemType type);

int usePotion(Player *player, Inventory *inventory,
              ItemType type);

int getTotalAttack(Player player);
int getTotalDefense(Player player);

void openEquipmentMenu(Player *player, Inventory *inventory);
void openPotionMenu(Player *player, Inventory *inventory);

#endif