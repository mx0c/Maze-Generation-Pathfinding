//
// Created by Marius on 19.02.2018.
//

#include "Rect.h"

Rect::Rect(int x, int y, int width, int height, SDL_Renderer* renderer) {
    this->rect = new SDL_Rect();
    this->rect->x = x;
    this->rect->y = y;
    this->rect->w = width;
    this->rect->h = height;
    this->renderer = renderer;
}

Rect::Rect(){
    this->rect = new SDL_Rect();
    this->rect->x = 0;
    this->rect->y = 0;
    this->rect->w = 0;
    this->rect->h = 0;
    this->renderer = nullptr;
}

void Rect::drawRect(SDL_Color color) {
    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(this->renderer, color.r ,color.g, color.b, color.a);

    // Render rect
    SDL_RenderFillRect(this->renderer, this->rect);

    // Render the rect to the screen
    SDL_RenderPresent(this->renderer);
}

void Rect::setRect(int x, int y, int width, int height, SDL_Renderer* renderer){
    this->rect->x = x;
    this->rect->y = y;
    this->rect->w = width;
    this->rect->h = height;
    this->renderer = renderer;
}