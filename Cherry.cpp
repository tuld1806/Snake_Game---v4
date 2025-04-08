#include "Cherry.h"
#include <cstdlib>
#include "Process.h"
#include "main.h"

void Cherry::addCherry(){
    srand(time(0));
    Position p;
    do{
        p = (rand() % BOARD_WIDTH, rand() % BOARD_HEIGHT);
    }while(game.getCellType(p) != CELL_EMPTY);
    cherryPos = p;
    game.setCellType(p, CELL_CHERRY);
}
