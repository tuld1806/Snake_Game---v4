#ifndef CHERRY_H_INCLUDED
#define CHERRY_H_INCLUDED
#include "Position.h"

class Game;
enum CherryStatus{
    SMALL1 = 0, SMALL2, SMALL3, SMALL4, BIG
};
class Cherry{
    Position cherryPos;
    CherryStatus status;
    Game& game;
public:
    void addCherry();
    void changeStatus();
    Cherry(CherryStatus status_, Game& game_):status(status_), game(game_){};
    Position getPos()const {return cherryPos;}
};
#endif // CHERRY_H_INCLUDED
