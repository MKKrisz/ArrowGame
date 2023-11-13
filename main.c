#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "debugmalloc.h"
#include "src/menu/menu.h"
#include "src/game.h"
#include "src/graphics/graphics.h"

#define PI 3.1415926


// Sets up the game configuration through an interactive menu, then starts the game.
int main(void) {
    init_Random();
    Init_Gfx();
    InitText();
    Graphics g = CreateGraphics(gfx_Load("Config/graphics.cfg"));
    IMG_Init(IMG_INIT_PNG);

    SDL_SetRenderDrawBlendMode(g.Renderer, SDL_BLENDMODE_BLEND);
    Game game;
    game.State = GAME_SET;

    while(game.State != GAME_EXITED && game.State != GAME_INVALID){
        LoadP1ic();
        Menu* main = LoadMenu("Menus/libMainMenu.so", &game, &g);
        UpdateLoop(main, &g);
        if(main->GetGame != NULL) game = (*main->GetGame)(); 
        FreeP1ic();
        DeallocMenu(main);
        GameLoop(&game, &g);
    }
    DestroyGraphics(&g);
    IMG_Quit();
}
