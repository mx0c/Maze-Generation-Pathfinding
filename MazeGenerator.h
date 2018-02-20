//
// Created by Marius on 20.02.2018.
//

#ifndef MAZESOLVER_MAZEGENERATOR_H
#define MAZESOLVER_MAZEGENERATOR_H
#include "Rect.h"
#include <array>

class MazeGenerator{
public:
        Rect** matrix;
        int MatrixSize;
        int windowWidth;
        int windowHeight;
        MazeGenerator(int matrixSize, int windowWidth, int windowHeight, SDL_Renderer* renderer);
        void GenerateMaze();
        void DrawMaze(SDL_Color color);
};
#endif //MAZESOLVER_MAZEGENERATOR_H
