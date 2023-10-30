#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>


typedef struct GraphicsConfig{
    int Width, Height;
    float Scaling;
    bool Fullscreen;
} gfxcfg;

/* Container for all the graphics related stuff.
 */
typedef struct Graphics {
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    SDL_Texture* Viewport;

    SDL_Texture* Arrow;

    int window_width;
    int window_height;

    float viewport_scale;
    int viewport_width;
    int viewport_height;
} Graphics;

Graphics CreateGraphics(gfxcfg* config);

/* Creates a Graphics object
 * @param const char* wName Name of the window
 * @param int width Width of the window
 * @param int height Height of the window
 * @param float scaliing size scaling for the internal viewport
 * @return a new Graphics object
 */
Graphics CreateGraphicsRaw(const char* wName, int width, int height, float scaling, bool fullscreen);

/* Frees all the heap allocated stuff of a graphics object.*/
void DestroyGraphics(Graphics* g);

/* Creates a new viewport with the new scale.*/
void RescaleViewport(Graphics* g, float scale);

// Not inplementing window resizing, since it is not needed.

/* Sets the current draw target of g to its viewport.*/
void BeginDraw(Graphics* g);

/* Sets the draw target to the window, draws the viewport to the window and presents it. */
void EndDraw(Graphics* g);



