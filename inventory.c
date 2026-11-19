#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "inventory.h"

void initInventory(Inventory *inventory) {
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        inventory->quantities[i] = 0;
    }

    for (int i = 0; i < ITEM_COUNT; i++) {
        inventory->items[i] = 0;
    }
}

void addResource(Inventory *inventory, ResourceType type) {
    if (type >= WOOD && type < NO_RESOURCE) {
        inventory->quantities[type]++;
    }
}

void addItem(Inventory *inventory, ItemType type) {
    if (type >= WOODEN_SWORD && type < ITEM_COUNT) {
        inventory->items[type]++;
    }
}

const char *getItemName(ItemType type) {
    switch (type) {
        case WOODEN_SWORD: return "Wooden Sword";
        case IRON_SWORD: return "Iron Sword";
        case STEEL_SWORD: return "Steel Sword";
        case CRYSTAL_SWORD: return "Crystal Sword";
        case DRAGON_SWORD: return "Dragon Sword";

        case CLOTH_ARMOR: return "Cloth Armor";
        case LEATHER_ARMOR: return "Leather Armor";
        case IRON_ARMOR: return "Iron Armor";
        case STEEL_ARMOR: return "Steel Armor";
        case DRAGON_ARMOR: return "Dragon Armor";

        case SMALL_POTION: return "Small Health Potion";
        case MEDIUM_POTION: return "Medium Health Potion";
        case LARGE_POTION: return "Large Health Potion";
        case STRENGTH_POTION: return "Strength Potion";
        case DEFENSE_POTION: return "Defense Potion";

        default: return "Unknown Item";
    }
}

void printInventory(Inventory inventory) {
    printf("\n--- RESOURCES ---\n");

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        printf("%s: %d\n",
               getResourceName((ResourceType)i),
               inventory.quantities[i]);
    }

    printf("\n--- ITEMS ---\n");

    int hasItems = 0;

    for (int i = 0; i < ITEM_COUNT; i++) {
        if (inventory.items[i] > 0) {
            printf("%s: %d\n",
                   getItemName((ItemType)i),
                   inventory.items[i]);

            hasItems = 1;
        }
    }

    if (!hasItems) {
        printf("Empty\n");
    }

    printf("\n");
}

Item getItem(ItemType type) {
    static const Item items[ITEM_COUNT] = {
        {WOODEN_SWORD, WEAPON, "Wooden Sword", 10, 5},
        {IRON_SWORD, WEAPON, "Iron Sword", 25, 10},
        {STEEL_SWORD, WEAPON, "Steel Sword", 45, 15},
        {CRYSTAL_SWORD, WEAPON, "Crystal Sword", 70, 20},
        {DRAGON_SWORD, WEAPON, "Dragon Sword", 100, 30},

        {CLOTH_ARMOR, ARMOR, "Cloth Armor", 10, 3},
        {LEATHER_ARMOR, ARMOR, "Leather Armor", 20, 5},
        {IRON_ARMOR, ARMOR, "Iron Armor", 40, 10},
        {STEEL_ARMOR, ARMOR, "Steel Armor", 65, 15},
        {DRAGON_ARMOR, ARMOR, "Dragon Armor", 100, 25},

        {SMALL_POTION, POTION, "Small Health Potion", 10, 20},
        {MEDIUM_POTION, POTION, "Medium Health Potion", 20, 40},
        {LARGE_POTION, POTION, "Large Health Potion", 35, 70},
        {STRENGTH_POTION, POTION, "Strength Potion", 40, 10},
        {DEFENSE_POTION, POTION, "Defense Potion", 40, 10}
    };

    if (type < WOODEN_SWORD || type >= ITEM_COUNT) {
        Item unknown = {ITEM_COUNT, POTION, "Unknown", 0, 0};
        return unknown;
    }

    return items[type];
}

int equipItem(Player *player, Inventory *inventory,
             ItemType type) {
    if (type < WOODEN_SWORD || type >+ ITEM_COUNT) {
        return 0;
    }

    if (inventory->items[type] <= 0) {
        return 0;
    }

    Item item = getItem(type);

    if (item.category == WEAPON) {
        player->equippedWeapon = type;
    } else if (item.category == ARMOR) {
        player->equippedArmor = type;
    } else {
        return 0;
    }
    
    return 1;
}

