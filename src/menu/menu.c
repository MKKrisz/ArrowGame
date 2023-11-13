#include "menu.h"
#include "../../debugmalloc.h"

InputConfig* p1ic;
Input* p1i;

void LoadP1ic(){
    p1ic = LoadInputConfig("Config/player0.icfg");
    p1i = malloc(sizeof(Input));
}
void SetP1ic(InputConfig* cfg, Input* i){
    p1ic = cfg;
    p1i = i;
}
void FreeP1ic(){
    DeloadInputConfig(p1ic);
    free(p1i);
}

Menu* LoadMenu(const char* path, void* data, Graphics* graph){
    Menu* op = malloc(sizeof(Menu));

    op->State = MENU_INVALID;
    op->WasUpdated = false;

    op->CustomData = data;

    op->Handle = dlopen(path, RTLD_NOW);
    //printf("%s", dlerror());
    op->Init = dlsym(op->Handle, "Init");
    (*op->Init)(op, data, graph);

    op->CustomUpdate = dlsym(op->Handle, "Update");
    op->CustomDraw = dlsym(op->Handle, "Draw");
    op->GetGame = dlsym(op->Handle, "Return");

    return op;
}

void ReloadMenu(Menu* m, Graphics* graph){
    for(int i = 0; i<m->EntryCount; i++){
        DeallocateMenuEntry(&m->Entries[i]);
    }
    free(m->Entries);
    (*m->Init)(m, m->CustomData, graph);
}

void InitBasicMenu(Menu* m, char** texts, int count, Graphics* gr){
    m->EntryCount = count;
    m->SelectedEntry = 1;
    m->Entries = malloc(sizeof(MenuEntry) * count);

    for(int i = 0; i<count; i++){
        if(i == 0){
            m->Entries[i].Type = MENU_TEXTBOX;
            m->Entries[i].Textbox = CreateTextbox(CreateText(texts[i], 22, gr));

            SetTextPos(
                m->Entries[i].Button->Text,
                1,
                gr->viewport_height - m->Entries[i].Textbox->Text->DrawRect.h - 1);

            m->Entries[0].Backdrop = (SDL_Rect) {
                0,
                gr->viewport_height - m->Entries[i].Textbox->Text->DrawRect.h - 2,
                gr->viewport_width,
                m->Entries[i].Textbox->Text->DrawRect.h + 2};
            continue;
        }
        m->Entries[i].Type = MENU_BUTTON;
        m->Entries[i].Button = CreateButton(CreateText(texts[i], 15, gr), NULL);
        SetTextPos(
            m->Entries[i].Button->Text,
            1,
            m->Entries[i-1].Backdrop.y - m->Entries[i].Button->Text->DrawRect.h - 2);
        m->Entries[i].Backdrop = (SDL_Rect){
            0,
            m->Entries[i-1].Backdrop.y - m->Entries[i].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[i].Button->Text->DrawRect.h + 2};

    }
}

void InitSliderMenu(Menu* m, char** texts, int tlen, float* defaults, Graphics* gr){
    m->EntryCount = tlen;
    m->SelectedEntry = 1;
    m->Entries = malloc(sizeof(MenuEntry) * tlen);

    for(int i = 0; i<tlen; i++){
        if(i == 0){
            m->Entries[i].Type = MENU_TEXTBOX;
            m->Entries[i].Textbox = CreateTextbox(CreateText(texts[i], 22, gr));

            SetTextPos(
                m->Entries[i].Button->Text,
                1,
                gr->viewport_height - m->Entries[i].Textbox->Text->DrawRect.h - 1);

            m->Entries[0].Backdrop = (SDL_Rect) {
                0,
                gr->viewport_height - m->Entries[i].Textbox->Text->DrawRect.h - 2,
                gr->viewport_width,
                m->Entries[i].Textbox->Text->DrawRect.h + 2};
            continue;
        }
        m->Entries[i].Type = MENU_SLIDER;
        m->Entries[i].Slider = CreateSlider(CreateText(texts[i], 15, gr), defaults[i], NULL);
        char str[20];
        sprintf(str, "%.2f", defaults[i]);
        m->Entries[i].Slider->ValueText = CreateText(str, 15, gr);
        SetTextPos(
            m->Entries[i].Slider->Text,
            1,
            m->Entries[i-1].Backdrop.y - m->Entries[i].Slider->Text->DrawRect.h - 2);
        SetTextPos(
            m->Entries[i].Slider->ValueText,
            gr->viewport_width - m->Entries[i].Slider->ValueText->DrawRect.w - 1,
            m->Entries[i-1].Backdrop.y - m->Entries[i].Slider->Text->DrawRect.h - 2);
        m->Entries[i].Backdrop = (SDL_Rect){
            0,
            m->Entries[i-1].Backdrop.y - m->Entries[i].Button->Text->DrawRect.h - 2,
            gr->viewport_width,
            m->Entries[i].Button->Text->DrawRect.h + 2};
    }
}


