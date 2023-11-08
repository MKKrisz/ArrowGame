#include "menuelements.h"
#include "textrenderer.h"
#include "../../debugmalloc.h"

Textbox* CreateTextbox(Text* t){
    Textbox* op = malloc(sizeof(Textbox));
    op->Text = t;
    return op;
}

void DrawTextbox(Textbox* t, Graphics* g){
    DrawText(t->Text, g);
}

void DestroyTextbox(Textbox* t){
    DestroyText(t->Text);
    free(t);
}

Button* CreateButton(Text* t, void (*interact)(struct Menu* menu)){
    Button* op = malloc(sizeof(Button));
    op->Text = t;
    op->Interact = interact;
    return op;
}

void DrawButton(Button* b, Graphics* g, bool selected){
    if(selected){
        SetTextColor(b->Text, (SDL_Color){0, 0, 0, 255});
    }
    else 
        SetTextColor(b->Text, BASE_FONT_COLOR);
    DrawText(b->Text, g);
}

void DestroyButton(Button* b){
    DestroyText(b->Text);
    free(b);
}

Slider* CreateSlider(Text* title, float def, void (*interact)(Menu* menu, Slider* self, float t)){
    Slider* op = malloc(sizeof(Slider));
    op->Text = title;
    op->Value = def;
    op->Modify = interact;
    return op;
}

void DrawSlider(Slider* s, Graphics* g, bool selected){
    if(selected){
        SetTextColor(s->Text, (SDL_Color){0, 0, 0, 0});
        SetTextColor(s->ValueText, (SDL_Color){0, 0, 0, 0});
    }
    else { 
        SetTextColor(s->Text, BASE_FONT_COLOR);
        SetTextColor(s->ValueText, BASE_FONT_COLOR);
    }
    DrawText(s->Text, g);
    DrawText(s->ValueText, g);
}

void DestroySlider(Slider* s){
    DestroyText(s->Text);
    DestroyText(s->ValueText);
    free(s);
}
