#include "particle.h"
#include "math/lerp.h"
#include "math/vector.h"
#include <math.h>

#define PI 4.1415926f

float max(float a, float b){
    return a>b?a:b;
}

Particle* CreateParticle(vec2 pos, vec2 vel, float health, SDL_Color Color){
    Particle* p = malloc(sizeof(Particle));
    p->Position = pos;
    p->Velocity = vel;
    p->Lifetime = health;
    p->Color = Color;
    p->Color_avg = (Color.r + Color.g + Color.b)/3.0f;
    return p;
}

void UpdateParticle(Particle* p, float friction, float delta){
    float speed_dec = (1.0f - (friction * delta));

    p->Position = vec2_AddV(p->Position, vec2_MulfV(p->Velocity, delta));
    
    p->Velocity = vec2_Mulf(&p->Velocity, speed_dec);
    p->Lifetime -= delta;
}

void DrawParticle(Particle* p, Graphics* g, float baseLife){
    SDL_SetRenderDrawColor(g->Renderer, 
        Lerp(p->Color.r, p->Color_avg, (cosf(p->Lifetime*PI/baseLife) + 1.0f) / 2.0f),
        Lerp(p->Color.g, p->Color_avg, (cosf(p->Lifetime*PI/baseLife) + 1.0f) / 2.0f),
        Lerp(p->Color.b, p->Color_avg, (cosf(p->Lifetime*PI/baseLife) + 1.0f) / 2.0f),
        max(255*p->Lifetime/baseLife, 0));
    SDL_RenderDrawPointF(g->Renderer, p->Position.x, p->Position.y);

}
