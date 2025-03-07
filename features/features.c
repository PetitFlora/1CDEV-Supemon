#include "features.h"
#include "../structures/structures.h"
#include "../display/display.h"

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int features_FileExists(const char* filePath) {
        FILE *file = fopen(filePath, "rb");
        if (file) {
            fclose(file);
            return 1;
        }
        return 0;
}

void features_LoadGame(char* filePath) {
    FILE *file = fopen(filePath, "rb");
    if (file) {
        fread(mainPlayer.name, sizeof(mainPlayer.name), 1, file);
        fread(&mainPlayer.supcoins, sizeof(mainPlayer.supcoins), 1, file);
        fread(mainPlayer.supemonList, sizeof(mainPlayer.supemonList), 1, file);
        fread(&mainPlayer.fightingSupemon, sizeof(mainPlayer.fightingSupemon), 1, file);
        fread(mainPlayer.bag, sizeof(mainPlayer.bag), 1, file);
        fclose(file);
    } else {
        printf("Failed to open save file.\n");
    }
}

void features_SaveGame(void) {
    FILE *file = fopen("save.bin", "wb");
    if (file) {
        fwrite(mainPlayer.name, sizeof(mainPlayer.name), 1, file);
        fwrite(&mainPlayer.supcoins, sizeof(mainPlayer.supcoins), 1, file);
        fwrite(mainPlayer.supemonList, sizeof(mainPlayer.supemonList), 1, file);
        fwrite(&mainPlayer.fightingSupemon, sizeof(mainPlayer.fightingSupemon), 1, file);
        fwrite(mainPlayer.bag, sizeof(mainPlayer.bag), 1, file);
        fclose(file);
    }
    else {
        printf("Failed to save the game.\n");
    }
}

void features_CreateNewPlayer(char* name, int starter) {
    strcpy(mainPlayer.name, name);
    mainPlayer.fightingSupemon = supedex[starter - 1];
}


supemon features_GenerateWildSupemon(void) {
    int j = rand() % 3;
    supemon randSupemon = supedex[j];
    randSupemon.lvl = mainPlayer.fightingSupemon.lvl;
    for (int i = 0; i < mainPlayer.fightingSupemon.lvl-1; i++) {
        if (features_Probability(50) == 1) {
            randSupemon.maxHps = ceil(randSupemon.maxHps * 1.3);
            randSupemon.baseAtt = ceil(randSupemon.baseAtt * 1.3);
            randSupemon.baseDef = ceil(randSupemon.baseDef * 1.3);
            randSupemon.baseEva = ceil(randSupemon.baseEva * 1.3);
            randSupemon.baseAcc = ceil(randSupemon.baseAcc * 1.3);
            randSupemon.baseSpd = ceil(randSupemon.baseSpd * 1.3);
        }
        else {
            randSupemon.maxHps = floor(randSupemon.maxHps * 1.3);
            randSupemon.baseAtt = floor(randSupemon.baseAtt * 1.3);
            randSupemon.baseDef = floor(randSupemon.baseDef * 1.3);
            randSupemon.baseEva = floor(randSupemon.baseEva * 1.3);
            randSupemon.baseAcc = floor(randSupemon.baseAcc * 1.3);
            randSupemon.baseSpd = floor(randSupemon.baseSpd * 1.3);
        }
    }
    randSupemon.hps = randSupemon.maxHps;
    randSupemon.att = randSupemon.baseAtt;
    randSupemon.def = randSupemon.baseDef;
    randSupemon.eva = randSupemon.baseEva;
    randSupemon.acc = randSupemon.baseAcc;
    randSupemon.spd = randSupemon.baseSpd;
    return randSupemon;
}

int features_Battle(supemon wildSupemon) {
    return mainPlayer.fightingSupemon.hps > 0 && wildSupemon.hps > 0;
}

int features_WhoAttacksFirst(supemon *wildSupemon) {
    if (mainPlayer.fightingSupemon.spd > wildSupemon->spd) {
        return 0;
    } else if (mainPlayer.fightingSupemon.spd < wildSupemon->spd) {
        return 1;
    } else {
        return features_Probability(50);
    }
}

int features_AsFainted(supemon *supemonToCheck) {
    return supemonToCheck->hps <= 0;
}

