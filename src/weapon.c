#include "../debugmalloc.h"
#include "weapon.h"
#include "arrow.h"
#include "bullet.h"
#include "dataStructures/BulletPasta.h"

Weapon* CreateWeapon(ShotType type, float damage, float speed, float accuracy, float frate, float rrate, int magsize){
    Weapon* op = malloc(sizeof(Weapon));
    if(type == SHOTTYPE_RANDOM){ type = RandomR(0, BULLETTYPE_LENGTH); }
    op->Type = type;
    op->Damage = damage;
    op->BulletSpeed = speed;
    op->Accuracy = accuracy;
    op->FireRate = frate;
    op->ReloadRate = rrate;
    op->MagazineSize = magsize;
    op->Magazine = 0;
    op->FireTimer = 0; 
    op->ReloadTimer = 0;

    return op;
}

Weapon* CopyWeapon(Weapon* base){
    Weapon* op = malloc(sizeof(Weapon));
    op->Type = base->Type;
    op->Damage = base->Damage;
    op->BulletSpeed = base->BulletSpeed;
    op->Accuracy = base->Accuracy;
    op->FireRate = base->FireRate;
    op->ReloadRate = base->ReloadRate;
    op->MagazineSize = base->MagazineSize;
    op->Magazine = base->Magazine;
    op->FireTimer = base->FireTimer;
    op->ReloadTimer = base->ReloadTimer;
    return op;
}

void DeallocWeapon(Weapon* w) { free(w); }

bool IsEmpty(Weapon* w){
    return w->Magazine<=0;
}

bool Fire(Arrow* a, Game* g){
    if(IsEmpty(a->Weapon)) return false;
    if(a->Weapon->FireTimer < 0) return false;

    add_BulletElement_front(g->Bullets, CreateBulletElement(CreateBullet(g, a)));
    a->Weapon->Magazine--;
    a->Velocity = vec2_SubV(a->Velocity, vec2_MulfV(g->Bullets->First->Sauce->Velocity, 0.001f));
    a->Weapon->FireTimer = -a->Weapon->FireRate; 
    return true;
}

void UpdateWeapon(Weapon* w, float delta){
    w->FireTimer += delta;
    w->ReloadTimer += delta;
    if(w->ReloadRate <= 0.01f) {w->Magazine++; return;}
    while(w->ReloadTimer > w->ReloadRate){
        w->ReloadTimer -= w->ReloadRate;
        if(w->Magazine < w->MagazineSize) 
            w->Magazine++;
    }
}
