#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "shop.h"

/**
 * Skontroluje, či hráč stojí presne jedno políčko vodorovne alebo zvisle od obchodníka
 * @param player Kópia hráča
 * @return 1, ak je hráč vedľa obchodníka, inak 0
 */
int isNearMerchant(Player player) {
    int merchantX = 3;
    int merchantY = 2;

    int distanceX = abs(player.x - merchantX);
    int distanceY = abs(player.y - merchantY);

    return distanceX + distanceY == 1;
}

/**
 * Zobrazí predaj surovín. Pri každom úspešnom predaji odpočíta jeden kus z inventára a pridá hráčovi príslušné zlato
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 */
void sellResources(Player *player, Inventory *inventory) {
    char choice;

    while (1) {
        system("cls");

        printf("=== SELL RESOURCES ===\n\n");
        printf("Gold: %d\n\n", player->gold);

        printf("1. Wood     %dx   2 Gold\n",
               inventory->quantities[WOOD]);

        printf("2. Stone    %dx   3 Gold\n",
               inventory->quantities[STONE]);

        printf("3. Iron     %dx   5 Gold\n",
               inventory->quantities[IRON]);

        printf("4. Crystal  %dx  10 Gold\n",
               inventory->quantities[CRYSTAL]);

        printf("\n0. Back\n");
        printf("\nChoose resource: ");

        choice = _getch();

        if (choice == '0') {
            return;
        }

        ResourceType type;
        int price;

        switch (choice) {
            case '1':
                type = WOOD;
                price = 2;
                break;
            case '2':
                type = STONE;
                price = 3;
                break;
            case '3':
                type = IRON;
                price = 5;
                break;
            case '4':
                type = CRYSTAL;
                price = 10;
                break;
            default:
                continue;
        }

        if (inventory->quantities[type] > 0) {
            inventory->quantities[type]--;
            player->gold += price;

            printf("\nSold 1 %s for %d Gold!\n",
                   getResourceName(type), price);
        } else {
            printf("\nYou don't have this resource!\n");
        }

        printf("Press any key to continue...");
        _getch();
    }
}

/**
 * Umožní kúpu zbrane, brnenia alebo elixíru. Skontroluje cenu, odpočíta zlato a pridá predmet do inventára
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 */
void buyItems(Player *player, Inventory *inventory) {
    char choice;

    while (1) {
        system("cls");

        printf("=== BUY ITEMS ===\n\n");
        printf("Gold: %d\n", player->gold);

        printInventory(*inventory);

        printf("\n");

        printf("1. Weapons\n");
        printf("2. Armor\n");
        printf("3. Potions\n");
        printf("0. Back\n");

        printf("\nChoose category: ");
        choice = _getch();

        if (choice == '0') {
            return;
        }

        int startIndex;

        switch (choice) {
            case '1':
                startIndex = WOODEN_SWORD;
                break;

            case '2':
                startIndex = CLOTH_ARMOR;
                break;

            case '3':
                startIndex = SMALL_POTION;
                break;

            default:
                continue;
        }

        system("cls");

        printf("=== ITEMS ===\n\n");
        printf("Gold: %d\n\n", player->gold);

        for (int i = 0; i < 5; i++) {
            Item item = getItem((ItemType)(startIndex + i));

            printf("%d. %s - %d Gold\n",
                   i + 1, item.name, item.price);
        }

        printf("\n0. Back\n");
        printf("\nChoose item: ");

        char itemChoice = _getch();

        if (itemChoice == '0') {
            continue;
        }

        if (itemChoice < '1' || itemChoice > '5') {
            continue;
        }

        int index = startIndex + (itemChoice - '1');

        Item item = getItem((ItemType)index);

        if (player->gold >= item.price) {
            player->gold -= item.price;
            addItem(inventory, item.type);

            printf("\nPurchased: %s!\n", item.name);
        } else {
            printf("\nNot enough gold!\n");
        }

        printf("Press any key to continue...");
        _getch();
    }
}

