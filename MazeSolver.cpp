//
// Created by Marius on 25.02.2018.
//

#include "MazeSolver.h"
#include <algorithm>
#include <stdlib.h>
#include <math.h>

MazeSolver::MazeSolver(MazeGenerator* mgen, SDL_Renderer* r){
    this->renderer = r;
    this->scale = mgen->getScale();
    this->start = mgen->getStart();
    this->end = mgen->getEnd();
    this->matrix = mgen->getMatrix();
    this->matrixSize = mgen->getSize();
    this->debug = false;
    this->dragStart = false;
    this->dragEnd = false;
}

bool MazeSolver::astar_solve(){
    vector<Cell*> closedSet;
    vector<Cell*> openSet;
    openSet.push_back(this->start);

    //reset matrix
    for(int x=0; x < matrixSize;x++){
        for(int y=0; y < matrixSize;y++) {
            this->matrix[x][y].h = 0;
            this->matrix[x][y].f = 0;
            this->matrix[x][y].g = 0;
            this->matrix[x][y].setVisited(false);
            this->matrix[x][y].cameFrom = nullptr;
        }
    }

    while(openSet.size() > 0){
        if(this->debug) {
            for (auto cell : closedSet) {
                if (!cell->highlighted) {
                    cell->highlighted = true;
                    cell->highlight({100, 0, 0, 0});
                }
            }
            for (auto cell : openSet) {
                cell->highlight({0, 100, 0, 0});
            }
        }

        Cell* current = openSet.at(0);
        //get cell with lowest f in openSet
        for (auto n : openSet) {
            if(n->f < current->f){
                current = n;
            }
        }
        //path found when current = end
        if(current == this->end){
            //reconstruct path from linked list
            this->path.push_back(current);
            while(current->cameFrom != nullptr){
                this->path.push_back(current->cameFrom);
                current = current->cameFrom;
            }
            this->drawPath({255,0,0,0});
            return true;
        }
        //remove current from openSet
        std::vector<Cell*>::iterator pos = std::find(openSet.begin(), openSet.end(), current);
        openSet.erase(pos);
        //add current to closedSet
        closedSet.push_back(current);

        for(auto neighbour : this->getNeighbours(current)){
            if(std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end()) {
                continue;
            }
            if(!(std::find(openSet.begin(), openSet.end(), neighbour) != openSet.end())){
                openSet.push_back(neighbour);
            }

            int tempG = current->g + 1;
            if(std::find(openSet.begin(), openSet.end(), neighbour) != openSet.end()) {
                if(tempG < neighbour->g)
                    neighbour->g = tempG;
            }else{
                neighbour->g = tempG;
            }
            neighbour->h = heuristic(neighbour,this->end);
            neighbour->f = neighbour->g + neighbour->h;
            neighbour->cameFrom = current;
        }
    }
    return false;
}

std::vector<Cell*> MazeSolver::getNeighbours(Cell* current){
    std::vector<Cell*> neighbours;
    map<string,bool> walls = current->getWalls();
    int x,y;
    std::tie(x,y) = current->getIndex();

    if(current->getY() != 0 && !walls["top"]){
        neighbours.push_back(this->getCell(x,y-1));
    }
    //Bottom Neighbour
    if(current->getY() != this->matrixSize-1 && !walls["bottom"]){
        neighbours.push_back(this->getCell(x,y+1));
    }
    //Left Neighbour
    if(current->getX() != 0 && !walls["left"]){
        neighbours.push_back(this->getCell(x-1,y));
    }
    //Right Neighbour
    if(current->getX() != this->matrixSize-1 && !walls["right"]){
        neighbours.push_back(this->getCell(x+1,y));
    }
    return neighbours;
}

int MazeSolver::heuristic(Cell* start, Cell* end){
    return abs(start->getX() - end->getX()) + abs(start->getY() - end->getY());
}

void MazeSolver::drawPath(SDL_Color color) {
    if(this->path.size() <= 0){
        return;
    }

    SDL_SetRenderDrawColor(this->renderer, color.r, color.g, color.b, color.a);
    for (size_t i = 0; i < this->path.size() - 1; i++) {
        SDL_RenderDrawLine(this->renderer,
                           this->path[i]->getX() + scale / 2,
                           this->path[i]->getY() + scale / 2,
                           this->path[i + 1]->getX() + scale / 2,
                           this->path[i + 1]->getY() + scale / 2
        );
    }
    SDL_RenderPresent(this->renderer);
}

Cell* MazeSolver::getCell(int x, int y){
    return &this->matrix[x][y];
}

void MazeSolver::dragndrop(SDL_Event e){
    int x,y;
    SDL_GetMouseState(&x,&y);

    if(this->dragStart){
        x = x / scale * scale;
        y = y / scale * scale;
        Cell* oldStart = start;
        this->start = &this->matrix[x / scale][y / scale];
        if(this->start != oldStart){
            oldStart->highlight({0,0,0,255});
            this->clearPath();
            this->astar_solve();
            this->drawPath({255, 0, 0, 255});
        }
    }

    if(this->dragEnd) {
        x = x / scale * scale;
        y = y / scale * scale;
        Cell* oldEnd = end;
        this->end = &this->matrix[x / scale][y / scale];
        if (this->end != oldEnd) {
            oldEnd->highlight({0, 0, 0, 255});
            this->clearPath();
            this->astar_solve();
            this->drawPath({255, 0, 0, 255});
        }
    }

    //highlight start and end point
    this->end->highlight({255,0,0,255});
    this->start->highlight({255,0,0,255});

    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        if(this->dragStart){
            this->dragStart = false;
        }
        if(this->dragEnd){
            this->dragEnd = false;
        }
        //check if endpoint is clicked
        if(x > this->end->getX() && x < this->end->getX() + this->scale && y > this->end->getY() && y < this->end->getY() + this->scale){
            this->dragEnd = true;
        }
        //check if startpoint is clicked
        if(x > this->start->getX() && x < this->start->getX() + this->scale && y > this->start->getY() && y < this->start->getY() + this->scale){
            this->dragStart = true;
        }
    }
}

void MazeSolver::clearPath(){
    drawPath({0,0,0,255});
    this->path.clear();
}