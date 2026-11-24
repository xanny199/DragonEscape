
#include <stdio.h>
#include "player.h"

/**
 * Nastaví počiatočný stav hráča: pozíciu, životy, útok, obranu, úroveň, skúsenosti, zlato, výbavu a bonusy elixírov
 * @param player Ukazovateľ na štruktúru hráča
 */
void initPlayer(Player *player) {
    player->x = 1;
    player->y = 1;
    player->hp = 100;
    player->maxHp = 100;
    player->attack = 15;
    player->defense = 5;
    player->level = 1;
    player->xp = 0;

    player->gold = 0;

    player->equippedWeapon = -1;
    player->equippedArmor = -1;

    player->potionAttackBonus = 0;
    player->potionDefenseBonus = 0;
}

/**
 * Vypíše základné štatistiky hráča a číselné hodnoty vybavenej zbrane a brnenia
 * @param player Kópia hráča
 */
void printPlayer(Player player) {
    printf("\n--- PLAYER STATS ---\n");
    printf("HP: %d/%d\n", player.hp, player.maxHp);
    printf("Attack: %d\n", player.attack);
    printf("Defense: %d\n", player.defense);
    printf("Level: %d\n", player.level);
    printf("XP: %d\n", player.xp);

    printf("Equipped weapon: %d\n", player.equippedWeapon);
    printf("Equipped armor: %d\n", player.equippedArmor);
}

/**
 * Určí hranicu celkových skúseností potrebných na ďalšiu úroveň; na maximálnej úrovni vráti nulu
 * @param player Kópia hráča
 * @return Počet XP potrebných na dosiahnutie ďalšej úrovne
 */
int getNextLevelXP(Player player) {
    if (player.level >= MAX_LEVEL) {
        return 0;
    }

    return player.level * XP_STEP;
}

/**
 * Pridá hráčovi skúsenosti, obmedzí ich na maximum a pri dosiahnutí hranice zvýši úroveň
 * @param player Ukazovateľ na hráča
 * @param amount Počet pridávaných XP
 */
void addExperience(Player *player, int amount) {
    if (amount <= 0 || player->level >= MAX_LEVEL) {
        return;
    }

    player->xp += amount;

    int maxXP = (MAX_LEVEL - 1) * XP_STEP;

    if (player->xp > maxXP) {
        player->xp = maxXP;
    }

    while (player->level < MAX_LEVEL &&
           player->xp >= getNextLevelXP(*player)) {

        player->level++;

        player->maxHp += 10;
        player->hp = player->maxHp;

        player->attack += 2;
        player->defense += 1;
    }
}