//
// Created by Marius on 25.02.2018.
//

#ifndef MAZESOLVER_MAZESOLVER_H
#define MAZESOLVER_MAZESOLVER_H

#include <vector>
#include "Cell.h"
#include "MazeGenerator.h"

class MazeSolver {
private:
    SDL_Renderer* renderer;
    Cell* start;
    Cell* end;
    Cell** matrix;
    std::vector<Cell*> path;
    int scale;
    int matrixSize;
    bool dragStart;
    bool dragEnd;
public:
    MazeSolver(MazeGenerator* mgen, SDL_Renderer* r);
    bool astar_solve();
    void drawPath(SDL_Color color);
    vector<Cell*> getNeighbours(Cell* current);
    int heuristic(Cell* start, Cell* end);
    Cell* getCell(int x, int y);
    void dragndrop(SDL_Event e);
    void clearPath();
    bool debug;
};

#endif //MAZESOLVER_MAZESOLVER_H
