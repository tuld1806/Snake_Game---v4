#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <chrono>
#include <ctime>
#include <SDL.h>

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Snake Game";

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;
const int CELL_SIZE = 30;

const double STEP_DELAY = 0.14;
#define CLOCK_NOW std::chrono::system_clock::now
typedef std::chrono::duration<double> ElapsedTime;

#endif // MAIN_H_INCLUDED
