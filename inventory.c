#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "inventory.h"

/**
 * Vynuluje počty všetkých surovín a predmetov v inventári.
 * @param inventory Ukazovateľ na inventár
 */
void initInventory(Inventory *inventory) {
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        inventory->quantities[i] = 0;
    }

    for (int i = 0; i < ITEM_COUNT; i++) {
        inventory->items[i] = 0;
    }
}

/**
 * Prida jeden kus suroviny, ak je jej typ platný
 * @param inventory Ukazovateľ na inventár
 * @param type Typ zbieranej suroviny
 */
void addResource(Inventory *inventory, ResourceType type) {
    if (type >= WOOD && type < NO_RESOURCE) {
        inventory->quantities[type]++;
    }
}

/**
 * Pridá jeden kus predmetu, ak jeho typ patrí do platného rozsahu.
 * @param inventory Ukazovateľ na inventár
 * @param type Typ kupovaného alebo získaného predmetu
 */
void addItem(Inventory *inventory, ItemType type) {
    if (type >= WOODEN_SWORD && type < ITEM_COUNT) {
        inventory->items[type]++;
    }
}

/**
 * Prevedie typ predmetu na textový názov vhodný na zobrazenie v menu
 * @param type Typ predmetu
 * @return Ukazovatel na názov predmetu alebo text Unnown Item
 */
const char *getItemName(ItemType type) {
    switch (type) {
        case WOODEN_SWORD: return "Wooden Sword";
        case IRON_SWORD: return "Iron Sword";
        case STEEL_SWORD: return "Steel Sword";
        case CRYSTAL_SWORD: return "Crystal Sword";
        case DRAGON_SWORD: return "Dragon Sword";

        case CLOTH_ARMOR: return "Cloth Armor";
        case LEATHER_ARMOR: return "Leather Armor";
        case IRON_ARMOR: return "Iron Armor";
        case STEEL_ARMOR: return "Steel Armor";
        case DRAGON_ARMOR: return "Dragon Armor";

        case SMALL_POTION: return "Small Health Potion";
        case MEDIUM_POTION: return "Medium Health Potion";
        case LARGE_POTION: return "Large Health Potion";
        case STRENGTH_POTION: return "Strength Potion";
        case DEFENSE_POTION: return "Defense Potion";

        default: return "Unknown Item";
    }
}

/**
 * Vypíše počty surovín a predmetov do konzoly. Inventár sa odovzdáva hodnotou, preto sa pri vypisovaní nemení
 * @param inventory Kópia inventára
 */
void printInventory(Inventory inventory) {
    printf("\n--- RESOURCES ---\n");

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        printf("%s: %d\n",
               getResourceName((ResourceType)i),
               inventory.quantities[i]);
    }

    printf("\n--- ITEMS ---\n");

    int hasItems = 0;

    for (int i = 0; i < ITEM_COUNT; i++) {
        if (inventory.items[i] > 0) {
            printf("%s: %d\n",
                   getItemName((ItemType)i),
                   inventory.items[i]);

            hasItems = 1;
        }
    }

    if (!hasItems) {
        printf("Empty\n");
    }

    printf("\n");
}

/**
 * Vyhľadá nemenné údaje o predmete v internej tabuľke: typ, kategóriu, názov, cenu a hodnotu bonusu.
 * @param type Typ požadovaného predmetu
 * @return Štruktúru Item s údajmi predmetu
 */
