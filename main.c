#include "structures/structures.h"
#include "display/display.h"
#include "features/features.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uploadSaveFile(void);
void newGame(void);
void home(void);
void wild(void);
void wildFight(void);
void shop(void);
void supemonCenter(void);
void leave(void);

void main(void) {
    int choice = display_GameTitle();
    switch (choice) {
    case 1:
        uploadSaveFile();
        break;
    case 2:
        newGame();
        break;
    default:
        break;
    }
}

void uploadSaveFile(void) {
    int choice = display_UploadSaveFile();
    char *filePath = malloc(256*sizeof(char));
    switch (choice) {
    case 1:
        printf(" Enter the file path :\n");
        scanf("%s", filePath);
        if (features_FileExists(filePath) == 1) {
            features_LoadGame(filePath);
            printf("Found the game !\n");
            printf("Welcome back %s!\n", mainPlayer.name);
            free(filePath);
            home();
        }
        else {
            printf("The file doesn't exist.\n");
            uploadSaveFile();
        }
        break;
    case 2:
        main();
        break;
    }
}

void newGame(void) {
    display_NewGame();
    home();
}

void home(void) {
    int where = display_Home();
    switch (where) {
    case 1:
        wild();
        break;
    case 2:
        shop();
        break;
    case 3:
        supemonCenter();
        break;
    case 4:
        leave();
        break;
    default:
        break;
    }
}

void wild(void){
    int choice = display_Wild();
    switch (choice) {
    case 1:
        wildFight();
        break;
    case 2:
        home();
        break;
    default:
        break;
    }
}

void wildFight(void) {
    supemon wildSupemon = features_GenerateWildSupemon();
    do {
        int fight = display_WildFight(wildSupemon);
        switch (fight) {
            case 1: {
                int won = features_FightAttack(&wildSupemon, 1);
                switch (won) {
                case 1:
                    printf("The opponent fainted! You won!\n");
                    features_WonBattle(wildSupemon);
                    features_ResetStat();
                    return wild();
                    break;
                case 2:
                    printf("You fainted! You're running to the Supemon Center\n");
                    features_ResetStat();
                    features_heal();
                    return supemonCenter();
                    break;
                default:
                    break;
                }}
                break;
            case 2:
                features_ChangeSupemon();
                int won = features_FightAttack(&wildSupemon, 0);
                if (won == 2) {
                    printf("You fainted! You're running to the Supemon Center\n");
                    features_ResetStat();
                    features_heal();
                    return supemonCenter();
                }
                break;
            case 3: {
                features_UseItem();
                int won = features_FightAttack(&wildSupemon, 0);
                if (won == 2) {
                    printf("You fainted! You're running to the Supemon Center\n");
                    features_ResetStat();
                    features_heal();
                    return supemonCenter();
                }
                break;}
            case 4: {
                int catch = features_CatchSupemon(wildSupemon);
                if (catch == 1) {
                    features_ResetStat();
                    return wild();
                }
                int won = features_FightAttack(&wildSupemon, 0);
                if (won == 2) {
                    printf("You fainted! You're running to the Supemon Center\n");
                    features_ResetStat();
                    features_heal();
                    return supemonCenter();
                }
                break;}
            case 5: {
                int run = features_RunAway(wildSupemon);
                switch (run) {
                case 0:
                    printf("You can't run away!\n");
                    int won = features_FightAttack(&wildSupemon, 0);
                    if (won == 2) {
                        printf("You fainted! You're running to the Supemon Center\n");
                        features_ResetStat();
                        features_heal();
                        return supemonCenter();
                    }
                    break;
                case 1:
                    printf("You ran away!\n");
                    features_ResetStat();
                    return home();
                    break;
                default:
                    break;
                }
                break;}
            default:
                break;
        }
    } while (features_Battle(wildSupemon) == 1);
}

void shop(void){
    int buySell = display_Shop();
    item *bag = mainPlayer.bag;
    switch (buySell) {
    case 1:
        if (mainPlayer.supcoins < 100) {
            printf("You don't have enough Supcoins to buy anything.\n");
            shop();
        }
        else {
            int buy = display_ShopBuy();
            int howMany = display_ShopHowMany(buy, 1);
            printf("You bought %d %s.\n", howMany, allItems[buy - 1].name);
            mainPlayer.supcoins -= howMany*allItems[buy - 1].price;
            printf("You have %d Supcoins left.\n", mainPlayer.supcoins);
            mainPlayer.bag[buy - 1].howManyItem += howMany;
            shop();
        }
        break;
    case 2:
        if (bag[0].howManyItem == 0 && bag[1].howManyItem == 0 && bag[2].howManyItem == 0) {
                printf("You don't have anything to sell.\n");
                shop();
        }
        else {
            int sell = display_ShopSell();
            int howMany = display_ShopHowMany(sell, 2);
            printf("You sold %d %s.\n", howMany, bag[sell - 1].name);
            mainPlayer.supcoins += howMany*bag[sell - 1].price/2;
            printf("You have %d Supcoins.\n", mainPlayer.supcoins);
            mainPlayer.bag[sell - 1].howManyItem -= howMany;
            shop();
        }
        break;
    case 3:
        home();
        break;
    default:
        break;
    }
}

void supemonCenter(void){
    display_AllSupemon();
    int heal = display_SupemonCenter();
    switch (heal) {
    case 1:
        features_heal();
        supemonCenter();
        break;
    case 2:
        features_ChangeSupemon();
        supemonCenter();
        break;
    case 3:
        home();
        break;
    default:
        break;
    }
}

void leave(void){
    int leave = display_Leave();
    switch (leave) {
    case 1:
        printf("Saving the game...\n");
        features_SaveGame();
        printf("Goodbye %s!\n", mainPlayer.name);
        break;
    case 2:
        home();
        break;
    default:
        break;
    }
}
