#pragma once

#ifdef VENDORED
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <stdbool.h>

#define BASE_SCALING 0.2


typedef struct GraphicsConfig{
    int Width, Height;
    float Scaling;
    uint Fullscreen;
} gfxcfg;

gfxcfg gfx_Load(char* path);
void gfx_Save(gfxcfg* config, char* path);
gfxcfg gfx_Default();

/* Container for all the graphics related stuff.
 */
typedef struct Graphics {
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Texture* Viewport;
    //This might be needed as SDL does not save the pointer to the actual Viewport texture, but to the native one.
    SDL_Texture* cViewport;

    SDL_Texture* Arrow;

    int window_width;
    int window_height;

    float viewport_scale;
    int viewport_width;
    int viewport_height;
} Graphics;

void Init_Gfx();

Graphics CreateGraphics(gfxcfg config);

/* Creates a Graphics object
 * @param const char* wName Name of the window
 * @param int width Width of the window
 * @param int height Height of the window
 * @param float scaliing size scaling for the internal viewport
 * @return a new Graphics object
 */
Graphics CreateGraphicsRaw(const char* wName, int width, int height, float scaling, uint flags);

/* Frees all the heap allocated stuff of a graphics object.*/
void DestroyGraphics(Graphics* g);

/* Creates a new viewport with the new scale.*/
void RescaleViewport(Graphics* g, float scale);

void ResizeWindow(Graphics* g, int w, int h);

void SetFullscreen(Graphics* g, bool state);

/* Sets the current draw target of g to its viewport.*/
void BeginDraw(Graphics* g);

/* Sets the draw target to the window, draws the viewport to the window and presents it. */
void EndDraw(Graphics* g);



