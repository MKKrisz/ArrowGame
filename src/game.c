#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../debugmalloc.h"
#include "game.h"
#include "bullet.h"
#include "dataStructures/BulletPasta.h"
#include "control/input.h"
#include "math/vector.h"
#include "menu/menu.h"

#define PI 3.1415926f
#define PARTICLE_BASE_LIFE 2.0f
#define THRUSTER_PARTICLE_SPAWNTIME 0.001f

Menu* menu;

// FIGYELMEZTETÉS AZ OLVASÓNAK: Ez a fájl írásról írásra olvashatatlanabb lesz, mindennemű karbantartási igyekezet
//     ellenére. Olvasás csak saját felelősségre (Azt pletykálják, olyan hatással van a szemre, mint 2
//     Pan-Galactic Gargle Blaster a márványpadlózatra)
// Starting work on tl;dr-s

// tl;dr: Ezt kapja a GameCallback, máshol nincs használva
typedef struct GameGraphicsTuple{
    Game* game;
    Graphics* graphics;
} GGTuple;

// tl;dr: Game loop, csak kicsit obfuszkáltabban
uint GameCallback(uint delta, void* data){

    // tl;dr: Kiszedjük az datákat a datából
    Graphics* g = ((GGTuple*)data)->graphics;
    Game* game = ((GGTuple*)data)->game;

    if(game->State != GAME_RUNNING) return 1;
    // tl;dr: delta = delta
    game->CDelta = (float)delta / 1000.0f;

    // tl;dr: Megnézzük elege lett-e a játékosnak
    SDL_Event currentEvent;
    while(SDL_PollEvent(&currentEvent) != 0){
        if(currentEvent.type == SDL_QUIT) game->State = GAME_EXITED;
    }

    // tl;dr: Sacreligios linkd-list updater csoda callok
    UpdateParticles(game);
    UpdateBullets(game, g);

    int alivecount = 0;

    for(int i = 0; i<game->PlayerCount; i++){
        Arrow* p1 = &game->Players[i];
        if(game->Players[i].Health <= 0) continue;
        alivecount++;

        //Ha előre gyorsult
        if(UpdateArrow(p1, game)){
            //És eltelt x idő
            while(p1->ThrusterTimerTM < 0){
                //csinál particle-t
                add_ParticleElement_front(game->Particles, new_ParticleElement( CreateParticle(
                    vec2_AddV(p1->Position, RandomVec2R(-1.0f, 1.0f)),
                    get_ThrusterParticleVelocity(p1, game),
                    PARTICLE_BASE_LIFE + RandomFR(-1.0f, 1.0f),
                    RandomColorC((SDL_Color){128, 70, 0, 255}, (SDL_Color){255, 200, 80, 0})
                    )));
                p1->ThrusterTimerTM += THRUSTER_PARTICLE_SPAWNTIME;
            }
            p1->ThrusterTimerTM -= game->CDelta;
        }

        //Ha le van nyomva a SHOOT gomb, lőjj!
        if(get_ButtonState(p1->Input, SHOOT) > 0){
            Fire(p1, game);
        }
        if(get_ButtonState(p1->Input, PAUSE) > 0 && menu == NULL){
            SetP1ic(p1->Config, p1->Input);
            //menu = LoadMenu("Menus/libPauseMenu.so", game, g);
            game->State = GAME_PAUSED;
        }

        //Visszapattint a képernyő széléről
        BounceEdge(p1, g);

        //
        for(int j = i+1; j<game->PlayerCount; j++){
            Arrow* p2 = &game->Players[j];
            if(p2->Health <= 0) continue;
            if(CollideArrow(p1, p2)){
                int cParticles = RandomR(10, 30);
                for(int z = 0; z < cParticles; z++){
                    add_ParticleElement_front(game->Particles, new_ParticleElement( CreateParticle(
                        vec2_MulfV(vec2_AddV(p1->Position, p2->Position), 0.5f),                //collision point
                        RandomVec2A((vec2_get_Length(&p1->Velocity) + vec2_get_Length(&p2->Velocity))/2 * RandomFR(0.25f, 1.f)),        //Average Velocity of the two
                        PARTICLE_BASE_LIFE + RandomFR(-1.0f, 1.0f),
                        RandomR(0, 2) == 1? p1->Color : p2->Color
                        )));
                }
            }
        }
    }
    if(alivecount<2){game->State = GAME_FINISHED;}
    return game->State != GAME_STOPPED;
}


