#include "graphics.h"
#include <SDL2/SDL.h>

Graphics CreateGraphics(const char* wName, int width, int height, float scaling){
    SDL_Init(SDL_INIT_EVERYTHING);
    Graphics g;
    g.Window = SDL_CreateWindow(wName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    g.Renderer = SDL_CreateRenderer(g.Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
    g.window_width = width;
    g.window_height = height;

    g.viewport_scale = scaling;
    g.viewport_width = (int)(width * scaling);
    g.viewport_height = (int)(height * scaling);
    g.Viewport = SDL_CreateTexture(g.Renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET, g.viewport_width, g.viewport_height);
    return g;
}

void DestroyGraphics(Graphics* g){
    // Since SDL apparently destroys all textures created with a renderer, this won't be needed
    // SDL_DestroyTexture(g->Viewport);
    SDL_DestroyRenderer(g->Renderer);
    SDL_DestroyWindow(g->Window);
    SDL_Quit();
}

void RescaleViewport(Graphics* g, float scale){
    g->viewport_scale = scale;
    g->viewport_width = (int)(g->window_width / scale);
    g->viewport_height = (int)(g->window_height / scale);

    SDL_DestroyTexture(g->Viewport);
    g->Viewport = SDL_CreateTexture(g->Renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_STREAMING, g->viewport_width, g->viewport_height);
}

void BeginDraw(Graphics* g){
    SDL_SetRenderTarget(g->Renderer, g->Viewport);
}

void EndDraw(Graphics* g){
    SDL_SetRenderTarget(g->Renderer, NULL);
    SDL_RenderCopyEx(g->Renderer, g->Viewport, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(g->Renderer);
}