int features_FightAttack(supemon *wildSupemon, int playerAttack) {
    int attack;
    int index;
    if (playerAttack == 1) {
        attack = display_FightAttack();
        index = features_WhoAttacksFirst(wildSupemon);
    }
    else {
        index = 2;
    }
    if (index == 0) {
        features_Attack(&mainPlayer.fightingSupemon, wildSupemon, attack-1);
        if (features_AsFainted(wildSupemon) == 1) {
            return 1;
        }
        features_Attack(wildSupemon, &mainPlayer.fightingSupemon, rand() % 2);
        if (features_AsFainted(&mainPlayer.fightingSupemon) == 1) {
            return 2;
        }
    }
    else if (index == 1) {
        features_Attack(wildSupemon, &mainPlayer.fightingSupemon, rand() % 2);
        if (features_AsFainted(&mainPlayer.fightingSupemon) == 1) {
            return 2;
        }
        features_Attack(&mainPlayer.fightingSupemon, wildSupemon, attack-1);
        if (features_AsFainted(wildSupemon) == 1) {
            return 1;
        }
    }
    else{
        features_Attack(wildSupemon, &mainPlayer.fightingSupemon, rand() % 2);
        if (features_AsFainted(&mainPlayer.fightingSupemon) == 1) {
            return 2;
        }
    }
}

void features_Attack(supemon *launcher, supemon *opponent, int attack) {
    move launch = launcher->moveList[attack];
    if (strcmp(launch.stat, "hps") == 0) {
        int accuracy = (((float)launcher->acc / (launcher->acc + opponent->eva)) + 0.1) * 100;
        if (features_Probability(accuracy) == 1) {
            float damage = ((float)launcher->att * ((float)launch.damage / opponent->def));
            if (damage != (int)damage) {
                if (features_Probability(50) == 1) {
                    damage = ceil(damage);
                }
                else {
                    damage = floor(damage);
                }
            }
            else {
                damage = (int)damage;
            }
            opponent->hps -= damage;
            printf("The attack hit! %s lost %d hps.\n", opponent->name, (int)damage);
        }
        else {
            printf("The attack missed!\n");
        }
    }
    else if (strcmp(launch.stat, "att") == 0) {
        launcher->att += launch.damage;
        printf("%s's attack increased by %d.\n", launcher->name, launch.damage);
    }
    else if (strcmp(launch.stat, "def") == 0) {
        launcher->def += launch.damage;
        printf("%s's defense increased by %d.\n", launcher->name, launch.damage);
    }
    else if (strcmp(launch.stat, "eva") == 0) {
        launcher->eva += launch.damage;
        printf("%s's evasion increased by %d.\n", launcher->name, launch.damage);
    }
}

void features_WonBattle(supemon wildSupemon) {
    srand(time(NULL));
    int expRand = rand() % 5;
    int moneyRand = rand() % 5;
    int expWon = wildSupemon.lvl*(100*(expRand+1));
    int moneyWon = wildSupemon.lvl*(100*(moneyRand+1));
    mainPlayer.fightingSupemon.exp += expWon;
    features_LvlUp();
    mainPlayer.supcoins += moneyWon;
    printf("You won %d exp and %d Supcoins.\n", expWon, moneyWon);
}


void features_ChangeSupemon(void) {
    int newFightingSupemon = display_ChangeSupemon();
    supemon temp = mainPlayer.fightingSupemon;
    mainPlayer.fightingSupemon = mainPlayer.supemonList[newFightingSupemon - 1];
    mainPlayer.supemonList[newFightingSupemon - 1] = temp;
}

void features_UseItem(void) {
    int item = display_Item();
    switch (item) {
    case 1:
        mainPlayer.fightingSupemon.hps += 5;
        break;
    case 2:
        mainPlayer.fightingSupemon.hps += 10;
        break;
    case 3:
    mainPlayer.fightingSupemon.exp += mainPlayer.fightingSupemon.lvl * 1000 - 500;
    features_LvlUp();
        break;
    default:
        break;
    }
    mainPlayer.bag[item - 1].howManyItem--;
    printf("You used a %s.\n", mainPlayer.bag[item - 1].name);
}

