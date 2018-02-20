//
// Created by Marius on 19.02.2018.
//

#ifndef SDL_DEMO_RECT_H
#define SDL_DEMO_RECT_H

#include "include/SDL2/SDL.h"

class Rect{
    private:
        SDL_Rect* rect;
        SDL_Renderer* renderer;
    public:
        Rect();
        Rect(int x, int y, int width, int height, SDL_Renderer* renderer);
        void drawRect(SDL_Color color);
        void setRect(int x, int y, int width, int height, SDL_Renderer* renderer);
};

#endif //SDL_DEMO_RECT_H
