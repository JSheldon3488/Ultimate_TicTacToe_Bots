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
            //Convert coordinates to a game #, row in that game, and column in that game.
            // Solve for game #
            int game_col = e.button.x/(3*tile_width);
            int game_row = e.button.y/(3*tile_height);
            click_result["x"] = e.button.x;
            click_result["y"] = e.button.y;
            click_result["board"] = (3*game_row + game_col);
            // Solve for row
            click_result["row"] = (e.button.y - 3*tile_height*game_row)/tile_height;
            click_result["col"] = (e.button.x - 3*tile_width*game_col)/tile_width;
            // Solve for col
        }
    }
    return click_result;
}