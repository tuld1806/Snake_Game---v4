#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "Position.h"
#include <iostream>
#include <vector>

class Game;

struct SnakeNode{

    Position position;
    SnakeNode *next;
    Direction NodeDirection;
    SnakeNode(Position position_, SnakeNode* next_ = nullptr):position(position_), next(next_){};

};
class Snake{
    SnakeNode *head, *tail;
    Game& game;
public:
    Direction currentDirection;
    Snake(Game& game_, Position start, Direction currentDirection);
    ~Snake();
    std::vector<SnakeNode*> getNodes();
    //void snakeLeave();
    void slideTo(Position newPosition);
    void move();
    void setDirection(Direction newDirection){ currentDirection = newDirection; }
    bool canChangeDirection(Direction newDirection);
    void growUp(Position newPosition);
};
#endif // SNAKE_H_INCLUDED
