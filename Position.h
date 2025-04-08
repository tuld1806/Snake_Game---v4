#ifndef POSITION_H
#define POSITION_H

#include "main.h"

enum Direction {
    UP = 0, DOWN, LEFT, RIGHT
};

struct Position
{
    int x, y;

    Position(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    Position move(Direction direction) const {
    	switch(direction) {
    		case UP: return Position(x, (y - 1 + BOARD_HEIGHT)%BOARD_HEIGHT );
    		case DOWN: return Position(x, (y + 1)%BOARD_HEIGHT );
    		case LEFT: return Position( (x - 1 + BOARD_WIDTH)%BOARD_WIDTH, y);
    		case RIGHT: return Position( (x + 1)%BOARD_WIDTH, y);
		}
    }

    bool operator==(Position p) const {
        return x == p.x && y == p.y;
    }
};

#endif // POSITION_H
