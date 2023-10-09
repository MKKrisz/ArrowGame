#include "textrenderer.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>



TTF_Font* BaseMenuFont;

void InitText(){
    TTF_Init();
    BaseMenuFont = TTF_OpenFont("Assets/ConnectionIi-2wj8.otf", BASE_FONT_SIZE);
}

Text* CreateText(char* text, int size){
    Text* op = malloc(sizeof(Text));
    op->Text = text;
    op->FontSize = size;
    op->Color = BASE_FONT_COLOR;
    op->RenderedTexture = NULL;
    op->DrawRect = (SDL_Rect){0, 0, 0, 0};
    return op;
}

void SetTextPos(Text* text, int x, int y){
    text->DrawRect.x = x;
    text->DrawRect.y = y;
}

void SetTextColor(Text* text, SDL_Color c){
    text->Color = c;
}

void DrawText(Text* text, Graphics* g){
    if(text->RenderedTexture == NULL){
        TTF_SetFontSize(BaseMenuFont, text->FontSize);
        SDL_Surface* temp = TTF_RenderText_Blended(BaseMenuFont, text->Text, text->Color);
        text->RenderedTexture = SDL_CreateTextureFromSurface(g->Renderer, temp);
        SDL_QueryTexture(text->RenderedTexture, NULL, NULL, &text->DrawRect.w, &text->DrawRect.h);
        SDL_FreeSurface(temp);
    }

    SDL_RenderCopyEx(g->Renderer, text->RenderedTexture, NULL, &text->DrawRect, 0, NULL, SDL_FLIP_VERTICAL);
}

void DestroyText(Text* text){
    SDL_DestroyTexture(text->RenderedTexture);
    free(text);
}
