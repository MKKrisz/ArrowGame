#pragma once

#include <SDL2/SDL.h>

typedef struct Color{
    union{float r; float L;};
    union{float g; float a;};
    float b;
    float alpha;
} Color;

typedef Color OKLab;
typedef Color sRGB;

sRGB CreateColor(float r, float g, float b, float a);

sRGB FromSDL_Color(SDL_Color c);

SDL_Color ToSDL_Color(sRGB c);

OKLab ToOKLab(sRGB c);

sRGB TosRGB(OKLab c);

OKLab* GenerateMonochromePalette(int count);

SDL_Color* GeneratePaletteM(int count);
