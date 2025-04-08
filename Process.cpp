#include "Process.h"

Game::Game(int width_, int height_):
    snake(*this, Position(width_/2, height_/2), RIGHT),
    box(width_, std::vector<CellType>(height_, CELL_EMPTY)),
    cherry(SMALL1), status(GAME_RUNNING),
    score(0){
    box[0][0] = CELL_CHERRY;
    box[width_/2][height_/2] = CELL_SNAKE;
}
void Game::interpretEvent(SDL_Event e){
    if(e.type == SDL_KEYUP){
        switch(e.key.keysym.sym){
            case SDLK_UP: inputQueue.push(UP); break;
            case SDLK_DOWN: inputQueue.push(DOWN); break;
            case SDLK_RIGHT: inputQueue.push(RIGHT); break;
            case SDLK_LEFT: inputQueue.push(LEFT); break;
        }
    }
}

void Game::processColision(Position pos, Position prevPos){
    switch(box[pos.x][pos.y]){
        //case CELL_SNAKE: status = GAME_OVER; break;
        //case CELL_CHERRY: setCellType(pos, CELL_SNAKE); setCellType(prevPos, CELL_EMPTY); break;
        case CELL_CHERRY: status = GAME_OVER; break;
        default: setCellType(pos, CELL_SNAKE); setCellType(prevPos, CELL_EMPTY);break;
    }
}

void Game::processInput(){
    Direction nextDirection;
    Position prevPos;
    while(!inputQueue.empty()){
        nextDirection = inputQueue.front();
        if(snake.canChangeDirection(nextDirection))snake.setDirection(nextDirection);
        inputQueue.pop();
        break;
    }

    prevPos = snake.getNode()->position;
    snake.move();
    processColision(snake.getNode()->position, prevPos);
}

void Game::setCellType(Position p, CellType cellType){
    box[p.x][p.y] = cellType;
}

void Game::setStatus(GameStatus status_){
    status = status_;
}