void GameLoop(Game* game, Graphics* g){    
    if(game->State != GAME_SET) return;
    menu = NULL;
    if(game->BaseWeapon->Type == HITSCAN) game->BaseWeapon->Damage /= 10.0f;

    game->Players = malloc(sizeof(Arrow) * game->PlayerCount);

    ParticlePasta pasta = new_ParticlePasta();
    game->Particles = &pasta;

    BulletPasta pasta2 = CreateBulletPasta();
    game->Bullets = &pasta2;

    InitArrows(game, g);

    game->State = GAME_RUNNING;
    game->CDelta = 0.1f;

    float wait = 1.0f;

    GGTuple params = {game, g};
    SDL_TimerID loopTimer = SDL_AddTimer(20, GameCallback, &params);

    while(game->State != GAME_STOPPED && game->State != GAME_EXITED){
        BeginDraw(g);

        SDL_SetRenderDrawColor(g->Renderer, 0, 0, 0, 0);
        SDL_RenderClear(g->Renderer);
        DrawParticles(game->Particles->First, g);
        DrawBullets(game->Bullets->First, g, game->CDelta);
        for(int i = 0; i<game->PlayerCount; i++){
            Arrow* p1 = &game->Players[i];
            DrawArrow(p1, g, game->BaseHealth);
        }
        if(game->State == GAME_PAUSED) {
            menu = LoadMenu("Menus/libPauseMenu.so", game, g);

            UpdateLoop(menu, g);
            if(menu->State == MENU_EXITED) game->State = GAME_EXITED;

            if(game->State == GAME_RESET) {
                RestartGame(game, g);
                game->State = GAME_RUNNING;
            }
            DeallocMenu(menu);
            menu = NULL;
        }
        if(game->State == GAME_FINISHED) {
            SetP1ic(game->Players[0].Config, game->Players[0].Input);
            menu = LoadMenu("Menus/libWinMenu.so", game, g);

            while(menu->State == MENU_RUNNING) {
                UpdateMenu(20, menu, wait > 0);
                DrawMenu(menu, g);
                wait -= 0.02f;
            }
            if(menu->State == MENU_EXITED) game->State = GAME_EXITED;
            if(game->State == GAME_RESET) {
                RestartGame(game, g);
                game->State = GAME_RUNNING;
            }
            DeallocMenu(menu);
            menu = NULL;
        }
        EndDraw(g);
    }

    SDL_RemoveTimer(loopTimer);
    Deallocate(game);
}


void InitArrows(Game* game, Graphics* g){
    for(int i = 0; i<game->PlayerCount; i++){
        char icfg_path[30];
        sprintf(icfg_path, "Config/player%d.icfg", i);
        game->Players[i] = (Arrow){
                .Config = LoadInputConfig(icfg_path),
                .Input = malloc(sizeof(Input)),
                .Position = (vec2){RandomFR(0, (float)g->viewport_width), RandomFR(0, (float)g->viewport_height)},
                .Velocity = vec2_Zero(),
                .Angle = RandomFR(0, 2*PI),
                .Inertia = 0,
                .Accel = game->BaseAccel,
                .AngularAccel = game->BaseAngular,
                .Health = game->BaseHealth,
                .Weapon = CopyWeapon(game->BaseWeapon),
                //.FireTimer = game->BaseFirerate,
                .ThrusterTimerTM = THRUSTER_PARTICLE_SPAWNTIME,
                .Color = RandomColorR(64, 256)
        };
    }
}

void BounceEdge(Arrow* arrow, Graphics* g){
    if(arrow->Position.x < 0){
        arrow->Velocity.x *= -1;
        arrow->Position.x = 0;
    }
    if(arrow->Position.x > (float)g->viewport_width) {
        arrow->Velocity.x *= -1;
        arrow->Position.x = (float)g->viewport_width;
    }
    if(arrow->Position.y < 0){
        arrow->Velocity.y *= -1;
        arrow->Position.y = 0;
    }
    if(arrow->Position.y > (float)g->viewport_height) {
        arrow->Velocity.y *= -1;
        arrow->Position.y = (float)g->viewport_height;
    }
}

void UpdateParticles(Game* game){
    ParticleElement* p = game->Particles->First;
    ParticleElement* op;

    if(p == NULL){return;}
    while(p != NULL && p->Sauce->Lifetime < 0){
        game->Particles->First = p->Next;
        ParticleElement* bad = p;
        p = p->Next;
        free(bad->Sauce);
        free(bad);
    }
    while(p != NULL){
        if(p->Sauce->Lifetime < 0){
            p = p->Next;
            remove_ParticleElement_after(op);
        }
        else{
            UpdateParticle(p->Sauce, game->BaseFriction, game->CDelta);
            op = p;
            p = p->Next;
        }
    }
}

