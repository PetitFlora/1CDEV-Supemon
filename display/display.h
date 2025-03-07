#ifndef DISPLAY_H
#define DISPLAY_H

#include "../structures/structures.h"

int display_Menus(const char* menu[],int nbLigne, int nbOutput);

int display_GameTitle(void);
int display_UploadSaveFile(void);
void display_NewGame(void);

int display_Home(void);

int display_Wild(void);
int display_WildFight(supemon wildSupemon);
int display_FightAttack(void);
int display_Item(void);

int display_Shop(void);
int display_ShopBuy(void);
int display_ShopSell(void);
int display_ShopHowMany(int nb, int buyOrSell);

int display_SupemonCenter(void);
void display_AllSupemon(void);
int display_ChangeSupemon(void);

int display_Leave(void);

#endif