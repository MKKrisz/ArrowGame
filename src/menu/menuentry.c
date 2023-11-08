#include "menuentry.h"
#include "../../debugmalloc.h"


void DrawMenuEntry(MenuEntry* entry, Graphics* g, bool selected) {
    if(selected) {
        SDL_SetRenderDrawColor(g->Renderer, BASE_FONT_COLOR_ELEMENTS);
    }
    else {
        SDL_SetRenderDrawColor(g->Renderer, 0, 0, 0, 0);
    }

    SDL_RenderFillRect(g->Renderer, &entry->Backdrop); 


    switch(entry->Type){
        case MENU_TEXTBOX:
            DrawTextbox(entry->Textbox, g);
            break;
        case MENU_BUTTON:
            DrawButton(entry->Button, g, selected);
            break;
        case MENU_SLIDER:
            DrawSlider(entry->Slider, g, selected);
            break;
    }
}
void HandleEntryInteract(Menu* menu, MenuEntry* entry, float dsliderf){
    switch(entry->Type){
        case MENU_BUTTON:
            if(entry->Button->Interact != NULL)
                (*entry->Button->Interact)(menu);
            break;
        case MENU_SLIDER:
            (*entry->Slider->Modify)(menu, entry->Slider, entry->Slider->Value + dsliderf);
            break;
        default: 
            break;
    }
}

void DeallocateMenuEntry(MenuEntry* e){
    switch(e->Type){
        case MENU_TEXTBOX:
            DestroyTextbox(e->Textbox);
            break;
        case MENU_BUTTON:
            DestroyButton(e->Button);
            break;
        case MENU_SLIDER:
            DestroySlider(e->Slider);
            break;
    }
}
