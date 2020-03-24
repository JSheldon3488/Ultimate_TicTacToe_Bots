#include "renderer.h"
#include "SDL2_gfxPrimitives.h"
#include <iostream>


Color::Color(int r, int g, int b) : r(r), g(g), b(b) {}


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

void Renderer::Render(const UltimateBoard &ultimateBoard, bool gameOver, State winner) {
    //Rectangle used for rendering the tiles
    SDL_Rect rect;

    //Clear Screen
    SDL_SetRenderDrawColor(_renderer, background_color.r, background_color.g, background_color.b, 255);
    SDL_RenderClear(_renderer);

    //Draw Grid
    for (Board board : ultimateBoard.boards) {
        for (Tile tile : board.grid) {
            rect.x = board.col*3*tile_width + tile.col*tile_width + board.col*20;
            rect.y = board.row*3*tile_height + tile.row*tile_height + board.row*20;
            rect.w = tile_width;
            rect.h = tile_height;

            // Set correct background color for the board
            if (board.winner == State::Player1) { SDL_SetRenderDrawColor(_renderer, xWin_color.r, xWin_color.g, xWin_color.b, 255);}
            else if (board.winner == State::Player2) {SDL_SetRenderDrawColor(_renderer, oWin_color.r, oWin_color.g, oWin_color.b, 255);}
            else if (!board.isActive) {SDL_SetRenderDrawColor(_renderer, inValid_color.r, inValid_color.g, inValid_color.b, 255);}
            else { SDL_SetRenderDrawColor(_renderer, tile_color.r, tile_color.g, tile_color.b, 255); }
            
            //Draw tile
            SDL_RenderFillRect(_renderer, &rect);
            SDL_SetRenderDrawColor(_renderer, tile_border.r, tile_border.g, tile_border.b, 255);
            SDL_RenderDrawRect(_renderer, &rect);
        }
    }
    
    //Draw X's and O's
    for (Board board : ultimateBoard.boards) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                Tile currentPosition = board.grid[(row*3+col)];
                if (currentPosition.isOccupied) {
                    //Draw X for Player1 or O for player2
                    if (currentPosition.getState() == State::Player1) {
                        drawX(_renderer, board.row, board.col, row,col);
                    }
                    else {drawO(_renderer, board.row, board.col, board.isActive, board.winner, row,col);}
                }
            }
        }
    }

    //Update Window Title
    UpdateWindowTitle(ultimateBoard.currentPlayer, gameOver, winner);

    //Update Screen
    SDL_RenderPresent(_renderer);
}


void Renderer::UpdateWindowTitle(State player, bool gameOver, State winner) {
    std::string title;
    if (!gameOver) {
        title = player == State::Player1 ? "Player X Turn" : "Player 0 Turn";
    }
    else {
        if (winner == State::Empty) {
            title = "Game ended in a DRAW";
        }
        else { title = player == State::Player1 ? "Player O WINS!!!" : "Player X WINS!!!"; }
    }
    SDL_SetWindowTitle(_window, title.c_str());
}


void Renderer::drawX(SDL_Renderer *renderer, const int board_row, const int board_col, const int row, const int col) {
    //Calculate all the coordinates needed
    const float topLeftY = row*tile_height + 0.25*tile_height + board_row*20 + 3*board_row*tile_height;
    const float topLeftX = col*tile_width + 0.25*tile_width + board_col*20 + 3*board_col*tile_width;
    const float bottomRightY = row*tile_height + 0.75*tile_height + board_row*20 + 3*board_row*tile_height;
    const float bottomRightX = col*tile_width + 0.75*tile_width + board_col*20 + 3*board_col*tile_width;
    const float bottomLeftY = row*tile_height + 0.25*tile_height + board_row*20 + 3*board_row*tile_height;
    const float bottomLeftX = col*tile_width + 0.75*tile_width + board_col*20 + 3*board_col*tile_width;
    const float topRightY = row*tile_height + 0.75*tile_height + board_row*20 + 3*board_row*tile_height;
    const float topRightX = col*tile_width + 0.25*tile_width + board_col*20 + 3*board_col*tile_width;
    
    //Draw left-top to right-bottom diagonal
    thickLineRGBA(renderer, topLeftX,topLeftY,bottomRightX,bottomRightY, x_color.r, x_color.g, x_color.b ,0,255);
    //Draw left-bottom to right-top diagonal
    thickLineRGBA(renderer, bottomLeftX,bottomLeftY,topRightX,topRightY, x_color.r, x_color.g, x_color.b ,0, 255);
}


void Renderer::drawO(SDL_Renderer *renderer, const int board_row, const int board_col, const bool active, State winner, const int row, const int col) {
    //Calculate all the coordinates needed
    const float radius = 0.25*tile_width;
    const float centerY = 0.5*tile_height + row*tile_height + board_row*20 + 3*board_row*tile_height;
    const float centerX = 0.5*tile_width + col*tile_width + board_col*20 + 3*board_col*tile_width;
    
    //Draw colorful outter circle
    filledCircleRGBA(renderer, centerX,centerY, radius+5, o_color.r, o_color.g, o_color.b, 255);
    
    //Draw inner circle to make appearance of O (depends on what the tile background is at this state in game)
    if (active) { 
        filledCircleRGBA(renderer, centerX,centerY, radius-5, tile_color.r, tile_color.g, tile_color.b, 255);
    }
    else if (winner == State::Player1) {
        filledCircleRGBA(renderer, centerX,centerY, radius-5, xWin_color.r, xWin_color.g, xWin_color.b, 255);
    }
    else if (winner == State::Player2) {
        filledCircleRGBA(renderer, centerX,centerY, radius-5, oWin_color.r, oWin_color.g, oWin_color.b, 255);
    }
    else { filledCircleRGBA(renderer, centerX,centerY, radius-5, inValid_color.r, inValid_color.g, inValid_color.b, 255); }
};