void UpdateMenuOnEvent(Menu* m, SDL_Event event){
    if(event.type == SDL_QUIT){
        m->State = MENU_EXITED;
        return;
    }
    bool keyupevent = false;
    bool controllerevent = false;
    if(event.key.type == SDL_KEYUP) keyupevent = true;
    if(event.cbutton.type == SDL_CONTROLLERBUTTONDOWN
        || (event.type == SDL_CONTROLLERAXISMOTION && abs(event.caxis.value) > CONTROLLER_DEADZONE))
        controllerevent = true;
    float ival = 0;
    SDL_KeyboardEvent kevent = event.key;
    SDL_Scancode scode = event.key.keysym.scancode;
    
    if((keyupevent && scode == SDL_SCANCODE_UP) || (controllerevent && get_ButtonState(p1i, M_UP))){
        if(m->SelectedEntry > 1){
            m->SelectedEntry--;
            while(m->Entries[m->SelectedEntry].Type == MENU_TEXTBOX && m->SelectedEntry > 1)
                m->SelectedEntry--;
        }
    }

    if((keyupevent && scode == SDL_SCANCODE_DOWN) || (controllerevent && get_ButtonState(p1i, M_DOWN))) {
        if(m->SelectedEntry < m->EntryCount-1){
            m->SelectedEntry++;
            while(m->Entries[m->SelectedEntry].Type == MENU_TEXTBOX && m->SelectedEntry < m->EntryCount-1)
                m->SelectedEntry++;
        }
    }

    if((keyupevent && scode == SDL_SCANCODE_RETURN) || (controllerevent && get_ButtonState(p1i, M_OK))){
        HandleEntryInteract(m, &m->Entries[m->SelectedEntry], 0);
    }
    if((keyupevent && scode == SDL_SCANCODE_ESCAPE) || (controllerevent && get_ButtonState(p1i, PAUSE))){
        m->State = MENU_STOPPED;
    }    

    if((keyupevent && scode == SDL_SCANCODE_LEFT) || (controllerevent && get_ButtonState(p1i, M_LEFT))) {
        ival = -SLIDER_DEFAULT_INCREMENT;
        if(kevent.keysym.mod & KMOD_LSHIFT || kevent.keysym.mod & KMOD_RSHIFT){
            ival *= 10;
        }
        if(kevent.keysym.mod & KMOD_LCTRL || kevent.keysym.mod & KMOD_RCTRL){
            ival *= 100;
        }
        HandleEntryInteract(m, &m->Entries[m->SelectedEntry], ival);
    }
    if((keyupevent && scode == SDL_SCANCODE_RIGHT) || (controllerevent && get_ButtonState(p1i, M_RIGHT))) {
        ival = SLIDER_DEFAULT_INCREMENT;
        if(kevent.keysym.mod & KMOD_LSHIFT || kevent.keysym.mod & KMOD_RSHIFT){
            ival *= 10;
        }
        if(kevent.keysym.mod & KMOD_LCTRL || kevent.keysym.mod & KMOD_RCTRL){
            ival *= 100;
        }
        HandleEntryInteract(m, &m->Entries[m->SelectedEntry], ival);
    }
}


void UpdateMenu(uint delta, void* menu, bool inputDisabled){
    Menu* m = (Menu*)menu;
    SDL_Event event;
    while(!inputDisabled && m->State & MENU_RUNNING && SDL_PollEvent(&event) != 0){
        UpdateButtons(p1ic, p1i);
        UpdateMenuOnEvent(m, event);

    }
    if(m->CustomUpdate != NULL) (*m->CustomUpdate)(m);
}

/* This function starts an update loop for the current menu.
 * REMARKS: Originally this function was supposed to start an update thread and simultaenously draw the menu,
 *          but since SDL render calls must be from the main thread, and new menus would be on the Update thread,
 *          that idea was ditched. Some of the things above make this obvious, but it is best if I typed it out.
 */
void UpdateLoop(Menu* m, Graphics* g){
    //SDL_TimerID menu = SDL_AddTimer(50, UpdateMenu, m);
    SDL_Event e;
    if(m->State & MENU_RUNNING) DrawMenu(m, g);
    while(m->State & MENU_RUNNING && SDL_WaitEvent(&e)){
        UpdateButtons(p1ic, p1i);
        UpdateMenuOnEvent(m, e);
        if(m->State & MENU_UPDATE) {
            FreeP1ic();
            LoadP1ic();
            ReloadMenu(m, g);
            m->WasUpdated = true;
        }
        if(m->CustomUpdate != NULL) (*m->CustomUpdate)(m);
        if(m->State & MENU_RUNNING) DrawMenu(m, g);
        //if(m->State & MENU_FAILED) break;
    }
    if(m->WasUpdated) m->State = m->State | MENU_WASUPDATED;
    //SDL_RemoveTimer(menu);
}

void DrawMenu(Menu* m, Graphics* g){
    if(m == NULL) return;
    if(m->State & MENU_RUNNING){
        BeginDraw(g);
        SDL_SetRenderDrawColor(g->Renderer, 0, 0, 0, 0);
        SDL_RenderClear(g->Renderer);
        if(m->CustomDraw != NULL)(*m->CustomDraw)(m, g);
        for(int i = 0; i<m->EntryCount; i++){
            DrawMenuEntry(&m->Entries[i], g, m->SelectedEntry == i);
        }
        EndDraw(g);
    }
}

void DeallocMenu(Menu* m){
    if(m == NULL) return;
    for(int i = 0; i<m->EntryCount; i++){
        DeallocateMenuEntry(&m->Entries[i]);
    }
    free(m->Entries);
    dlclose(m->Handle);
    free(m);
}
