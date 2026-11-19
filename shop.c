#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "shop.h"

int isNearMerchant(Player player) {
    int merchantX = 3;
    int merchantY = 2;

    int distanceX = abs(player.x - merchantX);
    int distanceY = abs(player.y - merchantY);

    return distanceX + distanceY == 1;
}

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

void openShop(Player *player, Inventory *inventory) {
    char choice;

    while (1) {
        system("cls");

        printf("=== MERCHANT ===\n\n");

        printf("Gold: %d\n", player->gold);

        printInventory(*inventory);

        printf("\n");

        printf("1. Buy items\n");
        printf("2. Sell resources\n");
        printf("3. Exit shop menu\n");

        printf("\nChoose option: ");

        choice = _getch();

        switch (choice) {
            case '1':
                buyItems(player, inventory);
                break;

            case '2':
                sellResources(player, inventory);
                break;

            case '3':
                return;

            default:
                break;
        }
    }
}