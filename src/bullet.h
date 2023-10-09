#pragma once

#include "math/vector.h"
#include "game.h"
#include "graphics/graphics.h"

#define BULLET_COLOR 255, 0, 0, 255

struct Game;
struct Arrow;

typedef enum BulletType {
    PROJECTILE = 0,
    HITSCAN = 1,
    HEATSEEK = 2,
} BulletType;

typedef struct Bullet {
    vec2 Position;
    vec2 Velocity;
    BulletType Type;
    struct Arrow* Owner;
} Bullet;


Bullet* CreateBullet(struct Game* game, struct Arrow* arrow, BulletType type);

void UpdateBullet(Bullet* b, struct Game* game);


vec2 GetHitVec(struct Arrow* arrow, Bullet* bullet, float delta);
bool CheckHit(vec2 HitVec);
bool CheckBounds(Bullet* bullet, Graphics* g);

void DrawBullet(Bullet* b, Graphics* g, float delta);




