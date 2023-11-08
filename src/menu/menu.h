#pragma once
#include <dlfcn.h>

#include "menuentry.h"
#include "../game.h"

#define SLIDER_DEFAULT_INCREMENT 0.05f

struct MenuEntry;

typedef enum MenuState{
    MENU_INVALID = 0,
    MENU_INIT = 1,
    MENU_RUNNING = 2,
    MENU_WAITING = 3,
    MENU_STOPPED = 4,
    MENU_EXITED = 5,
    MENU_UPDATE = 6,
    MENU_FAILED = 7,
    MENU_WASUPDATED = 8,
} MenuState;

typedef struct Menu{
    char* Name;
    void* Handle;

    MenuState State;
    bool WasUpdated;

    int EntryCount;
    struct MenuEntry* Entries;
    int SelectedEntry;
    void* CustomData;

    void (*Init)(struct Menu* menu, void* data, Graphics* graph);
    void (*CustomUpdate)(struct Menu* menu);
    Game (*GetGame)();
} Menu;

void LoadP1ic();

Menu* LoadMenu(const char* path, void* data, Graphics* graph);
void ReloadMenu(Menu* m, Graphics* graph);
void InitBasicMenu(Menu* m, char** texts, int count, Graphics* gr);
void InitSliderMenu(Menu* m, char** texts, int tlen, float* defaults, Graphics* gr);
uint UpdateMenu(uint delta, void* menu);
void UpdateLoop(Menu* m, Graphics* g);
void DrawMenu(Menu* m, Graphics* g);
void DeallocMenu(Menu* m);
