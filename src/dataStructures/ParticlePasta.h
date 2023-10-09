#pragma once

#include "../particle.h"


// Particle változók láncolt listaeleme
typedef struct ParticleElement { 
    Particle *Sauce;
    struct ParticleElement *Next;
} ParticleElement; 
    
// Particle változók láncolt listája. A "pasta" név egy nyelvbotlásból jön: "láncolt liszt" -> "tészta" -> "pasta"
typedef struct ParticlePasta { 
    ParticleElement* First;
} ParticlePasta; 
    
// Készít egy stack allokált láncolt Particle listát
ParticlePasta new_ParticlePasta();

// Készít egy heap allokált Particle listaelemet.
// Fontos, hogy data is heap allokált legyen, különben a program összefossa magát.
ParticleElement* new_ParticleElement(Particle* data);

// Egy láncolt Particle lista elejére helyez egy elemet.
void add_ParticleElement_front(ParticlePasta *pasta, ParticleElement *element);

// Egy láncelemhez kapcsol egy másikat.
void add_ParticleElement_after(ParticleElement *after, ParticleElement *element);

// Kivesz egy láncszemet a listából, majd deallokálja azt.
void remove_ParticleElement_after(ParticleElement *element);
