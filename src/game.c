#include "game.h"
#include "bullet.h"
#include "dataStructures/BulletPasta.h"
#include "control/input.h"
#include "graphics/color.h"
#include "math/vector.h"
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define PI 3.1415926f
#define PARTICLE_BASE_LIFE 2.0f
#define THRUSTER_PARTICLE_SPAWNTIME 0.001f

void GameLoop(Game* game, Graphics* g){    
    game->Players = malloc(sizeof(Arrow) * game->PlayerCount);

    ParticlePasta pasta = new_ParticlePasta();
    game->Particles = &pasta;

    BulletPasta pasta2 = CreateBulletPasta();
    game->Bullets = &pasta2;

    InitArrows(game, g);
    
    SDL_Texture* tex_arrow = IMG_LoadTexture(g->Renderer, "Assets/Arrow.png");

    SDL_Color* Palette = GeneratePaletteM(8);

    bool running = true;
    
    game->CDelta = 0.1f;
    struct timespec start;
    struct timespec end;

    
    while(running){
        clock_gettime(CLOCK_MONOTONIC, &start);

        //cement
        SDL_Event currentEvent;
        while(SDL_PollEvent(&currentEvent) != 0){
             if(currentEvent.type == SDL_QUIT) running = false;
        }

        BeginDraw(g);
        SDL_SetRenderDrawColor(g->Renderer, 0, 0, 0, 0);
        SDL_RenderClear(g->Renderer);

        ManageParticlePasta(game, g);
        ManageBulletPasta(game, g);

        for(int i = 0; i<game->PlayerCount; i++){
            if(game->Players[i].Health <= 0) continue;

            if(UpdateArrow(&game->Players[i], game)){
                while(game->Players[i].ThrusterTimerTM < 0){
                    add_ParticleElement_front(game->Particles, new_ParticleElement( CreateParticle(
                        vec2_AddV(game->Players[i].Position, RandomVec2R(-1.0f, 1.0f)),
                        get_ThrusterParticleVelocity(&game->Players[i], game),
                        PARTICLE_BASE_LIFE + RandomFR(-1.0f, 1.0f),
                        //RandomColorC((SDL_Color){128, 70, 0, 255}, (SDL_Color){255, 200, 80, 0})
                        Palette[RandomR(0, 8)]
                        )));
                    game->Players[i].ThrusterTimerTM += THRUSTER_PARTICLE_SPAWNTIME;
                }
                game->Players[i].ThrusterTimerTM -= game->CDelta;
            }

            if(get_ButtonState(game->Players[i].Input, SHOOT) > 0 && game->Players[i].FireTimer<0){
                add_BulletElement_front(game->Bullets, CreateBulletElement(CreateBullet(game, &game->Players[i], PROJECTILE)));
                game->Players[i].Velocity = vec2_AddV(game->Players[i].Velocity, vec2_MakeAM(game->Players[i].Angle, game->BaseBulletspeed * -0.0001f * game->BaseDamage));
                game->Players[i].FireTimer += game->BaseFirerate;
            }
            game->Players[i].FireTimer -= game->CDelta;

            BounceEdge(&game->Players[i], g);

            for(int j = i+1; j<game->PlayerCount; j++){
                if(game->Players[j].Health <= 0) continue;
                if(CollideArrow(&game->Players[i], &game->Players[j])){
                    int cParticles = RandomR(10, 30);
                    for(int z = 0; z < cParticles; z++){
                        add_ParticleElement_front(game->Particles, new_ParticleElement(CreateParticle(
                            vec2_MulfV(vec2_AddV(game->Players[i].Position, game->Players[j].Position), 0.5f),                //collision point
                            RandomVec2A((vec2_get_Length(&game->Players[i].Velocity) + vec2_get_Length(&game->Players[j].Velocity))/2 * RandomFR(0.25f, 1.f)),        //Average Velocity of the two
                            PARTICLE_BASE_LIFE + RandomFR(-1.0f, 1.0f),
                            RandomR(0, 2) == 1? game->Players[i].Color : game->Players[j].Color
                            )));
                    }
                }
            }

            SDL_SetTextureColorMod(tex_arrow, game->Players[i].Color.r, game->Players[i].Color.g, game->Players[i].Color.b);
            SDL_FRect playerRect = get_ArrowRect(&game->Players[i]);
            SDL_RenderCopyExF(g->Renderer, tex_arrow, NULL, &playerRect, game->Players[i].Angle*180/PI + 90, NULL, SDL_FLIP_NONE);
        }

        SDL_SetRenderDrawColor(g->Renderer, 255, 255, 255, 255);
        SDL_RenderDrawLineF(g->Renderer, 0, 0, g->viewport_width * game->Players[0].FireTimer / game->BaseFirerate,0);
        EndDraw(g);
        clock_gettime(CLOCK_MONOTONIC, &end);
        game->CDelta = (float)end.tv_sec - (float)start.tv_sec + ((float)end.tv_nsec/1000000000.0f - (float)start.tv_nsec/1000000000.0f);
        printf("%f\n", 1/game->CDelta);
    }
    Deallocate(game);
    free(Palette);
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
                .FireTimer = game->BaseFirerate,
                .ThrusterTimerTM = THRUSTER_PARTICLE_SPAWNTIME,
                .Color = RandomColor()
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

void ManageParticlePasta(Game* game, Graphics* g){
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
            DrawParticle(p->Sauce, g, PARTICLE_BASE_LIFE);
            op = p;
            p = p->Next;
        }
    }
}

