#include "controller.h"
#include <iostream>

/* Borad and UltimateBoard Vector Index Layout
    -------------
    | 0 | 1 | 2 |
    | 3 | 4 | 5 |
    | 6 | 7 | 8 |
    -------------
*/

Controller::Controller(const size_t tile_width, const size_t tile_height) : tile_width(tile_width), tile_height(tile_height)
{
    hasMoved = false;
}

void Controller::HandleInput(UltimateBoard &boards) {
    SDL_Event e;
    int game_col;
    int game_row;
    int game_board;
    int board_row;
    int board_col;

    while (!hasMoved) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            boards.gameOver = true;
            hasMoved = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            //Factor in additional spacing for x and y due to gaps between games
            int adjusted_x = e.button.x;
            int adjusted_y = e.button.y;
            // Adjust x coordinate
            if (e.button.x > tile_width*6+40) {
                adjusted_x -= 40;
            }
            else if (e.button.x > tile_width*3+20) {
                adjusted_x -= 20;
            }
            // Adjust y coordinate
            if (e.button.y > tile_height*6+40) {
                adjusted_y -= 40;
            }
            else if (e.button.y > tile_height*3+20) {
                adjusted_y -= 20;
            }

            //Convert coordinates to a game #, row in that game, and column in that game.
            // Solve for game #
            game_col = adjusted_x/(3*tile_width);
            game_row = adjusted_y/(3*tile_height);
            game_board = (3*game_row + game_col);
            // Solve for row and col
            board_row = (adjusted_y - 3*tile_height*game_row)/tile_height;
            board_col = (adjusted_x - 3*tile_width*game_col)/tile_width;
            
            //Check if a validMove
            if (isValidMove(boards, game_board, board_row, board_col)) {
                //Update boards
                boards.boards[game_board].grid[(board_row*3 + board_col)].setState(boards.currentPlayer);
                // Change Players 
                boards.currentPlayer = boards.currentPlayer == State::Player1 ? State::Player2 : State::Player1;
                hasMoved = true;
            }
        }
    }
}

bool Controller::isValidMove(UltimateBoard &boards, const int board, const int row, const int col) {
    if (boards.boards[board].isActive) {
        if (!boards.boards[board].grid[(3*row + col)].isOccupied) {
            return true;
        }
    }
    return false;
}