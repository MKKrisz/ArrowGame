#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "debugmalloc.h"
#include "src/menu/menu.h"
#include "src/game.h"
#include "src/graphics/graphics.h"


#define WIDTH 1920
#define HEIGHT 1080
#define SCALE 0.2f

#define PI 3.1415926


// Sets up the game configuration through an interactive menu, then starts the game.
int main(void) {
    init_Random();
    InitText();
    Graphics g = CreateGraphics("fos", WIDTH, HEIGHT, SCALE);
    IMG_Init(IMG_INIT_PNG);

    SDL_SetRenderDrawBlendMode(g.Renderer, SDL_BLENDMODE_BLEND);
    Game game;
    game.State = GAME_INVALID;

    Menu* main = LoadMenu("Menus/libMainMenu.so", &game, &g);
    UpdateLoop(main, &g);
    if(main->GetGame != NULL) game = (*main->GetGame)();
    
    GameLoop(&game, &g);

    DeallocMenu(main);

    DestroyGraphics(&g);
    IMG_Quit();
}
