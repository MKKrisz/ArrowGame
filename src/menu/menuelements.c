#include "menuelements.h"
#include "textrenderer.h"

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

Button* CreateButton(Text* t, char* menupath){
    Button* op = malloc(sizeof(Button));
    op->Text = t;
    op->NextMenuPath = menupath;
    return op;
}

void DrawButton(Button* b, Graphics* g, bool selected){
    if(selected){
        SetTextColor(b->Text, (SDL_Color){0, 0, 0, 0});
        SDL_RenderFillRect(g->Renderer, &b->Text->DrawRect);

    }
    else SetTextColor(b->Text, BASE_FONT_COLOR);
}

void DesstroyButton(Button* b){
    DestroyText(b->Text);
    free(b);
}

Slider* CreateSlider(Text* title, float min, float max, float def, float* modValue){
    Slider* op = malloc(sizeof(Slider));
    op->Text = title;
    op->Min = min;
    op->Max = max;
    op->Default = def;
    op->ModifiedValue = modValue;
    return op;
}

void DrawSlider(Slider* s, Graphics* g, bool selected){
    
}
