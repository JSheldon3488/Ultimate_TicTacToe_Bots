#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include "gameObjects.h"


class Controller {
public:
    Controller(const size_t tile_width, const size_t tile_height);
    void HandleInput(UltimateBoard &boards);
    bool hasMoved;

private:
    const size_t tile_width;
    const size_t tile_height;
    bool isValidMove(UltimateBoard &boards, const int board, const int row, const int col);
};

#endif