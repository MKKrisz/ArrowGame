#pragma once

#include "../src/menu/menu.h"

void Init(Menu* m, void* data, Graphics* graph);
void Update(Menu* m);
Game Return();

void M_PCount(Menu* m, Slider* self, float t);
void M_Accel(Menu* m, Slider* self, float t);
void M_Angular(Menu* m, Slider* self, float t);
void M_Friction(Menu* m, Slider* self, float t);
void M_HP(Menu* m, Slider* self, float t);
void M_WType(Menu* m, Slider* self, float t);
void M_WDmg(Menu* m, Slider* self, float t);
void M_WSpd(Menu* m, Slider* self, float t);
void M_Acc(Menu* m, Slider* self, float t);
void M_FR(Menu* m, Slider* self, float t);
void M_RR(Menu* m, Slider* self, float t);
void M_MS(Menu* m, Slider* self, float t);

void InputMenu(Menu* m);
void Start(Menu* m);
void Back(Menu* m);
