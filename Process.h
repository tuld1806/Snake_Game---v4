#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include "Snake.h"
#include "Cherry.h"
#include <queue>

enum CellType{
    CELL_EMPTY = 0, CELL_SNAKE, CELL_CHERRY
};
enum GameStatus{
    GAME_RUNNING = 0, GAME_OVER
};
class Game{

    std::vector< std::vector<CellType> > box;
    GameStatus status;
public:
    Snake snake;
    Cherry cherry;
    std:: queue<Direction> inputQueue;
    int isEaten;
    int pts;

    Game(int width_, int height_);
    ~Game();
    void interpretEvent(SDL_Event e);
    void processInput();

    CellType getCellType(Position p)const{ return box[p.x][p.y]; }
    void setCellType(Position p, CellType cellType);
    void processColision(Position pos);
    GameStatus getStatus()const { return status ;}
    void setStatus(GameStatus status_);
};

#endif // PROCESS_H_INCLUDED
