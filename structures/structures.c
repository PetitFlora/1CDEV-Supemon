#include "structures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

supemon supedex[3] = {
    {
        .name = "Supasaur  ",
        .lvl = 1, .exp = 0,
        .hps = 9, .maxHps = 9,
        .att = 1, .baseAtt = 1,
        .def = 1, .baseDef = 1,
        .eva = 3, .baseEva = 3,
        .acc = 2, .baseAcc = 2,
        .spd = 2, .baseSpd = 2,
        .moveList = {
            {.name = "Pound  ", .damage = 2, .stat = "hps", .who = "opponent"},
            {.name = "Foliage", .damage = 1, .stat = "eva", .who = "launcher"}
        }
    },
    {
        .name = "Supmander ",
        .lvl = 1, .exp = 0,
        .hps = 10, .maxHps = 10,
        .att = 1, .baseAtt = 1,
        .def = 1, .baseDef = 1,
        .eva = 1, .baseEva = 1,
        .acc = 2, .baseAcc = 2,
        .spd = 1, .baseSpd = 1,
        .moveList = {
            {.name = "Scratch", .damage = 3, .stat = "hps", .who = "opponent"},
            {.name = "Growl  ", .damage = 1, .stat = "att", .who = "launcher"}
        }
    },
    {
        .name = "Supirtle  ",
        .lvl = 1, .exp = 0,
        .hps = 11, .maxHps = 11,
        .att = 1, .baseAtt = 1,
        .def = 2, .baseDef = 2,
        .eva = 2, .baseEva = 2,
        .acc = 1, .baseAcc = 1,
        .spd = 2, .baseSpd = 2,
        .moveList = {
            {.name = "Pound  ", .damage = 2, .stat = "hps", .who = "opponent"},
            {.name = "Shell  ", .damage = 1, .stat = "def", .who = "launcher"}
        }
    }
};

item allItems[3] = {
    {
        .name = "Potion      ",
        .price = 100,
        .stat = "hps",
        .howMuchStat = 5,
    },
    {
        .name = "Super potion",
        .price = 300,
        .stat = "hps",
        .howMuchStat = 10,
    },
    {
        .name = "Rare candy  ",
        .price = 700,
        .stat = "lvl",
        .howMuchStat = 1,
    }
};

player mainPlayer = {
    .supcoins = 1000,
    .supemonList = {},
    .fightingSupemon = {},
    .bag = {
        {.name = "Potion", .price = 100, .stat = "hps", .howMuchStat = 5, .howManyItem = 1 },
        { .name = "Super potion", .price = 300, .stat = "hps", .howMuchStat = 10, .howManyItem = 0 },
        {.name = "Rare candy", .price = 700, .stat = "lvl", .howMuchStat = 1, .howManyItem = 0 }
    }
};