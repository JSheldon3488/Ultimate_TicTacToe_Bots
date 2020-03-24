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

std::map<std::string, int> Controller::HandleInput(UltimateBoard &ultimateBoard) {
    SDL_Event e;
    std::map<std::string, int> click;

    // Loop until you receive a valid move
    while (!hasMoved) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            click["board"] = -1;
            click["row"] = -1;
            click["col"] = -1;
            hasMoved = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            //Factor in additional spacing for x and y due to the gaps between boards
            int adjusted_x = e.button.x;
            int adjusted_y = e.button.y;
            // Adjust x coordinate
            if (e.button.x > tile_width*6+40) { adjusted_x -= 40; }
            else if (e.button.x > tile_width*3+20) { adjusted_x -= 20; }
            // Adjust y coordinate
            if (e.button.y > tile_height*6+40) { adjusted_y -= 40; }
            else if (e.button.y > tile_height*3+20) { adjusted_y -= 20; }

            //Convert coordinates to a board #, row in that board, and column in that board.
            // Solve for board #
            int ultimate_col = adjusted_x/(3*tile_width);
            int ultimate_row = adjusted_y/(3*tile_height);
            int ultimate_board = (3*ultimate_row + ultimate_col);
            // Solve for row and col
            int board_row = (adjusted_y - 3*tile_height*ultimate_row)/tile_height;
            int board_col = (adjusted_x - 3*tile_width*ultimate_col)/tile_width;
            
            //Check if a validMove
            if (isValidMove(ultimateBoard, ultimate_board, board_row, board_col)) {
                hasMoved = true;
                // Return where the move happened
                    click["board"] = ultimate_board;
                    click["row"] = board_row;
                    click["col"] = board_col;
                    return click;
            }
        }
    }
    return click;
}

bool Controller::isValidMove(UltimateBoard &ultimateBoard, const int board, const int row, const int col) {
    if (ultimateBoard.boards[board].isActive) {
        if (!ultimateBoard.boards[board].grid[(3*row + col)].isOccupied) {
            return true;
        }
    }
    return false;
}