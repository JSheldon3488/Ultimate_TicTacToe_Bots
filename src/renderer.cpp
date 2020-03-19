#include "renderer.h"
#include "SDL2_gfxPrimitives.h"
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

void Renderer::Render(Board board) {
    //Rectangle used for rendering the tiles
    SDL_Rect rect;
    rect.w = tile_width;
    rect.h = tile_height;

    //Clear Screen
    SDL_SetRenderDrawColor(_renderer, 255,255,255,0xFF);
    SDL_RenderClear(_renderer);

    //Draw Grid
    for (Tile tile : board.grid) {
        SDL_SetRenderDrawColor(_renderer, 0,0,0,0xFF);
        rect.x = tile.row * rect.w;
        rect.y = tile.col * rect.h;
        SDL_RenderDrawRect(_renderer, &rect);
    }

    //Draw X's and O's
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            Tile currentPosition = board.grid[(row*3+col)];
            if (currentPosition.isOccupied) {
                //Draw X for Player1 or O for player2
                if (currentPosition.getState() == State::Player1) {
                    drawX(_renderer,row,col);
                }
                else {drawO(_renderer,row,col);}
            }
        }
    }

    //Update Window Title

    //Update Screen
    SDL_RenderPresent(_renderer);
}
void UpdateWindowTitle() {
    return;
}

void Renderer::drawX(SDL_Renderer *renderer, const int row, const int col) {
    const float topLeftY = row*tile_width + 0.25*tile_width;
    const float topLeftX = col*tile_height + 0.25*tile_height;
    const float bottomRightY = row*tile_width + 0.75*tile_width;
    const float bottomRightX = col*tile_height + 0.75*tile_height;
    const float bottomLeftY = row*tile_width + 0.25*tile_width;
    const float bottomLeftX = col*tile_height + 0.75*tile_height;
    const float topRightY = row*tile_width + 0.75*tile_width;
    const float topRightX = col*tile_height + 0.25*tile_height;
    //Draw left-top to right-bottom diagonal
    thickLineRGBA(renderer, topLeftX,topLeftY,bottomRightX,bottomRightY, 10, 250,0,0,255);
    //Draw left-bottom to right-top diagonal
    thickLineRGBA(renderer, bottomLeftX,bottomLeftY,topRightX,topRightY, 10, 255,0,0, 255);
}

void Renderer::drawO(SDL_Renderer *renderer, const int row, const int col) {
    const float radius = 0.25*tile_width;
    const float centerY = 0.5*tile_width + row*tile_width;
    const float centerX = 0.5*tile_height + col*tile_height;
    //Draw colorful outter circle
    filledCircleRGBA(renderer, centerX,centerY, radius+5, 0,255,0, 255);
    //Draw white inner circle to make appearance of O
    filledCircleRGBA(renderer, centerX,centerY, radius-5, 255,255,255, 255);
};