Item getItem(ItemType type) {
    static const Item items[ITEM_COUNT] = {
        {WOODEN_SWORD, WEAPON, "Wooden Sword", 10, 5},
        {IRON_SWORD, WEAPON, "Iron Sword", 25, 10},
        {STEEL_SWORD, WEAPON, "Steel Sword", 45, 15},
        {CRYSTAL_SWORD, WEAPON, "Crystal Sword", 70, 20},
        {DRAGON_SWORD, WEAPON, "Dragon Sword", 100, 30},

        {CLOTH_ARMOR, ARMOR, "Cloth Armor", 10, 3},
        {LEATHER_ARMOR, ARMOR, "Leather Armor", 20, 5},
        {IRON_ARMOR, ARMOR, "Iron Armor", 40, 10},
        {STEEL_ARMOR, ARMOR, "Steel Armor", 65, 15},
        {DRAGON_ARMOR, ARMOR, "Dragon Armor", 100, 25},

        {SMALL_POTION, POTION, "Small Health Potion", 10, 20},
        {MEDIUM_POTION, POTION, "Medium Health Potion", 20, 40},
        {LARGE_POTION, POTION, "Large Health Potion", 35, 70},
        {STRENGTH_POTION, POTION, "Strength Potion", 40, 10},
        {DEFENSE_POTION, POTION, "Defense Potion", 40, 10}
    };

    if (type < WOODEN_SWORD || type >= ITEM_COUNT) {
        Item unknown = {ITEM_COUNT, POTION, "Unknown", 0, 0};
        return unknown;
    }

    return items[type];
}

/**
 * Vybaví hráča vlastnenou zbraňou alebo brnením
 * @param player Ukazovateľ na hráča
 * @param inventory Inventár na overenie, či hráč predmet vlastní
 * @param type Typ predmetu určeného na vybavenie
 * @return 1 pri úspešnom vybavení, inak 0
 */
int equipItem(Player *player, Inventory *inventory,
             ItemType type) {
    if (type < WOODEN_SWORD || type >= ITEM_COUNT) {
        return 0;
    }

    if (inventory->items[type] <= 0) {
        return 0;
    }

    Item item = getItem(type);

    if (item.category == WEAPON) {
        player->equippedWeapon = type;
    } else if (item.category == ARMOR) {
        player->equippedArmor = type;
    } else {
        return 0;
    }
    
    return 1;
}

/**
 * Použije vlastnený elixir. Liečivý obnoví HP najviac po maximum; silový alebo obranný nastaví jednorazový bonus, ak ešte nie je aktívny. 
 * Spotrebuje elixír iba pri úspechu
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 * @param type Typ elixíru
 * @return 1 pri úspešnom použití, inak 0.
 */
int usePotion(Player *player, Inventory *inventory,
              ItemType type) {

    if (type < SMALL_POTION || type > DEFENSE_POTION) {
        return 0;
    }

    if (inventory->items[type] <= 0) {
        return 0;
    }

    Item potion = getItem(type);

    switch (type) {
        case SMALL_POTION:
        case MEDIUM_POTION:
        case LARGE_POTION:
            if (player->hp >= player->maxHp) {
                return 0;
            }

            player->hp += potion.value;

            if (player->hp > player->maxHp) {
                player->hp = player->maxHp;
            }
            break;

        case STRENGTH_POTION:
            if (player->potionAttackBonus != 0) {
                return 0;
            }

            player->potionAttackBonus = potion.value;
            break;

        case DEFENSE_POTION:
            if (player->potionDefenseBonus != 0) {
                return 0;
            }

            player->potionDefenseBonus = potion.value;
            break;

        default:
            return 0;
    }

    inventory->items[type]--;
    return 1;
}

/**
 * Vypočíta výsledný útok zo základného útoku, bonusu vybavenej zbrane a účinku elixíru
 * @param player Kópia štruktúry hráča s údajmi o útoku a výbave
 * @return Celkovú hodnotu útoku
 */
int getTotalAttack(Player player) {
    int attack = player.attack + player.potionAttackBonus;

    if (player.equippedWeapon != -1) {
        Item weapon = getItem((ItemType) player.equippedWeapon);
        attack += weapon.value;
    }

    return attack;
}

/**
 * Vypočíta výslednú obranu zo základnej obrany, bonusu vybaveného brnenia a účinku elixíru
 * @param player Kópia štruktúry hráča s údajmi o obrane a výbave
 * @return Celkovú hodnotu obraný
 */
int getTotalDefense(Player player) {
    int defense = player.defense + player.potionDefenseBonus;

    if (player.equippedArmor != -1) {
        Item armor = getItem((ItemType) player.equippedArmor);
        defense += armor.value;
    }

    return defense;
}

