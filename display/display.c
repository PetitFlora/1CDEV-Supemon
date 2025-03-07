#include "display.h"
#include "../structures/structures.h"
#include "../features/features.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int display_Menus(const char* menu[],int nbLigne, int nbOutput) {
    int choice;
    int error;
    printf(" +-----------------------------------+\n");
    for (int i = 0; i < nbLigne; i++) {
        printf(" | %s |\n", menu[i]);
    }
    printf(" +-----------------------------------+\n");
    do {
        printf(" Choose : ");
        error = scanf("%d", &choice);
        if (error == 0) {
            while (getchar() != '\n') {}
            printf(" Invalid input.");
        }
    } while (error == 0 || !(choice >= 1 && choice <= nbOutput));
    return choice;
}

int display_GameTitle(void) {
    int choice = 0;
    const char* menu[] = {
        "Supemon :                        ",
        "      1 - Load a game            ",
        "      2 - New game               "
    };
    return display_Menus(menu, 3, 2);
}

int display_UploadSaveFile(void) {
    const char* menu[] = {
        "Upload a save file :             ",
        "      1 - Load Save File         ",
        "      2 - Go back                "
    };
    return display_Menus(menu, 3, 2);
}

void display_NewGame(void) {
    char *name = malloc(16*sizeof(char));
    int starter;
    int error;
    printf(" New Game\n");
    do {
        printf(" Enter your name (15 characters max) :\n");
        error = scanf("%s", name);
        if (error == 0) {
            while (getchar() != '\n') {}
            printf(" Invalid input.");
        }
    } while (error == 0);
    
    printf("Hello %s!\n", name);
    printf("Welcome in Supemon World!\n");
    printf(" +-----------------------------------+\n");
    printf(" | Choose your starter Supemon       |\n");
    for (int i = 0; i < 3; i++) {
        printf(" |      %d - %s               |\n", i+1, supedex[i].name);
    }
    printf(" +-----------------------------------+\n");
    do {
        printf(" Choose : ");
        error = scanf("%d", &starter);
        if (error == 0) {
            while (getchar() != '\n') {}
            printf(" Invalid input.");
        }
    } while (error == 0 || !(starter >= 1 && starter <= 3));
    features_CreateNewPlayer(name, starter);
}


int display_Home(void) {
    const char* menu[] = {
        "Home :                           ",
        "      1 - Into the Wild          ",
        "      2 - In the shop            ",
        "      3 - In the Supemon Center  ",
        "      4 - Leave the game         "
    };
    return display_Menus(menu, 5, 4);
}


int display_Wild(void){
    const char* menu[] = {
        "You are in the wild! :           ",
        "What do you want to do ? :       ",
        "      1 - Fight                  ",
        "      2 - Leave                  "
    };
    return display_Menus(menu, 4, 2);
}

int display_WildFight(supemon wildSupemon){
    int fight;
    printf(" Your turn...\n");
    printf("\n");
    printf(" -------------------------------------\n");
    printf(" %s (enemy)\n", wildSupemon.name);
    printf(" -------------------------------------\n");
    printf(" | HP : %d/%d              lvl : %d    |\n", wildSupemon.hps, wildSupemon.maxHps, wildSupemon.lvl);
    printf(" | Att : %d                Def : %d    |\n", wildSupemon.att, wildSupemon.def);
    printf(" | Acc : %d                Eva : %d    |\n", wildSupemon.acc, wildSupemon.eva);
    printf(" -------------------------------------\n");
    printf(" %s (%s)\n", mainPlayer.fightingSupemon.name, mainPlayer.name);
    printf(" -------------------------------------\n");
    printf(" | HP : %d/%d              lvl : %d    |\n", mainPlayer.fightingSupemon.hps, mainPlayer.fightingSupemon.maxHps, mainPlayer.fightingSupemon.lvl);
    printf(" | Att : %d                Def : %d    |\n", mainPlayer.fightingSupemon.att, mainPlayer.fightingSupemon.def);
    printf(" | Acc : %d                Eva : %d    |\n", mainPlayer.fightingSupemon.acc, mainPlayer.fightingSupemon.eva);
    printf(" -------------------------------------\n");

    printf("\n");

    const char* menu[] = {
        "You are fighting!                ",
        "What will you do ?               ",
        "      1 - Attack                 ",
        "      2 - Change Supemon         ",
        "      3 - Use an Item            ",
        "      4 - Capture                ",
        "      5 - Run away              "
    };
    return display_Menus(menu, 7, 5);
}

int display_FightAttack(void){
    int attack;
    int error;
    printf(" +-----------------------------------+\n");
    printf("  Choose your attack\n");
    for (int i = 0; i < 2; i++) {
        printf(" |      %d - %s      |\n",i+1, mainPlayer.fightingSupemon.moveList[i].name);
    }
    printf(" +-----------------------------------+\n");
    do {
        printf(" Choose : ");
        error = scanf("%d", &attack);
        if (error == 0) {
            while (getchar() != '\n') {}
            printf(" Invalid input.");
        }
    } while (error == 0 || !(attack >= 1 && attack <= 2));

    return attack;
}

