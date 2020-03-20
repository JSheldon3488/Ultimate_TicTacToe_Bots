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

void Renderer::Render(const UltimateBoard &boards) {
    //Rectangle used for rendering the tiles
    SDL_Rect rect;

    //Clear Screen
    SDL_SetRenderDrawColor(_renderer, 162,181,205 ,255);
    SDL_RenderClear(_renderer);

    //Draw Grid
    for (Board board : boards.boards) {
        for (Tile tile : board.grid) {
            rect.x = board.col*3*tile_width + tile.col*tile_width + board.col*20;
            rect.y = board.row*3*tile_height + tile.row*tile_height + board.row*20;
            rect.w = tile_width;
            rect.h = tile_height;
            if (board.isActive) { SDL_SetRenderDrawColor(_renderer, 255,255,255,255);}
            else { SDL_SetRenderDrawColor(_renderer, 105,105,105,255); }
            SDL_RenderFillRect(_renderer, &rect);
            SDL_SetRenderDrawColor(_renderer, 0,0,0,255);
            SDL_RenderDrawRect(_renderer, &rect);
        }
    }
    
    //Draw X's and O's
    for (Board board : boards.boards) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                Tile currentPosition = board.grid[(row*3+col)];
                if (currentPosition.isOccupied) {
                    //Draw X for Player1 or O for player2
                    if (currentPosition.getState() == State::Player1) {
                        drawX(_renderer, board.row, board.col, row,col);
                    }
                    else {drawO(_renderer, board.row, board.col, board.isActive, row,col);}
                }
            }
        }
    }

    //Update Window Title

    //Update Screen
    SDL_RenderPresent(_renderer);
    SDL_Delay(10000);
}
void UpdateWindowTitle() {
    return;
}

void Renderer::drawX(SDL_Renderer *renderer, const int board_row, const int board_col, const int row, const int col) {
    const float topLeftY = row*tile_height + 0.25*tile_height + board_row*20 + 3*board_row*tile_height;
    const float topLeftX = col*tile_width + 0.25*tile_width + board_col*20 + 3*board_col*tile_width;
    const float bottomRightY = row*tile_height + 0.75*tile_height + board_row*20 + 3*board_row*tile_height;
    const float bottomRightX = col*tile_width + 0.75*tile_width + board_col*20 + 3*board_col*tile_width;
    const float bottomLeftY = row*tile_height + 0.25*tile_height + board_row*20 + 3*board_row*tile_height;
    const float bottomLeftX = col*tile_width + 0.75*tile_width + board_col*20 + 3*board_col*tile_width;
    const float topRightY = row*tile_height + 0.75*tile_height + board_row*20 + 3*board_row*tile_height;
    const float topRightX = col*tile_width + 0.25*tile_width + board_col*20 + 3*board_col*tile_width;
    //Draw left-top to right-bottom diagonal
    thickLineRGBA(renderer, topLeftX,topLeftY,bottomRightX,bottomRightY, 10, 250,0,0,255);
    //Draw left-bottom to right-top diagonal
    thickLineRGBA(renderer, bottomLeftX,bottomLeftY,topRightX,topRightY, 10, 255,0,0, 255);
}

void Renderer::drawO(SDL_Renderer *renderer, const int board_row, const int board_col, const bool active, const int row, const int col) {
    const float radius = 0.25*tile_width;
    const float centerY = 0.5*tile_height + row*tile_height + board_row*20 + 3*board_row*tile_height;
    const float centerX = 0.5*tile_width + col*tile_width + board_col*20 + 3*board_col*tile_width;
    //Draw colorful outter circle
    filledCircleRGBA(renderer, centerX,centerY, radius+5, 0,255,0, 255);
    //Draw inner circle to make appearance of O
    if (active) { 
        filledCircleRGBA(renderer, centerX,centerY, radius-5, 255,255,255, 255);
    }
    else { filledCircleRGBA(renderer, centerX,centerY, radius-5, 105,105,105, 255); }
};
