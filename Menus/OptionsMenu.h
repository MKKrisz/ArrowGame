#pragma once

#include "../src/menu/menu.h"

void Init(Menu* m, void* data, Graphics* graph);
//void Update(Menu* m);
//Game Return();

void GraphicsMenu(Menu* m);
void InputMenu(Menu* m);
void RandomMenu(Menu* m);
void CustomMenu(Menu* m);
void Back(Menu* m);
