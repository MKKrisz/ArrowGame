#pragma once

#include "../src/menu/menu.h"

void Init(Menu* m, void* data, Graphics* graph);
void Update(Menu* m);
Game Return();

void M_Res(Menu* m, Slider* self, float t);
void M_Scale(Menu* m, Slider* self, float t);
void M_Fullscreen(Menu* m, Slider* self, float t);
void Apply(Menu* m);
void Back(Menu* m);
