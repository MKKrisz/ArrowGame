#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "src/game.h"

//DELETE AFTER TESTING
#include "src/graphics/graphics.h"


#define WIDTH 1920
#define HEIGHT 1080
#define SCALE 0.2f

#define PI 3.1415926


// Sets up the game configuration through an interactive menu, then starts the game.
int main(void) {
    init_Random();
    Graphics g = CreateGraphics("fos", WIDTH, HEIGHT, SCALE);
    IMG_Init(IMG_INIT_PNG);



    SDL_SetRenderDrawBlendMode(g.Renderer, SDL_BLENDMODE_BLEND);

    float damage = RandomFR(1, 20);

    Game game = (Game){
        .PlayerCount = 2,
        .BaseAccel = 300.0f,
        .BaseAngular = PI*4.0f,
        .BaseHealth = 100.0f,
        .BaseFriction = 0.75f,
        .BaseWeapon = CreateWeapon(
            (ShotType)HEATSEEK,
            damage,
            500.0f,
            0.05f,
            0.4f,
            20
            )
        };

    
    GameLoop(&game, &g);

    DestroyGraphics(&g);
    IMG_Quit();
}
