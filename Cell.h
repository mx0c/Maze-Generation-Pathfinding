//
// Created by Marius on 19.02.2018.
//

#ifndef SDL_DEMO_RECT_H
#define SDL_DEMO_RECT_H

#include "include/SDL2/SDL.h"
#include <map>
#include <string>

using namespace std;

class Cell{
    private:
        map<string,bool> walls;
        int x;
        int y;
        int scale;
        SDL_Renderer* renderer;
    public:
        Cell();
        Cell(int x, int y, int scale, SDL_Renderer* renderer);
        void drawCell(SDL_Color color);
        void setCell(int x, int y, int scale, SDL_Renderer* renderer);
};

#endif //SDL_DEMO_RECT_H
