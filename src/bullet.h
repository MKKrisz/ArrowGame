#pragma once

#include "math/vector.h"
#include "game.h"
#include "graphics/graphics.h"

#define BULLET_COLOR Lerp(255, 0, b->Lifetime/(1000*vec2_get_Length(&b->Velocity))), 0, 0, 255

struct Game;
struct Arrow;
struct Weapon;

typedef enum BulletType {
    PROJECTILE = 0,
    HITSCAN = 1,
    HEATSEEK = 2,
    BULLETTYPE_LENGTH = 3
} BulletType;

typedef struct Bullet {
    vec2 Position;
    vec2 Velocity;
    float Damage;
    float Lifetime;
    BulletType Type;
    struct Arrow* Owner;
} Bullet;


Bullet* CreateBullet(struct Game* game, struct Arrow* arrow);

void UpdateBullet(Bullet* b, struct Game* game);


vec2 GetHitVec(struct Arrow* arrow, Bullet* bullet, float delta);
bool CheckHit(vec2 HitVec);
bool CheckBounds(Bullet* bullet, Graphics* g);

void DrawBullet(Bullet* b, Graphics* g, float delta);




