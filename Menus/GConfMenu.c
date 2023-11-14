#include "GConfMenu.h"
#include "../debugmalloc.h"
#include "../src/gcfg.h"
#include "../src/weapon.h"

Graphics* gr;
Game game;
char* filepath;
Gcfg gcfg;
int fits;
int lastSelId;
int coffset;

void Init(Menu* m, void* data, Graphics* graph){
    gr = graph;
    
    filepath = (char*)data;
    gcfg = gcfg_Load(filepath);
    fits = (graph->viewport_height - 22)/15;
    lastSelId = 1;
    coffset = 0;

    m->State = MENU_INIT;

    m->Name = "Custom Game Config";

    char* texts[] = {"Config", "Players:", "Input setup", "Acceleration:", "Turn Accel:", "Friction:", "HP:", "Weapon Type:",
        "Weapon Damage:", "Bullet Speed:", "Weapon Spread(rad):", "Fire Delay(s):", "Reload Delay(s):", "Magazine Size:",
        "Start Game", "Back"};
    float defs[] = {0, 
                    gcfg.Values[GCFG_PLAYERCOUNT].min,
                    0,
                    (gcfg.Values[GCFG_ACCEL].min + gcfg.Values[GCFG_ACCEL].max) / 2,
                    (gcfg.Values[GCFG_ANGULAR].min + gcfg.Values[GCFG_ANGULAR].max) / 2,
                    (gcfg.Values[GCFG_FRICTION].min + gcfg.Values[GCFG_FRICTION].max) / 2,
                    (gcfg.Values[GCFG_HP].min + gcfg.Values[GCFG_HP].max) / 2,
                    gcfg.Values[GCFG_WEAPON_TYPE].min,
                    (gcfg.Values[GCFG_WEAPON_DMG].min + gcfg.Values[GCFG_WEAPON_DMG].max) / 2,
                    (gcfg.Values[GCFG_WEAPON_SPD].min + gcfg.Values[GCFG_WEAPON_SPD].max) / 2,
                    (gcfg.Values[GCFG_WEAPON_ACC].min + gcfg.Values[GCFG_WEAPON_ACC].max) / 2,
                    (gcfg.Values[GCFG_WEAPON_FRATE].min + gcfg.Values[GCFG_WEAPON_FRATE].max) / 2,
                    (gcfg.Values[GCFG_WEAPON_RRATE].min + gcfg.Values[GCFG_WEAPON_RRATE].max) / 2,
                    (gcfg.Values[GCFG_WEAPON_MAGSIZE].min + gcfg.Values[GCFG_WEAPON_MAGSIZE].max) / 2,
                    0,
                    0};
    InitSliderMenu(m, texts, 16, defs, gr);

    DestroySlider(m->Entries[2].Slider);
    DestroySlider(m->Entries[14].Slider);
    DestroySlider(m->Entries[15].Slider);

    m->Entries[2].Type = MENU_BUTTON;
    m->Entries[2].Button = CreateButton(CreateText(texts[2], 15, gr), NULL);
    SetTextPos(
            m->Entries[2].Button->Text,
            1,
            m->Entries[1].Backdrop.y - m->Entries[2].Button->Text->DrawRect.h - 2);
    m->Entries[2].Backdrop = (SDL_Rect){0,
                                         m->Entries[1].Backdrop.y - m->Entries[2].Button->Text->DrawRect.h - 2,
                                         gr->viewport_width,
                                         m->Entries[1].Button->Text->DrawRect.h + 1};

    m->Entries[14].Type = MENU_BUTTON;
    m->Entries[14].Button = CreateButton(CreateText(texts[14], 15, gr), NULL);
    SetTextPos(
            m->Entries[14].Button->Text,
            1, 
            m->Entries[13].Backdrop.y - m->Entries[14].Button->Text->DrawRect.h - 2);
    m->Entries[14].Backdrop = (SDL_Rect){0,
            m->Entries[13].Backdrop.y - m->Entries[14].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[13].Button->Text->DrawRect.h + 1};

    m->Entries[15].Type = MENU_BUTTON;
    m->Entries[15].Button = CreateButton(CreateText(texts[15], 15, gr), NULL);
    SetTextPos(
            m->Entries[15].Button->Text,
            1, 
            m->Entries[14].Backdrop.y - m->Entries[15].Button->Text->DrawRect.h - 2);
    m->Entries[15].Backdrop = (SDL_Rect){0,
            m->Entries[14].Backdrop.y - m->Entries[15].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[14].Button->Text->DrawRect.h + 1};
    
    m->Entries[1].Slider->Modify = M_PCount;
    m->Entries[2].Button->Interact = InputMenu;
    m->Entries[3].Slider->Modify = M_Accel;
    m->Entries[4].Slider->Modify = M_Angular;
    m->Entries[5].Slider->Modify = M_Friction;
    m->Entries[6].Slider->Modify = M_HP;
    m->Entries[7].Slider->Modify = M_WType;
    m->Entries[8].Slider->Modify = M_WDmg;
    m->Entries[9].Slider->Modify = M_WSpd;
    m->Entries[10].Slider->Modify = M_Acc;
    m->Entries[11].Slider->Modify = M_FR;
    m->Entries[12].Slider->Modify = M_RR;
    m->Entries[13].Slider->Modify = M_MS;


    
    m->Entries[14].Button->Interact = Start;
    m->Entries[15].Button->Interact = Back;

    for(int i = 1; i < 13; i++){
        if(i == 2) continue;
        HandleEntryInteract(m, &m->Entries[i], 0);
    }

    m->State = MENU_RUNNING;
}

