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

Move Controller::HandleInput(UltimateBoard &ultimateBoard) {
    SDL_Event e;
    Move move;

    // Loop until you receive a valid move
    while (!hasMoved) {
        SDL_PollEvent(&e);
        // Handle Clickling "X" in top right
        if (e.type == SDL_QUIT) {
            move.ultimate_row = -1;
            move.ultimate_col = -1;
            move.board_row = -1;
            move.board_col = -1;
            hasMoved = true;
            return move;
        }

        // Handle Clicking anywhere in the game
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            // Factor in additional spacing for x and y due to the gaps between boards
            int adjusted_x = e.button.x;
            int adjusted_y = e.button.y;
            // Adjust x coordinate
            if (e.button.x > tile_width*6+40) { adjusted_x -= 40; }
            else if (e.button.x > tile_width*3+20) { adjusted_x -= 20; }
            // Adjust y coordinate
            if (e.button.y > tile_height*6+40) { adjusted_y -= 40; }
            else if (e.button.y > tile_height*3+20) { adjusted_y -= 20; }

            // Convert coordinates to set up move.
            // Solve for board #
            move.ultimate_col = adjusted_x/(3*tile_width);
            move.ultimate_row = adjusted_y/(3*tile_height);
            // Solve for row and col
            move.board_row = (adjusted_y - 3*tile_height*move.ultimate_row)/tile_height;
            move.board_col = (adjusted_x - 3*tile_width*move.ultimate_col)/tile_width;
            
            // Check if a validMove
            if (isValidMove(ultimateBoard, move)) {
                hasMoved = true;
                return move;
            }
        }
    }
}

bool Controller::isValidMove(UltimateBoard &ultimateBoard, Move &move) {
    if (ultimateBoard.boards[move.ultimate_row*3 + move.ultimate_col].isActive) {
        if (!ultimateBoard.boards[move.ultimate_row*3 + move.ultimate_col].tiles[(move.board_row*3 + move.board_col)].isOccupied) {
            return true;
        }
    }
    return false;
}