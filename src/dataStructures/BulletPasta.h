#pragma once

#include "../bullet.h"

// Bullet változók láncolt listaeleme
typedef struct BulletElement {
    Bullet *Sauce;
    struct BulletElement *Next;
} BulletElement;

// Bullet változók láncolt listája. Elnevezés: ld.: ParticlePasta.h
typedef struct BulletPasta {
    BulletElement* First;
} BulletPasta;

// Készít egy stack allokált láncolt Bullet listát
BulletPasta CreateBulletPasta();

// Készít egy heap allokált Bullet listaelemet.
// Fontos, hogy data is heap allokált legyen, különben a program összefossa magát.
BulletElement* CreateBulletElement(Bullet* data);

void DeallocBulletElement(BulletElement* element);

// Egy láncolt Bullet lista elejére helyez egy elemet.
void add_BulletElement_front(BulletPasta *pasta, BulletElement *element);

// Egy láncelemhez kapcsol egy másikat.
void add_BulletElement_after(BulletElement *after, BulletElement *element);

// Kivesz egy láncszemet a listából, majd deallokálja azt.
void remove_BulletElement_after(BulletElement *element);

void remove_BulletElement_front(BulletPasta* pasta);
