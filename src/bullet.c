#include "bullet.h"

Bullet* CreateBullet(Game* game, Arrow* arrow, BulletType type){
    Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
    bullet->Position = arrow->Position;
    bullet->Velocity = vec2_MakeAM(arrow->Angle, game->BaseBulletspeed);
    bullet->Type = type;
    bullet->Owner = arrow;
    return bullet;
}

void UpdateBullet(Bullet* b, Game* game){
    switch(b->Type){
        case PROJECTILE:
            b->Position = vec2_AddV(b->Position, vec2_MulfV(b->Velocity, game->CDelta));
            break;

        case HITSCAN:
            break;
        case HEATSEEK:
            for(int i = 0; i<game->PlayerCount; i++){
                vec2 VArrow = vec2_AddV(game->Players[i].Position, vec2_NegV(b->Position));
                float dist = vec2_get_Length(&VArrow);

                b->Velocity = vec2_AddV(b->Velocity, vec2_MulfV(vec2_Normalize(&VArrow), game->BaseBulletspeed/dist));
            }
            b->Position = vec2_AddV(b->Position, vec2_MulfV(b->Velocity, game->CDelta));
            break;
    }
}


#define MISS (vec2){0.0f/0.0f, 0.0f/0.0f};
#define HIT(t) HIT_BASE(t)
#define HIT_BASE(t) (vec2){bullet->Position.x + (t * dir.x), bullet->Position.y + (t * dir.y)} 
vec2 GetHitVec(Arrow* arrow, Bullet* bullet, float delta){
    if(bullet == NULL) return MISS;
    if(arrow == bullet->Owner)return MISS;

    vec2 origin = vec2_AddV(bullet->Position, vec2_NegV(arrow->Position));
    
    vec2 dir = vec2_Normalize(&bullet->Velocity);
    float a = vec2_DotV(dir, dir);
    float b = 2 * vec2_DotV(dir, origin);
    float c = vec2_DotV(origin, origin) - (ARROW_SIZE * ARROW_SIZE)/4.0f;

    float d = b*b - 4*a*c;
    if(d<0) return MISS;

    float t1 = (-b - sqrt(d)) / (2*a);
    if(bullet->Type == HITSCAN) return HIT(t1);
    else if(t1 < delta) return HIT(t1);
    return MISS;
}

#undef HIT
#undef HIT_BASE
#undef MISS

bool CheckHit(vec2 HitVec){
    if(isnan(HitVec.x) && isnan(HitVec.y)) return false;
    return true;
}

bool CheckBounds(Bullet* bullet, Graphics* g){
    return bullet->Position.x < 0 || bullet->Position.x >= (float)g->viewport_width || bullet->Position.y < 0 || bullet->Position.y >= (float)g->viewport_height;
}


void DrawBullet(Bullet* b, Graphics* g, float delta){
    SDL_SetRenderDrawColor(g->Renderer, BULLET_COLOR);
    SDL_RenderDrawLineF(g->Renderer, b->Position.x, b->Position.y, b->Position.x + (b->Velocity.x*delta), b->Position.y + (b->Velocity.y*delta));
}



