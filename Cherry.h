#ifndef CHERRY_H_INCLUDED
#define CHERRY_H_INCLUDED
#include "Position.h"

enum CherryStatus{
    SMALL1 = 0, SMALL2, SMALL3, SMALL4, BIG
};
class Cherry{
    Position cherryPos;
    CherryStatus status;
public:
    Position addCherry(int width_, int height_);
    void changeStatus();
    Cherry(CherryStatus status_):status(status_){};
    Position getPos()const {return cherryPos;}
};
#endif // CHERRY_H_INCLUDED
