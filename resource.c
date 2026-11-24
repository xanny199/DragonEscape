#include <stdlib.h>

#include "resource.h"
#include "map.h"

/**
 * Rozpozná surovinu podľa znaku mapy W, S, I alebo C
 * @param symbol Znak načítaný z mapy
 * @return Typ suroviny alebo NO_RESOURCE pri neznámom znaku
 */
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

/**
 * Vráti textovy názov suroviny používaný pri vypisovaní inventára a predaji
 * @param type Typ suroviny
 * @return Ukazovateľ na názov suroviny alebo text Unknown
 */
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
        default:
            return "Unknown";
    }
}

/**
 * Odstráni staré suroviny z brlohu a rozmiestni tri drevá, tri kamene, dve železá a jeden kryštál pomocou rand()
 * @param player Kópia hráča
 */
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

/**
 * Určí počet skúseností získaných za zdvihnutie konkrétnej suroviny
 * @param type Typ zozbieranej suroviny
 * @return 5 pre drevo, 7 pre kameň, 10 pre železo, 15 pre kryštál
 */
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

/**
 * Prejde celú mapu brlohu a všetky znaky surovín nahradí bodkou
 */
void clearResources(void) {
    for (int y = 0; y < MAP_ROWS; y++) {
        for (int x = 0; x < MAP_COLS; x++) {
            ResourceType type = getResourceType(lairMap[y][x]);

            if (type != NO_RESOURCE) {
                lairMap[y][x] = '.';
            }
        }
    }
}