int features_CatchSupemon(supemon wildSupemon) {
    for (int i = 0; i < 5; i++) {
        if (!mainPlayer.supemonList[i].lvl) {
            float catchRate = ((float)(wildSupemon.maxHps - wildSupemon.hps) / wildSupemon.maxHps - 0.5) * 100;
            if (features_Probability(catchRate)) {
                mainPlayer.supemonList[i] = wildSupemon;
                printf("You caught %s!\n", wildSupemon.name);
                return 1;
            }
            else {
                printf("The Supemon escaped!\n");
                return 0;
            }
        }
        else if (i == 4 && mainPlayer.supemonList[i].lvl) {
            printf("You don't have enough space in your team.\n");
            return 0;
        }
    }
}

int features_RunAway(supemon wildSupemon) {
    int speedCkeck = ((float)mainPlayer.fightingSupemon.spd / (mainPlayer.fightingSupemon.spd + wildSupemon.spd)) * 100;
    if (features_Probability(speedCkeck)) {
        return 1;
    }
    else {
        return 0;
    }
}


int features_Probability(int probability) {
    srand(time(NULL));
    int nb = rand() % 100;
    return nb <= probability;
}

void features_heal(void) {
    printf("Healing your Supemons...\n");
    mainPlayer.fightingSupemon.hps = mainPlayer.fightingSupemon.maxHps;
    for (int i = 0; i < 5; i++) {
        mainPlayer.supemonList[i].hps = mainPlayer.supemonList[i].maxHps;
    }
    printf("Your Supemons are healed!\n");
}

void features_LvlUp(void) {
    int howManyExpToNewLvl = mainPlayer.fightingSupemon.lvl * 1000 - 500;
    while (mainPlayer.fightingSupemon.exp >= howManyExpToNewLvl) {
        mainPlayer.fightingSupemon.lvl++;
        mainPlayer.fightingSupemon.exp -= howManyExpToNewLvl;
        srand(time(NULL));
        if (features_Probability(50) == 1) {
            mainPlayer.fightingSupemon.maxHps = ceil(mainPlayer.fightingSupemon.maxHps * 1.3);
            mainPlayer.fightingSupemon.baseAtt = ceil(mainPlayer.fightingSupemon.baseAtt * 1.3);
            mainPlayer.fightingSupemon.baseDef = ceil(mainPlayer.fightingSupemon.baseDef * 1.3);
            mainPlayer.fightingSupemon.baseEva = ceil(mainPlayer.fightingSupemon.baseEva * 1.3);
            mainPlayer.fightingSupemon.baseAcc = ceil(mainPlayer.fightingSupemon.baseAcc * 1.3);
            mainPlayer.fightingSupemon.baseSpd = ceil(mainPlayer.fightingSupemon.baseSpd * 1.3);
        }
        else {
            mainPlayer.fightingSupemon.maxHps = floor(mainPlayer.fightingSupemon.hps * 1.3);
            mainPlayer.fightingSupemon.baseAtt = floor(mainPlayer.fightingSupemon.baseAtt * 1.3);
            mainPlayer.fightingSupemon.baseDef = floor(mainPlayer.fightingSupemon.baseDef * 1.3);
            mainPlayer.fightingSupemon.baseEva = floor(mainPlayer.fightingSupemon.baseEva * 1.3);
            mainPlayer.fightingSupemon.baseAcc = floor(mainPlayer.fightingSupemon.baseAcc * 1.3);
            mainPlayer.fightingSupemon.baseSpd = floor(mainPlayer.fightingSupemon.baseSpd * 1.3);
        }
        howManyExpToNewLvl += 1000;
    }
}

void features_ResetStat(void) {
    mainPlayer.fightingSupemon.att = mainPlayer.fightingSupemon.baseAtt;
    mainPlayer.fightingSupemon.def = mainPlayer.fightingSupemon.baseDef;
    mainPlayer.fightingSupemon.eva = mainPlayer.fightingSupemon.baseEva;
    mainPlayer.fightingSupemon.acc = mainPlayer.fightingSupemon.baseAcc;
    mainPlayer.fightingSupemon.spd = mainPlayer.fightingSupemon.baseSpd;
}