/**
 * Zobrazí vlastnené zbrane alebo brnenia danej kategórie a umožní hráčovi vybrať vybavený predmet
 * Ide o pomocnú funkciu používanú len v tomto súbore.
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 * @param category Požadovaná kategória WEAPON alebo ARMOR
 */
static void chooseEquipment(Player *player,
                            Inventory *inventory,
                            ItemCategory category) {
    system("cls");

    printf("=== EQUIP ITEM ===\n\n");

    int available[ITEM_COUNT];
    int count = 0;

    for (int i = 0; i < ITEM_COUNT; i++) {
        Item item = getItem((ItemType)i);

        if (item.category == category &&
            inventory->items[i] > 0) {

            available[count] = i;

            printf("%d. %s (+%d %s)\n",
                   count + 1,
                   item.name,
                   item.value,
                   category == WEAPON ? "Attack" : "Defense");

            count++;
        }
    }

    printf("\n0. Back\n");

    if (count == 0) {
        printf("You have no items in this category.\n");
        _getch();
        return;
    }

    printf("\nChoose item: ");

    char choice = _getch();

    if (choice == '0') {
        return;
    }

    int selected = choice - '1';

    if (selected < 0 || selected >= count) {
        return;
    }

    ItemType type = (ItemType)available[selected];

    if (equipItem(player, inventory, type)) {
        printf("\nEquipped: %s\n", getItemName(type));
    }

    printf("Press any key to continue...");
    _getch();
}

/**
 * Otvorí menu výbavy, zobrazí aktuálnu zbraň, brnenie a výsledné štatistiky a umožní zmeniť výbavu
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 */
void openEquipmentMenu(Player *player, Inventory *inventory) {
    char choice;

    while (1) {
        system("cls");

        printf("=== EQUIPMENT MENU ===\n\n");

        printf("Attack: %d\n", getTotalAttack(*player));
        printf("Defense: %d\n\n", getTotalDefense(*player));

        printf("Equipped Weapon: %s\n",
               player->equippedWeapon == -1
                   ? "None"
                   : getItemName((ItemType)player->equippedWeapon));

        printf("Equipped Armor: %s\n\n",
               player->equippedArmor == -1
                   ? "None"
                   : getItemName((ItemType)player->equippedArmor));

        printf("1. Equip Weapon\n");
        printf("2. Equip Armor\n");
        printf("0. Back\n");

        choice = _getch();

        if (choice == '0') {
            return;
        }

        switch (choice) {
            case '1':
                chooseEquipment(player, inventory, WEAPON);
                break;

            case '2':
                chooseEquipment(player, inventory, ARMOR);
                break;

            default:
                break;
        }
    }
}

/**
 * Otvorí menu elixírov mimo boja. Umožní použiť vlastnený elixír a zobrazí informáciu o úspechu alebo dôvode odmietnutia.
 * @param player Ukazovateľ na hráča
 * @param inventory Ukazovateľ na inventár
 */
void openPotionMenu(Player *player, Inventory *inventory) {
    while (1) {
        system("cls");

        printf("=== POTIONS ===\n\n");

        printf("HP: %d/%d\n", player->hp, player->maxHp);
        printf("Attack: %d\n", getTotalAttack(*player));
        printf("Defense: %d\n\n", getTotalDefense(*player));

        for (int i = 0; i < 5; i++) {
            ItemType type = (ItemType)(SMALL_POTION + i);
            Item potion = getItem(type);

            printf("%d. %s (+%d) x%d\n",
                   i + 1, potion.name, potion.value,
                   inventory->items[type]);
        }

        printf("\n0. Back\n");
        printf("Choose potion: ");

        char choice = _getch();

        if (choice == '0') {
            return;
        }

        if (choice < '1' || choice > '5') {
            continue;
        }

        ItemType type = (ItemType)(SMALL_POTION + choice - '1');

        if (usePotion(player, inventory, type)) {
            printf("\nUsed: %s\n", getItemName(type));
        } else {
            printf("\nCannot use this potion!\n");
            printf("Check quantity, HP or active bonus.\n");
        }

        printf("Press any key to continue...");
        _getch();
    }
}