#include <stdlib.h>

#include "resource.h"
#include "map.h"

ResourceType getResourceType(char symbol) {
    switch (symbol) {
        case 'W':
            return WOOD;
        case 'S':
            return STONE;
        case 'I':
            return IRON;
        case 'C':
            return CRYSTAL;
        default:
            return NO_RESOURCE;
    }
}

const char *getResourceName(ResourceType type) {
    switch (type) {
        case WOOD:
            return "Wood";
        case STONE:
            return "Stone";
        case IRON:
            return "Iron";
        case CRYSTAL:
            return "Crystal";
        case DRAGON_SCALE:
            return "Dragon Scale";
        default:
            return "Unknown";
    }
}

void generateResources(Player player) {
    char symbols[] = {
        'W', 'W', 'W',
        'S', 'S', 'S',
        'I', 'I',
        'C'
    };

    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            if (getResourceType(lairMap[y][x]) != NO_RESOURCE) {
                lairMap[y][x] = '.';
            }
        }
        
    }
    
    int count = sizeof(symbols) / sizeof(symbols[0]);

    for (int i = 0; i < count; i++) {
        int x;
        int y;

        do {
            x = 1 + rand() % (MAP_COLS - 2);
            y = 1 + rand() % (MAP_ROWS - 2);
        } while (lairMap[y][x] != '.' || (x == player.x && y == player.y));
        
        lairMap[y][x] = symbols[i];
    }
}

int getResourceXP(ResourceType type) {
    switch (type) {
        case WOOD:
            return 5;

        case STONE:
            return 7;

        case IRON:
            return 10;

        case CRYSTAL:
            return 15;

        default:
            return 0;
    }
}
