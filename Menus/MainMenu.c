#include "MainMenu.h"
#include "../debugmalloc.h"
#include "../src/menu/textrenderer.h"
//#include "../src/control/random.h"

#define PI 3.1415926

Game game;
Graphics* graph;

void Init(Menu* m, Game* g, Graphics* gr){
    if(g != NULL) game = *g;
    game.State = GAME_INVALID;
    graph = gr;

    m->Name = "MainMenu";

    m->EntryCount = 5;
    m->SelectedEntry = 1;
    m->Entries = malloc(sizeof(MenuEntry) * m->EntryCount);

    m->Entries[0].Type = MENU_TEXTBOX;
    m->Entries[0].Textbox = CreateTextbox(CreateText("ArrowGame", 22, gr));
    SetTextPos(m->Entries[0].Button->Text, 1, gr->viewport_height - m->Entries[0].Textbox->Text->DrawRect.h - 1);
    m->Entries[0].Backdrop = (SDL_Rect){0,
                                        gr->viewport_height - m->Entries[0].Textbox->Text->DrawRect.h - 2,
                                        gr->viewport_width,
                                        m->Entries[0].Textbox->Text->DrawRect.h + 2};

    m->Entries[1].Type = MENU_BUTTON;
    m->Entries[1].Button = CreateButton(CreateText("Random Game", 15, gr), StartRandomGame);
    SetTextPos(m->Entries[1].Button->Text, 1, m->Entries[0].Backdrop.y - m->Entries[1].Button->Text->DrawRect.h - 2);
    m->Entries[1].Backdrop = (SDL_Rect){0,
                                        m->Entries[0].Backdrop.y - m->Entries[1].Button->Text->DrawRect.h - 2, 
                                        gr->viewport_width,
                                        m->Entries[1].Button->Text->DrawRect.h + 2};
    
    m->Entries[2].Type = MENU_BUTTON;
    m->Entries[2].Button = CreateButton(CreateText("Custom Game", 15, gr), StartCustomGame);
    SetTextPos(m->Entries[2].Button->Text, 1, m->Entries[1].Backdrop.y - m->Entries[2].Button->Text->DrawRect.h - 2);
    m->Entries[2].Backdrop = (SDL_Rect){0,
                                        m->Entries[1].Backdrop.y - m->Entries[2].Button->Text->DrawRect.h - 2,
                                        gr->viewport_width,
                                        m->Entries[2].Button->Text->DrawRect.h + 2};

    m->Entries[3].Type = MENU_BUTTON;
    m->Entries[3].Button = CreateButton(CreateText("Options", 15, gr), SetOptions);
    SetTextPos(m->Entries[3].Button->Text, 1, m->Entries[2].Backdrop.y - m->Entries[3].Button->Text->DrawRect.h - 2);
    m->Entries[3].Backdrop = (SDL_Rect){0,
                                        m->Entries[2].Backdrop.y - m->Entries[3].Button->Text->DrawRect.h - 2,
                                        gr->viewport_width,
                                        m->Entries[3].Button->Text->DrawRect.h + 2};

    m->Entries[4].Type = MENU_BUTTON;
    m->Entries[4].Button = CreateButton(CreateText("Quit", 15, gr), Quit);
    SetTextPos(m->Entries[4].Button->Text, 1, m->Entries[3].Backdrop.y - m->Entries[4].Button->Text->DrawRect.h - 2);
    m->Entries[4].Backdrop = (SDL_Rect){0,
                                        m->Entries[3].Backdrop.y - m->Entries[4].Button->Text->DrawRect.h - 2,
                                        gr->viewport_width,
                                        m->Entries[3].Button->Text->DrawRect.h + 2};
}

void Update(Menu* m){}
//Game Return();

void StartRandomGame(Menu* menu){
    game = (Game){
        .State = GAME_SET,
        .PlayerCount = 2,
        .BaseAccel = RandomFR(100, 500),
        .BaseAngular = RandomFR(PI*3.0f, PI*6.0f),
        .BaseHealth = RandomFR(50, 200),
        .BaseFriction = RandomFR(0.5f, 1.3f),
        .BaseWeapon = CreateWeapon(
                (ShotType)RandomR(0, 3),
                RandomFR(1, 70),
                RandomFR(20, 1000),
                RandomFR(0, 0.2f),
                RandomFR(0, 5),
                RandomR(1, 50)
                )
    };
    menu->Running = false;
}

void StartCustomGame(Menu* menu){
    return;
    //TODO: Implement GameConfig.so
    Menu* cfg = LoadMenu("Menus/GameConfig.so", NULL, graph);
    while(cfg->Running){
        UpdateMenu(cfg, 0.1);
    }
    game = cfg->GetGame();
    DeallocMenu(cfg);
    if(game.PlayerCount > 0) menu->Running = false;
}

void SetOptions(Menu* menu){
    return;     // No thanks, I'm not implementing that yet
}

void Quit(Menu* menu){
    menu->Running = false;
}

Game Return(){
    return game;
}
