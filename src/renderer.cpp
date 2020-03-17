#include "renderer.h"
#include <iostream>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height, 
                   const std::size_t tile_width, 
                   const std::size_t tile_height) : screen_width(screen_width), screen_height(screen_height), 
                                                    tile_height(tile_height), tile_width(tile_width) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize." << std::endl;
        std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
    }
    // Create Window
    _window = SDL_CreateWindow("Ultimate Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                        screen_width, screen_height, SDL_WINDOW_SHOWN);
    if (nullptr == _window) {
        std::cerr << "Window could not be created." << std::endl;
        std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
    }
    // Create Renderer
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == _renderer) {
        std::cerr << "Renderer could not be created." << std::endl;
        std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Renderer::Render(std::vector<std::string> board) {
    //Clear Screen
    SDL_SetRenderDrawColor(_renderer, 255,255,255,0xFF);
    SDL_RenderClear(_renderer);

    //Draw Grid

    //Draw X's and O's

    //Update Window Title

    //Update Screen
    SDL_RenderPresent(_renderer);
}
void UpdateWindowTitle() {
    return;
}