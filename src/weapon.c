#include "weapon.h"
#include "arrow.h"
#include "bullet.h"
#include "dataStructures/BulletPasta.h"

Weapon* CreateWeapon(ShotType type, float damage, float speed, float accuracy, float frate, int magsize){
    Weapon* op = malloc(sizeof(Weapon));
    if(type == SHOTTYPE_RANDOM){ type = RandomR(0, BULLETTYPE_LENGTH); }
    op->Type = type;
    op->Damage = damage;
    op->BulletSpeed = speed;
    op->Accuracy = accuracy;
    op->FireRate = frate;
    op->MagazineSize = magsize;

    return op;
}
void DeallocWeapon(Weapon* w) { free(w); }

bool IsEmpty(Weapon* w){
    return w->Magazine<=0;
}

bool Fire(Arrow* a, Game* g){
    if(IsEmpty(a->Weapon)) return false;

    add_BulletElement_front(g->Bullets, CreateBulletElement(CreateBullet(g, a)));
    a->Weapon->Magazine--;
    return true;
}

void UpdateWeapon(Weapon* w, float delta){
    w->FireTimer += delta;
    while(w->FireTimer > w->FireRate){
        w->FireTimer -= w->FireRate;
        if(w->Magazine < w->MagazineSize) 
            w->Magazine++;
    }
}
