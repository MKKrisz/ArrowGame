#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include "../../debugmalloc.h"
#include "textrenderer.h"

TTF_Font* BaseMenuFont;

void InitText(){
    TTF_Init();
    BaseMenuFont = TTF_OpenFont("Assets/font.otf", BASE_FONT_SIZE);
    //printf("%s", TTF_GetError());
}
void BlankRender(Text* text, Graphics* g){
    if(text->RenderedTexture == NULL){
        TTF_SetFontSize(text->Font, text->FontSize);
        SDL_Surface* temp = TTF_RenderText_Blended(text->Font, text->Text, text->Color);
        //printf("%s\n", SDL_GetError());
        text->RenderedTexture = SDL_CreateTextureFromSurface(g->Renderer, temp);
        SDL_QueryTexture(text->RenderedTexture, NULL, NULL, &text->DrawRect.w, &text->DrawRect.h);
        SDL_FreeSurface(temp);
    }
}

Text* CreateText(char* text, int size, Graphics* g){
    Text* op = malloc(sizeof(Text));
    op->Text = malloc((strlen(text) + 1)*sizeof(char));
    strcpy(op->Text, text);
    op->FontSize = size;
    op->Font = TTF_OpenFont("Assets/font.otf", size);
    op->Color = BASE_FONT_COLOR;
    op->RenderedTexture = NULL;
    op->DrawRect = (SDL_Rect){0, 0, 0, 0};
    BlankRender(op, g);
    return op;
}

void SetTextPos(Text* text, int x, int y){
    text->DrawRect.x = x;
    text->DrawRect.y = y;
}

void SetTextColor(Text* text, SDL_Color c){
    text->Color = c;
    SDL_DestroyTexture(text->RenderedTexture);
    text->RenderedTexture = NULL;
}
void SetTextString(Text* text, const char* str, Graphics* g){
    text->Text = realloc(text->Text, (strlen(str) + 1) * sizeof(char));
    strcpy(text->Text, str);
    text->RenderedTexture = NULL;
    BlankRender(text, g);
}

void DrawText(Text* text, Graphics* g){
    if(text->RenderedTexture == NULL){
        //TTF_SetFontSize(BaseMenuFont, text->FontSize);
        SDL_Surface* temp = TTF_RenderText_Blended(text->Font, text->Text, text->Color);
        text->RenderedTexture = SDL_CreateTextureFromSurface(g->Renderer, temp);
        SDL_QueryTexture(text->RenderedTexture, NULL, NULL, &text->DrawRect.w, &text->DrawRect.h);
        SDL_FreeSurface(temp);
    }

    SDL_RenderCopyEx(g->Renderer, text->RenderedTexture, NULL, &text->DrawRect, 0, NULL, SDL_FLIP_VERTICAL);
}

void DestroyText(Text* text){
    SDL_DestroyTexture(text->RenderedTexture);
    TTF_CloseFont(text->Font);
    free(text->Text);
    free(text);
}