int usePotion(Player *player, Inventory *inventory,
              ItemType type) {

    if (type < SMALL_POTION || type > DEFENSE_POTION) {
        return 0;
    }

    if (inventory->items[type] <= 0) {
        return 0;
    }

    Item potion = getItem(type);

    switch (type) {
        case SMALL_POTION:
        case MEDIUM_POTION:
        case LARGE_POTION:
            if (player->hp >= player->maxHp) {
                return 0;
            }

            player->hp += potion.value;

            if (player->hp > player->maxHp) {
                player->hp = player->maxHp;
            }
            break;

        case STRENGTH_POTION:
            if (player->potionAttackBonus != 0) {
                return 0;
            }

            player->potionAttackBonus = potion.value;
            break;

        case DEFENSE_POTION:
            if (player->potionDefenseBonus != 0) {
                return 0;
            }

            player->potionDefenseBonus = potion.value;
            break;

        default:
            return 0;
    }

    inventory->items[type]--;
    return 1;
}

int getTotalAttack(Player player) {
    int attack = player.attack + player.potionAttackBonus;

    if (player.equippedWeapon != -1) {
        Item weapon = getItem((ItemType) player.equippedWeapon);
        attack += weapon.value;
    }

    return attack;
}

int getTotalDefense(Player player) {
    int defense = player.defense + player.potionDefenseBonus;

    if (player.equippedArmor != -1) {
        Item armor = getItem((ItemType) player.equippedArmor);
        defense += armor.value;
    }

    return defense;
}

static void chooseEquipment(Player *player,
                            Inventory *inventory,
                            ItemCategory category) {
    system("cls");

    printf("=== EQUIP ITEM ===\n\n");

    int available[ITEM_COUNT];
    int count = 0;

    for (int i = 0; i < ITEM_COUNT; i++) {
        Item item = getItem((ItemType)i);

        if (item.category == category &&
            inventory->items[i] > 0) {

            available[count] = i;

            printf("%d. %s (+%d %s)\n",
                   count + 1,
                   item.name,
                   item.value,
                   category == WEAPON ? "Attack" : "Defense");

            count++;
        }
    }

    printf("\n0. Back\n");

    if (count == 0) {
        printf("You have no items in this category.\n");
        _getch();
        return;
    }

    printf("\nChoose item: ");

    char choice = _getch();

    if (choice == '0') {
        return;
    }

    int selected = choice - '1';

    if (selected < 0 || selected >= count) {
        return;
    }

    ItemType type = (ItemType)available[selected];

    if (equipItem(player, inventory, type)) {
        printf("\nEquipped: %s\n", getItemName(type));
    }

    printf("Press any key to continue...");
    _getch();
}

void openEquipmentMenu(Player *player, Inventory *inventory) {
    char choice;

    while (1) {
        system("cls");

        printf("=== EQUIPMENT MENU ===\n\n");

        printf("Attack: %d\n", getTotalAttack(*player));
        printf("Defense: %d\n\n", getTotalDefense(*player));

        printf("Equipped Weapon: %s\n",
               player->equippedWeapon == -1
                   ? "None"
                   : getItemName((ItemType)player->equippedWeapon));

        printf("Equipped Armor: %s\n\n",
               player->equippedArmor == -1
                   ? "None"
                   : getItemName((ItemType)player->equippedArmor));

        printf("1. Equip Weapon\n");
        printf("2. Equip Armor\n");
        printf("0. Back\n");

        choice = _getch();

        if (choice == '0') {
            return;
        }

        switch (choice) {
            case '1':
                chooseEquipment(player, inventory, WEAPON);
                break;

            case '2':
                chooseEquipment(player, inventory, ARMOR);
                break;

            default:
                break;
        }
    }
}

void openPotionMenu(Player *player, Inventory *inventory) {
    while (1) {
        system("cls");

        printf("=== POTIONS ===\n\n");

        printf("HP: %d/%d\n", player->hp, player->maxHp);
        printf("Attack: %d\n", getTotalAttack(*player));
        printf("Defense: %d\n\n", getTotalDefense(*player));

        for (int i = 0; i < 5; i++) {
            ItemType type = (ItemType)(SMALL_POTION + i);
            Item potion = getItem(type);

            printf("%d. %s (+%d) x%d\n",
                   i + 1, potion.name, potion.value,
                   inventory->items[type]);
        }

        printf("\n0. Back\n");
        printf("Choose potion: ");

        char choice = _getch();

        if (choice == '0') {
            return;
        }

        if (choice < '1' || choice > '5') {
            continue;
        }

        ItemType type = (ItemType)(SMALL_POTION + choice - '1');

        if (usePotion(player, inventory, type)) {
            printf("\nUsed: %s\n", getItemName(type));
        } else {
            printf("\nCannot use this potion!\n");
            printf("Check quantity, HP or active bonus.\n");
        }

        printf("Press any key to continue...");
        _getch();
    }
}