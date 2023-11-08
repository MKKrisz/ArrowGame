#pragma once

#include "../src/menu/menu.h"

void Init(Menu* m, void* data, Graphics* graph);
void Update(Menu* m);
Game Return();


void M_Dev(Menu* m, Slider* self, float t);
void M_Fw(Menu* m, Slider* self, float t);
void M_B(Menu* m, Slider* self, float t);
void M_L(Menu* m, Slider* self, float t);
void M_R(Menu* m, Slider* self, float t);
void M_Sh(Menu* m, Slider* self, float t);
void M_P(Menu* m, Slider* self, float t);

void Apply(Menu* m);
void Back(Menu* m);

void UpdateSliderTexts(Menu* m);
