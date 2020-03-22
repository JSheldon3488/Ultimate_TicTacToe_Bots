#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "gameObjects.h"
#include <map>


class Controller {
public:
    Controller(const size_t tile_width, const size_t tile_height);
    std::map<std::string, int> HandleInput(UltimateBoard &ultimateBoard);
    bool hasMoved;

private:
    const size_t tile_width;
    const size_t tile_height;
    bool isValidMove(UltimateBoard &ultimateBoard, const int board, const int row, const int col);
};

#endif