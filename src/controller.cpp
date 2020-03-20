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
{}

std::map<std::string, int> Controller::HandleInput() {
    std::map<std::string, int> click_result;
    // Cannot have initialized to 0's that is a real board position
    click_result["board"] = -2;
    click_result["row"] = -2;
    click_result["col"] = -2;
    
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            click_result["board"] = -1;
            click_result["row"] = -1;
            click_result["col"] = -1;
            break;
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
            int game_col = adjusted_x/(3*tile_width);
            int game_row = adjusted_y/(3*tile_height);
            click_result["board"] = (3*game_row + game_col);
            // Solve for row and col
            click_result["row"] = (adjusted_y - 3*tile_height*game_row)/tile_height;
            click_result["col"] = (adjusted_x - 3*tile_width*game_col)/tile_width;      
        }
    }
    return click_result;
}