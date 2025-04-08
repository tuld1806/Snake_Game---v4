#include "Cherry.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Position Cherry::addCherry(int width_, int height_){
    Position p(rand() % width_, rand() % height_);
    return p;
}
