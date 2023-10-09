#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "src/game.h"

//DELETE AFTER TESTING
#include "src/graphics/graphics.h"
#include "src/menu/textrenderer.h"


#define WIDTH 1920
#define HEIGHT 1080
#define SCALE 0.2f

#define PI 3.1415926

int main(void) {
    init_Random();
    InitText();
    Graphics g = CreateGraphics("fos", WIDTH, HEIGHT, SCALE);
    IMG_Init(IMG_INIT_PNG);



    SDL_SetRenderDrawBlendMode(g.Renderer, SDL_BLENDMODE_BLEND);

    //PURELY TESTING
    //Text* tesxt = CreateText("The quick brown fox jumped over me", 20);
    //while(true){
    //    BeginDraw(&g);
    //    DrawText(tesxt, &g);
    //    EndDraw(&g);
    //}
    //END OF TEST

    Game game = (Game){
        .PlayerCount = 2,
        .BaseAccel = 300.0f,
        .BaseAngular = PI*4.0f,
        .BaseHealth = 100.0f,
        .BaseFriction = 0.75f,
        .BaseBulletspeed = 300.0f,
        .BaseFirerate = 0.5f,
        .BaseDamage = 5,
    };
    
    GameLoop(&game, &g);

    DestroyGraphics(&g);
    IMG_Quit();
}
