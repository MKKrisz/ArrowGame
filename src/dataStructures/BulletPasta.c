#include "BulletPasta.h"
#include "../../debugmalloc.h"

BulletPasta CreateBulletPasta() {
    return (BulletPasta) {.First = NULL};
}

BulletElement* CreateBulletElement(Bullet* data) {
    BulletElement* p = (BulletElement*)malloc(sizeof(BulletElement));
    p->Sauce = data;
    p->Next = NULL;
    return p;
}

void DeallocBulletElement(BulletElement* element){
    free(element->Sauce);
    free(element);
}

void add_BulletElement_front(BulletPasta *pasta, BulletElement *element){
    if(pasta->First == NULL) { pasta->First = element; return;}
    element->Next = pasta->First;
    pasta->First = element;
}

void add_BulletElement_after(BulletElement *after, BulletElement *element){
    element->Next = after->Next;
    after->Next = element;
}

void remove_BulletElement_after(BulletElement *element) {
    if(element == NULL) return;
    if(element->Next == NULL) return;
    BulletElement* rossz = element->Next;
    element->Next = element->Next->Next;
    DeallocBulletElement(rossz);
}

void remove_BulletElement_front(BulletPasta* pasta){
    if(pasta == NULL) return;
    if(pasta->First == NULL) return;
    BulletElement* rossz = pasta->First;
    pasta->First = pasta->First->Next;
    DeallocBulletElement(rossz);
}

