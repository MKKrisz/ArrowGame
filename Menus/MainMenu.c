#include "MainMenu.h"
#include "../debugmalloc.h"
#include "../src/gcfg.h"

#define PI 3.1415926

Game game;
Graphics* graph;

void Init(Menu* m, void* data, Graphics* gr){
    if(data != NULL) game = *(Game*)data;
    game.State = GAME_INVALID;
    graph = gr;

    m->State = MENU_INIT;

    m->Name = "MainMenu";
    char* texts[] = {"ArrowGame", "Random Game", "Custom Game", "Options", "Quit"};
    InitBasicMenu(m, texts, 5, gr);
    m->Entries[1].Button->Interact = StartRandomGame;
    m->Entries[2].Button->Interact = StartCustomGame;
    m->Entries[3].Button->Interact = SetOptions;
    m->Entries[4].Button->Interact = Quit;

    m->State = MENU_RUNNING;
}

void Update(Menu* m){}

//TODO: Load edge values from file
void StartRandomGame(Menu* menu){
    Gcfg g = gcfg_Load("Config/random.gcfg");
    //printf("%d", (int)g.Values[GCFG_WEAPON_TYPE].min);
    game = (Game){
        .State = GAME_SET,
        .PlayerCount = (int)g.Values[GCFG_PLAYERCOUNT].min,
        .BaseAccel = RandomRange(g.Values[GCFG_ACCEL]),
        .BaseAngular = RandomRange(g.Values[GCFG_ANGULAR]),
        .BaseHealth = RandomRange(g.Values[GCFG_HP]),
        .BaseFriction = RandomRange(g.Values[GCFG_FRICTION]),
        .BaseWeapon = CreateWeapon(
                (int)g.Values[GCFG_WEAPON_TYPE].min == BULLETTYPE_LENGTH? RandomR(0, 3) : (int)g.Values[GCFG_WEAPON_TYPE].min,
                RandomRange(g.Values[GCFG_WEAPON_DMG]),
                RandomRange(g.Values[GCFG_WEAPON_SPD]),
                RandomRange(g.Values[GCFG_WEAPON_ACC]),
                RandomRange(g.Values[GCFG_WEAPON_FRATE]),
                RandomRange(g.Values[GCFG_WEAPON_MAGSIZE])
                )
    };
    printf("%u", game.BaseWeapon->Type);
    menu->State = MENU_STOPPED;
}

void StartCustomGame(Menu* menu){
    return;
    //TODO: Implement GameConfig.so
    Menu* cfg = LoadMenu("Menus/GameConfig.so", NULL, graph);
    UpdateLoop(cfg, graph);
    game = cfg->GetGame();
    DeallocMenu(cfg);
    if(game.PlayerCount > 0) menu->State = false;
}

void SetOptions(Menu* menu){
    Menu* opts = LoadMenu("Menus/libOptionsMenu.so", NULL, graph);
    //Graphics g = *graph;
    menu->State = MENU_WAITING;
    UpdateLoop(opts, graph);
    menu->State = MENU_RUNNING;
    if(opts->State == MENU_EXITED) menu->State = MENU_EXITED;
    if(opts->State & MENU_WASUPDATED) menu->State = MENU_UPDATE;
    DeallocMenu(opts);
}

void Quit(Menu* menu){
    game.State = GAME_INVALID;
    menu->State = false;
}

Game Return(){
    return game;
}
