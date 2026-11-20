#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#include "game.h"
#include "player.h"
#include "map.h"
#include "timer.h"
#include "resource.h"
#include "inventory.h"
#include "shop.h"
#include <time.h>
    


void startGame(void) {
    Player player;
    initPlayer(&player);

    Inventory inventory;
    initInventory(&inventory);

    srand((unsigned int)time(NULL));

    Location location = SHOP;

    player.x = 1;
    player.y = 1;

    int savedX = 10;
    int savedY = 1;

    DragonTimer timer;

    int lastRemaining = -1;
    int redraw = 1;

    while (1) {
        int remaining = -1;

        if (location == LAIR) {
            remaining = getRemainingTime(&timer);

            if (remaining == 0) {
                system("cls");
                printf("DRAGON HAS AWAKENED!\n");
                printf("The dragon attacks you!\n");
                printf("Battle system coming soon.\n");
                return;
            }
        }

        if (redraw || remaining != lastRemaining) {
            system("cls");

            printf("=== DRAGON ESCAPE ===\n\n");
            printMap(player, location);

            printf("\nHP: %d/%d\n",
                   player.hp, player.maxHp);
            printf("Gold: %d\n", player.gold);
            printInventory(inventory);

            printf("Level: %d/%d\n", player.level, MAX_LEVEL);

            if (player.level < MAX_LEVEL) {
                printf("XP: %d/%d\n",
                    player.xp, getNextLevelXP(player));
            } else {
                printf("XP: MAX\n");
            }

            if (location == LAIR) {
                printf("Dragon arrives in: %ds\n",
                       remaining);

                if (remaining <= 15) {
                    printf("WARNING! Dragon is coming!\n");
                }
            } else {
                printf("SHOP - SAFE ZONE\n");
            }

            printf("WASD - Move | E - Merchant | I - Equipment | P - Potions | Q - Quit\n");

            lastRemaining = remaining;
            redraw = 0;
        }

        if (_kbhit()) {
            char move = _getch();

            int newX = player.x;
            int newY = player.y;

            switch (move) {
                case 'w':
                    newY--;
                    break;
                case 's':
                    newY++;
                    break;
                case 'a':
                    newX--;
                    break;
                case 'd':
                    newX++;
                    break;
                case 'e':
                    if (location == SHOP && isNearMerchant(player)) {
                        openShop(&player, &inventory);
                        redraw = 1;
                    }
                    continue;
                case 'i':
                    if (location == SHOP) {
                        openEquipmentMenu(&player, &inventory);
                        redraw = 1;
                    }
                    continue;
                case 'p':
                    if (location == SHOP) {
                        openPotionMenu(&player, &inventory);
                        redraw = 1;
                    }
                    continue;
                case 'q':
                    return;
                default:
                    continue;
            }

            if (!canMove(location, newX, newY)) {
                continue;
            }

            if (location == LAIR &&
                lairMap[newY][newX] == 'E') {

                savedX = player.x;
                savedY = player.y;

                location = SHOP;
                player.x = 3;
                player.y = 3;

            } else if (location == SHOP &&
                       shopMap[newY][newX] == 'E') {

                location = LAIR;
                player.x = savedX;
                player.y = savedY;

                generateResources(player);

                startTimer(&timer);

            } else {
                player.x = newX;
                player.y = newY;

                if (location == LAIR) {
                    char symbol = lairMap[player.y][player.x];

                    ResourceType type = getResourceType(symbol);

                    if (type != NO_RESOURCE) {
                        addResource(&inventory, type);

                        int experience = getResourceXP(type);
                        addExperience(&player, experience);

                        lairMap[player.y][player.x] = '.';
                    }
                }
                
            }

            redraw = 1;
        }

        Sleep(50);
    }
}

void showMenu() {
    char choice;

    while (1) {
        printf("\n=== DRAGON ESCAPE ===\n");
        printf("1. New Game\n");
        printf("2. Exit\n");
        printf("Choose option: ");

        choice = _getch();

        switch (choice) {
            case '1':
                startGame();
                return;

            case '2':
                printf("\nGoodbye!\n");
                return;

            default:
                printf("\nInvalid option!\n");
                break;
        }
    }
}