void OffsetOne(MenuEntry* m, int offset){
    m->Backdrop.y += offset;
    m->Textbox->Text->DrawRect.y += offset;
    switch(m->Type){
        case MENU_SLIDER:
            m->Slider->ValueText->DrawRect.y += offset;
            break;
        default:
            break;
    }
}

void OffsetAll(Menu* m, int offset){
    for(int i = 0; i<m->EntryCount; i++){
        OffsetOne(&m->Entries[i], offset);
    }
}

void Update(Menu* m){
    if(lastSelId == m->SelectedEntry) return;
    if(m->SelectedEntry % fits == 0 && lastSelId < m->SelectedEntry){
        OffsetAll(m, (fits+1)*15);
        coffset += (fits+1)*15;
    }
    if(m->SelectedEntry % fits == fits-1 && lastSelId > m->SelectedEntry){
        OffsetAll(m, -(fits+1)*15);
        coffset -= (fits+1)*15;
    }
    lastSelId = m->SelectedEntry;
}



void SetValR(Menu* m, Slider* self, float min, float max, bool integer, float t){
    float* val = &self->Value;

    float mul = integer?20:1;
    float diff = t - *val;

    *val += diff*mul + 0.000001f;
    if(*val < min) *val = min;
    if(*val > max) *val = max;

    char* vstr = malloc(30*sizeof(char));
    integer?sprintf(vstr, "%.0f", *val):sprintf(vstr, "%.2f", *val);
    SetTextString(self->ValueText, vstr, gr);
    self->ValueText->DrawRect.x = gr->viewport_width - self->ValueText->DrawRect.w;
    free(vstr);
}
void SetVal(Menu* m, Slider* self, int id, bool integer, float t){
    SetValR(m, self, gcfg.Values[id].min, gcfg.Values[id].max, integer, t);
}

char* wtypes[] = {"Projectile", "Hitscan", "Heat-seeker", "Random"};
void SetWType(Menu* m, Slider* self, float t){
    float* val = &gcfg.Values[GCFG_WEAPON_TYPE].min;
    float diff = t - *val;

    *val += diff*20 + 0.0000001;
    if(*val < 0) {*val = 3.000001f;}
    if(*val > 3) {*val = 0.000001f;}
    self->Value = *val;

    char* vstr = wtypes[(int)*val];
    SetTextString(self->ValueText, vstr, gr);
    self->ValueText->DrawRect.x = gr->viewport_width - self->ValueText->DrawRect.w;
}

void InputMenu(Menu* m){
    Menu* i = LoadMenu("Menus/libIPlayerSelector.so", NULL, gr);
    m->State = MENU_WAITING;
    UpdateLoop(i, gr);
    m->State = MENU_RUNNING;
    if(i->State & MENU_EXITED) m->State = MENU_EXITED;
    else if(i->State & MENU_WASUPDATED) m->State = MENU_UPDATE;
    DeallocMenu(i);
}

void M_PCount(Menu* m, Slider* self, float t)	{SetValR(m, self, 2, 4, true, t);}
void M_Accel(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_ACCEL, false, t);}
void M_Angular(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_ANGULAR, false, t);}
void M_Friction(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_FRICTION, false, t);}
void M_HP(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_HP, false, t);}
void M_WType(Menu* m, Slider* self, float t)	{SetWType(m, self, t);}
void M_WDmg(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_WEAPON_DMG, false, t);}
void M_WSpd(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_WEAPON_SPD, false, t);}
void M_Acc(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_WEAPON_ACC, false, t);}
void M_FR(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_WEAPON_FRATE, false, t);}
void M_RR(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_WEAPON_RRATE, false, t);}
void M_MS(Menu* m, Slider* self, float t)	{SetVal(m, self, GCFG_WEAPON_MAGSIZE, false, t);}


void Start(Menu* m){
    game = (Game){.State = GAME_SET,
        .PlayerCount = (int)m->Entries[1].Slider->Value,
        .BaseAccel = m->Entries[3].Slider->Value,
        .BaseAngular = m->Entries[4].Slider->Value,
        .BaseFriction = m->Entries[5].Slider->Value,
        .BaseHealth = m->Entries[6].Slider->Value,
        .BaseWeapon = CreateWeapon(
                m->Entries[7].Slider->Value,
                m->Entries[8].Slider->Value,
                m->Entries[9].Slider->Value,
                m->Entries[10].Slider->Value,
                m->Entries[11].Slider->Value,
                m->Entries[12].Slider->Value,
                m->Entries[13].Slider->Value)};
    m->State = MENU_STOPPED;
}
void Back(Menu* m){
    game.State = GAME_INVALID;
    m->State = MENU_STOPPED;
}

Game Return(){
    return game;
}
