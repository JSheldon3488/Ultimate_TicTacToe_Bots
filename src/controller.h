#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>
#include "gameObjects.h"


/* Controller class is used for getting, processing, and returning correct user input */
class Controller {
public:
    Controller(const size_t tile_width, const size_t tile_height);
    Move HandleInput(UltimateBoard &ultimateBoard);
    bool hasMoved;

private:
    const size_t tile_width;
    const size_t tile_height;
    bool isValidMove(UltimateBoard &ultimateBoard, Move &move);
};

#endif