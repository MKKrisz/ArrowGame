#pragma once

#include "arrow.h"
#include "dataStructures/ParticlePasta.h"
#include "particle.h"
#include "bullet.h"
#include "arrow.h"
#include "weapon.h"
#include "graphics/graphics.h"
#include "control/input.h"
#include "control/random.h"

struct BulletPasta;
struct BulletElement;
struct Bullet;
struct Arrow;
struct Weapon;

typedef enum GameState{
    GAME_INVALID = 0,
    GAME_SET = 1,
    GAME_RUNNING = 2,
    GAME_PAUSED = 3,
    GAME_RESET = 4,
    GAME_FINISHED = 5,
    GAME_STOPPED = 6
} GameState;

// Egy játék konfigurációjának és fontosabb belső változóinak tárolója.
typedef struct Game {
    GameState State;
    int PlayerCount;
    float BaseAccel;
    float BaseAngular;
    float BaseFriction;
    float BaseHealth;

    struct Weapon* BaseWeapon;

    struct Arrow* Players;

    ParticlePasta* Particles;
    struct BulletPasta* Bullets;
    float CDelta;
} Game;

void GameLoop(Game* game, Graphics* g);

void InitArrows(Game* game, Graphics* g);

void BounceEdge(struct Arrow* arrow, Graphics* g);


// Put this here, because I don't know where else to put it
// Ő lenne a "tésztaszűrő". Ő felel a láncolt listában tárolt Particle-k frissítéséért, kirajzolásáért, illetve törléséért.
// Ha meg kéne mondanom, hogy mi tud a legnagyobb valószínűséggel memory leaket okozni, ezt a funkciót mondanám.
void UpdateParticles(Game* game);
void DrawParticles(ParticleElement* first, Graphics* g);

bool ProcessHits(Game* game, struct Bullet* b);

void UpdateBullets(Game* game, Graphics* g);
void DrawBullets(struct BulletElement* first, Graphics* g, float delta);

void Deallocate(Game* game);
