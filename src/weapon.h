#pragma once

#include "game.h"

struct Game;
struct Arrow; 

typedef enum ShotType {
    SHOTTYPE_RANDOM = 4,
} ShotType;

typedef struct Weapon{
    ShotType Type;
    float Damage;
    float BulletSpeed;
    float Accuracy;
    float FireRate;
    int MagazineSize;

    int Magazine;
    float FireTimer;
} Weapon;

Weapon* CreateWeapon(ShotType type, float damage, float speed, float accuracy, float frate, int magsize);
void DeallocWeapon(Weapon* w);

bool IsEmpty(Weapon* w);

bool Fire(struct Arrow* w, struct Game* g);

void UpdateWeapon(Weapon* w, float delta);
