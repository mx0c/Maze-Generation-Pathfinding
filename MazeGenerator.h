//
// Created by Marius on 20.02.2018.
//

#ifndef MAZESOLVER_MAZEGENERATOR_H
#define MAZESOLVER_MAZEGENERATOR_H
#include "Cell.h"
#include <array>
#include <stack>

class MazeGenerator{
public:
        Cell** matrix;
        int MatrixSize;
        Cell* currentCell;
        std::stack<Cell*> CellStack;
        SDL_Renderer* renderer;
        Cell* start;
        Cell* end;
        MazeGenerator(int matrixSize, int windowWidth, int windowHeight, SDL_Renderer* renderer);
        void GenerateMaze();
        void DrawMaze(SDL_Color color);
        Cell* getCellNeighbour();
        void removeWalls(Cell* current, Cell* next);
        void pickRandomStartEnd();
        void highlightCell(SDL_Color c, Cell* cell);
};
#endif //MAZESOLVER_MAZEGENERATOR_H
