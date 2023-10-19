#include "ParticlePasta.h"
#include "../../debugmalloc.h"

ParticlePasta new_ParticlePasta() { 
    return (ParticlePasta) {.First = NULL};
} 
    
ParticleElement* new_ParticleElement(Particle* data) { 
    ParticleElement* p = malloc(sizeof(ParticleElement));
    p->Sauce = data;
    p->Next = NULL;
    return p; 
}

void add_ParticleElement_front(ParticlePasta *pasta, ParticleElement *element){
    if(pasta->First == NULL) {
        pasta->First = element;
        return;
    }
    element->Next = pasta->First;
    pasta->First = element;
}
    
void add_ParticleElement_after(ParticleElement *after, ParticleElement *element){ 
    element->Next = after->Next;
    after->Next = element;
} 
    
void remove_ParticleElement_after(ParticleElement *element) {
    if(element == NULL) return;
    if(element->Next == NULL) return;
    ParticleElement* rossz = element->Next;
    element->Next = element->Next->Next;
    free(rossz->Sauce);
    free(rossz); 
} 

