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
}

bool MazeSolver::astar_solve(){
    vector<Cell*> closedSet;
    vector<Cell*> openSet;
    openSet.push_back(this->start);

    while(openSet.size() > 0){
        /*for(auto cell : closedSet){
            cell->highlight({100,0,0,0});
        }
        for(auto cell : openSet){
            cell->highlight({0,100,0,0});
        }*/

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
            this->drawPath({0,0,255,0});
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
    printf("no path found");
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

