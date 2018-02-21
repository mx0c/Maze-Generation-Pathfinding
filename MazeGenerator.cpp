//
// Created by Marius on 20.02.2018.
//
#include "MazeGenerator.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

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

    this->renderer = renderer;
    this->MatrixSize = matrixSize;
}

void MazeGenerator::GenerateMaze(){
    this->currentCell = &this->matrix[0][0];
    this->currentCell->setVisited(true);
    Cell* next;
    while(true) {
        next = this->getCellNeighbour();
        if(next == NULL) {
            if(this->CellStack.size() > 0) {
                this->currentCell = this->CellStack.top();
                this->CellStack.pop();
                continue;
            }else{
                break;
            }
        }
        this->CellStack.push(currentCell);
        this->removeWalls(currentCell, next);
        currentCell = next;
        this->currentCell->setVisited(true);
    }
    this->DrawMaze({255, 255, 255, 0});
}

void MazeGenerator::DrawMaze(SDL_Color color){
    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
    // Clear winow
    SDL_RenderClear(this->renderer);

    for(int x = 0; x < this->MatrixSize; x++) {
        for (int y = 0; y < this->MatrixSize; y++) {
            this->matrix[x][y].drawCell(color);
        }
    }
}

Cell* MazeGenerator::getCellNeighbour(){
    int x,y;
    std::tie(x, y) = this->currentCell->getIndex();
    vector<Cell*> neighbours;

    //srand (time(NULL));
    int neighbourCount = 0;

    //Top Neighbour
    if(y != 0 && !this->matrix[x][y-1].getVisited()){
        neighbours.push_back(&this->matrix[x][y-1]);
        neighbourCount++;
    }
    //Bottom Neighbour
    if(y != this->MatrixSize-1 && !this->matrix[x][y+1].getVisited()){
        neighbours.push_back(&this->matrix[x][y+1]);
        neighbourCount++;
    }
    //Left Neighbour
    if(x != 0 && !this->matrix[x-1][y].getVisited()){
        neighbours.push_back(&this->matrix[x-1][y]);
        neighbourCount++;
    }
    //Right Neighbour
    if(x != this->MatrixSize-1 && !this->matrix[x+1][y].getVisited()){
        neighbours.push_back(&this->matrix[x+1][y]);
        neighbourCount++;
    }

    if(neighbourCount == 0)
        return NULL;

    //generate random index
    int randIndex = rand() % neighbourCount;
    //return random unvisited neighbour
    return neighbours.at(randIndex);
}

void MazeGenerator::removeWalls(Cell* a, Cell* b) {
    //get indices
    int ax,ay;
    std::tie(ax, ay)= a->getIndex();
    int bx,by;
    std::tie(bx, by)= b->getIndex();

    //calculate delta
    int deltaX = ax - bx;
    int deltaY = ay - by;

    //remove x walls
    if(deltaX == 1){
        a->walls["left"] = false;
        b->walls["right"] = false;
    }else if(deltaX == -1){
        a->walls["right"] = false;
        b->walls["left"] = false;
    }

    //remove y walls
    if(deltaY == 1){
        a->walls["top"] = false;
        b->walls["bottom"] = false;
    }else if(deltaY == -1){
        a->walls["bottom"] = false;
        b->walls["top"] = false;
    }
}