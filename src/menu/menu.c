#include "menu.h"
#include "../../debugmalloc.h"

Menu* LoadMenu(const char* path, Game* g, Graphics* graph){
    Menu* op = malloc(sizeof(Menu));

    op->Running = true;

    op->Handle = dlopen(path, RTLD_NOW);
    printf("%s", dlerror());
    
    void (*Init)(Menu* base, Game* g, Graphics* graph);
    Init = dlsym(op->Handle, "Init");
    (*Init)(op, g, graph);

    op->CustomUpdate = dlsym(op->Handle, "Update");
    op->GetGame = dlsym(op->Handle, "Return");

    return op;
}

void UpdateMenu(Menu* m, float delta){
    SDL_Event event;
    while(SDL_PollEvent(&event) != 0){
        if(event.type == SDL_QUIT){
            m->Running = false;
        }
        if(event.type == SDL_KEYUP){
            SDL_KeyboardEvent kevent = event.key;
            switch(kevent.keysym.scancode){
                case SDL_SCANCODE_UP:
                    if(m->SelectedEntry > 0){
                        m->SelectedEntry--;
                        while(m->Entries[m->SelectedEntry].Type == MENU_TEXTBOX && m->SelectedEntry > 0)
                            m->SelectedEntry--;
                    }
                    break;

                case SDL_SCANCODE_DOWN:
                    if(m->SelectedEntry < m->EntryCount-1){
                        m->SelectedEntry++;
                        while(m->Entries[m->SelectedEntry].Type == MENU_TEXTBOX && m->SelectedEntry > 0)
                            m->SelectedEntry++;
                    }
                    break;

                case SDL_SCANCODE_RETURN:
                case SDL_SCANCODE_SPACE:
                    HandleEntryInteract(m, &m->Entries[m->SelectedEntry], 0);
                    break;

                case SDL_SCANCODE_ESCAPE:
                    m->Running = false;
                    break;

                case SDL_SCANCODE_LEFT:
                    HandleEntryInteract(m, &m->Entries[m->SelectedEntry], -SLIDER_DEFAULT_INCREMENT);
                    break;
                case SDL_SCANCODE_RIGHT:
                    HandleEntryInteract(m, &m->Entries[m->SelectedEntry], SLIDER_DEFAULT_INCREMENT);                
                default:
                    break;
            }
        }
    }
    if(m->CustomUpdate != NULL) (*m->CustomUpdate)(m);
}

void DrawMenu(Menu* m, Graphics* g){
    BeginDraw(g);
    SDL_SetRenderDrawColor(g->Renderer, 0, 0, 0, 0);
    SDL_RenderClear(g->Renderer);
    for(int i = 0; i<m->EntryCount; i++){
        DrawMenuEntry(&m->Entries[i], g, m->SelectedEntry == i);
    }
    EndDraw(g);
}

void UpdateLoop(Menu* m, Graphics* g){
    while(m->Running){
        UpdateMenu(m, 0.1);
        DrawMenu(m, g);
    }
}

void DeallocMenu(Menu* m){
    for(int i = 0; i<m->EntryCount; i++){
        DeallocateMenuEntry(&m->Entries[i]);
    }
    free(m->Entries);
    dlclose(m->Handle);
    free(m);
}
