#pragma once

#include "../src/menu/menu.h"

void Init(Menu* m, void* data, Graphics* graph);
void Update(Menu* m);
Game Return();

void StartRandomGame(Menu* menu);
void StartCustomGame(Menu* menu);
void SetOptions(Menu* menu);
void Quit(Menu* menu);
