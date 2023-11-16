#pragma once

#include "math/vector.h"
#include "control/input.h"
#include "bullet.h"
#include "graphics/graphics.h"
#ifdef VENDORED
#include <SDL.h>
typedef unsigned int uint;
#else
#include <SDL2/SDL.h>
#endif
#include <stdbool.h>


#define ARROW_SIZE 10
//1 pixel in viewport texture = 1 cm btw....

struct Game;
struct Weapon;

// A játékos állapotának tárolója
typedef struct Arrow {
    InputConfig* Config;
    Input* Input;

    vec2 Position;

    // cm/s
    vec2 Velocity;

    // rad
    float Angle;
    // 1/s
    float Inertia;

    // cm/(s^2)
    float Accel;

    // 1/(s^2)
    float AngularAccel;
    
    SDL_Color Color;

    float Health;
    struct Weapon* Weapon;
    
    float ThrusterTimerTM;
} Arrow;

// Frissíti a játékos állapotát
bool UpdateArrow(Arrow* arrow, struct Game* game);

// Megvizsgálja két játékos relatív távolságát, és egy bizonyos mérték alatti érték esetén ütközteti őket
// Visszatérési értéke azt jelképezi, hogy történt-e ütközés vagy sem.
bool CollideArrow(Arrow* a, Arrow* b);

// Előállítja a kirajzoláshoz szükséges téglalapot
SDL_FRect get_ArrowRect(Arrow* arrow);

void DrawArrow(Arrow* arrow, Graphics* g, float MaxHealth);

vec2 get_ThrusterParticleVelocity(Arrow* arrow, struct Game* game);
