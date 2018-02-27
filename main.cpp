#include <iostream>

#include "include/SDL2/SDL.h"
#include "MazeGenerator.h"
#include "MazeSolver.h"

#define WIN_HEIGHT 900
#define WIN_WIDTH 900

using namespace std;

int main (int argc, char** argv)
{
    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "MazeSolver", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIN_HEIGHT,
        WIN_WIDTH,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0);

    // Clear winow
    SDL_RenderClear( renderer );

    MazeGenerator* generator = new MazeGenerator(75, WIN_WIDTH, WIN_HEIGHT, renderer);
    generator->GenerateMaze();
    generator->pickRandomStartEnd();

    MazeSolver* solver = new MazeSolver(generator,renderer);
    while(!solver->astar_solve()){
        generator->DrawMaze({255,255,255,0});
        generator->pickRandomStartEnd();
    }

    //gameLoop
    SDL_Event e;
    while( SDL_WaitEvent(&e) )
    {
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT) break;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}