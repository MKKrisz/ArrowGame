#pragma once

#include "../src/menu/menu.h"

void Init(Menu* m, void* data, Graphics* gr);
void Update(Menu* m);
void Draw(Menu* m, Graphics* g);
Game Return();

void NewGame(Menu* m);
void QTM(Menu* m);
void QTD(Menu* m);