bool ProcessHits(Game* game, Bullet* b){
    if(b == NULL) return false;
    for(int i = 0; i < game->PlayerCount; i++){
        if(game->Players[i].Health <= 0) continue;
        vec2 hitVec = GetHitVec(&game->Players[i], b, game->CDelta);
        //printf("%f %f\n", hitVec.x, hitVec.y);
        if(CheckHit(hitVec)){
            game->Players[i].Health -= game->BaseDamage;
            game->Players[i].Velocity = vec2_AddV(game->Players[i].Velocity, vec2_MulfV(b->Velocity, 0.0001f));
            int cParticles = RandomR(1, 8);
            for(int z = 0; z < cParticles; z++){
                add_ParticleElement_front(game->Particles, new_ParticleElement(CreateParticle(
                    hitVec,
                    vec2_AddV(RandomVec2A(game->BaseBulletspeed * 0.01f), vec2_AddV(b->Position, vec2_NegV(game->Players[i].Position))),
                    PARTICLE_BASE_LIFE + RandomFR(-1.0f, 1.0f),
                    game->Players[i].Color
                )));
            }
            if(game->Players[i].Health <= 0){
                int cParticles = RandomR(100, 200);
                for(int z = 0; z < cParticles; z++){
                    add_ParticleElement_front(game->Particles, new_ParticleElement(CreateParticle(
                            game->Players[i].Position,
                            RandomVec2A(10),
                            PARTICLE_BASE_LIFE + RandomFR(-1.0f, 1.0f),
                            game->Players[i].Color
                    )));
                }
            }
            return true;
        }
    }
    return false; 
}

void ManageBulletPasta(Game* game, Graphics* g){
    BulletElement* p = game->Bullets->First;
    BulletElement* oldp;

    if(p == NULL){return;}
    while(p != NULL && p == game->Bullets->First){
        if(ProcessHits(game, p->Sauce) || CheckBounds(p->Sauce, g)){
            remove_BulletElement_front(game->Bullets);
            p = game->Bullets->First;
        }
        else {
            DrawBullet(p->Sauce, g, game->BaseBulletspeed * 0.00001f);
            UpdateBullet(p->Sauce, game);
            oldp = p;
            p = p->Next;
        }
    }
    while(p != NULL){
        if(ProcessHits(game, p->Sauce) || CheckBounds(p->Sauce, g)){
            p = p->Next;
            remove_BulletElement_after(oldp);
        }
        else{
            DrawBullet(p->Sauce, g, game->BaseBulletspeed*0.00001f);
            UpdateBullet(p->Sauce, game);
            oldp = p;
            p = p->Next;
        }
    }
}

void Deallocate(Game* game){
    for(int i = 0; i<game->PlayerCount; i++){
        free(game->Players[i].Config);
        free(game->Players[i].Input);
    }
    free(game->Players);
    ParticleElement* p = game->Particles->First;
    while(p != NULL){
        ParticleElement* op = p;
        p = p->Next;
        free(op->Sauce);
        free(op);
    }
    BulletElement* b = game->Bullets->First;
    while(b != NULL){
        BulletElement* ob = b;
        b = b->Next;
        free(ob->Sauce);
        free(ob);
    }
}

