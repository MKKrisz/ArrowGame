#pragma once

#include "math/vector.h"
#include "graphics/graphics.h"
#include <SDL2/SDL.h>

// Particle = a színes egypixeles bizbaszok a képernyőn
typedef struct Praticle {
    vec2 Position;
    vec2 Velocity;
    float Lifetime;
    SDL_Color Color;
    float Color_avg;
} Particle;

// 1 azaz 1db particle-t allokál a HEAPEN (mert a Particle spagettihez az kell)
Particle* CreateParticle(vec2 pos, vec2 vel, float health, SDL_Color Color);

// Frissíti egy particle értékeit
void UpdateParticle(Particle* p, float friction, float delta);

// Kirajzol egy Particle-t
//TODO: Olyan rajzoló metódus, ami nem fade-elteti szürkébe a particle-t.
void DrawParticle(Particle* p, Graphics* g, float baseLife);
