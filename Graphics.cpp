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

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        logSDLError( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
        Mix_GetError() );
    }

}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
    Mix_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

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
    eat_sound = loadSound("assets\\eat_cherry.wav");
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

    pictures[CHERRY] = loadTexture("assets\\cherry.png");
    pictures[SNAKE_HEAD] = loadTexture("assets\\snake_head.png");
    pictures[SNAKE_CORNER] = loadTexture("assets\\corner.png");
    pictures[SNAKE_BODY] = loadTexture("assets\\body.png");
    pictures[SNAKE_TAIL] = loadTexture("assets\\tail.png");
    pictures[MAP] = loadTexture("assets\\map.jpg");
    pictures[PLAY_BUTTON] = loadTexture("assets\\play_button.png");
    pictures[ENDING] = loadTexture("assets\\game_over.png");
}

Mix_Music* Graphics::loadMusic(const char* path){
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,
            "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}

void Graphics::play(Mix_Music *gMusic){
    if (gMusic == nullptr) return;
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic( gMusic, -1 );
    }
    else if( Mix_PausedMusic() == 1 ) {
        Mix_ResumeMusic();
    }
}

Mix_Chunk* Graphics::loadSound(const char* path) {
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,SDL_LOG_PRIORITY_ERROR,"Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
}
void Graphics::play(Mix_Chunk* gChunk) {
    if (gChunk != nullptr) {
        Mix_PlayChannel( -1, gChunk, 0 );
    }
}

