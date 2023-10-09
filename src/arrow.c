#include "arrow.h"

#define PI 3.1415926f

bool UpdateArrow(Arrow* arrow, Game* game){
    UpdateButtons(arrow->Config, arrow->Input);
    UpdateWeapon(arrow->Weapon, game->CDelta);
    
    float speed_dec = (1.0f - (game->BaseFriction * game->CDelta));

    float Angle_Accel = get_ButtonState(arrow->Input, LEFT) * arrow->AngularAccel;
    Angle_Accel -= get_ButtonState(arrow->Input, RIGHT) * arrow->AngularAccel;

    arrow->Inertia += Angle_Accel * game->CDelta;

    arrow->Angle += arrow->Inertia * game->CDelta;
    arrow->Inertia *= speed_dec;

    float Accel_mag = get_ButtonState(arrow->Input, FORWARD) * arrow->Accel;
    Accel_mag -= get_ButtonState(arrow->Input, BACK) * arrow->Accel;

    vec2 Accel = vec2_MakeAM(arrow->Angle, Accel_mag);
    arrow->Velocity.x += Accel.x * game->CDelta;
    arrow->Velocity.y += Accel.y * game->CDelta;

    arrow->Position.x += arrow->Velocity.x * game->CDelta;
    arrow->Position.y += arrow->Velocity.y * game->CDelta;

    arrow->Velocity = vec2_Mulf(&arrow->Velocity, speed_dec);
    return arrow->Input->state[FORWARD] > 0;
}

bool CollideArrow(Arrow* a, Arrow* b){
    //a-ból b-be mutató vektor
    vec2 distance = {a->Position.x - b->Position.x, a->Position.y - b->Position.y};
    if(vec2_get_Length(&distance) > ARROW_SIZE*3.0f/4.0f) return false;

    vec2 normal = vec2_Normalize(&distance);
    vec2 normalC = (vec2){normal.x, -normal.y};

    vec2 aRot;
    aRot.x = (a->Velocity.x * normalC.x) - (a->Velocity.y * normalC.y);
    aRot.y = (a->Velocity.x * normalC.y) + (a->Velocity.y * normalC.x);

    vec2 bRot;
    bRot.x = (b->Velocity.x * normalC.x) - (b->Velocity.y * normalC.y);
    bRot.y = (b->Velocity.x * normalC.y) + (b->Velocity.y * normalC.x);

    vec2 aNew;
    aNew.x = bRot.x;     //Kapja
    aNew.y = aRot.y;     //Tartja

    vec2 bNew;
    bNew.x = aRot.x;
    bNew.y = bRot.y;

    a->Velocity.x = (aNew.x * normal.x) - (aNew.y * normal.y);
    a->Velocity.y = (aNew.x * normal.y) + (aNew.y * normal.x);

    b->Velocity.x = (bNew.x * normal.x) - (bNew.y * normal.y);
    b->Velocity.y = (bNew.x * normal.y) + (bNew.y * normal.x);
    
    return true;
}

SDL_FRect get_ArrowRect(Arrow* arrow){
    return (SDL_FRect){
        .x = arrow->Position.x - ARROW_SIZE/2.0f,
        .y = arrow->Position.y - ARROW_SIZE/2.0f,
        .w = ARROW_SIZE,
        .h = ARROW_SIZE
    };
}

vec2 get_ThrusterParticleVelocity(Arrow* arrow, Game* game){
    return vec2_MakeAM(arrow->Angle - PI + RandomFR(-PI/RandomFR(3.0f, 5.0f), PI/RandomFR(3.0f, 5.0f)), game->BaseAccel/10 + RandomFR(-1.0f, 1.0f));
}
