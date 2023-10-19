#include "bullet.h"
#include "../debugmalloc.h"

#define PI 3.1415926f

Bullet* CreateBullet(Game* game, Arrow* arrow){
    Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
    bullet->Position = arrow->Position;
    bullet->Velocity = vec2_MakeAM(arrow->Angle + RandomFR(-arrow->Weapon->Accuracy, arrow->Weapon->Accuracy), game->BaseWeapon->BulletSpeed); 
    bullet->Type = (BulletType)arrow->Weapon->Type;
    bullet->Owner = arrow;
    return bullet;
}

void UpdateBullet(Bullet* b, Game* game){
    if(b->Type == HEATSEEK){        
        for(int i = 0; i<game->PlayerCount; i++){
            if(b->Owner == &game->Players[i]) continue;
            if(game->Players[i].Health <= 0) continue;
            vec2 VArrow = vec2_AddV(game->Players[i].Position, vec2_NegV(b->Position));
            float dist = vec2_get_Length(&VArrow);

            b->Velocity = vec2_AddV(b->Velocity, vec2_MulfV(VArrow, game->BaseWeapon->BulletSpeed *PI/(dist*dist)));
            b->Velocity = vec2_MulfV(vec2_Normalize(&b->Velocity), game->BaseWeapon->BulletSpeed);
        }
    }
    b->Position = vec2_AddV(b->Position, vec2_MulfV(b->Velocity, game->CDelta));
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
    if(b->Type == HITSCAN){
        float t = 0;
        float ang = fmod(vec2_get_Angle(&b->Velocity), 2*PI);
        if(ang <= PI){
            t = (g->viewport_height - b->Position.y )/ b->Velocity.y;
        }
        if(ang > PI){
            t =  (b->Position.y )/ b->Velocity.y;
        }
        SDL_RenderDrawLine(g->Renderer, b->Owner->Position.x, b->Owner->Position.y, b->Owner->Position.x + (b->Velocity.x*t), b->Owner->Position.y + (b->Velocity.y*t));
    }
    else SDL_RenderDrawLineF(g->Renderer, b->Position.x, b->Position.y, b->Position.x + (b->Velocity.x*delta), b->Position.y + (b->Velocity.y*delta));
}



