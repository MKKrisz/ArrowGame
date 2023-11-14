#include "WinMenu.h"
#include "../src/dataStructures/BulletPasta.h"
#include "../src/arrow.h"
#include "../debugmalloc.h"

Graphics* gr;
Game* game;

void Init(Menu* m, void* data, Graphics* graph){
    gr = graph;
    game = (Game*)data;
    
    int winner = -1;
    for(int i = 0; i < game->PlayerCount; i++){
        if(game->Players[i].Health > 0){
            winner = i+1;
            break;
        }
    }

    char* texts[] = {"PLACEHOLDER         ", "New Game", "Quit to Menu", "Quit to Desktop"};
    texts[0] = malloc(20 * sizeof(char));
    if(winner >= 0) sprintf(texts[0], "Player %d Wins!!", winner);
    else sprintf(texts[0], "Nobody Wins!!");
    InitBasicMenu(m, texts, 4, gr);
    free(texts[0]);
    
    m->Entries[1].Button->Interact = NewGame;
    m->Entries[2].Button->Interact = QTM;
    m->Entries[3].Button->Interact = QTD;

    m->State = MENU_RUNNING;
}

void Update(Menu* m){
    UpdateParticles(game);
    UpdateBullets(game, gr);

    for(int i = 0; i<game->PlayerCount; i++){
        Arrow* p1 = &game->Players[i];
        if(game->Players[i].Health <= 0) continue;
        //UpdateArrow(p1, game);
        BounceEdge(p1, gr);
    }
}

void Draw(Menu* m, Graphics* g){
    DrawParticles(game->Particles->First, g);
    DrawBullets(game->Bullets->First, g, game->CDelta);
    for(int i = 0; i<game->PlayerCount; i++){
        Arrow* p1 = &game->Players[i];
        DrawArrow(p1, g, game->BaseHealth);
    }
}

void NewGame(Menu* m){
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

