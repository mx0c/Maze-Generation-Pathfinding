//
// Created by Marius on 19.02.2018.
//

#include "Cell.h"

Cell::Cell(){
    this->walls["right"] = true;
    this->walls["left"] = true;
    this->walls["top"] = true;
    this->walls["bottom"] = true;
    this->visited = false;
    this->f = 0;
    this->h = 0;
    this->g = 0;
    this->cameFrom = nullptr;
    this->highlighted = false;
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

void Cell::setWalls(string wall, bool value) {
    this->walls[wall] = value;
}

int Cell::getX(){
    return this->x;
}

int Cell::getY(){
    return this->y;
}

int Cell::getScale(){
    return this->scale;
}

map<string,bool> Cell::getWalls(){
    return this->walls;
}

void Cell::highlight(SDL_Color clr){
    SDL_Rect r;
    r.x = this->getX();
    r.y = this->getY();
    r.w = this->getScale();
    r.h = this->getScale();

    // Set render color
    SDL_SetRenderDrawColor( this->renderer, clr.r, clr.g, clr.b, clr.a);

    // Render rect
    SDL_RenderFillRect( this->renderer, &r );

    // Render the rect to the screen
    SDL_RenderPresent(this->renderer);

    //redraw Cell
    this->drawCell({255,255,255,255});
}
