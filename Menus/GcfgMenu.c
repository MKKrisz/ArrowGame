#include "GcfgMenu.h"
#include "../debugmalloc.h"
#include "../src/gcfg.h"

Graphics* gr;
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

    m->Name = "Gcfg";

    char* texts[] = {"Config", "Players:", "Acceleration Min:", "Acceleration Max:", "Turn Accel Min:", 
        "Turn Accel Max:", "Friction Min:", "Friction Max:", "HP Min:", "HP Max:", "Weapon Type:", 
        "Weapon Damage Min:", "Weapon Damage Max:", "Bullet Speed Min:", "Bullet Speed Max:", "Weapon Spread Min:", "Weapon Spread Max:", 
        "Fire Delay Min:","Fire Delay Max:", "Reload Delay Min:", "Reload Delay Max:", "Magazine Size Min:",
        "Magazine Size Max:", "Apply", "Back"};
    float defs[] = {0, 
                    gcfg.Values[GCFG_PLAYERCOUNT].min,
                    gcfg.Values[GCFG_ACCEL].min,
                    gcfg.Values[GCFG_ACCEL].max,
                    gcfg.Values[GCFG_ANGULAR].min,
                    gcfg.Values[GCFG_ANGULAR].max,
                    gcfg.Values[GCFG_FRICTION].min,
                    gcfg.Values[GCFG_FRICTION].max,
                    gcfg.Values[GCFG_HP].min,
                    gcfg.Values[GCFG_HP].max,
                    gcfg.Values[GCFG_WEAPON_TYPE].min,
                    gcfg.Values[GCFG_WEAPON_DMG].min,
                    gcfg.Values[GCFG_WEAPON_DMG].max,
                    gcfg.Values[GCFG_WEAPON_SPD].min,
                    gcfg.Values[GCFG_WEAPON_SPD].max,
                    gcfg.Values[GCFG_WEAPON_ACC].min,
                    gcfg.Values[GCFG_WEAPON_ACC].max,
                    gcfg.Values[GCFG_WEAPON_FRATE].min,
                    gcfg.Values[GCFG_WEAPON_FRATE].max,
                    gcfg.Values[GCFG_WEAPON_RRATE].min,
                    gcfg.Values[GCFG_WEAPON_RRATE].max,
                    gcfg.Values[GCFG_WEAPON_MAGSIZE].min,
                    gcfg.Values[GCFG_WEAPON_MAGSIZE].max,
                    0,
                    0};
    InitSliderMenu(m, texts, 25, defs, gr);

    DestroySlider(m->Entries[23].Slider);
    DestroySlider(m->Entries[24].Slider); 
    
    m->Entries[23].Type = MENU_BUTTON;
    m->Entries[23].Button = CreateButton(CreateText(texts[23], 15, gr), NULL);
    SetTextPos(
            m->Entries[23].Button->Text,
            1, 
            m->Entries[22].Backdrop.y - m->Entries[23].Button->Text->DrawRect.h - 2);
    m->Entries[23].Backdrop = (SDL_Rect){0,
            m->Entries[22].Backdrop.y - m->Entries[23].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[22].Button->Text->DrawRect.h + 2};

    m->Entries[24].Type = MENU_BUTTON;
    m->Entries[24].Button = CreateButton(CreateText(texts[24], 15, gr), NULL);
    SetTextPos(
            m->Entries[24].Button->Text,
            1, 
            m->Entries[23].Backdrop.y - m->Entries[24].Button->Text->DrawRect.h - 2);
    m->Entries[24].Backdrop = (SDL_Rect){0,
            m->Entries[23].Backdrop.y - m->Entries[24].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[23].Button->Text->DrawRect.h + 2};

    m->Entries[1].Slider->Modify = M_PCount;
    m->Entries[2].Slider->Modify = M_Accel_Min;
    m->Entries[3].Slider->Modify = M_Accel_Max;
    m->Entries[4].Slider->Modify = M_Angular_Min;
    m->Entries[5].Slider->Modify = M_Angular_Max;
    m->Entries[6].Slider->Modify = M_Friction_Min;
    m->Entries[7].Slider->Modify = M_Friction_Max;
    m->Entries[8].Slider->Modify = M_HP_Min;
    m->Entries[9].Slider->Modify = M_HP_Max;
    m->Entries[10].Slider->Modify = M_WType;
    m->Entries[11].Slider->Modify = M_WDmg_Min;
    m->Entries[12].Slider->Modify = M_WDmg_Max;
    m->Entries[13].Slider->Modify = M_WSpd_Min;
    m->Entries[14].Slider->Modify = M_WSpd_Max;
    m->Entries[15].Slider->Modify = M_FR_Min;
    m->Entries[16].Slider->Modify = M_FR_Max;
    m->Entries[17].Slider->Modify = M_FR_Min;
    m->Entries[18].Slider->Modify = M_FR_Max;
    m->Entries[19].Slider->Modify = M_RR_Min;
    m->Entries[20].Slider->Modify = M_RR_Max;
    m->Entries[21].Slider->Modify = M_MS_Min;
    m->Entries[22].Slider->Modify = M_MS_Max;


    m->Entries[23].Button->Interact = Apply;
    m->Entries[24].Button->Interact = Back;

    for(int i = 1; i < 23; i++){
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

void SetVal(Menu* m, Slider* self, int id, bool mx, bool integer, float t){
    Range* r = &gcfg.Values[id];

    float* val;
    if(mx) val = &r->max;
    else val = &r->min;

    float mul = integer?20:1;
    float diff = t - *val;

    *val += diff*mul;
    self->Value = *val + 0.00001;

    char* vstr = malloc(30*sizeof(char));
    integer?sprintf(vstr, "%.0f", *val):sprintf(vstr, "%.2f", *val);
    SetTextString(self->ValueText, vstr, gr);
    self->ValueText->DrawRect.x = gr->viewport_width - self->ValueText->DrawRect.w;
    free(vstr);
}

void SetPCount(Menu* m, Slider* self, float t){
    float* val = &gcfg.Values[0].min;
    float diff = t - *val;

    *val += diff * 20 + 0.1;
    
    if(*val < 2) {*val = 2;}
    if(*val > 4) {*val = 4;}
    
    self->Value = *val;

    char* vstr = malloc(5*sizeof(char));
    sprintf(vstr, "%.0f", *val);
    SetTextString(self->ValueText, vstr, gr);
    self->ValueText->DrawRect.x = gr->viewport_width - self->ValueText->DrawRect.w;
    free(vstr);
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


void M_PCount(Menu* m, Slider* self, float t)		{SetPCount(m, self, t);}
void M_Accel_Min(Menu* m, Slider* self, float t)        {SetVal(m, self, 1, false, false, t);}
void M_Accel_Max(Menu* m, Slider* self, float t)	{SetVal(m, self, 1, true, false, t);}
void M_Angular_Min(Menu* m, Slider* self, float t)	{SetVal(m, self, 2, false, false, t);}
void M_Angular_Max(Menu* m, Slider* self, float t)	{SetVal(m, self, 2, true, false, t);}
void M_Friction_Min(Menu* m, Slider* self, float t)	{SetVal(m, self, 3, false, false, t);}
void M_Friction_Max(Menu* m, Slider* self, float t)	{SetVal(m, self, 3, true, false, t);}
void M_HP_Min(Menu* m, Slider* self, float t)		{SetVal(m, self, 4, false, false, t);}
void M_HP_Max(Menu* m, Slider* self, float t)		{SetVal(m, self, 4, true, false, t);}
void M_WType(Menu* m, Slider* self, float t)		{SetWType(m, self, t);}
void M_WDmg_Min(Menu* m, Slider* self, float t)		{SetVal(m, self, 6, false, false, t);}
void M_WDmg_Max(Menu* m, Slider* self, float t)		{SetVal(m, self, 6, true, false, t);}
void M_WSpd_Min(Menu* m, Slider* self, float t)		{SetVal(m, self, 7, false, false, t);}
void M_WSpd_Max(Menu* m, Slider* self, float t)		{SetVal(m, self, 7, true, false, t);}
void M_Acc_Min(Menu* m, Slider* self, float t)		{SetVal(m, self, 8, false, false, t);}
void M_Acc_Max(Menu* m, Slider* self, float t)		{SetVal(m, self, 8, true, false, t);}
void M_FR_Min(Menu* m, Slider* self, float t)		{SetVal(m, self, 9, false, false, t);}
void M_FR_Max(Menu* m, Slider* self, float t)		{SetVal(m, self, 9, true, false, t);}
void M_RR_Min(Menu* m, Slider* self, float t)		{SetVal(m, self, 10, false, false, t);}
void M_RR_Max(Menu* m, Slider* self, float t)		{SetVal(m, self, 10, true, false, t);}
void M_MS_Min(Menu* m, Slider* self, float t)		{SetVal(m, self, 11, false, false, t);}
void M_MS_Max(Menu* m, Slider* self, float t)		{SetVal(m, self, 11, true, false, t);}


void Apply(Menu* m){
    gcfg_Save(filepath, &gcfg);
    Back(m);
}
void Back(Menu* m){
    m->State = MENU_STOPPED;
}
