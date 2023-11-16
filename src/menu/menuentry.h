#pragma once

#include <SDL2/SDL.h>

#include "menuelements.h"
#include "menu.h"

// Trying to do something like inheritance in c

struct Textbox;
struct Button;
struct Slider;

struct Menu;


typedef enum MEntry_t {
    MENU_TEXTBOX = 0,
    MENU_BUTTON = 1,
    MENU_SLIDER = 2
} MEntry_t;

typedef struct MenuEntry{
    MEntry_t Type;
    SDL_Rect Backdrop;
    union{
        struct Textbox* Textbox;
        struct Button* Button;
        struct Slider* Slider;
    };
} MenuEntry;

//This object does not have an allocator

void DrawMenuEntry(MenuEntry* entry, Graphics* g, bool selected);
void HandleEntryInteract(struct Menu* menu, MenuEntry* entry, float dsliderf);

void DeallocateMenuEntry(MenuEntry* e);
