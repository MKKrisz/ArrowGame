#pragma once

#ifdef VENDORED
#include <SDL.h>
#include <SDL_ttf.h>
typedef unsigned int uint;
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif
#include "../graphics/graphics.h"

#define BASE_FONT_SIZE 12
#define BASE_FONT_COLOR (SDL_Color){180, 230, 255, 255}
#define BASE_FONT_COLOR_ELEMENTS 180, 230, 255, 255
#define BASE_FONT_COLOR_RED   180
#define BASE_FONT_COLOR_GREEN 230
#define BASE_FONT_COLOR_BLUE  255

void InitText();

typedef struct Text{
    SDL_Texture* RenderedTexture;
    char* Text;
    TTF_Font* Font;
    int FontSize;
    SDL_Color Color;
    SDL_Rect DrawRect;
} Text;

Text* CreateText(char* text, int size, Graphics* g);
void SetTextPos(Text* text, int x, int y);
void SetTextColor(Text* text, SDL_Color c);
void SetTextString(Text* text, const char* str, Graphics* g);
void DrawText(Text* text, Graphics* g);
void DestroyText(Text* text);


