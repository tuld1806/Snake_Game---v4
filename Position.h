#ifndef POSITION_H
#define POSITION_H

#include "main.h"

enum Direction {
    RIGHT = 0, UP, LEFT, DOWN
};

struct Position
{
    int x, y;

    Position(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    Position move(Direction direction) const {
    	switch(direction) {
    		case UP: return Position(x, y - 1 );
    		case DOWN: return Position(x, y + 1);
    		case LEFT: return Position( x - 1, y);
    		case RIGHT: return Position( x + 1, y);
		}
    }

    bool operator==(Position p) const {
        return x == p.x && y == p.y;
    }

    Position operator - (Position p) const {
        return Position(x - p.x, y - p.y);
    }
};

#endif // POSITION_H
