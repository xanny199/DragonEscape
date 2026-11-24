#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "combat.h"
#include "inventory.h"

/**
 * Zobrazí elixíry dostupné počas súboja a pokúsi sa použiť vybraný elixír
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 * @return 1 pri úspešnom použití elixíru, inak 0
 */
static int chooseCombatPotion(Player *player,
                              Inventory *inventory) {
    system("cls");

    printf("=== COMBAT POTIONS ===\n\n");
    printf("HP: %d/%d\n\n", player->hp, player->maxHp);

    for (int i = 0; i < 5; i++) {
        ItemType type = (ItemType)(SMALL_POTION + i);

        printf("%d. %s - x%d\n",
               i + 1,
               getItemName(type),
               inventory->items[type]);
    }

    printf("\n0. Back\n");
    printf("Choose potion: ");

    char choice = _getch();

    if (choice == '0') {
        return 0;
    }

    if (choice < '1' || choice > '5') {
        return 0;
    }

    ItemType type = (ItemType)(SMALL_POTION + choice - '1');

    if (!usePotion(player, inventory, type)) {
        printf("\nCannot use this potion!\n");
        printf("Press any key to continue...");
        _getch();
        return 0;
    }

    printf("\nUsed: %s\n", getItemName(type));

    return 1;
}

/**
 * Riadi ťahový súboj hráča s drakom. Hráč môže útočiť, brániť sa alebo použiť elixír; po platnej akcii môže drak zaútočiť. Po súboji sa zrušia dočasné bonusy elixírov.
 * @param player Ukazovateľ na hráča
 * @param dragon Ukazovateľ na draka
 * @param inventory Ukazovateľ na inventár
 * @return 1 pri víťazstve hráča, 0 pri porážke
 */
int fightDragon(Player *player, Dragon *dragon, Inventory *inventory) {
    while (player->hp > 0 && dragon->hp > 0) {
        system("cls");

        printf("=== DRAGON BATTLE ===\n\n");

        printf("PLAYER\n");
        printf("HP: %d/%d\n", player->hp, player->maxHp);
        printf("Attack: %d\n", getTotalAttack(*player));
        printf("Defense: %d\n\n", getTotalDefense(*player));

        printf("DRAGON\n");
        printf("HP: %d/%d\n", dragon->hp, dragon->maxHp);
        printf("Attack: %d\n", dragon->attack);
        printf("Defense: %d\n\n", dragon->defense);

        printf("1. Attack\n");
        printf("2. Defend\n");
        printf("3. Use Potion\n");
        printf("\nChoose action: ");

        char choice = _getch();
        int defending = 0;

        if (choice == '1') {
            int damage = getTotalAttack(*player) - dragon->defense;

            if (damage < 1) {
                damage = 1;
            }

            dragon->hp -= damage;

            if (dragon->hp < 0) {
                dragon->hp = 0;
            }

            printf("\nYou attacked the dragon!\n");
            printf("Damage dealt: %d\n", damage);

        } else if (choice == '2') {
            defending = 1;
            printf("\nYou take a defensive stance!\n");

        } else if (choice == '3') {
            if (!chooseCombatPotion(player, inventory)) {
                continue;
            }
        } else {
            continue;
        }

        if (dragon->hp > 0) {
            int damage = dragon->attack - getTotalDefense(*player);

            if (damage < 1) {
                damage = 1;
            }

            if (defending) {
                damage = (damage + 1) / 2;
            }

            player->hp -= damage;

            if (player->hp < 0) {
                player->hp = 0;
            }

            printf("\nDragon attacks you!\n");
            printf("Damage received: %d\n", damage);
        }

        printf("\nPress any key to continue...");
        _getch();

    }

    int victory = dragon->hp <= 0;

    player->potionAttackBonus = 0;
    player->potionDefenseBonus = 0;

    return victory;
}