/**
 * Umožní predať vlastnené predmety za polovicu ceny
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 */
static void sellItems(Player *player, Inventory *inventory) {
    while (1) {
        system("cls");

        printf("=== SELL ITEMS ===\n\n");
        printf("Gold: %d\n\n", player->gold);

        printf("1. Weapons\n");
        printf("2. Armor\n");
        printf("3. Potions\n");
        printf("0. Back\n");

        char categoryChoice = _getch();
        int startIndex;

        switch (categoryChoice) {
            case '1':
                startIndex = WOODEN_SWORD;
                break;
            case '2':
                startIndex = CLOTH_ARMOR;
                break;
            case '3':
                startIndex = SMALL_POTION;
                break;
            case '0':
                return;
            default:
                continue;
        }

        system("cls");
        printf("=== SELL ITEMS ===\n\n");

        for (int i = 0; i < 5; i++) {
            ItemType type = (ItemType)(startIndex + i);
            Item item = getItem(type);

            printf("%d. %s - %d Gold (x%d)\n",
                   i + 1,
                   item.name,
                   item.price / 2,
                   inventory->items[type]);
        }

        printf("\n0. Back\n");
        printf("Choose item: ");

        char itemChoice = _getch();

        if (itemChoice == '0') {
            continue;
        }

        if (itemChoice < '1' || itemChoice > '5') {
            continue;
        }

        ItemType type = (ItemType)(startIndex + itemChoice - '1');

        if (inventory->items[type] <= 0) {
            printf("\nYou do not have this item!\n");
        } else {
            Item item = getItem(type);
            int sellPrice = item.price / 2;

            inventory->items[type]--;
            player->gold += sellPrice;

            if (player->equippedWeapon == (int)type &&
                inventory->items[type] == 0) {
                player->equippedWeapon = -1;
            }

            if (player->equippedArmor == (int)type &&
                inventory->items[type] == 0) {
                player->equippedArmor = -1;
            }

            printf("\nSold: %s for %d Gold\n",
                   item.name, sellPrice);
        }

        printf("Press any key to continue...");
        _getch();
    }
}

/**
 * Ponúka nákup ďalšej úrovne, maximálnych HP, útoku a obrany. Pred vykonaním vylepšenia kontroluje cenu a pri úrovni aj maximum
 * @param player Ukazovateľ na hráca
 */
static void buyUpgrades(Player *player) {
    while (1) {
        system("cls");

        printf("=== HERO UPGRADES ===\n\n");
        printf("Gold: %d\n", player->gold);
        printf("Level: %d/%d\n", player->level, MAX_LEVEL);
        printf("HP: %d/%d\n", player->hp, player->maxHp);
        printf("Attack: %d\n", getTotalAttack(*player));
        printf("Defense: %d\n\n", getTotalDefense(*player));

        printf("1. Next Level - %d Gold\n",
               player->level * 30);
        printf("2. +10 Max HP - 30 Gold\n");
        printf("3. +2 Attack - 40 Gold\n");
        printf("4. +1 Defense - 30 Gold\n");
        printf("0. Back\n");

        char choice = _getch();

        if (choice == '0') {
            return;
        }

        switch (choice) {
            case '1':
                if (player->level >= MAX_LEVEL) {
                    printf("\nMaximum level reached!\n");
                } else if (player->gold < player->level * 30) {
                    printf("\nNot enough Gold!\n");
                } else {
                    int neededXP = getNextLevelXP(*player) - player->xp;

                    player->gold -= player->level * 30;
                    addExperience(player, neededXP);

                    printf("\nLevel increased to %d!\n", player->level);
                }
                break;

            case '2':
                if (player->gold < 30) {
                    printf("\nNot enough Gold!\n");
                } else {
                    player->gold -= 30;
                    player->maxHp += 10;
                    player->hp += 10;
                    printf("\nMax HP increased!\n");
                }
                break;

            case '3':
                if (player->gold < 40) {
                    printf("\nNot enough Gold!\n");
                } else {
                    player->gold -= 40;
                    player->attack += 2;
                    printf("\nAttack increased!\n");
                }
                break;

            case '4':
                if (player->gold < 30) {
                    printf("\nNot enough Gold!\n");
                } else {
                    player->gold -= 30;
                    player->defense += 1;
                    printf("\nDefense increased!\n");
                }
                break;

            default:
                continue;
        }

        printf("Press any key to continue...");
        _getch();
    }
}

/**
 * Zobrazí inventár a podmenu predaja surovín alebo predmetov
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventá
 */
static void openSellMenu(Player *player, Inventory *inventory) {
    while (1) {
        system("cls");

        printf("=== SELL MENU ===\n\n");

        printInventory(*inventory);

        printf("1. Sell Resources\n");
        printf("2. Sell Items\n");
        printf("0. Back\n");

        char choice = _getch();

        switch (choice) {
            case '1':
                sellResources(player, inventory);
                break;
            case '2':
                sellItems(player, inventory);
                break;
            case '0':
                return;
            default:
                break;
        }
    }
}

/**
 * Hlavné menu obchodníka. Umožní nákup predmetov, predaj alebo vylepšenie postavy
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 */
void openShop(Player *player, Inventory *inventory) {
    char choice;

    while (1) {
        system("cls");

        printf("=== MERCHANT ===\n\n");

        printf("Gold: %d\n", player->gold);
        printf("Level: %d/%d\n", player->level, MAX_LEVEL);

        printInventory(*inventory);

        printf("\n");

        printf("1. Buy Items\n");
        printf("2. Sell\n");
        printf("3. Hero Upgrades\n");
        printf("0. Exit\n");

        printf("\nChoose option: ");

        choice = _getch();

        
        switch (choice) {
            case '1':
                buyItems(player, inventory);
                break;

            case '2':
                openSellMenu(player, inventory);
                break;
            case '3':
                buyUpgrades(player);
                break;
            case '0':
                return;
            default:
                break;
        }
    }
}