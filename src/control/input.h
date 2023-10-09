#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

#define CONTROLLER_DEADZONE 5000.0f
#define CONTROLLER_MAX 32767.0f

typedef enum InputID {
    FORWARD = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    SHOOT = 4,
    BOOST = 5,
    PAUSE = 6,
    INPUT_ID_LENGTH = 7
} InputID;

typedef enum Input_t {
    KEYBOARD = 0,
    BUTTON = 1,
    POSITIVE_AXIS = 2,
    NEGATIVE_AXIS = 3,
} Input_t;

// Az adott bemenet konfigurációjának tárolója
typedef struct ButtonInfo {
    Input_t Type;
    union {
	SDL_Scancode Key;
	SDL_GameControllerButton Button;
	SDL_GameControllerAxis Axis;
    };
} ButtonInfo;

// Az adott konfiguráció tárolója
typedef struct InputConfig {
    SDL_GameController* Controller;
    ButtonInfo Buttons[7]; 
} InputConfig;

// Valamilyen bemeneti konfiguráció állapotának tárolója
typedef struct Input {
    const Uint8* kbState;
    float state[7];
} Input;

// Kinyeri a bemeneti konfigurációból egy adott konfiguráció értékét.
ButtonInfo* get_ButtonInfo(InputConfig* cfg, int id);

// Beállítja egy adott bemenet konfigurációját.
void set_ButtonInfo(InputConfig* cfg, int id, ButtonInfo button);

// Frissíti az adott bemeneti konfiguráció állapotát.
void UpdateButton(InputConfig* cfg, Input* input, int id);

// Frissíti a megadott konfiguráció összes bemenetének állapotát.
void UpdateButtons(InputConfig* cfg, Input* input);

// Egy bemenet állapotát adja visza.
float get_ButtonState(Input* input, int id);

// Előállít egy bemeneti konfigurációt.
ButtonInfo ButtonInfo_Make(Input_t type, uint ID);

// Betölt fájlból egy bemeneti konfigurációt.
InputConfig* LoadInputConfig(const char* path);

// Fájlba ment egy bemeneti konfigurációt.
void SaveInputConfig(const char* path, InputConfig* cfg);
