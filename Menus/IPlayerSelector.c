#include "../debugmalloc.h"
#include "IPlayerSelector.h"

Graphics* gr;
Game* game;

void Init(Menu* m, void* data, Graphics* graph){
    gr = graph;
    game = (Game*)data;

    m->State = MENU_INIT;

    m->Name = "PlayerSelector_Input";

    char* texts[6] = {"Select player", "Player    1", "Player    2", "Player    3", "Player    4", "Back"};
    InitBasicMenu(m, texts, 6, gr);

    m->Entries[1].Button->Interact = p1;
    m->Entries[2].Button->Interact = p2;
    m->Entries[3].Button->Interact = p3;
    m->Entries[4].Button->Interact = p4;
    m->Entries[5].Button->Interact = Back;
    
    m->State = MENU_RUNNING;
}

void LoadInputMenu(Menu* m, int playerno){
    Menu* imenu = LoadMenu("Menus/libInputMenu.so", &playerno, gr);
    UpdateLoop(imenu, gr);
    (*imenu->GetGame)();
    if(imenu->State == MENU_EXITED) m->State = MENU_EXITED;
    else if(imenu->State & MENU_WASUPDATED) m->State = MENU_UPDATE;
    DeallocMenu(imenu);
}

void p1(Menu* m){LoadInputMenu(m, 1);}
void p2(Menu* m){LoadInputMenu(m, 2);}
void p3(Menu* m){LoadInputMenu(m, 3);}
void p4(Menu* m){LoadInputMenu(m, 4);}

void Back(Menu* m){
    m->State = MENU_STOPPED;
}
