#include "PauseMenu.h"
#include "../src/dataStructures/BulletPasta.h"
#include "../debugmalloc.h"

Graphics* gr;
Game* game;

void Init(Menu* m, void* data, Graphics* graph){
    gr = graph;
    game = (Game*)data;

    char* texts[] = {"Paused", "Continue", "Restart", "Quit to Menu", "Quit to Desktop"};
    InitBasicMenu(m, texts, 5, gr);

    m->Entries[1].Button->Interact = Continue;
    m->Entries[2].Button->Interact = Restart;
    m->Entries[3].Button->Interact = QTM;
    m->Entries[4].Button->Interact = QTD;

    m->State = MENU_RUNNING;
}

void Draw(Menu* m, Graphics* g){
    DrawParticles(game->Particles->First, g);
    DrawBullets(game->Bullets->First, g, game->CDelta);
    for(int i = 0; i<game->PlayerCount; i++){
        Arrow* p1 = &game->Players[i];
        DrawArrow(p1, g, game->BaseHealth);
    }
}

void Continue(Menu* m){
    game->State = GAME_RUNNING;
    m->State = MENU_STOPPED;
}

void Restart(Menu* m){
    game->State = GAME_RESET;
    m->State = MENU_STOPPED;
}

void QTM(Menu* m){
    game->State = GAME_STOPPED;
    m->State = MENU_STOPPED;
}
void QTD(Menu* m){
    game->State = GAME_EXITED;
    m->State = MENU_STOPPED;
}
