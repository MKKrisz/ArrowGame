#include "graphics.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include <SDL2/SDL_image.h>
#include "../../debugmalloc.h"

#define PrintError(x) if(x != 0){ \
    printf("%s at %s:%d\n", SDL_GetError(), __FILE__, __LINE__); \
}
#define PrintErrorPointer(x) if(x == NULL){ \
    printf("%s at %s:%d\n", SDL_GetError(), __FILE__, __LINE__); \
}
#define PrintErrorImg(x) if(x == NULL){ \
    printf("%s at %s:%d\n", IMG_GetError(), __FILE__, __LINE__); \
}




/* File Format: WIDTH HEIGHT SCALING FULLSCREEN
 * I differ from the original spec here, as instead of storing a single bool in the file for
 * fullscreen, I store the SDL_WindowFlags value
 */
gfxcfg gfx_Load(char* path){
    FILE* f = fopen(path, "r");
    gfxcfg ret = gfx_Default();
    if(f == NULL) {
        gfx_Save(&ret, path);
        return ret;
    }
    fscanf(f, "%d %d %f %u", &ret.Width, &ret.Height, &ret.Scaling, &ret.Fullscreen);
    fclose(f);
    return ret;
}

void gfx_Save(gfxcfg* config, char* path){
    FILE* f = fopen(path, "w+");
    fprintf(f, "%d %d %f %u", config->Width, config->Height, config->Scaling, config->Fullscreen);
    fclose(f);
}

gfxcfg gfx_Default(){
    SDL_DisplayMode current;
    PrintError(SDL_GetCurrentDisplayMode(0, &current));
    return (gfxcfg){current.w, current.h, BASE_SCALING, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN};
}

void Init_Gfx(){
    PrintError(SDL_Init(SDL_INIT_EVERYTHING));
}


Graphics CreateGraphics(gfxcfg config){
    return CreateGraphicsRaw("ArrowGame", config.Width, config.Height, config.Scaling, config.Fullscreen);
}

Graphics CreateGraphicsRaw(const char* wName, int width, int height, float scaling, uint flags){
    Graphics g;
    g.Window = SDL_CreateWindow(wName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);
    PrintErrorPointer(g.Window);
    if(flags & SDL_WINDOW_FULLSCREEN){
        SDL_DisplayMode dm;
        PrintError(SDL_GetCurrentDisplayMode(0, &dm));
        dm.w = width; dm.h = height;
        PrintError(SDL_SetWindowDisplayMode(g.Window, &dm));
    }
    g.Renderer = SDL_CreateRenderer(g.Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
    PrintErrorPointer(g.Renderer);

    g.Arrow = IMG_LoadTexture(g.Renderer, "Assets/Arrow.png");
    PrintErrorImg(g.Arrow);

    g.window_width = width;
    g.window_height = height;

    g.viewport_scale = scaling;
    g.viewport_width = (int)(width * scaling);
    g.viewport_height = (int)(height * scaling);
    g.Viewport = SDL_CreateTexture(g.Renderer, SDL_PIXELFORMAT_ARGB32, SDL_TEXTUREACCESS_TARGET, g.viewport_width, g.viewport_height);
    PrintErrorPointer(g.Viewport);
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
    PrintErrorPointer(g->Viewport);
}

void BeginDraw(Graphics* g){
    PrintError(SDL_SetRenderTarget(g->Renderer, g->Viewport));
    PrintError(SDL_SetRenderDrawColor(g->Renderer, 0, 0, 0, 0));
    PrintError(SDL_RenderClear(g->Renderer));
}

void EndDraw(Graphics* g){
    PrintError(SDL_SetRenderTarget(g->Renderer, NULL));
    PrintError(SDL_RenderCopyEx(g->Renderer, g->Viewport, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL));
    SDL_RenderPresent(g->Renderer);
}
