#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <vector>
#include <string>
#include <SDL.h>
#include <iostream>

enum PictureID {
    CHERRY = 0, SNAKE_HEAD, SNAKE_CORNER,
    SNAKE_BODY, SNAKE_TAIL, MAP, PLAY_BUTTON, PIC_COUNT
};

void logSDLError(const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

class Graphics{

    SDL_Texture* pictures[PIC_COUNT];
    SDL_Renderer* renderer;
    SDL_Texture* loadTexture(std::string name);

public:
    Graphics(SDL_Renderer* renderer_);
    ~Graphics();

    void loadPictures();
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
};

#endif // GRAPHICS_H_INCLUDED
