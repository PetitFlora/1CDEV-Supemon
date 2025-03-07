#ifndef GAME_FEATURES_H
#define GAME_FEATURES_H

#include "../structures/structures.h"

int features_FileExists(const char *filePath);
void features_LoadGame(char* filePath);
void features_SaveGame(void);
void features_CreateNewPlayer(char* name, int starter);

supemon features_GenerateWildSupemon(void);
int features_Battle(supemon wildSupemon);
int features_WhoAttacksFirst(supemon *wildSupemon);
int features_AsFainted(supemon *supemonToCheck);
int features_FightAttack(supemon *wildSupemon, int playerAttack);
void features_Attack(supemon *launcher, supemon *opponent, int attack);
void features_WonBattle(supemon wildSupemon);

void features_ChangeSupemon(void);
void features_UseItem(void);
int features_CatchSupemon(supemon wildSupemon);
int features_RunAway(supemon wildSupemon);

int features_Probability(int probability);
void features_heal(void);
void features_LvlUp(void);
void features_ResetStat(void);

#endif