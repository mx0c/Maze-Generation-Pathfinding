//
// Created by Marius on 20.02.2018.
//

#ifndef MAZESOLVER_MAZEGENERATOR_H
#define MAZESOLVER_MAZEGENERATOR_H

#include "Cell.h"
#include <array>
#include <stack>

class MazeGenerator{
    private:
        Cell** matrix;
        Cell* currentCell;
        Cell* start;
        Cell* end;
        int MatrixSize;
        stack<Cell*> CellStack;
        SDL_Renderer* renderer;
        int scale;
    public:
        MazeGenerator(int matrixSize, int windowWidth, int windowHeight, SDL_Renderer* renderer);
        void GenerateMaze();
        void DrawMaze(SDL_Color color);
        void removeWalls(Cell* current, Cell* next);
        void pickRandomStartEnd();
        Cell* getCellNeighbour();
        Cell** getMatrix();
        int getSize();
        Cell* getStart();
        Cell* getEnd();
        int getScale();
        void destroy();
};
#endif //MAZESOLVER_MAZEGENERATOR_H
