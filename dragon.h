#ifndef DRAGON_H
#define DRAGON_H

typedef struct {
    int x;
    int y;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int isAwake;
} Dragon;

void initDragon(Dragon *dragon);
void spawnDragon(Dragon *dragon);

#endif