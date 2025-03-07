#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    char name[16];
    int price;
    char stat[8];
    int howMuchStat;
    int howManyItem
}item;

typedef struct {
    char name[16];
    int damage;
    char stat[4];
    char who[9]; // Opponent or Launcher
}move;

typedef struct {
    char name[11];
    int lvl;
    int exp;
    int hps;
    int maxHps;
    int att;
    int baseAtt;
    int def;
    int baseDef;
    int eva;
    int baseEva;
    int acc;
    int baseAcc;
    int spd;
    int baseSpd;
    move moveList[2];
}supemon;

typedef struct {
    char name[16];
    int supcoins;
    supemon supemonList[5];
    supemon fightingSupemon;
    item bag[3];
}player;

extern supemon supedex[3];
extern item allItems[3];
extern player mainPlayer;

#endif