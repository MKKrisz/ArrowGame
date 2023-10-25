#pragma once
#include <dlfcn.h>

#include "menuentry.h"
#include "../game.h"

#define SLIDER_DEFAULT_INCREMENT 0.05f

struct MenuEntry;

typedef struct Menu{
    char* Name;
    void* Handle;

    bool Running;

    int EntryCount;
    struct MenuEntry* Entries;
    int SelectedEntry;

    void (*CustomUpdate)(struct Menu* menu);
    Game (*GetGame)();
} Menu;

Menu* LoadMenu(const char* path, Game* g, Graphics* graph);
void UpdateMenu(Menu* m, float delta);
void UpdateLoop(Menu* m, Graphics* g);
void DrawMenu(Menu* m, Graphics* g);
void DeallocMenu(Menu* m);
