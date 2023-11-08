#include "random.h"
#include "../../debugmalloc.h"

void init_Random(){
    srand(time(NULL));
}

uint Random(){
    return rand();
}

int RandomR(int min, int max){
    return Random() % (max - min) + min;
}

float RandomF(){
    return rand() / (float)RAND_MAX;
}

float RandomFR(float min, float max){
    return RandomF() * (max-min) + min;
}

float RandomRange(Range r){
    if(r.type == SINGLE) return r.min;
    return RandomFR(r.min, r.max);
}


#define PI 3.1415926

vec2 RandomVec2(){
    return (vec2){ RandomF(), RandomF() };
}
vec2 RandomVec2R(float min, float max){
    return (vec2){ RandomFR(min, max), RandomFR(min, max)};
}
vec2 RandomVec2A(float magnitude){
    return vec2_MakeAM(RandomF()*PI*2, magnitude);
}
vec2 RandomVec2M(float angle){
    return vec2_MakeAM(angle, RandomF());
}
vec2 RandomVec2MR(float angle, float l_min, float l_max){
    return vec2_MakeAM(angle, RandomFR(l_min, l_max)); 
}
vec2 RandomVec2AMR(float l_min, float l_max){
    return vec2_MakeAM(RandomF()*PI*2, RandomFR(l_min, l_max));
}

SDL_Color RandomColor(){
    return (SDL_Color){RandomR(0, 256), RandomR(0, 256), RandomR(0, 256), 255};
}

SDL_Color RandomColorR(int min, int max){
    return (SDL_Color){RandomR(min, max), RandomR(min, max), RandomR(min, max), 255};
}

SDL_Color RandomColor3R(int r_min, int r_max, int g_min, int g_max, int b_min, int b_max){
    return (SDL_Color){RandomR(r_min, r_max), RandomR(g_min, g_max), RandomR(b_min, b_max), 255};
}

SDL_Color RandomColorC(SDL_Color min, SDL_Color max){
    return (SDL_Color){RandomR(min.r, max.r), RandomR(min.g, max.g), RandomR(min.b, max.b), RandomR(min.a, max.a)};
}

SDL_Color RandomColor4R(int r_min, int r_max, int g_min, int g_max, int b_min, int b_max, int a_min, int a_max){
    return (SDL_Color){RandomR(r_min, r_max), RandomR(g_min, g_max), RandomR(b_min, b_max), RandomR(a_min, a_max)};
}

