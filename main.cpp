#include "Graphics.h"
#include <cmath>
#include "Process.h"

void renderSplashScreen();
void renderGameplay(SDL_Renderer* renderer);
void pauseProcess(SDL_Event* e);
bool pauseState = false;
Graphics* graphics = nullptr; // global picture manager
Game game(BOARD_WIDTH, BOARD_HEIGHT);
SDL_Rect playGrid = {385, 250, 150, 54};
int main(int argc, char* argv[]){

    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    graphics = new Graphics(renderer);
    SDL_Event e;
    renderSplashScreen();
    auto start = CLOCK_NOW();

    renderGameplay(renderer);
    while (true) {
        while (SDL_PollEvent(&e)) {

            pauseProcess(&e);
            if(!pauseState)game.interpretEvent(e);
        }

        if(!pauseState){

            auto end = CLOCK_NOW();
            ElapsedTime elapsed = end-start;
            if (elapsed.count() > STEP_DELAY) {
                game.processInput();
                if(game.getStatus() == GAME_OVER)break;
                renderGameplay(renderer);
                start = end;
            }
            SDL_Delay(1);
        }
        else {
            renderGameplay(renderer);
            /*for(int j = 0; j< BOARD_HEIGHT; j++){
                for(int i = 0; i< BOARD_WIDTH; i++)
                    std::cout<<game.getCellType(Position(i, j))<<' ';
                std::cout<<std::endl;
            }
            std::cout<<std::endl;
            SDL_Delay(100);*/
        }

    }

    delete graphics;
    quitSDL(window, renderer);
    return 0;
}
void drawCell(SDL_Renderer* renderer, SDL_Texture* texture, Position pos, Direction dir)
{
	SDL_Rect cell;
	cell.x = pos.x * CELL_SIZE;
	cell.y = pos.y * CELL_SIZE;
	cell.w = CELL_SIZE;
	cell.h = CELL_SIZE;
	//SDL_RenderCopyEx(renderer, texture, NULL, &cell);
	double angle;
	switch(dir){
        case UP: angle = 270; break;
        case DOWN: angle = 90; break;
        case LEFT: angle = 180; break;
        default: angle = 0;
	}
    SDL_RenderCopyEx(renderer, texture, NULL, &cell, angle, NULL, SDL_FLIP_NONE);
}
Direction rotation(Position low, Position high, Position c){
    Position tmp = low - c;

    if(tmp == Position(0, -1)){
        tmp = high - c;
        if(tmp == Position(-1, 0))
            return RIGHT;
        return DOWN;
    }
    else if(tmp == Position(1, 0)){
        tmp = high - c;
        if(tmp == Position(0, 1))return LEFT;
    }
    return UP;
}
void drawSnake(SDL_Renderer* renderer, std::vector<SnakeNode*> nodes ){
    int length = nodes.size();
    drawCell(renderer, graphics->getImage(SNAKE_HEAD), nodes[length - 1]->position,
             nodes[length - 1]->NodeDirection);
    Position prevPos = nodes[length - 1]->position, nextPos;

    //through head to tail
    for(int i = length - 2; i >= 1; i--){
        nextPos = nodes[i - 1]->position;
        if(nextPos.x == prevPos.x || nextPos.y == prevPos.y){
            drawCell(renderer, graphics->getImage(SNAKE_BODY), nodes[i]->position, nodes[i]->NodeDirection);
        }

        else {
            if(nextPos.y > prevPos.y)std::swap(nextPos, prevPos);
            //prevPos is always higher
            drawCell(renderer, graphics->getImage(SNAKE_CORNER), nodes[i]->position,
                 rotation(nextPos, prevPos, nodes[i]->position) );


        }
        prevPos = nodes[i]->position;
    }
    drawCell(renderer, graphics->getImage(SNAKE_TAIL), nodes[0]->position, nodes[1]->NodeDirection);

}

void drawCherry(SDL_Renderer* renderer, Position pos){
    drawCell(renderer, graphics->getImage(CHERRY), pos, RIGHT);
}
void renderSplashScreen(){
    std::cout << "Press any key to start game." << std::endl;
    std::cout << "Press space to pause game or continue." << std::endl;

    waitUntilKeyPressed();
}

void renderGameplay(SDL_Renderer* renderer){

    SDL_RenderCopy(renderer, graphics->getImage(MAP), NULL, NULL);
    drawSnake(renderer, game.snake.getNodes());
    drawCherry(renderer, game.cherry.getPos());
    if(pauseState)
        SDL_RenderCopy(renderer, graphics->getImage(PLAY_BUTTON), nullptr, &playGrid);
    SDL_RenderPresent(renderer);
}

void pauseProcess(SDL_Event* e){
    if(e->type == SDL_KEYDOWN)
        if(e->key.keysym.sym == SDLK_SPACE)pauseState = !pauseState;
}
