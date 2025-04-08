#include "Snake.h"
#include "Process.h"

Snake::Snake(Game& game_, Position start, Direction initDirection): game(game_), head(new SnakeNode(start)), currentDirection(initDirection){
    //snakeMove(start);
    start.x-= 1;
    head->NodeDirection = currentDirection;
    tail = new SnakeNode(start, head);
    tail->NodeDirection = currentDirection;
}

void Snake::slideTo(Position newPosition){}
bool Snake::canChangeDirection(Direction newDirection){
    if (currentDirection == UP || currentDirection == DOWN)
        return newDirection == RIGHT || newDirection == LEFT;
    return newDirection == UP || newDirection == DOWN;
}
void Snake::move() {
    head->position = head->position.move(currentDirection);
    head->NodeDirection = currentDirection;
}
