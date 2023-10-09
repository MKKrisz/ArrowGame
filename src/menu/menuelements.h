#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../graphics/graphics.h"
#include "textrenderer.h"


//Kinda looks like: Blahblahblah
typedef struct Textbox {
    Text* Text;
} Textbox;

Textbox* CreateTextbox(Text* t);
void DrawTextbox(Textbox* t, Graphics* g);
void DestroyTextbox(Textbox* t);


//Looks just like the textbox, except selectable
typedef struct Button{
    Text* Text;
    char* NextMenuPath;
} Button;

Button* CreateButton(Text* t, char* menupath);
void DrawButton(Button* b, Graphics* g, bool selected);
void DestroyButton(Button* b);

//Looks like:  Blah        50 -----o-----
typedef struct Slider{
    Text* Text;
    float* ModifiedValue;
    float Min;
    float Max;
    float Default;
    //hack
    struct Text* Current;
} Slider;

Slider* CreateSlider(Text* title, float min, float max, float def, float* modValue);
void DrawSlider(Slider* s, Graphics* g, bool selected);
void DestroySlider(Slider* s);


