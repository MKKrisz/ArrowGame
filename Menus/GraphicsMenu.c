#include "GraphicsMenu.h"
#include "../debugmalloc.h"

Graphics* gr;

void Init(Menu* m, void* data, Graphics* graph){
    gr = graph;

    m->State = MENU_INIT;

    m->Name = "Graphics";

    char* texts[] = {"Graphics", "Width:", "Height:", "Scale:", "Fullscreen:", "Apply", "Back"};
    float defs[] = {0, 
                    gr->window_width, 
                    gr->window_height, 
                    gr->viewport_scale, 
                    (SDL_GetWindowFlags(graph->Window) & SDL_WINDOW_FULLSCREEN) == 1,
                    0,
                    0};
    InitSliderMenu(m, texts, 7, defs, gr);

    DestroySlider(m->Entries[5].Slider);
    DestroySlider(m->Entries[6].Slider); 
    
    m->Entries[5].Type = MENU_BUTTON;
    m->Entries[5].Button = CreateButton(CreateText(texts[5], 15, gr), NULL);
    SetTextPos(
            m->Entries[5].Button->Text,
            1, 
            m->Entries[4].Backdrop.y - m->Entries[5].Button->Text->DrawRect.h - 2);
    m->Entries[5].Backdrop = (SDL_Rect){0,
            m->Entries[4].Backdrop.y - m->Entries[5].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[5].Button->Text->DrawRect.h + 2};

    m->Entries[6].Type = MENU_BUTTON;
    m->Entries[6].Button = CreateButton(CreateText(texts[6], 15, gr), NULL);
    SetTextPos(
            m->Entries[6].Button->Text,
            1, 
            m->Entries[5].Backdrop.y - m->Entries[6].Button->Text->DrawRect.h - 2);
    m->Entries[6].Backdrop = (SDL_Rect){0,
            m->Entries[5].Backdrop.y - m->Entries[6].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[6].Button->Text->DrawRect.h + 2};

    m->Entries[1].Slider->Modify = M_Res;
    m->Entries[2].Slider->Modify = M_Res;
    m->Entries[3].Slider->Modify = M_Scale;
    m->Entries[4].Slider->Modify = M_Fullscreen;
    m->Entries[5].Button->Interact = Apply;
    m->Entries[6].Button->Interact = Back;

    for(int i = 1; i < 5; i++){
        HandleEntryInteract(m, &m->Entries[i], 0);
    }

    m->State = MENU_RUNNING;
}


void M_Res(Menu* m, Slider* self, float t){
    self->Value += (t-self->Value)*20;
    if(self->Value < 0) self->Value = 0;
    if(self->Value > 32767) self->Value = 32767;
    char str[20];
    sprintf(str, "%.0f", self->Value);
    SetTextString(self->ValueText, str, gr);
    SetTextPos(self->ValueText, 
                gr->viewport_width - self->ValueText->DrawRect.w - 1,
                self->ValueText->DrawRect.y);
}

void M_Scale(Menu* m, Slider* self, float t){
    self->Value = t;
    if(self->Value < 0) self->Value = 0;
    if(self->Value > 2) self->Value = 2;
    char str[20];
    sprintf(str, "%.2f", self->Value);
    SetTextString(self->ValueText, str, gr);
    SetTextPos(self->ValueText, 
                gr->viewport_width - self->ValueText->DrawRect.w - 1,
                self->ValueText->DrawRect.y);
   
}
void M_Fullscreen(Menu* m, Slider* self, float t){
    self->Value += (t-self->Value)*20;
    if(self->Value < 0) self->Value = 0;
    if(self->Value > 1) self->Value = 1;
    char str[5];
    sprintf(str, "%s", self->Value != 0? "Yes" : "No");
    SetTextString(self->ValueText, str, gr);
    SetTextPos(self->ValueText, 
                gr->viewport_width - self->ValueText->DrawRect.w - 1,
                self->ValueText->DrawRect.y);

}
void Apply(Menu* m){
    gfxcfg cfg = (gfxcfg){
        .Width = m->Entries[1].Slider->Value,
        .Height = m->Entries[2].Slider->Value,
        .Scaling = m->Entries[3].Slider->Value,
        .Fullscreen = m->Entries[4].Slider->Value != 0 ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN
    };
    gfx_Save(&cfg, "Config/graphics.cfg");
    SetFullscreen(gr, m->Entries[4].Slider->Value != 0);
    ResizeWindow(gr, cfg.Width, cfg.Height);
    RescaleViewport(gr, cfg.Scaling);
    m->State = MENU_UPDATE;
}
void Back(Menu* m){
    m->State = MENU_STOPPED;
}