void DrawParticles(ParticleElement* first, Graphics* g){
    ParticleElement* p = first;
    while(p != NULL){
        DrawParticle(p->Sauce, g, PARTICLE_BASE_LIFE);
        p = p->Next;
    }
}

bool ProcessHits(Game* game, Bullet* b){
    if(b == NULL) return false;

    for(int i = 0; i < game->PlayerCount; i++){
        Arrow* p = &game->Players[i];
        Weapon* w = p->Weapon;

        if(p->Health <= 0) continue;

        vec2 hitVec = GetHitVec(p, b, game->CDelta);
        //printf("%f %f\n", hitVec.x, hitVec.y);

        if(CheckHit(hitVec)){
            p->Health -= w->Damage;
            p->Velocity = vec2_AddV(p->Velocity, vec2_MulfV(b->Velocity, 0.001f));

            int cParticles = RandomR(1, 8);
            for(int z = 0; z < cParticles; z++){
                vec2 bpvel = vec2_AddV(RandomVec2A(w->BulletSpeed * 0.01f), vec2_SubV(b->Position, p->Position));
                if(b->Type == HITSCAN) {bpvel = RandomVec2A(w->BulletSpeed*0.01f);}
                add_ParticleElement_front(game->Particles, new_ParticleElement( CreateParticle(
                    hitVec,
                    bpvel,
                    PARTICLE_BASE_LIFE + RandomFR(-1.0f, 1.0f),
                    p->Color
                )));
            }

            if(p->Health <= 0){
                int cdParticles = RandomR(100, 200);
                for(int z = 0; z < cdParticles; z++){
                    add_ParticleElement_front(game->Particles, new_ParticleElement( CreateParticle(
                            p->Position,
                            RandomVec2A(50),
                            PARTICLE_BASE_LIFE + RandomFR(-1.0f, 1.0f),
                            p->Color
                    )));
                }
            }
            if(b->Type != HITSCAN)return true;
        }
    }
    return false; 
}

void UpdateBullets(Game* game, Graphics* g){
    BulletElement* p = game->Bullets->First;
    BulletElement* oldp;

    if(p == NULL){return;}
    while(p != NULL && p == game->Bullets->First){
        if(ProcessHits(game, p->Sauce) || CheckBounds(p->Sauce, g) || p->Sauce->Lifetime <= 0){
            remove_BulletElement_front(game->Bullets);
            p = game->Bullets->First;
        }
        else {
            UpdateBullet(p->Sauce, game);
            oldp = p;
            p = p->Next;
        }
    }
    while(p != NULL){
        if(ProcessHits(game, p->Sauce) || CheckBounds(p->Sauce, g) || p->Sauce->Lifetime <= 0){
            p = p->Next;
            remove_BulletElement_after(oldp);
        }
        else{
            UpdateBullet(p->Sauce, game);
            oldp = p;
            p = p->Next;
        }
    }
}

void DrawBullets(BulletElement* first, Graphics* g, float delta){
    BulletElement* p = first;
    while(p != NULL){
        DrawBullet(p->Sauce, g, delta);
        p = p->Next;
    }
}

void RestartGame(Game* game, Graphics* gr){
    for(int i = 0; i<game->PlayerCount; i++){
        DeloadInputConfig(game->Players[i].Config);
        free(game->Players[i].Input);
        free(game->Players[i].Weapon);
    }
    free(game->Players);
    ParticleElement* p = game->Particles->First;
    while(p != NULL){
        ParticleElement* op = p;
        p = p->Next;
        free(op->Sauce);
        free(op);
    }

    while(game->Bullets->First != NULL){
        remove_BulletElement_front(game->Bullets);
    }

    game->Players = malloc(sizeof(Arrow) * game->PlayerCount);
    game->Particles->First = NULL;

    game->Bullets->First = NULL;

    InitArrows(game, gr);

    game->CDelta = 0.1f;
    game->State = GAME_RUNNING;
}

void Deallocate(Game* game){
    for(int i = 0; i<game->PlayerCount; i++){
        DeloadInputConfig(game->Players[i].Config);
        free(game->Players[i].Input);
        free(game->Players[i].Weapon);
    }
    free(game->Players);
    ParticleElement* p = game->Particles->First;
    while(p != NULL){
        ParticleElement* op = p;
        p = p->Next;
        free(op->Sauce);
        free(op);
    }
    
    while(game->Bullets->First != NULL){
        remove_BulletElement_front(game->Bullets);
    }
    free(game->BaseWeapon);
}

