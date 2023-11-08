#pragma once

#include "../src/menu/menu.h"

void Init(Menu* m, void* data, Graphics* graph);
void Update(Menu* m);
Game Return();

void M_PCount(Menu* m, Slider* self, float t);
void M_Accel_Min(Menu* m, Slider* self, float t);
void M_Accel_Max(Menu* m, Slider* self, float t);
void M_Angular_Min(Menu* m, Slider* self, float t);
void M_Angular_Max(Menu* m, Slider* self, float t);
void M_Friction_Min(Menu* m, Slider* self, float t);
void M_Friction_Max(Menu* m, Slider* self, float t);
void M_HP_Min(Menu* m, Slider* self, float t);
void M_HP_Max(Menu* m, Slider* self, float t);
void M_WType(Menu* m, Slider* self, float t);
void M_WDmg_Min(Menu* m, Slider* self, float t);
void M_WDmg_Max(Menu* m, Slider* self, float t);
void M_WSpd_Min(Menu* m, Slider* self, float t);
void M_WSpd_Max(Menu* m, Slider* self, float t);
void M_Acc_Min(Menu* m, Slider* self, float t);
void M_Acc_Max(Menu* m, Slider* self, float t);
void M_FR_Min(Menu* m, Slider* self, float t);
void M_FR_Max(Menu* m, Slider* self, float t);
void M_RR_Min(Menu* m, Slider* self, float t);
void M_RR_Max(Menu* m, Slider* self, float t);
void M_MS_Min(Menu* m, Slider* self, float t);
void M_MS_Max(Menu* m, Slider* self, float t);

void Apply(Menu* m);
void Back(Menu* m);
