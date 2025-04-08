#include "Graphics.h"
#include <SDL_image.h>

void logSDLError(const std::string &msg, bool fatal){
    std::cout << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int screenWidth, int screenHeight, const char* windowTitle){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError("SDL_Init", true);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError("CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError("CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

#include <SDL.h>

void waitUntilClick(SDL_Rect rect) {
    SDL_Event event;
    bool waiting = true;

    while (waiting) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                waiting = false;
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                if (mouseX >= rect.x && mouseX <= rect.x + rect.w &&
                    mouseY >= rect.y && mouseY <= rect.y + rect.h) {
                    waiting = false;
                }
            }
        }
    }
}

Graphics::Graphics(SDL_Renderer* renderer_) : renderer(renderer_){
    loadPictures();
}

Graphics::~Graphics(){
    for (SDL_Texture* texture : pictures)
        SDL_DestroyTexture(texture);
}

SDL_Texture* Graphics::loadTexture(std::string name ){
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( name.c_str() );
    if ( loadedSurface == nullptr )
        logSDLError("Unable to load image " + name + " SDL_image Error: " + IMG_GetError());
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            logSDLError("Unable to create texture from " + name + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void Graphics::loadPictures(){

    pictures[CHERRY] = loadTexture("cherry.png");
    pictures[SNAKE_HEAD] = loadTexture("snake_head.png");
    pictures[SNAKE_CORNER] = loadTexture("corner.png");
    pictures[SNAKE_BODY] = loadTexture("body.png");
    pictures[SNAKE_TAIL] = loadTexture("tail.png");
    pictures[MAP] = loadTexture("map.jpg");
    pictures[PLAY_BUTTON] = loadTexture("play_button.png");
    pictures[ENDING] = loadTexture("game_over.png");
}

