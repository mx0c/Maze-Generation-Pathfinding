//
// Created by Marius on 20.02.2018.
//
#include "MazeGenerator.h"
#include <iostream>

MazeGenerator::MazeGenerator(int matrixSize, int windowWidth, int windowHeight, SDL_Renderer* renderer) {
    //alloc 2D Array
    this->matrix = new Cell*[matrixSize];
    for(int i = 0; i < matrixSize; ++i) {
        this->matrix[i] = new Cell[matrixSize];
    }

    //init 2D Array
    for(int x = 0; x < matrixSize; x++) {
        for (int y = 0; y < matrixSize; y++) {
            int wScale = windowWidth/matrixSize;
            int hScale = windowHeight/matrixSize;
            int xPos = x*wScale;
            int yPos = y*hScale;
            this->matrix[x][y].setCell(xPos, yPos, hScale, renderer);
        }
    }

    this->MatrixSize = matrixSize;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
}

void MazeGenerator::GenerateMaze(){

}

void MazeGenerator::DrawMaze(SDL_Color color){
    for(int x = 0; x < this->MatrixSize; x++) {
        for (int y = 0; y < this->MatrixSize; y++) {
            this->matrix[x][y].drawCell(color);
        }
    }
}