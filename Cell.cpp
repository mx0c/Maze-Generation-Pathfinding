//
// Created by Marius on 19.02.2018.
//

#include "Cell.h"
#include <tuple>

Cell::Cell(){
    this->walls["right"] = true;
    this->walls["left"] = true;
    this->walls["top"] = true;
    this->walls["bottom"] = true;
    this->visited = false;
}

void Cell::drawCell(SDL_Color color) {
    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(this->renderer, color.r ,color.g, color.b, color.a);

    if(this->walls["right"]){
        SDL_RenderDrawLine(this->renderer, x+scale, y, x+scale, y+scale);
    }
    if(this->walls["left"]){
        SDL_RenderDrawLine(this->renderer, x, y, x, y+scale);
    }
    if(this->walls["top"]){
        SDL_RenderDrawLine(this->renderer, x, y, x+scale, y);
    }
    if(this->walls["bottom"]){
        SDL_RenderDrawLine(this->renderer, x, y+scale, x+scale, y+scale);
    }

    // Render the walls to the screen
    SDL_RenderPresent(this->renderer);
}

void Cell::setCell(int x, int y, int scale, SDL_Renderer *renderer) {
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->renderer = renderer;
}

void Cell::setVisited(bool visited){
    this->visited = visited;
}

std::tuple<int, int> Cell::getIndex(){
    int x = this->x / this->scale;
    int y = this->y / this->scale;
    return std::make_tuple(x, y);
}

bool Cell::getVisited(){
    return this->visited;
}