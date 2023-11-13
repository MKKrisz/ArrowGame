#include "InputMenu.h"
#include "../debugmalloc.h"

int playerNo;
InputConfig* ic;
char path[30];
Graphics* gr;
char* askinput = "Press a button...";

void Init(Menu* m, void* data, Graphics* graph){
    playerNo = *(int*)data;
    if(playerNo < 0 || playerNo > 4) {m->State = MENU_INVALID; return;}
    gr = graph;

    char title[20];

    sprintf(title, "Input: Player %1d", playerNo);
    sprintf(path, "Config/player%d.icfg", playerNo-1);
    ic = LoadInputConfig(path);

    //Leaving out "Boost", as it is unused in the game
    char* texts[10] = {title, "Device:", "Forward:", "Back:", "Left:", "Right:", "Shoot:", "Pause:", "Apply", "Back"};
    float defaults[10] = {0, ic->UsesCtrl, 
        (float)ic->Buttons[0].Key, 
        (float)ic->Buttons[1].Key, 
        (float)ic->Buttons[2].Key, 
        (float)ic->Buttons[3].Key, 
        (float)ic->Buttons[4].Key, 
        (float)ic->Buttons[9].Key, 
        0, 0};
    InitSliderMenu(m, texts, 10, defaults, gr);

    DestroySlider(m->Entries[8].Slider);
    DestroySlider(m->Entries[9].Slider); 
    
    m->Entries[8].Type = MENU_BUTTON;
    m->Entries[8].Button = CreateButton(CreateText(texts[8], 15, gr), NULL);
    SetTextPos(
            m->Entries[8].Button->Text,
            1, 
            m->Entries[7].Backdrop.y - m->Entries[8].Button->Text->DrawRect.h - 2);
    m->Entries[8].Backdrop = (SDL_Rect){0,
            m->Entries[7].Backdrop.y - m->Entries[8].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[8].Button->Text->DrawRect.h + 2};

    m->Entries[9].Type = MENU_BUTTON;
    m->Entries[9].Button = CreateButton(CreateText(texts[9], 15, gr), NULL);
    SetTextPos(
            m->Entries[9].Button->Text,
            1, 
            m->Entries[8].Backdrop.y - m->Entries[9].Button->Text->DrawRect.h - 2);
    m->Entries[9].Backdrop = (SDL_Rect){0,
            m->Entries[8].Backdrop.y - m->Entries[9].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[9].Button->Text->DrawRect.h + 2};
    
    m->Entries[1].Slider->Modify = M_Dev;
    m->Entries[2].Slider->Modify = M_Fw;
    m->Entries[3].Slider->Modify = M_B;
    m->Entries[4].Slider->Modify = M_L;
    m->Entries[5].Slider->Modify = M_R;
    m->Entries[6].Slider->Modify = M_Sh;
    m->Entries[7].Slider->Modify = M_P;

    m->Entries[8].Button->Interact = Apply;
    m->Entries[9].Button->Interact = Back;

    UpdateSliderTexts(m);
    m->State = MENU_RUNNING;
}

void UpdateSliderTexts(Menu* m){
    for(int i = 1; i<8; i++){
        int ici = i-2;  //Input Config Iterator
        if(ici >= 5) {ici++;}

        const char* txt;
        if(i == 1){
            txt = ic->UsesCtrl ? "Controller":"Keyboard";
        }
        else 
            txt = GetEnumName(ic->Buttons[ici].Type, ic->Buttons[ici].Button);

        Slider* self = m->Entries[i].Slider;
        SetTextString(self->ValueText, txt, gr);
        SetTextPos(self->ValueText, 
                gr->viewport_width - self->ValueText->DrawRect.w - 1,
                self->ValueText->DrawRect.y);
    }
}



void GrabAndSetInput(Menu* m, Slider* self, int i){
    SetTextString(self->ValueText, askinput, gr);
    SetTextPos(self->ValueText, 
                gr->viewport_width - self->ValueText->DrawRect.w - 1,
                self->ValueText->DrawRect.y);
    DrawMenu(m, gr);
    
    SDL_Event ev;
    if(ic->UsesCtrl){
        while(SDL_WaitEvent(&ev) && ((ev.type != SDL_CONTROLLERAXISMOTION || abs(ev.caxis.value) < CONTROLLER_DEADZONE) && ev.type != SDL_CONTROLLERBUTTONDOWN && ev.type != SDL_QUIT));
        switch(ev.type){
            case SDL_CONTROLLERAXISMOTION:
                if(ev.caxis.value < 0){ic->Buttons[i].Type = NEGATIVE_AXIS;}
                else ic->Buttons[i].Type = POSITIVE_AXIS;
                ic->Buttons[i].Axis = ev.caxis.axis;
                break;

            case SDL_CONTROLLERBUTTONDOWN:
                ic->Buttons[i].Type = BUTTON;
                ic->Buttons[i].Button = ev.cbutton.button;
                break;
            case SDL_QUIT:
                m->State = MENU_EXITED;
                break;
            default:
                break;
        }
    }
    else {
        while(SDL_WaitEvent(&ev) && ev.type != SDL_KEYUP);
        ic->Buttons[i].Type = KEYBOARD;
        ic->Buttons[i].Key = ev.key.keysym.scancode;
    }
    UpdateSliderTexts(m);
}

void M_Dev(Menu* m, Slider* self, float t){
    self->Value += (t-self->Value)*20;
    if(self->Value < 0) self->Value = false;
    if(self->Value > 1) self->Value = true;
    ic->UsesCtrl = self->Value;
    if(ic->UsesCtrl) ic->Controller = SDL_GameControllerOpen(0);
    else ic->Controller = NULL;

    char str[20];
    sprintf(str, "%s", self->Value != 0? "Controller" : "Keyboard");
    SetTextString(self->ValueText, str, gr);
    SetTextPos(self->ValueText, 
                gr->viewport_width - self->ValueText->DrawRect.w - 1,
                self->ValueText->DrawRect.y);
}
void M_Fw(Menu*m, Slider* self, float t){
    if(t - self->Value == 0) GrabAndSetInput(m, self, FORWARD);
}
void M_B(Menu*m, Slider* self, float t){
    if(t - self->Value == 0) GrabAndSetInput(m, self, BACK);
}
void M_L(Menu*m, Slider* self, float t){
    if(t - self->Value == 0) GrabAndSetInput(m, self, LEFT);
}
void M_R(Menu*m, Slider* self, float t){
    if(t - self->Value == 0) GrabAndSetInput(m, self, RIGHT);
}
void M_Sh(Menu*m, Slider* self, float t){
    if(t - self->Value == 0) GrabAndSetInput(m, self, SHOOT);
}
void M_P(Menu*m, Slider* self, float t){
    if(t - self->Value == 0) GrabAndSetInput(m, self, PAUSE);
}

void Apply(Menu* m){
    SaveInputConfig(path, ic);
    DeloadInputConfig(ic);
    m->State = MENU_UPDATE;
}

void Back(Menu* m){
    m->State = MENU_STOPPED;
}

Game Return(){
    DeloadInputConfig(ic);
    return (Game){0};
}
