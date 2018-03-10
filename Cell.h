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
        bool visited;
        SDL_Renderer* renderer;
    public:
        int f;
        int h;
        int g;
        Cell* cameFrom;
        bool highlighted;
        Cell();
        void drawCell(SDL_Color color);
        tuple<int, int> getIndex();
        bool getVisited();
        int getX();
        int getY();
        void setX(int x);
        void setY(int y);
        int getScale();
        void setCell(int x, int y, int scale, SDL_Renderer* renderer);
        void setWalls(string wall, bool value);
        void setVisited(bool visited);
        map<string,bool> getWalls();
        void highlight(SDL_Color clr);
};

#endif //SDL_DEMO_RECT_H
