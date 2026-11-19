
#ifndef PLAYER_H
#define PLAYER_H

#define MAX_LEVEL 5
#define XP_STEP 40

typedef struct {
    int x;
    int y;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int level;
    int xp;
    int gold;
    
    int equippedWeapon;
    int equippedArmor;

    int potionAttackBonus;
    int potionDefenseBonus;
} Player;

void initPlayer(Player *player);
void printPlayer(Player player);

#endif