int display_Item(void){
    int whatItem;
    int error;
    item *bag = mainPlayer.bag;
    printf(" +-----------------------------------+\n");
    printf("  What do you want to use ?         \n");
    for (int i = 0; i < 3; i++) {
        printf(" |      %d - %s - %d     |\n",i+1, bag[i].name, bag[i].howManyItem);
    }
    printf(" +-----------------------------------+\n");
    do {
        printf(" Choose : ");
        error = scanf("%d", &whatItem);
        if (error == 0) {
            while (getchar() != '\n') {}
            printf(" Invalid input.");
        }
    } while (error == 0 || !(whatItem >= 1 && whatItem <= 3 && bag[whatItem - 1].howManyItem > 0));

    return whatItem;
}


int display_Shop(void){
    printf(" You have %d Supcoins\n",  mainPlayer.supcoins);
    const char* menu[] = {
        "What do you want to do ?         ",
        "      1 - Buy                    ",
        "      2 - Sell                   ",
        "      3 - Leave                  "
    };
    return display_Menus(menu, 4, 3);
}

int display_ShopBuy(void){
    int buy;
    int error;
    printf(" +-----------------------------------+\n");
    printf("  You have %d Supcoins\n", mainPlayer.supcoins);
    printf("  What do you want to buy ?\n");
    for (int i = 0; i < 3; i++) {
        printf(" |      %d - %s - %d $   |\n",i+1, allItems[i].name, allItems[i].price);
    }
    printf(" +-----------------------------------+\n");
    do {
        printf(" Choose : ");
        error = scanf("%d", &buy);
        if (error == 0) {
            while (getchar() != '\n') {}
            printf(" Invalid input.");
        }
    } while (error == 0 || !(buy >= 1 && buy <= 3 && mainPlayer.supcoins >= allItems[buy - 1].price));

    return buy;
}

int display_ShopSell(void){
    int sell;
    int error;
    item *bag = mainPlayer.bag;
    printf(" +-----------------------------------+\n");
    printf("  You have %d Supcoins\n", mainPlayer.supcoins);
    printf("  What do you want to sell ?\n");
    for (int i = 0; i < 3; i++) {
        printf(" |      %d - %s - %d $ - %d   |\n", i+1, bag[i].name, bag[i].price/2, bag[i].howManyItem);
    }
    printf(" +-----------------------------------+\n");
    do {
        printf(" Choose : ");
        error = scanf("%d", &sell);
        if (error == 0) {
            while (getchar() != '\n') {}
            printf(" Invalid input.");
        }
    } while (error == 0 || !(sell >= 1 && sell <= 3 && bag[sell - 1].howManyItem > 0));

    return sell;
}

int display_ShopHowMany(int nb, int buyOrSell){
    int howMany;
    int error;
    if (buyOrSell == 1) {
        do {
            printf("How many do you want to buy ?\n");
            error = scanf("%d", &howMany);
            if (error == 0) {
                while (getchar() != '\n') {}
                printf(" Invalid input.");
            }
        } while (error == 0 || howMany*allItems[nb - 1].price > mainPlayer.supcoins);
        return howMany;
    }
    else {
        do {
            printf("How many do you want to sell ?\n");
            error = scanf("%d", &howMany);
            if (error == 0) {
                while (getchar() != '\n') {}
                printf(" Invalid input.");
            }
        } while (error == 0 || howMany > mainPlayer.bag[nb - 1].howManyItem);
        return howMany;
    }
}


int display_SupemonCenter(void){
    const char* menu[] = {
        "Supemon Center :                 ",
        "      1 - Heal                   ",
        "      2 - Change Fighting Supemon",
        "      3 - Leave                  "
    };
    return display_Menus(menu, 4, 3);
}

void display_AllSupemon(void) {
    printf(" +-----------------------------------+\n");
    printf(" |      %s  - %d/%d hps       |\n", mainPlayer.fightingSupemon.name, mainPlayer.fightingSupemon.hps, mainPlayer.fightingSupemon.maxHps);
    for (int i = 0; i < 5; i++) {
        supemon supemonInfos = mainPlayer.supemonList[i];
        printf(" |      %s  - %d/%d hps       |\n", supemonInfos.name, supemonInfos.hps, supemonInfos.maxHps);
    }
    printf(" +-----------------------------------+\n");

}

int display_ChangeSupemon(void) {
    int newFightingSupemon;
    int error;
    printf(" +-----------------------------------+\n");
    printf("  Current fighting Supemon :        \n");
    printf("           %s  - lvl %d      \n", mainPlayer.fightingSupemon.name, mainPlayer.fightingSupemon.lvl);
    printf(" +-----------------------------------+\n");
    printf("  Choose your fighting Supemon      \n");
    for (int i = 0; i < 5; i++) {
        supemon supemonInfos = mainPlayer.supemonList[i];
        printf(" |      %d - %s  - lvl %d      |\n", i+1, supemonInfos.name, supemonInfos.lvl);
    }
    printf(" +-----------------------------------+\n");
    do
    {
        printf(" Choose : ");
        error = scanf("%d", &newFightingSupemon);
        if (error == 0) {
            while (getchar() != '\n') {}
            printf(" Invalid input.");
        }
    } while (error == 0 || !(newFightingSupemon >= 1 && newFightingSupemon <= 5));

    return newFightingSupemon;
}


int display_Leave(void){
    const char* menu[] = {
        "Are you sure you want to leave ? ",
        "      1 - Save                   ",
        "      2 - Keep playing           "
    };
    return display_Menus(menu, 3, 2);
}
