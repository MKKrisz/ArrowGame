#include "OptionsMenu.h"

Game game;
Graphics* graph;

void Init(Menu* m, void* data, Graphics* gr){
    graph = gr;

    m->State = MENU_INIT;
    m->Name = "Options";

    char* texts[] = {"Options", "Graphics", "Input", "Random Game Settings", "Custom Game Settings", "Back"};
    InitBasicMenu(m, texts, 6, graph);
    m->Entries[1].Button->Interact = GraphicsMenu;
    m->Entries[2].Button->Interact = InputMenu;
    m->Entries[3].Button->Interact = RandomMenu;
    m->Entries[4].Button->Interact = CustomMenu;
    m->Entries[5].Button->Interact = Back;
    m->State = MENU_RUNNING;
}

void GraphicsMenu(Menu* m){
    Menu* gr = LoadMenu("Menus/libGraphicsMenu.so", NULL, graph);
    m->State = MENU_WAITING;
    UpdateLoop(gr, graph);
    m->State = MENU_RUNNING;
    if(gr->State == MENU_EXITED) m->State = MENU_EXITED;
    if(gr->State & MENU_WASUPDATED) m->State = MENU_UPDATE;
    DeallocMenu(gr);

}
void InputMenu(Menu* m){
    Menu* i = LoadMenu("Menus/libIPlayerSelector.so", NULL, graph);
     m->State = MENU_WAITING;
    UpdateLoop(i, graph);
    m->State = MENU_RUNNING;
    if(i->State == MENU_EXITED) m->State = MENU_EXITED;
    if(i->State & MENU_WASUPDATED) m->State = MENU_UPDATE;
    DeallocMenu(i);
}
void RandomMenu(Menu* m){
    Menu* g = LoadMenu("Menus/libGcfgMenu.so", "Config/random.gcfg", graph);
    m->State = MENU_WAITING;
    UpdateLoop(g, graph);
    m->State = MENU_RUNNING;
    if(g->State == MENU_EXITED) m->State = MENU_EXITED;
    if(g->State & MENU_WASUPDATED) m->State = MENU_UPDATE;
    DeallocMenu(g);
}
void CustomMenu(Menu* m){
    Menu* g = LoadMenu("Menus/libGcfgMenu.so", "Config/custom.gcfg", graph);
    m->State = MENU_WAITING;
    UpdateLoop(g, graph);
    m->State = MENU_RUNNING;
    if(g->State == MENU_EXITED) m->State = MENU_EXITED;
    if(g->State & MENU_WASUPDATED) m->State = MENU_UPDATE;
    DeallocMenu(g);
}
void Back(Menu* m){
    m->State = MENU_STOPPED;
}
