#pragma once

#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>

#include "../math/vector.h"
#include "../gcfg.h"

// Jelenlegi idővel seedeli a random generátort.
void init_Random();

// Random egészt állít elő 0 és RAND_MAX között.
uint Random();

// Random egészt állít elő min és max között.
int RandomR(int min, int max);

// Random float-ot állít elő 0 és 1 között.
float RandomF();

// Random float-ot állít elő min és max között.
float RandomFR(float min, float max);

// Random 2D-s vektort hoz létre úgy, hogy x és y 0 és 1 között legyen.
vec2 RandomVec2();

// Random vektort hoz létre úgy, hogy x és y min és max között van.
vec2 RandomVec2R(float min, float max);

// Vektort hoz létre fix hosszal, véletlenszerű szöggel.
vec2 RandomVec2A(float magnitude);

// Vektort hoz létre fix szöggel, 0 és 1 közötti hosszal.
vec2 RandomVec2M(float angle);

// Vektort hoz létre fix szöggel, l_min és l_max közötti hosszal.
vec2 RandomVec2MR(float angle, float l_min, float l_max);

// Vektort hoz létre random szöggel, l_min és l_max közti hosszal.
vec2 RandomVec2AMR(float l_min, float l_max);

float RandomRange(Range r);

//TODO: Make a custom color struct ranging between 0 and 1

// Random színt ad vissza, alfa = 255.
SDL_Color RandomColor();

// Random szint hoz létre úgy, hogy r, g és b min és max között van, alfa == 255.
SDL_Color RandomColorR(int min, int max);

// Random színt hoz létre úgy, hogy az egyes színelemek a hozzájuk tartozó intervallumokon belül vannak, alfa = 255.
SDL_Color RandomColor3R(int r_min, int r_max, int g_min, int g_max, int b_min, int b_max);

SDL_Color RandomColorC(SDL_Color min, SDL_Color max);

// Random színt hoz létre úgy, hogy az egyes színelemek és alfa a hozzájuk tartozó intervallumokon belül vannak
SDL_Color RandomColor4R(int r_min, int r_max, int g_min, int g_max, int b_min, int b_max, int a_min, int a_max);
