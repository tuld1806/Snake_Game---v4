#include "Snake.h"
#include "Process.h"

Snake::Snake(Game& game_, Position start, Direction initDirection): game(game_), head(new SnakeNode(start)), currentDirection(initDirection){
    //snakeMove(start);
    head->NodeDirection = currentDirection;
    start.x-= 1;
    SnakeNode* body = new SnakeNode(start, head);
    body->NodeDirection = currentDirection;
    start.x-= 1;
    tail = new SnakeNode(start, body);
    tail->NodeDirection = currentDirection;
}

Snake::~Snake() {

    SnakeNode* current = head;
    while (current != nullptr) {
        SnakeNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
}
std::vector<SnakeNode*> Snake::getNodes(){
    std::vector<SnakeNode*> nodes;
    for(SnakeNode* p = tail; p != nullptr; p = p->next){
        nodes.push_back(p);
    }

    return nodes;
}
void Snake::slideTo(Position newPosition){
    SnakeNode *oldTail = tail;

	tail = tail->next;
    oldTail->next = nullptr;
    oldTail->position = newPosition;
    oldTail->NodeDirection = currentDirection;
    head->next = oldTail;
    head = oldTail;
}
bool Snake::canChangeDirection(Direction newDirection){
    if (currentDirection == UP || currentDirection == DOWN)
        return newDirection == RIGHT || newDirection == LEFT;
    return newDirection == UP || newDirection == DOWN;
}

void Snake::growUp(Position newPosition){
    head->next = new SnakeNode(newPosition);
    head = head->next;
    head->NodeDirection = currentDirection;
}

void Snake::move() {
    Position newPosition = head->position.move(currentDirection);
    game.processColision(newPosition);
    if(game.isEaten == 1){
        growUp(newPosition);
    }
    else {
        game.setCellType(tail->position, CELL_EMPTY);
        slideTo(newPosition);
    }
}
