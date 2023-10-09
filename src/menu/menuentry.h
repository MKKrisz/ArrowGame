#pragma once

#include "menuelements.h"

//Trying to do something like inheritance in c

typedef enum MEntry_t {
    TEXTBOX = 0,
} MEntry_t;

typedef struct MenuEntry{
    MEntry_t type;
    union{
        Textbox* textbox;
    };
} MenuEntry;
