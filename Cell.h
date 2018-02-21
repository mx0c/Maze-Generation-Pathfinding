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
    public:
        map<string,bool> walls;
        int x;
        int y;
        int scale;
        bool visited;
        SDL_Renderer* renderer;

        Cell();
        void drawCell(SDL_Color color);
        void setCell(int x, int y, int scale, SDL_Renderer* renderer);
        void setVisited(bool visited);
        tuple<int, int> getIndex();
        bool getVisited();
};

#endif //SDL_DEMO_RECT_H
