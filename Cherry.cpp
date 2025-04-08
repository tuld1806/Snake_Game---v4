#include "Cherry.h"
#include <cstdlib>
#include "Process.h"
#include "main.h"

void Cherry::addCherry(){
    srand(time(0));
    Position p;
    do{
        p.x = rand() % BOARD_WIDTH;
        p.y = rand() % BOARD_HEIGHT;
    }while(game.getCellType(p) != CELL_EMPTY);
    cherryPos = p;
    game.setCellType(p, CELL_CHERRY);
}

Cherry::~Cherry(){
    status = SMALL1;
}
