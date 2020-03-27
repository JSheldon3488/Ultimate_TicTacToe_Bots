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
        for (Tile tile : board.tiles) {
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
        for (Tile tile : board.tiles) {
            if (tile.isOccupied) {
                //Draw X for Player1 or O for player2
                if (tile.getState() == State::Player1) {
                    drawX(_renderer, board, tile);
                }
                else { drawO(_renderer, board, tile, ultimateBoard.last_CPU_move); }
            }
        }
    }

    drawBoardWinners(_renderer, ultimateBoard);
    UpdateWindowTitle(ultimateBoard.currentPlayer, gameOver, winner);
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


void Renderer::drawX(SDL_Renderer *renderer, Board &board, Tile &tile) {
    //Calculate all the coordinates needed
    const float topLeftY = tile.row*tile_height + 0.25*tile_height + board.row*20 + 3*board.row*tile_height;
    const float topLeftX = tile.col*tile_width + 0.25*tile_width + board.col*20 + 3*board.col*tile_width;
    const float bottomRightY = tile.row*tile_height + 0.75*tile_height + board.row*20 + 3*board.row*tile_height;
    const float bottomRightX = tile.col*tile_width + 0.75*tile_width + board.col*20 + 3*board.col*tile_width;
    const float bottomLeftY = tile.row*tile_height + 0.25*tile_height + board.row*20 + 3*board.row*tile_height;
    const float bottomLeftX = tile.col*tile_width + 0.75*tile_width + board.col*20 + 3*board.col*tile_width;
    const float topRightY = tile.row*tile_height + 0.75*tile_height + board.row*20 + 3*board.row*tile_height;
    const float topRightX = tile.col*tile_width + 0.25*tile_width + board.col*20 + 3*board.col*tile_width;
    
    //Draw left-top to right-bottom diagonal
    thickLineRGBA(renderer, topLeftX,topLeftY,bottomRightX,bottomRightY, 10, x_color.r, x_color.g, x_color.b ,255);
    //Draw left-bottom to right-top diagonal
    thickLineRGBA(renderer, bottomLeftX,bottomLeftY,topRightX,topRightY, 10, x_color.r, x_color.g, x_color.b ,255);
}


void Renderer::drawO(SDL_Renderer *renderer, Board &board, Tile &tile, Move lastMove) {
    //Calculate all the coordinates needed
    const float radius = 0.25*tile_width;
    const float centerY = 0.5*tile_height + tile.row*tile_height + board.row*20 + 3*board.row*tile_height;
    const float centerX = 0.5*tile_width + tile.col*tile_width + board.col*20 + 3*board.col*tile_width;

    //Highlight last CPU play
    if (lastMove == Move(board.row, board.col, tile.row, tile.col)) {
        filledCircleRGBA(renderer, centerX,centerY, radius+12, 255,215,0, 255);
        filledCircleRGBA(renderer, centerX,centerY, radius+10, o_color.r, o_color.g, o_color.b, 255);
    }
    
    //Draw colorful outter circle
    filledCircleRGBA(renderer, centerX,centerY, radius+5, o_color.r, o_color.g, o_color.b, 255);
    
    //Draw inner circle to make appearance of O (depends on what the tile background is at this state in game)
    if (board.isActive) { 
        filledCircleRGBA(renderer, centerX,centerY, radius-5, tile_color.r, tile_color.g, tile_color.b, 255);
    }
    else if (board.winner == State::Player1) {
        filledCircleRGBA(renderer, centerX,centerY, radius-5, xWin_color.r, xWin_color.g, xWin_color.b, 255);
    }
    else if (board.winner == State::Player2) {
        filledCircleRGBA(renderer, centerX,centerY, radius-5, oWin_color.r, oWin_color.g, oWin_color.b, 255);
    }
    else { filledCircleRGBA(renderer, centerX,centerY, radius-5, inValid_color.r, inValid_color.g, inValid_color.b, 255); }
}

void Renderer::drawBoardWinners(SDL_Renderer *renderer, const UltimateBoard &ultimateBoard) {
    // For each board if winner is not emptry or draw then draw the winner
    for (Board board : ultimateBoard.boards) {
        if (board.winner == State::Player1 || board.winner == State::Player2) {
            float start_centerX = 3*board.col*tile_width + board.col*20 + board.winTile_start->col*tile_width + 0.5*tile_width;
            float start_centerY = 3*board.row*tile_height + board.row*20 + board.winTile_start->row*tile_height + 0.5*tile_height;
            float end_centerX = 3*board.col*tile_width + board.col*20 + board.winTile_end->col*tile_width + 0.5*tile_width;
            float end_centerY = 3*board.row*tile_height + board.row*20 + board.winTile_end->row*tile_height + 0.5*tile_height;
            
            if (board.winner == State::Player1) {
                thickLineRGBA(renderer, start_centerX,start_centerY,end_centerX,end_centerY, 10, x_color.r, x_color.g, x_color.b ,255);
            }
            else {
                thickLineRGBA(renderer, start_centerX,start_centerY,end_centerX,end_centerY, 10, o_color.r, o_color.g, o_color.b ,255); 
            }
        }   
    }
}