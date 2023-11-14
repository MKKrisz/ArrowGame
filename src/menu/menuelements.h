#pragma once

#include "../graphics/graphics.h"
#include "textrenderer.h"
#include "menu.h"

struct Menu;

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
    void (*Interact)(struct Menu* menu);
} Button;

Button* CreateButton(Text* t, void (*interact)(struct Menu* menu));
void DrawButton(Button* b, Graphics* g, bool selected);
void DestroyButton(Button* b);

//Looks like:  Blah        50
typedef struct Slider{
    Text* Text;
    void (*Modify)(struct Menu* menu, struct Slider* self, float t);
    float Value;
    struct Text* ValueText;
} Slider;

Slider* CreateSlider(Text* title, float def, void (*interact)(struct Menu* menu, struct Slider* self, float t));
void DrawSlider(Slider* s, Graphics* g, bool selected);
void DestroySlider(Slider* s);


