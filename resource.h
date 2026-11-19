
#ifndef RESOURCE_H
#define RESOURCE_H

#include "player.h"

typedef enum {
    WOOD,
    STONE,
    IRON,
    CRYSTAL,
    DRAGON_SCALE,
    NO_RESOURCE
} ResourceType;

typedef struct {
    ResourceType type;
    int quantity;
} Resource;

ResourceType getResourceType(char symbol);
const char *getResourceName(ResourceType type);
void generateResources(Player player);

#endif