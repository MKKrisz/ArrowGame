#include <stdio.h>

#include "../../debugmalloc.h"
#include "input.h"

int usedJoysticks = 0;

//These are SDL_GameControllerButton names, except they are made human-readable
/*char* buttonNames[21] = {"A", "B", "X", "Y", "Back", "Guide", "Start", "LS", "RS", "LB", "RS", "Dpad Up",
                         "Dpad Down", "Dpad Left", "Dpad Right", "MISC1", "PADDLE1", "PADDLE2", "PADDLE3",
                         "PADDLE4", "TOUCHPAD"}*/


const char* GetEnumName(Input_t type, uint value){
    switch(type){
        case KEYBOARD:
            return SDL_GetScancodeName((SDL_Scancode)value);
        case BUTTON:
            return SDL_GameControllerGetStringForButton(value);
        case POSITIVE_AXIS:
        case NEGATIVE_AXIS:
            return SDL_GameControllerGetStringForAxis(value);
            
    }
    return NULL;
}

ButtonInfo* get_ButtonInfo(InputConfig* cfg, int id) {
    return &(cfg->Buttons[id]);
}
void set_ButtonInfo(InputConfig* cfg, int id, ButtonInfo button){
    cfg->Buttons[id] = button;
}

void UpdateButton(InputConfig* cfg, Input* input, int id){
    ButtonInfo* btn = get_ButtonInfo(cfg, id);
    switch(btn->Type){
        case KEYBOARD:
            input->state[id] = input->kbState[btn->Key];
            break;
        case BUTTON:
            input->state[id] = SDL_GameControllerGetButton(cfg->Controller, btn->Button);
            break;
        case POSITIVE_AXIS:
            input->state[id] = (float)SDL_GameControllerGetAxis(cfg->Controller, btn->Axis) / CONTROLLER_MAX;
            if(input->state[id] < CONTROLLER_DEADZONE/CONTROLLER_MAX) input->state[id] = 0;
            break;
        case NEGATIVE_AXIS:
            input->state[id] = (float)SDL_GameControllerGetAxis(cfg->Controller, btn->Axis) * (-1) / CONTROLLER_MAX;
            if(input->state[id] < CONTROLLER_DEADZONE/CONTROLLER_MAX) input->state[id] = 0;
            break;
    }
}


void UpdateButtons(InputConfig* cfg, Input* input){
    input->kbState = SDL_GetKeyboardState(NULL);
    for(int i = 0; i < TRUE_INPUT_ID_LENGTH; i++){
        UpdateButton(cfg, input, i);
    }
}

float get_ButtonState(Input* input, int id){
    return input->state[id];
}

ButtonInfo ButtonInfo_Make(Input_t type, uint ID){
    ButtonInfo btn;
    btn.Type = type;
    switch(type){
        case KEYBOARD:
            btn.Key = ID;
            break;
        case BUTTON:
            btn.Button = ID;
            break;
        case POSITIVE_AXIS:
        case NEGATIVE_AXIS:
            btn.Axis = ID;
            break;
    }
    return btn;
}

InputConfig* LoadInputConfig(const char* path){
    InputConfig* cfg = malloc(sizeof(InputConfig));
    set_ButtonInfo(cfg, M_UP,   (ButtonInfo){.Type = KEYBOARD, .Key = SDL_SCANCODE_UNKNOWN});
    set_ButtonInfo(cfg, M_DOWN, (ButtonInfo){.Type = KEYBOARD, .Key = SDL_SCANCODE_UNKNOWN});
    set_ButtonInfo(cfg, M_LEFT, (ButtonInfo){.Type = KEYBOARD, .Key = SDL_SCANCODE_UNKNOWN});
    set_ButtonInfo(cfg, M_RIGHT,(ButtonInfo){.Type = KEYBOARD, .Key = SDL_SCANCODE_UNKNOWN});
    set_ButtonInfo(cfg, M_OK,   (ButtonInfo){.Type = KEYBOARD, .Key = SDL_SCANCODE_UNKNOWN});

    FILE* file = fopen(path, "r");
    if(file == NULL){ file = fopen("Config/default.icfg", "r");}

    for(int i = 0; i < INPUT_ID_LENGTH; i++){
        fscanf(file, "%u %u\n", &cfg->Buttons[i].Type, &cfg->Buttons[i].Key);
    }
    cfg->UsesCtrl = false;
    for(int i = 0; i<INPUT_ID_LENGTH; i++){
        if(cfg->Buttons[i].Type != 0){
            cfg->UsesCtrl = true;
            break;
        }
    }
    if(cfg->UsesCtrl && usedJoysticks < SDL_NumJoysticks()){
        cfg->Controller = SDL_GameControllerOpen(usedJoysticks);
        //printf("%s", SDL_GetError());
        usedJoysticks++;
        set_ButtonInfo(cfg, M_UP,   (ButtonInfo){.Type = BUTTON, .Button = SDL_CONTROLLER_BUTTON_DPAD_UP});
        set_ButtonInfo(cfg, M_DOWN, (ButtonInfo){.Type = BUTTON, .Button = SDL_CONTROLLER_BUTTON_DPAD_DOWN});
        set_ButtonInfo(cfg, M_LEFT, (ButtonInfo){.Type = BUTTON, .Button = SDL_CONTROLLER_BUTTON_DPAD_LEFT});
        set_ButtonInfo(cfg, M_RIGHT,(ButtonInfo){.Type = BUTTON, .Button = SDL_CONTROLLER_BUTTON_DPAD_RIGHT});
        set_ButtonInfo(cfg, M_OK,   (ButtonInfo){.Type = BUTTON, .Button = SDL_CONTROLLER_BUTTON_A});
    }
    else cfg->Controller = NULL;
    //printf("%s", SDL_GetError());
    return cfg;
}

void DeloadInputConfig(InputConfig* cfg){
    if(cfg == NULL) return;
    if(cfg->Controller != NULL){
        SDL_GameControllerClose(cfg->Controller);
        usedJoysticks--;
    }
    free(cfg);
}

void SaveInputConfig(const char* path, InputConfig* cfg){
    FILE* file = fopen(path, "w");

    for(int i = 0; i < INPUT_ID_LENGTH; i++){
        //Beacuse of how unions work, this should just work regardless aswell
        fprintf(file, "%u %u\n", cfg->Buttons[i].Type, cfg->Buttons[i].Key);
    }
    fclose(file);
}
